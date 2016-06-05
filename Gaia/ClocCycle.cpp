#include "stdafx.h"
#include "ClockCycle.h"
#include "resource.h"
ClockCycle::ClockCycle(){

}
ClockCycle::ClockCycle(int x, int  y)
{
	this->outputGraph.assign(1, deque<int>());
	this->objKind = CLOCKCYCLE;
	this->objSize = SMALL;
	this->SetPoint(x, y);
	this->SetRadius(0);
	this->name = _T("Å¬·°");
	this->arrow = this->GetArrow();
	this->ins = vector<CRect>();
	this->outs.assign(1, CRect());
	CRect rect(this->base_point.x + 5, this->base_point.y + 5, this->base_point.x + this->GetLength() * 10 - 25, this->base_point.y + this->GetLength() * 10 - 25);
	this->outs[0] = CRect(rect.right, (rect.bottom + rect.top) / 2 - 6, rect.right + 12, (rect.bottom + rect.top) / 2 + 6);
	SingleTon<GaiaDrawGrid>::use()->inBtns.push_back(this->outs[0]);
	auto& db = SingleTon<GaiaDrawGrid>::use()->dBoard;
	db[outs[0].CenterPoint().x / 10][outs[0].CenterPoint().y / 10] = 0;
	Update(this->outs[0]);
	
}
void ClockCycle::Draw(CDC* pDC){
	CRect rect(this->base_point.x + 5, this->base_point.y + 5, this->base_point.x + this->GetLength() * 10 - 25, this->base_point.y + this->GetLength() * 10 - 25);
	CDC memDC;
	CBitmap bmp;
	this->baseRect = rect;
	this->arrow = this->GetArrow();
	memDC.CreateCompatibleDC(pDC);
	VERIFY(radius >= 0);
	VERIFY(radius <= 3);
	switch (this->radius){
	case 0: bmp.LoadBitmapW(IDB_CLK);
		this->outs[0] = CRect(rect.right, (rect.bottom + rect.top) / 2 - 6, rect.right + 12, (rect.bottom + rect.top) / 2 + 6);
		break;
	case 1: bmp.LoadBitmapW(IDB_CLK);
		this->outs[0] = CRect((rect.right + rect.left) / 2 - 6, rect.bottom, (rect.right + rect.left) / 2 + 6 , rect.bottom + 12);
		break;
	case 2: bmp.LoadBitmapW(IDB_CLK);
		this->outs[0] = CRect(rect.left-20, (rect.bottom + rect.top) / 2 - 6, rect.left-8, (rect.bottom + rect.top) / 2 + 6);
		break;
	case 3: bmp.LoadBitmapW(IDB_CLK);
		this->outs[0] = CRect((rect.right + rect.left) / 2 - 6, rect.top-12, (rect.right + rect.left) / 2 + 6, rect.top);
		break;
	}
	BITMAP bmpinfo;
	bmp.GetBitmap(&bmpinfo);
	memDC.SelectObject(&bmp);
	pDC->TransparentBlt(this->base_point.x - 5, this->base_point.y - 5, 50, 50, &memDC, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, RGB(0, 0, 0));
}

void ClockCycle::Calculate(){
	auto& db = SingleTon<GaiaDrawGrid>::use()->dBoard;
	if (outputGraph[0].size() > 15){
		outputGraph[0].clear();
	}
	if (db[this->outs[0].CenterPoint().x / 10][this->outs[0].CenterPoint().y / 10] == -1){
		return;
	}
	outputGraph[0].push_back(db[this->outs[0].CenterPoint().x / 10][this->outs[0].CenterPoint().y / 10]);
}

IMPLEMENT_SERIAL(ClockCycle, GaiaLLogic, 12)
void ClockCycle::Serialize(CArchive& ar){
	GaiaLLogic::Serialize(ar);

}