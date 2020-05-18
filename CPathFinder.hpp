//*******************
// auteur : yann c.
// date : 11/10/12
// file : creastar / Cpathfinder.hpp
// description : déclaration du pathfinder
//*******************

#include "stdafx.h"



#ifndef PATHFINDER_HPP
#define PATHFINDER_HPP

class Cmap;

class CPathFinder
{

protected :


	std::vector<Cway*> m_VecWay;
	Cway* m_WinningWay;

	int m_idBegin;
	bool m_bPathFound;
	creap::Vector2f m_vSizeCases;
	Cmap* m_map;
	bool m_bLaunch;

	float timeToFind;
	unsigned int m_Conso;

public :

	CPathFinder();
	CPathFinder( Ccases* _begin, creap::Vector2f _sizeCase, Cmap* _map );

	virtual ~CPathFinder();


	void CalculateAstar();

	void DeleteAlreadyKnowWay();
	void DeleteLoopWay();
	void SortByWeight();
	int DeleteNullWays();

	void ModeStepByStep();
	void Modeinstant();

	void ReinitPathFinder(Ccases* _BeginCase);

	float getTimeToFind();

	unsigned int getConso(){return m_Conso;};

	bool IsFound(){return m_bPathFound;};
	bool IsLaunch(){return m_bLaunch;};

};


#endif