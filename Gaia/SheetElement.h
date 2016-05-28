#pragma once
#include"stdafx.h"
class SheetElement
{
public:
	SheetElement();
	virtual ~SheetElement();
	int topID;
	int parentID;
	int myID;
	CString name;
	COLORREF color;
	bool operator<(const SheetElement& e)const;
};