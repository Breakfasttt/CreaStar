//*******************
// auteur : yann c.
// date : 11/10/12
// file : creastar / CchoixMap.cpp
// description : déclaration du pathfinder
//*******************

#include "stdafx.h"
#include "CchoixMap.hpp"




CchoixMap::CchoixMap()
{

	m_MapChoisie = false;

	m_titre =  creamText_CreateWithString("A*");
	m_choix =  creamText_CreateWithString("");
	m_infos =  creamText_CreateWithString("Entrez nom_de_fichier.txt (il doit etre au niveau du .exe) :");

	m_titre->init();
	m_choix->init();
	m_infos->init();


	
	m_titre->setPosition(creap::Vector2f(50.0f,50.0f));
	m_titre->setScale(2.0f,2.0f);

	m_infos->setPosition(creap::Vector2f(100.0f,250.0f));
	m_choix->setPosition(creap::Vector2f(100.0f,300.0f));

	m_NomTaper = "";

}

CchoixMap::~CchoixMap()
{
	m_titre->deinit();
	 m_choix->deinit();
	 m_infos->deinit();

}

void CchoixMap::updateChoixMap()
{


	TaperNom();
	m_choix->setString(m_NomTaper);


}

void CchoixMap::displayChoixMap()
{
	if(m_titre)
		creamGraphic_Draw(m_titre);

	if(m_infos)
		creamGraphic_Draw(m_infos);

	if(m_choix)
		creamGraphic_Draw(m_choix);
	
}

void CchoixMap::TaperNom()
{

	char tempChar;

	tempChar = creamKeyboard_GetLastChar();


	if(tempChar!=0)
	{
		m_NomTaper.push_back(tempChar);
	}


	if( creamKeyboard_GetKeyState(creamKeyboard_KeyCode::Back) == 0 )
	{
		if(m_NomTaper.size() >0)
		{
			m_NomTaper.pop_back();
		}
	}


	if( creamKeyboard_GetKeyState(creamKeyboard_KeyCode::Return) == 0 )
	{
		m_MapChoisie = true;
	}

}


std::string  CchoixMap::getNameMap()
{
	return m_NomTaper;
}


void CchoixMap::setInfosText(std::string _infos)
{
	//m_infos->setString("Cette map n'existe pas. Verifiez l'extension et l'emplacement du fichier et recommencez :");
	m_infos->setString(_infos);
}