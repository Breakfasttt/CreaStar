//*******************
// auteur : yann c.
// date : 11/10/12
// file : creastar / Ccases.hpp
// description : définition d'une case de map
//*******************


#include "stdafx.h"



Ccases::Ccases()
{

	m_iPoids = 1;
	m_fLengthToEnd = 0.0f;

	m_vPosition = creapVector2f(0.0f,0.0f);
	m_vSize = creapVector2f(0.0f,0.0f);

	m_Rectangle = NULL;

	m_type = OPEN;

	for (int i =0; i < 4 ;++i)
	{
		m_CaseLink[i] = NULL;
	}

	m_textPoids.init();
	m_textWay.init();
}

Ccases::Ccases(creapVector2f _size, creapVector2f _Pos , int _poids )
{

	m_iPoids = _poids;

	m_vPosition = _Pos;
	m_vSize = _size;

	
	m_Rectangle = creamShape_CreateRectangle(creapVector2f(0.0f,0.0f),m_vSize);

	m_Rectangle->init();


	cream::Color FillColor = cream::Color::WHITE;
	FillColor.a = 0;

	m_Rectangle->setColor(FillColor);
	m_Rectangle->setOutlineColor(cream::Color::Red);

	m_Rectangle->setInitPosition(m_vPosition);
	m_Rectangle->setPosition(m_vPosition);


	m_Rectangle->setVisible(true);
	m_Rectangle->setActive(true);


	if(m_iPoids !=0)
	{
		m_type = OPEN;
	}
	else
	{
		m_type = BLOCK;
	}	


	for (int i =0; i < 4 ;++i)
	{
		m_CaseLink[i] = NULL;
	}

	m_textPoids.init();
	m_textPoids.setPosition(m_vPosition);
	m_textPoids.setColor(cream::Color::Magenta);
	m_textPoids.setCharacterSize(12);

	std::ostringstream oss;

	oss << m_iPoids ;

	m_textPoids.setString(oss.str());


	m_textWay.init();	
	m_textWay.setColor(cream::Color::Magenta);
	m_textWay.setCharacterSize(8);
	m_textWay.setPosition(m_vPosition + creap::Vector2f(0,30));

}



Ccases::~Ccases()
{
	if(m_Rectangle != NULL)
	{
		m_Rectangle->forceDestroy();
		m_Rectangle->deinit();
		m_Rectangle = NULL;
	}


	for (int i =0; i < 4 ;++i)
	{
		m_CaseLink[i] = NULL;
	}

	m_textPoids.deinit();
	m_textWay.deinit();

}

void Ccases::displayCases()
{
	creamWindow_Draw(m_Rectangle);
	//creamWindow_Draw(&m_textPoids);
	//creamWindow_Draw(&m_textWay);
		
}


void Ccases::updateCases()
{

	cream::Color FillColor ;

	switch(m_type)
	{
		case OPEN :	FillColor = cream::Color::White;
					FillColor.a =0;					
					break;

		case BLOCK : FillColor = cream::Color::Blue;		 
					 break;

		case BEGIN : FillColor = cream::Color::Yellow; 	 
					 break;

		case END :  FillColor = cream::Color::Red;	 
					break;

		case PATH :  FillColor = cream::Color::Green;						 
					break;

		case CALCULATE :  FillColor = cream::Color::Cyan;					  		 
						  break;

		default :   FillColor = cream::Color::White;
					FillColor.a =0;		
					break;	
	}

	m_Rectangle->setColor(FillColor);
}


void Ccases::BlockOrDeblockThisCase()
{
	if( m_type == BLOCK)
	{
		m_type = OPEN;
	}
	else if( m_type != BEGIN && m_type != END )
	{
		m_type = BLOCK;
	}
	else
	{
	}
}


void Ccases::CalculateLengthToPosition(creap::Vector2f _EndVector)
{

	creap::Vector2f vecCaseToEnd;
	creap::Vector2f endVector = _EndVector;
	creap::Vector2f Position = m_vPosition;

	endVector.x() /= m_vSize.x();
	endVector.y() /= m_vSize.y();

	Position.x() /= m_vSize.x();
	Position.y() /= m_vSize.y();

	vecCaseToEnd = endVector - Position ;

	m_fLengthToEnd = (float)(vecCaseToEnd.x() + vecCaseToEnd.y());

	if(m_fLengthToEnd < 0)
		m_fLengthToEnd = -m_fLengthToEnd;
}

float Ccases::getPoids()
{
	return (float)m_iPoids;
}

float Ccases::getWightToEnd()
{
	return m_fLengthToEnd;
}


void Ccases::setLink(Ccases* _case , DirLink _dir)
{
	m_CaseLink[_dir] = _case;
}

Ccases* Ccases::getCase(DirLink _dir)
{
	return m_CaseLink[_dir];
}


void Ccases::setTextPoids(float _poids)
{
	
	std::ostringstream oss;
	oss << (int)_poids ;
	m_textWay.setString(oss.str());



}

void Ccases::reinitTextPoid()
{
	m_textWay.setString("");	
}
