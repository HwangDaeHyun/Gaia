#pragma once
#ifndef GOEUN_EDITOR_AND_GATE_H_7DF_INCLUDE
#define GOEUN_EDITOR_AND_GATE_H_7DF_INCLUDE
#include"GaiaObject.h"
#include"GaiaLLogic.h"

class AndGate :public GaiaLLogic
{
public:
	AndGate(){}
	void Draw(CDC* pDC)override{
		CRect rect(this->base_point.x, this->base_point.y, this->base_point.x + GaiaObjectSize.GetLength() * 10 - 20, this->base_point.y + GaiaObjectSize.GetLength() * 10 - 20);
		this->baseRect = rect;


		CBrush brush(mv == RGB(0, 0, 0) ? basic : mv);
		CBrush *old = pDC->SelectObject(&brush);
		CBrush brush2(RGB(241, 5, 5));
		//pDC->FillRect(rect, &brush2);

		CPen pen;
		pen.CreatePen(PS_NULL, 1, RGB(241, 95, 95));
		pDC->SelectObject(&pen);
		VERIFY(radius >= 0);
		VERIFY(radius <= 3);
		int whalf = rect.Width() / 2;
		int hhalf = rect.Height() / 2;
		CRect elp, rec;
		CPoint p1, p2;
		CPoint pt;
		//
		CRect elp2;
		//
		CDC memDC;
		memDC.CreateCompatibleDC(pDC);
		CBitmap bmp;
		switch (radius){
		case 0:
			bmp.LoadBitmapW(IDB_AND_0);
			this->out = CRect(rect.right, (rect.bottom + rect.top) / 2 - 5, rect.right + 10, (rect.bottom + rect.top) / 2 + 5);
			this->in1 = CRect(rect.left - 10, (rect.bottom + rect.top) / 2 - 25, rect.left, (rect.bottom + rect.top) / 2 - 15);
			this->in2 = CRect(rect.left - 10, (rect.bottom + rect.top) / 2 + 15, rect.left, (rect.bottom + rect.top) / 2 + 25);
			//여기
			break;
		case 1:
			bmp.LoadBitmapW(IDB_AND_90);
			break;
		case 2:

		case 3:
			break;
		}
		static_assert(sizeof(int) == sizeof(LONG), "이 플랫폼은 지원하지않습니다.");
		BITMAP bmpinfo;
		//CBitmap* oldbmp = memDC.SelectObject(&bmp);
		bmp.GetBitmap(&bmpinfo);
		memDC.SelectObject(&bmp);
		pDC->TransparentBlt(this->base_point.x, this->base_point.y, 60, 60, &memDC, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, RGB(0, 0, 0));
		//memDC.SelectObject(oldbmp);


		pDC->SelectObject(&brush);
		pDC->Ellipse(elp);

		pDC->Rectangle(rec);
		//CBrush temp(SingleTon<GaiaLayoutRepo> ::use()->Getrightside);
		//pDC->SelectObject(&temp);
		//pDC->Ellipse(elp2);
		pDC->SelectObject(&brush);
		CPen pen2;
		pen2.CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
		pDC->SelectObject(pen2);

		pDC->MoveTo(out.left, (out.top + out.bottom) / 2);
		pDC->LineTo(out.right - out.Width() / 2, (out.top + out.bottom) / 2);

		pDC->MoveTo(in1.left + in1.Width() / 2, (in1.top + in1.bottom) / 2);
		pDC->LineTo(in1.right, (in1.top + in1.bottom) / 2);

		pDC->MoveTo(in2.left + in2.Width() / 2, (in2.top + in2.bottom) / 2);
		pDC->LineTo(in2.right, (in2.top + in2.bottom) / 2);
		pDC->SelectObject(old);
	}
	void Calculate() override{
		auto& db = SingleTon<GaiaDrawGrid>::use()->dBoard;
		//if (db[this->out.CenterPoint().x / 10][this->out.CenterPoint().y] == -1){
		if (db[this->in1.CenterPoint().x / 10][this->in1.CenterPoint().y / 10] == 0){
			db[this->out.CenterPoint().x / 10][this->out.CenterPoint().y / 10] = 0;
		}
		else if (db[this->in2.CenterPoint().x / 10][this->in2.CenterPoint().y / 10] == 0){
			db[this->out.CenterPoint().x / 10][this->out.CenterPoint().y / 10] = 0;
		}
		else{
			if (db[this->in1.CenterPoint().x / 10][this->in1.CenterPoint().y / 10] == 1 || db[this->in2.CenterPoint().x / 10][this->in2.CenterPoint().y / 10] == 1){
				db[this->out.CenterPoint().x / 10][this->out.CenterPoint().y / 10] = 1;
			}
		}
	}
	//}
};

#endif