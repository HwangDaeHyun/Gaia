#pragma once

#include "GaiaObject.h"
#include "GaiaLLogic.h"

#include "GaiaRepo.h"
class InputBtn :
	public GaiaLLogic
{
public:
	InputBtn(){
		
	}
	InputBtn(int x, int y){
		this->objKind = INBUTTON;
		this->objSize = SMALL;
		this->SetPoint(x, y);
		this->SetRadius(0);
		this->name = _T("버튼");
		this->arrow = this->GetArrow();
		
		CRect rect(this->base_point.x + 5, this->base_point.y + 5, this->base_point.x + this->GetLength() * 10 - 25, this->base_point.y + this->GetLength() * 10 - 25);
		this->out = CRect(rect.right, (rect.bottom + rect.top) / 2 - 6, rect.right + 12, (rect.bottom + rect.top) / 2 + 6);
		SingleTon<GaiaDrawGrid>::use()->inBtns.push_back(this->out);
		auto& db = SingleTon<GaiaDrawGrid>::use()->dBoard;
		db[out.CenterPoint().x / 10][out.CenterPoint().y / 10] = 0;
		Update(this->out);

	}
public:
	void Draw(CDC* pDC)override{
		
		CRect rect(this->base_point.x + 5, this->base_point.y + 5, this->base_point.x + GaiaObjectSize.GetSmallLength() * 10 - 25, this->base_point.y + GaiaObjectSize.GetSmallLength() * 10 - 25);
		CRect rect2(this->base_point.x + 9, this->base_point.y + 9, this->base_point.x + GaiaObjectSize.GetSmallLength() * 10 - 29, this->base_point.y + GaiaObjectSize.GetSmallLength() * 10 - 29);
		this->baseRect = rect;
		CBrush brush(RGB(200, 11, 211));
		CPen pen;
		pen.CreatePen(PS_NULL, 1, RGB(241, 95, 95));
		pDC->SelectObject(&pen);
		VERIFY(radius >= 0);
		VERIFY(radius <= 3);
		switch (radius){
		case 0:
			this->out = CRect(rect.right, (rect.bottom + rect.top) / 2 - 6, rect.right + 12, (rect.bottom + rect.top) / 2 + 6);
			this->in1 = CRect();
			this->in2 = CRect();
			//여기
			break;
		case 1:

			break;
		case 2:

		case 3:
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
		pDC->Ellipse(this->out);
	}
	void Calculate() override{};
};

