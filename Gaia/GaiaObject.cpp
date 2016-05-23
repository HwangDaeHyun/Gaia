#include "stdafx.h"
#include "GaiaObject.h"


GaiaObject::GaiaObject()
{
	this->basic = RGB(103, 153, 255);
	this->mv = RGB(0, 0, 0);

}
GaiaObject::~GaiaObject()
{
}
void GaiaObject::SetRadius(int r){
	VERIFY(r >= 0);
	VERIFY(r < 4);
	this->radius = r;
}