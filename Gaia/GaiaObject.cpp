#include "stdafx.h"
#include "GaiaObject.h"


GaiaObject::GaiaObject()
{
	GaiaObject();

}
GaiaObject::~GaiaObject()
{
}
void GaiaObject::SetRadius(int r){
	VERIFY(r >= 0);
	VERIFY(r < 4);
	this->radius = r;
}