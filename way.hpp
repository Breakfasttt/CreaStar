//*******************
// auteur : yann c.
// date : 11/10/12
// file : creastar / way.hpp
// description : déclaration d'un chemin constituer de cases
//*******************

#include "stdafx.h"


#ifndef WAY_HPP
#define WAY_HPP


class Cway
{

protected :

	std::vector<Ccases*> m_vWayWithCases;


public :

	Cway();
	Cway(const Cway&);
	virtual ~Cway();


	void addCase(Ccases*);
	void ActiveWinnerWay();
	void ActiveCalculateWay();

	float getWayWeight();
	Ccases* getLastCaseOfThisWay();
	bool isLooping();


	void ShowWayPoids();
	void ReinitWayPoids();

	unsigned int getConsoCases();



};

#endif