#pragma once
#include"stdafx.h"
class MenuElement
{
public:
	MenuElement();
	virtual ~MenuElement();
	int parentID;
	int myID;
	CBitmap* image;
	bool operator<(const MenuElement& e)const;
};

