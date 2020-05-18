//*******************
// auteur : yann c.
// date : 11/10/12
// file : creastar / Ccases.hpp
// description : déclaration d'une case de map
//*******************


#include <sstream>


#ifndef CCASES_HPP
#define CCASES_HPP


	enum TypeBlock
	{
		OPEN,
		BLOCK,
		BEGIN,
		END,
		PATH,
		CALCULATE,
	};

	enum DirLink
	{
		TOP,
		BOT,
		LEFT,
		RIGHT,	
	};


class Ccases
{

protected :

	int m_iPoids;
	float m_fLengthToEnd;

	creapVector2f m_vPosition;
	creapVector2f m_vSize;

	creamShapePtr m_Rectangle;

	TypeBlock m_type;

	Ccases* m_CaseLink[4];

	creamText m_textPoids;
	creamText m_textWay;

public :


	Ccases();
	Ccases(creapVector2f _size, creapVector2f _Pos , int _poids );
	virtual ~Ccases();


	void updateCases();
	void displayCases();


	inline void setType(TypeBlock _t) {m_type = _t;};
	inline TypeBlock getType() {return m_type ;};


	void BlockOrDeblockThisCase();
	inline void MakeThisBeginCase() {m_type = BEGIN;};
	inline void MakeThisEndCase() {m_type = END;};


	inline creapVector2f getPositionCase() {return m_vPosition;};
	inline creapVector2f getSizeCase() {return m_vSize;};

	void CalculateLengthToPosition(creap::Vector2f);
	float getPoids();
	float getWightToEnd();

	void setLink(Ccases*, DirLink);
	Ccases* getCase(DirLink);


	void setTextPoids(float _poids);
	void reinitTextPoid();
	unsigned int getConso() {return sizeof(*this);};


};







#endif
