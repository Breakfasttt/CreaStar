//*******************
// auteur : yann c.
// date : 11/10/12
// file : creastar / Cmap.hpp
// description : déclaration  de map
//*******************


#include "stdafx.h"
#include "CPathFinder.hpp"

#ifndef CMAP_HPP
#define CMAP_HPP


enum CasePlaced
{
	NOTHING_PLACED,
	BEGIN_PLACED,
	END_PLACED,
	ALL_PLACED,
};

enum ModeMap
{
	MODE_EDIT,
	MODE_DISPLAYONLY,
	MODE_PATHFINDING,
};


class Cmap
{
protected :


	std::string m_szMapName;

	std::vector<Ccases*> m_vecCases;

	int m_iLargeur;
	int m_iHauteur;

	creap::Vector2f m_vCoordBegin;
	creap::Vector2f m_vCoordEnd;
	creap::Vector2f m_vSizeCases;

	CasePlaced m_CasePlaced;
	ModeMap m_modeMap;

	CPathFinder* m_pathFinder;

	Chud* m_HUD;


public :


	Cmap();
	Cmap(std::string _path);

	virtual ~Cmap();


	bool LoadMap();
	void SauveMap();

	void UpdateMap();
	void DisplayMap();

	Ccases* getCaseInVectorWithMouse();
	Ccases* getCaseInVectorWithCoord(float , float);
	Ccases* getBeginCase();
	Ccases* getEndCase();


	void BlockCase();
	void PlaceBeginAndEndCase();
	void ReinitBeginAndEnd();
	void ChangeModeMap();
	bool CalculateWeight();

	void MakeLinksBetweenCase();

	void ReinitCaseForPath();


};



#endif