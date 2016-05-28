#include "stdafx.h"
#include "SheetElement.h"


SheetElement::SheetElement()
{
}


SheetElement::~SheetElement()
{
}

bool SheetElement::operator<(const SheetElement& e)const {
	return this->myID < e.myID;
}