//*******************
// auteur : yann c.
// date : 11/10/12
// file : creastar / Cmap.hpp
// description : définition de map
//*******************


#include "stdafx.h"



Cmap::Cmap() : m_vecCases()
{

	m_iLargeur = 0;
	m_iHauteur = 0;

	m_vCoordBegin = creap::Vector2f(0.0f,0.0f);
	m_vCoordEnd = creap::Vector2f(0.0f,0.0f);
	m_vSizeCases = creap::Vector2f(0.0f,0.0f);

	m_szMapName = "";

	m_CasePlaced = NOTHING_PLACED;
	m_modeMap = MODE_DISPLAYONLY;


	m_HUD = new Chud();

}

Cmap::Cmap(std::string _path)
{
	m_iLargeur = 0;
	m_iHauteur = 0;

	m_vCoordBegin = creap::Vector2f(0.0f,0.0f);
	m_vCoordEnd = creap::Vector2f(0.0f,0.0f);
	m_vSizeCases = creap::Vector2f(0.0f,0.0f);

	m_szMapName = _path;

	m_HUD = new Chud();

}

Cmap::~Cmap()
{

	for(int i = 0 ; i < m_vecCases.size() ; ++i)
	{
		delete m_vecCases[i];
	}

	m_vecCases.clear();
}


bool Cmap::LoadMap()
{

	std::ifstream fileMap;
	fileMap.open(m_szMapName);


	if(fileMap.is_open())
	{

		std::string bufferLine;

		fileMap >> m_iLargeur >> m_iHauteur ;
		fileMap >> m_vCoordBegin.x() >> m_vCoordBegin.y() ;
		fileMap >> m_vCoordEnd.x() >> m_vCoordEnd.y() ;


		m_vSizeCases.x() = 800.0f / (float)m_iLargeur ;
		m_vSizeCases.y() = 600.0f / (float)m_iHauteur ;


		char tempCharLu = ' ';
		creap::Vector2f tempPosition(0.0f,0.0f);
		bool blectureEnCours = false;

		int iCptCase = 0;

		while( !fileMap.eof())
		{

			fileMap.get(tempCharLu);
		
			//std::cout << tempCharLu;
			int tempIntLu ;

			//tempIntLu = atoi(&tempCharLu);

			tempIntLu = (int)(tempCharLu - '0');

			if( (int)tempIntLu >=0 && tempIntLu<=9 && tempCharLu != '\t' && tempCharLu != '\n' && tempCharLu != ' '  )
			{
				

				blectureEnCours = true;
				m_vecCases.push_back( new Ccases(m_vSizeCases,tempPosition,tempIntLu ) ) ;
				iCptCase++;

				tempPosition.x() += m_vSizeCases.x();

				if(iCptCase   == m_iLargeur)
				{
					iCptCase = 0;
					tempPosition.x() = 0.0f;
					tempPosition.y() += m_vSizeCases.y();		
				}
			}
		}		
		fileMap.close();

		m_CasePlaced = NOTHING_PLACED;

		Ccases* CaseBeginAndEnd = getCaseInVectorWithCoord( m_vCoordBegin.x() , m_vCoordBegin.y() );

		if(CaseBeginAndEnd!=NULL)
		{
			CaseBeginAndEnd->MakeThisBeginCase();
			m_CasePlaced = BEGIN_PLACED;
		}

		CaseBeginAndEnd = getCaseInVectorWithCoord( m_vCoordEnd.x() , m_vCoordEnd.y() );

		if(CaseBeginAndEnd!=NULL)
		{
			CaseBeginAndEnd->MakeThisEndCase();

			if(m_CasePlaced == BEGIN_PLACED)
			{
				m_CasePlaced = ALL_PLACED;
			}
			else
			{
				m_CasePlaced = END_PLACED;
			}			
		}



		MakeLinksBetweenCase();

		CaseBeginAndEnd = NULL;

		m_modeMap = MODE_DISPLAYONLY;


		m_pathFinder = new CPathFinder(NULL,m_vSizeCases,this);

		return true;

	}
	else
	{
		return false;
		std::cout << "Fail load file " << std:: endl;
	}	
}

void Cmap::SauveMap()
{
}

void Cmap::UpdateMap()
{

	ChangeModeMap();

	switch(m_modeMap)
	{
	case MODE_EDIT :  	BlockCase();
		PlaceBeginAndEndCase();
		break;

	case MODE_DISPLAYONLY :  
		break;

	case MODE_PATHFINDING :  m_pathFinder->CalculateAstar();


		break;

	default :  break;
	}

	m_HUD->HUDsetMode((int)m_modeMap);
	m_HUD->HUDsetInfosText((int)m_modeMap);

	float Time =   m_pathFinder->getTimeToFind();
	unsigned int Conso = m_pathFinder->getConso();

	m_HUD->HUDsetConsoTextText(Conso);

	if(Time>=0.0f)
	{
		m_HUD->HUDsetTimeToFindText(Time);
	}
	else
	{
		m_HUD->HUDsetTimeToFindText(0);
	}

	for(int i = 0 ; i < m_vecCases.size() ; ++i)
	{
		m_vecCases[i]->updateCases();
	}


	Ccases* TempCase = getCaseInVectorWithMouse();

	if(TempCase != NULL)
	{
		m_HUD->setAfficheCase(true);
		m_HUD->HUDsetTypeCaseText( (int)TempCase->getType() );
		m_HUD->HUDsetPositionCaseText( TempCase->getPositionCase() ) ;
		m_HUD->HUDsetPoidsCaseText( TempCase->getPoids()  );

		if(m_pathFinder->IsLaunch())
		{
			m_HUD->HUDsetTimeToFindText(-1.0f);
		}

		TempCase = NULL;
	}
	else
	{
		m_HUD->setAfficheCase(false);
	}

}

void Cmap::DisplayMap()
{

	if( m_pathFinder->IsFound() )
	{

		for(int i = 0 ; i < m_vecCases.size() ; ++i)
		{
			m_vecCases[i]->displayCases();
		}
	}

	if(m_HUD);
		m_HUD->DisplayHUD();

}


Ccases* Cmap::getCaseInVectorWithMouse()
{

	creap::Vector2f MousePosition = creamMouse_GetPosition();
	creap::Vector2f TempPosition;

	for(int i =0; i < m_vecCases.size() ;++i)
	{

		TempPosition = m_vecCases[i]->getPositionCase();

		if( TempPosition.x() <= MousePosition.x() && TempPosition.y() <= MousePosition.y() 
			&&  ( TempPosition.x() + m_vSizeCases.x() ) >= MousePosition.x() 
			&&	( TempPosition.y() + m_vSizeCases.y() ) >= MousePosition.y()                )
		{

			//std::cout << " case position : " << TempPosition << std::endl;
			return  m_vecCases[i];
		}
	}


	return NULL;
}

Ccases* Cmap::getCaseInVectorWithCoord(float _x , float _y)
{
	creap::Vector2f CasePosition =  creap::Vector2f(0.0f,0.0f) ;

	CasePosition.x() = _x * m_vSizeCases.x()  ;
	CasePosition.y() = _y * m_vSizeCases.y() ;

	creap::Vector2f TempPosition;

	for(int i =0; i < m_vecCases.size() ;++i)
	{

		TempPosition = m_vecCases[i]->getPositionCase() + m_vSizeCases/2.0f;

		if( TempPosition.x() >=  CasePosition.x() &&
			TempPosition.y() >=  CasePosition.y() &&
		    TempPosition.x()  <  ( CasePosition.x()+ m_vSizeCases.x() ) &&
			TempPosition.y()  <  ( CasePosition.y()+ m_vSizeCases.y() ) )
		{

			//std::cout << " case position : " << TempPosition << std::endl;
			return  m_vecCases[i];
		}
	}


	return NULL;

}


void Cmap::BlockCase()
{
	if(creamMouse_LeftClick() == 1)
	{
		Ccases* CaseToBlock = NULL;

		CaseToBlock = getCaseInVectorWithMouse();

		if(CaseToBlock !=NULL)
		{
			CaseToBlock->BlockOrDeblockThisCase();
		}
		else
		{
			std::cout << "Erreur lors du choix de la case " << std:: endl;
		}
	}
}


void Cmap::PlaceBeginAndEndCase()
{
	if( creamMouse_RightClick() == 1 )
	{

		Ccases* ChoosenCase = getCaseInVectorWithMouse();

		if(ChoosenCase!=NULL)
		{

			if( ChoosenCase->getType() != BLOCK )
			{
				switch(m_CasePlaced)
				{

				case NOTHING_PLACED : ChoosenCase->setType(BEGIN);
					m_CasePlaced = BEGIN_PLACED ;
					m_vCoordBegin = ChoosenCase->getPositionCase();
					break;

				case BEGIN_PLACED :  if( ChoosenCase->getType() != BEGIN)
									 {
										 ChoosenCase->setType(END);
										 m_CasePlaced = ALL_PLACED;
										 m_vCoordEnd = ChoosenCase->getPositionCase();
									 }
									 break;

				case END_PLACED :	if( ChoosenCase->getType() != END)
									{
										ChoosenCase->setType(BEGIN);
										m_CasePlaced = ALL_PLACED;
										m_vCoordBegin = ChoosenCase->getPositionCase();
									}
									break;

				case ALL_PLACED : if( ChoosenCase->getType() != END &&
									  ChoosenCase->getType() != BEGIN )
								  {

									  ReinitBeginAndEnd() ;
									  ChoosenCase->setType(BEGIN);
									  m_CasePlaced = BEGIN_PLACED ;
								  }
								  break;

				default  : break;
				}	
			}
		}
	}
}


void Cmap::ReinitBeginAndEnd()
{
	for(int i =0; i < m_vecCases.size() ;++i)
	{

		if( m_vecCases[i]->getType() == BEGIN ||
			m_vecCases[i]->getType() == END   )
		{
			m_vecCases[i]->setType(OPEN);
		}
	}	
}

void Cmap::ChangeModeMap()
{
	if(creamKeyboard_GetKeyState(creamKeyboard_KeyCode::Space) == 1 || m_modeMap == MODE_DISPLAYONLY )
	{
		switch(m_modeMap)
		{
		case MODE_EDIT :  m_modeMap = MODE_DISPLAYONLY;
			//std::cout << "display mode " << std::endl ;
			break;

		case MODE_DISPLAYONLY :  m_modeMap = MODE_PATHFINDING;
							if( CalculateWeight())
							{
								m_pathFinder->ReinitPathFinder (getBeginCase() );
							}
							else
							{
								m_modeMap = MODE_EDIT;
							}
			
			//std::cout << "path mode " << std::endl ;
			break;

		case MODE_PATHFINDING : m_modeMap = MODE_EDIT;
			ReinitCaseForPath();
			//std::cout << "edit mode " << std::endl ;
			break;

		default : m_modeMap = MODE_DISPLAYONLY; break;
		}
	}
}

bool Cmap::CalculateWeight()
{

	if(getEndCase() != NULL)
	{
		creap::Vector2f _End = getEndCase()->getPositionCase();

		for(int i =0; i < m_vecCases.size() ;++i)
		{
			m_vecCases[i]->CalculateLengthToPosition(_End);	
		}
		return true;
	}

	return false;
}


void Cmap::MakeLinksBetweenCase()
{

	for(int i = 0 ; i < m_vecCases.size() ; ++i)
	{
		if( i - m_iLargeur < 0)
		{
			m_vecCases[i]->setLink(NULL,TOP);
		}
		else
		{
			m_vecCases[i]->setLink(m_vecCases[i - m_iLargeur],TOP);
		}

		if( i + m_iLargeur >= m_vecCases.size() )
		{
			m_vecCases[i]->setLink(NULL,BOT);
		}
		else
		{
			m_vecCases[i]->setLink(m_vecCases[i + m_iLargeur],BOT);
		}


		int modulo = i %  m_iLargeur;

		if( modulo == 0)
		{
			m_vecCases[i]->setLink( NULL , LEFT);
		}
		else
		{
			m_vecCases[i]->setLink( m_vecCases[i -1] , LEFT);
		}


		modulo = (i+1) % m_iLargeur;

		if(modulo == 0 || (i+1) >= m_vecCases.size() )
		{
			m_vecCases[i]->setLink( NULL , RIGHT);
		}
		else
		{
			m_vecCases[i]->setLink( m_vecCases[i +1] , RIGHT);
		}

	}

}


Ccases* Cmap::getBeginCase()
{
	for(int i =0; i < m_vecCases.size(); ++i)
	{
		if(m_vecCases[i]->getType() == BEGIN)
		{
			return m_vecCases[i];
		}
	}

	return NULL;
}


Ccases* Cmap::getEndCase()
{
	for(int i =0; i < m_vecCases.size(); ++i)
	{
		if(m_vecCases[i]->getType() == END)
		{
			return m_vecCases[i];
		}
	}

	return NULL;
}


void Cmap::ReinitCaseForPath()
{
	for(int i =0; i < m_vecCases.size(); ++i)
	{
		if(m_vecCases[i]->getType() == CALCULATE || 
			m_vecCases[i]->getType() == PATH )
		{
			m_vecCases[i]->setType(OPEN);
			m_vecCases[i]->reinitTextPoid();
		}
		else if( m_vecCases[i]->getType() == END || 
			m_vecCases[i]->getType() == BEGIN )
		{
			m_vecCases[i]->reinitTextPoid();
		}
	}

}

