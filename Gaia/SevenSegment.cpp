#include "stdafx.h"
#include "SevenSegment.h"
#include "Resource.h"

SevenSegment::SevenSegment(){
	this->ins.assign(8, CRect());
	this->outs.assign(1, CRect());
	this->name = _T("seven seg");
	this->arrow = this->GetArrow();
	this->objSize = BIG;
}
void SevenSegment::Draw(CDC* pDC){
	CRect rect(this->base_point.x, this->base_point.y, this->base_point.x + this->GetLength() * 10 - 10 + 1, this->base_point.y + this->GetLength() * 10 - 10 + 1);
	this->baseRect = rect;
	CBrush brush(mv == RGB(0, 0, 0) ? basic : mv);

	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CBitmap bmp;
	//입력 영역 지정입니다. 
	//동쪽 북쪽 서쪽 남쪽순
	//east
	this->ins[0] = CRect(rect.left - 10, (rect.bottom + rect.top) / 2 - 30, rect.left, (rect.bottom + rect.top) / 2 - 20);
	this->ins[1] = CRect(rect.left - 10, (rect.bottom + rect.top) / 2 + 20, rect.left, (rect.bottom + rect.top) / 2 + 30);
	//north
	this->ins[2] = CRect((rect.left + rect.right) / 2 - 30, rect.top - 10, (rect.left + rect.right) / 2 - 20, rect.top);
	this->ins[3] = CRect((rect.left + rect.right) / 2 + 20, rect.top - 10, (rect.left + rect.right) / 2 + 30, rect.top);
	//west
	this->ins[4] = CRect(rect.right, (rect.bottom + rect.top) / 2 - 30, rect.right + 10, (rect.bottom + rect.top) / 2 - 20);
	this->ins[5] = CRect(rect.right, (rect.bottom + rect.top) / 2 + 20, rect.right + 10, (rect.bottom + rect.top) / 2 + 30);
	//south
	this->ins[6] = CRect((rect.left + rect.right) / 2 - 30, rect.bottom, (rect.left + rect.right) / 2 - 20, rect.bottom + 10);
	this->ins[7] = CRect((rect.left + rect.right) / 2 + 20, rect.bottom, (rect.left + rect.right) / 2 + 30, rect.bottom + 10);

	for_each(begin(this->ins), end(this->ins), [&pDC](CRect& rect)->void{pDC->Rectangle(rect); });
	CRect dRects[8];
	dRects[0].SetRect(rect.left + 15, rect.top + 15, rect.left + 25, rect.top + 35);
	dRects[1].SetRect(rect.left + 30, rect.top + 5, rect.right - 30, rect.top + 15);
	dRects[2].SetRect(rect.right - 25, rect.top + 15, rect.right - 15, rect.top + 35);
	dRects[3].SetRect(rect.left + 30, rect.top + 35, rect.right - 30, rect.top + 45);
	dRects[4].SetRect(rect.left + 15, rect.top + 45, rect.left + 25, rect.top + 75);
	dRects[5].SetRect(rect.right - 25, rect.top + 45, rect.right - 15, rect.top + 75);
	dRects[6].SetRect(rect.left + 30, rect.top + 75, rect.right - 30, rect.top + 85);
	dRects[7].SetRect(rect.left + 30, rect.top + 75, rect.right - 30, rect.top + 85);
	auto& db = SingleTon<GaiaDrawGrid>::use()->dBoard;
	CBrush brush1(RGB(200, 200, 150));
	CBrush brush2(RGB(255, 255, 255));
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