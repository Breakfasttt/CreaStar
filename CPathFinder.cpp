//*******************
// auteur : yann c.
// date : 11/10/12
// file : creastar / way.hpp
// description : définition du PathFinder
//*******************


#include "stdafx.h"


CPathFinder::CPathFinder() :  m_VecWay()
{
	m_WinningWay = NULL;
	m_bPathFound = false;
	m_idBegin =0;
	m_map = NULL;
}

CPathFinder::CPathFinder(Ccases* _begin ,creap::Vector2f _sizeCase, Cmap* _map ) : m_VecWay()
{

	m_bLaunch = false;
	m_bPathFound = false;
	m_map = _map;
	m_Conso = 0;

	m_vSizeCases = _sizeCase;

	if(_begin != NULL)
	{
		Cway* tempWay = new Cway();
		tempWay->addCase(_begin);
		m_VecWay.push_back(tempWay);
	}

}

CPathFinder::~CPathFinder()
{

	delete m_WinningWay;

	for(int i =0; i < m_VecWay.size() ; ++i)
	{
		delete m_VecWay[i] ;
	}

	m_VecWay.clear();

	m_map = NULL;

}


void CPathFinder::CalculateAstar()
{
	if( creamMouse_LeftClick() == 1  && m_bPathFound == false)
	{
		ModeStepByStep();	
	}
	else if(creamMouse_RightClick() == 1 && !m_bPathFound)
	{
		m_bLaunch = true;

		Modeinstant();	
	}
}

void CPathFinder::DeleteAlreadyKnowWay()
{
	for(int i =0; i < m_VecWay.size()-1 ; ++i)
	{
		if(m_VecWay[i] != NULL )
		{
			for(int j = (i+1); j < m_VecWay.size() ; ++j)
			{

				if(m_VecWay[j] != NULL)
				{

					if( m_VecWay[i]->getLastCaseOfThisWay()->getPositionCase() ==
						m_VecWay[j]->getLastCaseOfThisWay()->getPositionCase() )
					{
						if( m_VecWay[i]->getWayWeight() <= 
							m_VecWay[j]->getWayWeight() )
						{
							delete m_VecWay[j];
							m_VecWay[j] = NULL;
						}	
					}
				}
			}	
		}
	}
}


void CPathFinder::SortByWeight()
{
	for(int i =0; i < m_VecWay.size() ; ++i)
	{
		for(int j = i ; j < m_VecWay.size() ; ++j)
		{
			if(m_VecWay[i] == NULL && m_VecWay[j] != NULL)
			{
				m_VecWay[i] = m_VecWay[j];
				m_VecWay[j] = NULL;
			}
			else if( (m_VecWay[i] != NULL && m_VecWay[j] == NULL ) || 
				(m_VecWay[i] == NULL && m_VecWay[j] == NULL )	  ) 
			{			
			}
			else if( m_VecWay[i]->getWayWeight() > m_VecWay[j]->getWayWeight() )
			{
				Cway* tempWay = m_VecWay[j];
				m_VecWay[j] = m_VecWay[i];
				m_VecWay[i] = tempWay;		
			}	
		}
	}
}


int CPathFinder::DeleteNullWays()
{


	while(m_VecWay[m_VecWay.size()-1] == NULL)
	{
		m_VecWay.pop_back();

		if(m_VecWay.size() ==0)
			return -1;
	}

	return 0;
}

void CPathFinder::DeleteLoopWay()
{
	for(int i =0; i < m_VecWay.size() ; ++i)
	{
		if(m_VecWay[i] != NULL)
		{
			if(m_VecWay[i]->isLooping())
			{
				delete m_VecWay[i];
				m_VecWay[i] = NULL;
			}
		}
	}

}


void CPathFinder::ReinitPathFinder(Ccases* _BeginCase)
{

	for(int i =0; i < m_VecWay.size() ; ++i)
	{
		delete m_VecWay[i];
	}

	m_VecWay.clear();

	if( _BeginCase !=NULL)
	{
		Cway* tempWay = new Cway();
		tempWay->addCase(_BeginCase);
		m_VecWay.push_back(tempWay);
	}


	m_bPathFound = false;
	m_bLaunch = false;

}

void CPathFinder::ModeStepByStep()
{
	if(m_VecWay.size() != 0)
	{
		//extraction du premier chemin
		Cway* ExtrateWay = m_VecWay[0] ;

		// (extend des way)

		Ccases* LastCaseOfExtratedWay = ExtrateWay->getLastCaseOfThisWay();

		for(int i =0; i < 4 ;++i)
		{

			if(LastCaseOfExtratedWay->getCase((DirLink)i) != NULL )
			{

				if(LastCaseOfExtratedWay->getCase((DirLink)i)->getType() != BLOCK && 
					LastCaseOfExtratedWay->getCase((DirLink)i)->getType() != PATH &&
					LastCaseOfExtratedWay->getCase((DirLink)i)->getType() != CALCULATE )
				{
					Cway* NewExtendWay = new Cway(*ExtrateWay);
					NewExtendWay->addCase(LastCaseOfExtratedWay->getCase((DirLink)i) );
					m_VecWay.push_back(NewExtendWay);
				}
			}	
		}

		m_VecWay[0]->ReinitWayPoids();
		delete m_VecWay[0];
		m_VecWay[0] = NULL;

		// on supprime les chemin qui boucle
		DeleteLoopWay();
		//on supprime les chemin déja connu et trop long
		DeleteAlreadyKnowWay();
		//on range les chemins par taille (les chemins supprimer = NULL sont mis en derniers
		SortByWeight();
		//on supprime les chemins NULL du vecteur
		DeleteNullWays();

		// si le vecteur n'esty pas nul, une solution a eté trouver, on la met dans la winning Way;

		m_map->ReinitCaseForPath();

		if( m_VecWay.size() != 0 )
		{
			m_WinningWay = m_VecWay[0];

			for(int i =0; i < m_VecWay.size() ; ++i)
			{
				m_VecWay[i]->ActiveCalculateWay();
				m_VecWay[i]->ShowWayPoids();
			}

			m_WinningWay->ActiveWinnerWay();

			if(m_WinningWay->getLastCaseOfThisWay()->getType() == END)
			{
				m_bPathFound = true;
				//std::cout << "Chemin Trouver !!!" << std::endl;
			}
		}
		else 
		{
			std::cout << "Pas de chemins trouver" << std::endl;
		}
	}

	//std::cout << "Etape Fini ! Position LastCase : " << m_WinningWay->getLastCaseOfThisWay()->getPositionCase() << std::endl;

}

void CPathFinder::Modeinstant()
{
	timeToFind = creamWindow_GetApplicationTime();

	m_Conso = 0;

	do
	{
		//extraction du premier chemin
		Cway* ExtrateWay = m_VecWay[0] ;

		// (extend des way)

		Ccases* LastCaseOfExtratedWay = ExtrateWay->getLastCaseOfThisWay();

		for(int i =0; i < 4 ;++i)
		{

			if(LastCaseOfExtratedWay->getCase((DirLink)i) != NULL )
			{

				if(LastCaseOfExtratedWay->getCase((DirLink)i)->getType() != BLOCK && 
					LastCaseOfExtratedWay->getCase((DirLink)i)->getType() != PATH &&
					LastCaseOfExtratedWay->getCase((DirLink)i)->getType() != CALCULATE )
				{
					Cway* NewExtendWay = new Cway(*ExtrateWay);
					NewExtendWay->addCase(LastCaseOfExtratedWay->getCase((DirLink)i) );
					m_VecWay.push_back(NewExtendWay);
				}
			}	
		}


		delete m_VecWay[0];
		m_VecWay[0] = NULL;

		// on supprime les chemin qui boucle
		DeleteLoopWay();
		//on supprime les chemin déja connu et trop long
		DeleteAlreadyKnowWay();
		//on range les chemins par taille (les chemins supprimer = NULL sont mis en derniers
		SortByWeight();
		//on supprime les chemins NULL du vecteur
		DeleteNullWays();

		unsigned int TempNbreCase =0;

		if(m_VecWay.size() != 0)
		{
			for(int i =0; i < m_VecWay.size() ; ++i)
			{
				m_VecWay[i]->ActiveCalculateWay();
				m_VecWay[i]->ShowWayPoids();

				TempNbreCase += m_VecWay[i]->getConsoCases();
			}

			m_WinningWay = m_VecWay[0];
			m_bPathFound = true;

		}
		else
		{
			m_WinningWay = NULL;
		}

		if( TempNbreCase > m_Conso)
		{
			m_Conso = TempNbreCase;
		}


	}while( m_VecWay.size() != 0 && m_WinningWay->getLastCaseOfThisWay()->getType() != END);

	timeToFind = creamWindow_GetApplicationTime() - timeToFind;
	timeToFind *= 1000.0f;


	if(m_WinningWay)
	{
		m_WinningWay->ActiveWinnerWay();
		//std::cout << "Chemin trouver ! en : " << timeToFind << " ms" << std::endl;
		m_bLaunch = false;
	}
	else
	{
		timeToFind = -1;
		std::cout << "Pas de chemin trouver" << std::endl;
		m_bLaunch = false;
	}

}

float CPathFinder::getTimeToFind()
{

	if(m_bPathFound)
	{
		return  timeToFind;
	}

	return -1;

}
