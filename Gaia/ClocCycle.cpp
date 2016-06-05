#include "stdafx.h"
#include "ClockCycle.h"
#include "resource.h"
ClockCycle::ClockCycle(){

}
ClockCycle::ClockCycle(int x, int  y)
{
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
	memDC.CreateCompatibleDC(pDC);
	VERIFY(radius >= 0);
	VERIFY(radius <= 3);
	switch (this->radius){
	case 0: bmp.LoadBitmapW(IDB_CLK);
		this->outs[0] = CRect(rect.right, (rect.bottom + rect.top) / 2 - 6, rect.right + 12, (rect.bottom + rect.top) / 2 + 6);
		break;
	}
	BITMAP bmpinfo;
	//CBitmap* oldbmp = memDC.SelectObject(&bmp);
	bmp.GetBitmap(&bmpinfo);
	memDC.SelectObject(&bmp);
	pDC->TransparentBlt(this->base_point.x - 5, this->base_point.y - 5, 50, 50, &memDC, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, RGB(0, 0, 0));
}

void ClockCycle::Calculate(){

}
IMPLEMENT_SERIAL(ClockCycle, GaiaLLogic, 2)
void ClockCycle::Serialize(CArchive& ar){
	GaiaLLogic::Serialize(ar);
}