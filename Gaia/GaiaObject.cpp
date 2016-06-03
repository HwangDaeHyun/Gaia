#include "stdafx.h"
#include "GaiaObject.h"
#include"GaiaRepo.h"

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
int GaiaObject::GetLength(){
	int len = 0;
	switch (this->objSize){
	case SMALL:
		return len = SingleTon<GaiaObjectSizeInfo>::use()->GetSmallLength();
	case MID:
		return len = SingleTon<GaiaObjectSizeInfo>::use()->GetLength();

	case BIG:
		return len = SingleTon<GaiaObjectSizeInfo>::use()->GetBigLength();

	default:
		return 0;
	}
}
CString GaiaObject::GetArrow(){
	CString temp;
	switch (this->radius){
	case 0:
		temp = _T("EAST");
		break;
	case 1:
		temp = _T("DOWN");
		break;
	case 2:
		temp = _T("LEFT");
		break;
	case 3:
		temp = _T("UP");
		break;
	default:
		break;
	}
	return temp;
}
void GaiaObject::Draw(CDC* pDC){

}