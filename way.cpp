//*******************
// auteur : yann c.
// date : 11/10/12
// file : creastar / way.cpp
// description : définition d'un chemin constituer de cases
//*******************





#include "stdafx.h"




Cway::Cway() : m_vWayWithCases()
{


}

Cway::Cway(const Cway& _copie) 
{

	for(int i = 0; i < _copie.m_vWayWithCases.size() ; ++i)
	{
		m_vWayWithCases.push_back( _copie.m_vWayWithCases[i] );
	}


}

Cway::~Cway()
{

	for(int i =0; i < m_vWayWithCases.size(); ++i)
	{
		m_vWayWithCases.pop_back();
	}

}


void Cway::addCase(Ccases* _caseToAdd)
{	
	if(_caseToAdd != NULL)
	{
		m_vWayWithCases.push_back(_caseToAdd);
	}
}

void Cway::ActiveWinnerWay()
{
	for(int i =0; i < m_vWayWithCases.size(); ++i)
	{
		if(m_vWayWithCases[i]->getType() != (BEGIN ) && 
			m_vWayWithCases[i]->getType() != (END )    )
		{
			m_vWayWithCases[i]->setType(PATH);
		}
	}	
}

void Cway::ActiveCalculateWay()
{
	for(int i =0; i < m_vWayWithCases.size(); ++i)
	{
		if(m_vWayWithCases[i]->getType() != (BEGIN ) && 
			m_vWayWithCases[i]->getType() != (END )    )
		{
			m_vWayWithCases[i]->setType(CALCULATE);
		}
	}
}


float Cway::getWayWeight()
{
	float result =0.0f;

	for(int i =0; i < m_vWayWithCases.size(); ++i)
	{
		result +=	m_vWayWithCases[i]->getPoids();
	}	

	result += m_vWayWithCases[m_vWayWithCases.size() -1]->getWightToEnd();

	return result;
}

Ccases* Cway::getLastCaseOfThisWay()
{

	int LastCase = m_vWayWithCases.size() -1;

	return m_vWayWithCases[LastCase];
	
}


bool Cway::isLooping()
{
	for(int i =0 ; i < m_vWayWithCases.size()-1 ; ++i)
	{
		if( m_vWayWithCases[i]->getPositionCase() ==
			m_vWayWithCases[m_vWayWithCases.size() -1]->getPositionCase() )
		{	
			return true;
		}
	}

	return false;

}


void Cway::ShowWayPoids()
{
	this->getLastCaseOfThisWay()->setTextPoids( getWayWeight() );

}

void Cway::ReinitWayPoids()
{
	for(int i =0; i < m_vWayWithCases.size(); ++i)
	{	
		m_vWayWithCases[i]->reinitTextPoid();
	}	
}

unsigned int Cway::getConsoCases()
{
	unsigned int conso =0;

	for(int i =0; i < m_vWayWithCases.size(); ++i)
	{	
		conso = m_vWayWithCases[i]->getConso();
	}

	return conso;
}

