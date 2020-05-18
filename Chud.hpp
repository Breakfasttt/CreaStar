//*******************
// auteur : yann c.
// date : 05/11/12
// file : creastar / Chud.hpp
// description : HUD de la map, permet l'affichage des infos de la map
//*******************



#ifndef CHUD_HPP
#define CHUD_HPP

#include "stdafx.h"

class Chud
{

protected :

	creamTextPtr m_ModeChoose;

	creamTextPtr m_PositionCase;
	creamTextPtr m_TypeCase;
	creamTextPtr m_PoidsCase;

	creamTextPtr m_TimeToFind;
	creamTextPtr m_ConsoMemory;

	creamTextPtr m_Infos;

	creamTextPtr m_LegendBlue;
	creamTextPtr m_LegendCyan;
	creamTextPtr m_LegendRed;
	creamTextPtr m_LegendYellow;
	creamTextPtr m_LegendGreen;
	creamTextPtr m_LegendBlack;

	bool AfficheCase;

public :

	Chud();
	virtual ~Chud();

	void DisplayHUD();

	void HUDsetMode(int _type);

	void HUDsetTypeCaseText(int _type);
	void HUDsetPositionCaseText(creap::Vector2f);
	void HUDsetPoidsCaseText(int poids);
	void HUDsetTimeToFindText(float);
	void HUDsetInfosText(int _type);

	void HUDsetConsoTextText(unsigned int _conso);

	inline void setAfficheCase(bool _b){AfficheCase = _b;};

};


#endif