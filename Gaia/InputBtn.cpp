#include "stdafx.h"
#include "InputBtn.h"
InputBtn::InputBtn(){
	this->objKind = INBUTTON;
	this->objSize = SMALL;
	this->SetRadius(0);
	this->name = _T("버튼");
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

InputBtn::InputBtn(int x, int y){
	this->objKind = INBUTTON;
	this->objSize = SMALL;
	this->SetPoint(x, y);
	this->SetRadius(0);
	this->name = _T("버튼");
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
void InputBtn::Draw(CDC* pDC){
	CRect rect(this->base_point.x + 5, this->base_point.y + 5, this->base_point.x + SingleTon<GaiaObjectSizeInfo>::use()->GetSmallLength() * 10 - 25, this->base_point.y + SingleTon<GaiaObjectSizeInfo>::use()->GetSmallLength() * 10 - 25);
	CRect rect2(this->base_point.x + 9, this->base_point.y + 9, this->base_point.x + SingleTon<GaiaObjectSizeInfo>::use()->GetSmallLength() * 10 - 29, this->base_point.y + SingleTon<GaiaObjectSizeInfo>::use()->GetSmallLength() * 10 - 29);
	this->baseRect = rect;
	this->arrow = this->GetArrow();
	CBrush brush(RGB(0, 0, 100));
	CPen pen;
	pen.CreatePen(PS_NULL, 1, RGB(241, 95, 95));
	pDC->SelectObject(&pen);
	pDC->SelectObject(&brush);
	VERIFY(radius >= 0);
	VERIFY(radius <= 3);
	switch (radius){
	case 0:
		this->outs[0] = CRect(rect.right, (rect.bottom + rect.top) / 2 - 6, rect.right + 12, (rect.bottom + rect.top) / 2 + 6);
		//여기
		break;
	case 1:
		this->outs[0] = CRect((rect.right + rect.left) / 2 - 6, rect.bottom, (rect.right + rect.left) / 2  + 6, rect.bottom +12);
		break;
	case 2:
		this->outs[0] = CRect(rect.left-12, (rect.bottom + rect.top) / 2 - 6, rect.left , (rect.bottom + rect.top) / 2 + 6);
		break;
	case 3:
		this->outs[0] = CRect((rect.right + rect.left) / 2 - 6, rect.top - 10, (rect.right + rect.left) / 2 + 6, rect.top +2 );
		break;
	}
	pDC->RoundRect(&rect, { 30, 30 });
	CBrush brush2(RGB(200, 110, 111));
	CBrush brush3(RGB(150, 150, 200));
	if (this->btn == false){
		pDC->SelectObject(&brush2);
	}
	else{
		pDC->SelectObject(&brush3);
	}

	pDC->Ellipse(&rect2);
	CBrush brush4(RGB(0, 0, 100));
	pDC->SelectObject(&brush4);
	pDC->Ellipse(this->outs[0]);
	pen.DeleteObject();
	brush.DeleteObject();
	brush2.DeleteObject();
	brush3.DeleteObject();
	brush4.DeleteObject();
}

void InputBtn::Calculate(){}