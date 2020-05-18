//*******************
// auteur : yann c.
// date : 05/11/12
// file : creastar / Chud.hpp
// description : HUD de la map, permet l'affichage des infos de la map
//*******************


#include "stdafx.h"



Chud::Chud()
{

	AfficheCase = false;

	m_ModeChoose = creamText_CreateWithString("") ;

	 m_PositionCase= creamText_CreateWithString("") ;
	 m_TypeCase= creamText_CreateWithString("") ;
	 m_PoidsCase= creamText_CreateWithString("") ;

	 m_TimeToFind= creamText_CreateWithString("") ;

	 m_Infos= creamText_CreateWithString("") ;

	  m_ConsoMemory= creamText_CreateWithString("") ;


	 m_LegendBlue   = creamText_CreateWithString("Case bleu : Mur") ;
	 m_LegendCyan   = creamText_CreateWithString("Case Cyan : Testée") ;
	 m_LegendRed    = creamText_CreateWithString("Case Rouge : Fin") ;
	 m_LegendYellow = creamText_CreateWithString("Case Jaune : Début") ;
	 m_LegendGreen  = creamText_CreateWithString("Case Vert : Chemin") ;
	 m_LegendBlack  = creamText_CreateWithString("Case Noir : vide") ;

	 m_ModeChoose->init();

	 m_PositionCase->init();
	 m_TypeCase->init();
	 m_PoidsCase->init();

	 m_TimeToFind->init();
	 m_ConsoMemory->init();

	 m_Infos->init();

	 m_LegendBlue->init();
	 m_LegendCyan->init();
	 m_LegendRed->init();
	 m_LegendYellow->init();
	 m_LegendGreen->init();
	 m_LegendBlack->init();

	 m_LegendBlue->setColor(creamColor::Blue);
	 m_LegendCyan->setColor(creamColor::Cyan);
	 m_LegendRed->setColor(creamColor::Red);
	 m_LegendYellow->setColor(creamColor::Yellow);
	 m_LegendGreen->setColor(creamColor::Green);
	 m_LegendBlack->setColor(creamColor::White);


	 m_LegendBlue->setPosition( creap::Vector2f(810,450) );
	 m_LegendCyan->setPosition( creap::Vector2f(810,470) );
	 m_LegendRed->setPosition( creap::Vector2f(810,490) );
	 m_LegendYellow->setPosition( creap::Vector2f(810,510) );
	 m_LegendGreen->setPosition( creap::Vector2f(810,530) );
	 m_LegendBlack->setPosition( creap::Vector2f(810,550) );

	m_ModeChoose->setPosition( creap::Vector2f(810,30) );

	m_Infos->setPosition( creap::Vector2f(810,90) );
	m_Infos->setScale(0.8f,0.8f);

	m_TimeToFind->setPosition( creap::Vector2f(810,420) );
	m_TimeToFind->setScale(0.8f,0.8f);

	m_TypeCase->setPosition( creap::Vector2f(810,200) );
	m_TypeCase->setScale(0.8f,0.8f);

	m_PositionCase->setPosition( creap::Vector2f(810,260) );
	m_PositionCase->setScale(0.8f,0.8f);

	m_PoidsCase->setPosition( creap::Vector2f(810,285) );
	m_PoidsCase->setScale(0.8f,0.8f);

	m_ConsoMemory->setPosition( creap::Vector2f(810,395) );
	m_ConsoMemory->setScale(0.8f,0.8f);

}

Chud::~Chud()
{
	m_ModeChoose->deinit();
	 m_PositionCase->deinit();
	 m_TypeCase->deinit();
	 m_PoidsCase->deinit();

	 m_TimeToFind->deinit();

	 m_Infos->deinit();
	 m_ConsoMemory->deinit();

	 m_LegendBlue->deinit();
	 m_LegendCyan->deinit();
	 m_LegendRed->deinit();
	 m_LegendYellow->deinit();
	 m_LegendGreen->deinit();
	 m_LegendBlack->deinit();

}

void Chud::DisplayHUD()
{

	if(m_LegendBlue)
		creamGraphic_Draw(m_LegendBlue);
	if(m_LegendCyan)
		creamGraphic_Draw(m_LegendCyan);
	if(m_LegendRed)
		creamGraphic_Draw(m_LegendRed);
	if(m_LegendYellow)
		creamGraphic_Draw(m_LegendYellow);
	if(m_LegendGreen)
		creamGraphic_Draw(m_LegendGreen);
	if(m_LegendBlack)
		creamGraphic_Draw(m_LegendBlack);

	if(m_ModeChoose)
		creamGraphic_Draw(m_ModeChoose);
	if(m_Infos)
		creamGraphic_Draw(m_Infos);

	if(m_TimeToFind)
		creamGraphic_Draw(m_TimeToFind);

	if(m_ConsoMemory)
		creamGraphic_Draw(m_ConsoMemory);

	if(AfficheCase)
	{
	
		if(m_TypeCase)
			creamGraphic_Draw(m_TypeCase);	
		if(m_PositionCase)
			creamGraphic_Draw(m_PositionCase);
		if(m_PoidsCase)
			creamGraphic_Draw(m_PoidsCase);	
	}
}

void Chud::HUDsetTypeCaseText(int _type)
{
	std::ostringstream oss;
	oss << "Infos Case : " << std::endl << std::endl;
	oss << "Type : " ;

	switch(_type)
	{
		case 0 : oss << "libre" << std::endl; break;
		case 1 : oss << "mur" << std::endl; break;
		case 2 : oss << "début" << std::endl; break;
		case 3 : oss << "fin" << std::endl; break;
		case 4 : oss << "chemin" << std::endl; break;
		case 5 : oss << "testé" << std::endl; break;
		default: oss << "ERREUR" << std::endl; break;
	}

	m_TypeCase->setString( oss.str() );

}

void Chud::HUDsetPositionCaseText(creap::Vector2f _position)
{
	std::ostringstream oss;

	oss << "Pos : " << _position  << std::endl;

	m_PositionCase->setString( oss.str() );
}

void Chud::HUDsetPoidsCaseText(int _poids)
{
	std::ostringstream oss;

	oss << "Poids : " << _poids << std::endl;

	m_PoidsCase->setString( oss.str() );
}

void Chud::HUDsetTimeToFindText(float _time)
{
	std::ostringstream oss;

	oss << "Temps de calcul : " << _time << " ms" << std::endl;

	m_TimeToFind->setString( oss.str() );
}

void Chud::HUDsetInfosText(int _type )
{
	std::ostringstream oss;

	oss << "Espace : Changer de Mode " << std::endl;

	switch(_type)
	{
	case 0 : oss << "Infos : " << std::endl << std::endl << "Clique gauche : Mur " << std::endl
											<< "Clique droit : Debut/arrivé " << std::endl;break;
		case 1 : oss << "Infos : " << std::endl << std::endl << "Affichage seulement" << std::endl;break;
		case 2 : oss << "Infos : " << std::endl << std::endl << "Clique gauche : Pas à pas " << std::endl
								   << "Clique droit : Instantané " << std::endl;break;
		default : oss << "Error" << std::endl;
	}

	m_Infos->setString( oss.str() );

}

void Chud::HUDsetMode(int _type)
{
	std::ostringstream oss;

	switch(_type)
	{
		case 0 : oss << "Mode : Edit" << std::endl; break;
		case 1 : oss << "Mode : Display" << std::endl;break;
		case 2 : oss << "Mode : PathFinding" << std::endl;break;
		default : oss << "Error" << std::endl;
	}

	m_ModeChoose->setString( oss.str() );
}


void Chud::HUDsetConsoTextText(unsigned int _conso)
{
	std::ostringstream oss;

	oss << "Mémoire utilisé : " << _conso << std::endl;

	m_ConsoMemory->setString( oss.str() );

}