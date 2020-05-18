#include "stdafx.h"
#include "CchoixMap.hpp"



Cmap* mapTest = NULL;
CchoixMap* ecranChoix = NULL;

bool BmapChoisie = false;


bool Initialiser()
{
	ecranChoix = new CchoixMap();

	return true;
}



bool BouclePrincipale()
{


	if(BmapChoisie)
	{
		if(mapTest != NULL)
		{
			mapTest->UpdateMap();
			mapTest->DisplayMap();
		}
	}
	else
	{
		ecranChoix->updateChoixMap();
		ecranChoix->displayChoixMap();

		if( ecranChoix->IsMapChoisie() )
		{
			BmapChoisie = true;


			mapTest = new Cmap( ecranChoix->getNameMap() );

			if(mapTest != NULL)
			{
				if( ! mapTest->LoadMap() )
				{
					BmapChoisie = false;
					ecranChoix->setIsmapChoisie(false);	
					ecranChoix->setInfosText("Cette map n'existe pas.\n Verifiez l'extension,l'emplacement et le contenu du fichier et recommencez :");
				}

			}
			else
			{
				std::cout << "erreur" << std::endl;
				BmapChoisie = false;
				ecranChoix->setIsmapChoisie(false);
			}
		
		}
	
	}

	return true;
}



bool Desinitialiser()
{

	return true;
}



int _tmain(int argc, _TCHAR* argv[])
{
	CREAM_C_DEFINITION;
}

