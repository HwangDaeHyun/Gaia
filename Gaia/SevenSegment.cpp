#include "stdafx.h"
#include "SevenSegment.h"
#include "Resource.h"

SevenSegment::SevenSegment(){
	this->ins.assign(8, CRect());
	this->outs.assign(1, CRect());
	this->name = _T("seven seg");
	this->arrow = this->GetArrow();
	this->objSize = LARG;
	this->objKind = SEVENSEG;
}
void SevenSegment::Draw(CDC* pDC){
	CRect rect(this->base_point.x, this->base_point.y, this->base_point.x + this->GetLength() * 10 - 10 + 1, this->base_point.y + this->GetLength() * 10 - 10 + 1);
	this->baseRect = rect;
	CBrush brush(mv == RGB(0, 0, 0) ? basic : mv);
	CBrush b(RGB(40, 40, 40));
	CPen pen(PS_SOLID, 5, RGB(40, 40, 255));
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CBitmap bmp;
	pDC->SelectObject(&b);
	CPen* old = pDC->SelectObject(&pen);
	pDC->RoundRect(rect, CPoint(9, 9));
	switch (this->radius){
	case 0:
		for (int i = 0; i < 7; i++){
			this->ins[i] = CRect(rect.left - 10, rect.top + 5 + (i * 20), rect.left, rect.top + 15 + (i * 20));
			pDC->Rectangle(this->ins[i]);
		}
		break;
	case 1:
		for (int i = 0; i < 7; i++){
			this->ins[i] = CRect(rect.left + 5 + (i * 20), rect.top - 10, rect.left + 15 + (i * 20), rect.top);
			pDC->Rectangle(this->ins[i]);
		}
		break;
	case 2:
		for (int i = 0; i < 7; i++){
			this->ins[i] = CRect(rect.right, rect.top + 5 + (i * 20), rect.right + 10, rect.top + 15 + (i * 20));
			pDC->Rectangle(this->ins[i]);
		}
		break;
	case 3:
		for (int i = 0; i < 7; i++){
			this->ins[i] = CRect(rect.left + 5 + (i * 20), rect.bottom, rect.left + 15 + (i * 20), rect.bottom + 10);
			pDC->Rectangle(this->ins[i]);
		}
		break;
	}

	CRect dRects[7];
	dRects[0].SetRect(rect.left + 45, rect.top + 20, rect.right - 45, rect.top + 30);
	dRects[1].SetRect(rect.right - 30, rect.top + 30, rect.right - 40, rect.top + 65);
	dRects[2].SetRect(rect.right - 30, rect.bottom - 65, rect.right - 40, rect.bottom - 30);
	dRects[3].SetRect(rect.left + 45, rect.bottom - 30, rect.right - 45, rect.bottom - 20);
	dRects[4].SetRect(rect.left + 30, rect.bottom - 65, rect.left + 40, rect.bottom - 30);
	dRects[5].SetRect(rect.left + 30, rect.top + 30, rect.left + 40, rect.top + 65);
	dRects[6].SetRect(rect.left + 45, rect.top + 65, rect.right - 45, rect.bottom - 65);

	auto& db = SingleTon<GaiaDrawGrid>::use()->dBoard;
	CBrush brush1(RGB(255, 20, 20));
	CBrush brush2(RGB(70, 70, 70));
	for (int i = 0; i < ins.size(); i++){
		if (db[this->ins[i].CenterPoint().x / 10][this->ins[i].CenterPoint().y / 10] == TRUE){
			pDC->FillRect(dRects + i, &brush1);
		}
		else{
			pDC->FillRect(dRects + i, &brush2);
		}
	}
}
void SevenSegment::Calculate(){

}
IMPLEMENT_SERIAL(SevenSegment, GaiaLLogic, 14)
void SevenSegment::Serialize(CArchive& ar){
	GaiaLLogic::Serialize(ar);
}