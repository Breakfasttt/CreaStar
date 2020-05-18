//*******************
// auteur : yann c.
// date : 11/10/12
// file : creastar / CchoixMap.hpp
// description : déclaration du pathfinder
//*******************

#include "stdafx.h"


#ifndef CHOIXMAP_HPP
#define CHOIXMAP_HPP


class CchoixMap
{


protected :

	creamTextPtr m_titre;
	creamTextPtr m_choix;
	
	creamTextPtr m_infos;

	std::string m_NomTaper;

	bool m_MapChoisie;


public:

	CchoixMap();
	~CchoixMap();

	void updateChoixMap();
	void displayChoixMap();

	void TaperNom();

	bool IsMapChoisie(){return m_MapChoisie;};
	void setIsmapChoisie(bool _b){m_MapChoisie = _b;};

	std::string getNameMap();

	void setInfosText(std::string);



};


#endif