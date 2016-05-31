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
	CBitmap* hover_image;
	bool operator<(const MenuElement& e)const;
};

