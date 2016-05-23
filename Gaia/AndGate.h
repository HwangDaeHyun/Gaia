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
		CRect rect(this->base_point.x - 5, this->base_point.y - 5, this->base_point.x + GaiaObjectSize.GetLength() * 10 - 5, this->base_point.y + GaiaObjectSize.GetLength() * 10 - 5);
		this->baseRect = rect;
		ior = rect.Width() / 10;
		CBrush brush(mv == RGB(0, 0, 0) ? basic : mv);
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
		const int dv = 5;
		switch (radius){
		case 0:
			elp = CRect(rect.left + whalf / 2, rect.top + rect.Height() / dv, rect.right - rect.Width() / dv, rect.bottom - rect.Height() / dv);
			rec = CRect(rect.left + rect.Width() / dv, rect.top + rect.Height() / dv, elp.left + elp.Width() / 2, rect.bottom - rect.Height() / dv);
			p1 = CPoint(rec.right - 1, rec.top + 1);
			p2 = CPoint(rec.right - 1, rec.bottom - 3);
			pt = CPoint(rect.right, (rect.top + rect.bottom) / 2);
			//this->out = CRect(elp.right - this->ior, elp.top + elp.Height() / 2 - this->ior, elp.right + this->ior, elp.top + elp.Height() / 2 + this->ior);
			this->out = CRect(pt.x - ior, pt.y - ior, pt.x + ior, pt.y + ior);
			pt = CPoint(rect.left, rect.top + rect.Width() / 3);
			this->in1 = CRect(pt.x - ior, pt.y - ior, pt.x + ior, pt.y + ior);
			pt = CPoint(rect.left, rect.bottom - rect.Width() / 3);
			this->in2 = CRect(pt.x - ior, pt.y - ior, pt.x + ior, pt.y + ior);
			//this->in2 = CRect(rec.left - ior, rec.top + rec.Height() / 5 * 4 - ior, rec.left + ior, rec.top + rec.Height() / 5 * 4 + ior);
			//this->in1 = CRect(rec.left - ior, rec.top + rec.Height() / 5 * 1 - ior, rec.left + ior, rec.top + rec.Height() / 5 * 1 + ior);
			//or
			elp2 = CRect(rect.left + rect.Width() / dv - 10, rect.top + rect.Height() / dv, rect.left + rect.Width() / dv + 10, rect.bottom - rect.Height() / dv);
			break;
		case 1:

			elp = CRect(rect.left + rect.Width() / 10, rect.top + hhalf / 2, rect.right - rect.Width() / 10, rect.bottom - rect.Height() / 10);
			rec = CRect(rect.left + rect.Width() / 10, rect.top + rect.Height() / 10, rect.right - rect.Width() / 10, elp.top + elp.Height() / 2);
			
			
			p1 = CPoint(rec.left + 1, rec.bottom - 1);
			p2 = CPoint(rec.right - 3, rec.bottom - 1);
			this->out = CRect(elp.left + elp.Width() / 2 - this->ior, elp.bottom - this->ior, elp.left + elp.Width() / 2 + this->ior, elp.bottom + this->ior);
			this->in2 = CRect(rec.left + rec.Width() / 5 * 4 - ior, rec.top - ior, rec.left + rec.Width() / 5 * 4 + ior, rec.top + ior);
			this->in1 = CRect(rec.left + rec.Width() / 5 * 1 - ior, rec.top - ior, rec.left + rec.Width() / 5 * 1 + ior, rec.top + ior);

			break;
		case 2:

		case 3:
			break;
		}
		static_assert(sizeof(int) == sizeof(LONG), "이 플랫폼은 지원하지않습니다.");

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
	}
};

#endif