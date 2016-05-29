#pragma once
#ifndef OR_GATE_H_7DF_INCLUDE
#define OR_GATE_H_7DF_INCLUDE
#include"GaiaObject.h"
#include"GaiaLLogic.h"

class OrGate :public GaiaLLogic
{
public:
	OrGate(){
		this->name = _T("OR");
		this->arrow = this->GetArrow();
	}
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
			bmp.LoadBitmapW(IDB_OR_0);
			this->out = CRect(rect.right, (rect.bottom + rect.top) / 2 - 5, rect.right + 10, (rect.bottom + rect.top) / 2 + 5);
			this->in1 = CRect(rect.left - 10, (rect.bottom + rect.top) / 2 - 25, rect.left, (rect.bottom + rect.top) / 2 - 15);
			this->in2 = CRect(rect.left - 10, (rect.bottom + rect.top) / 2 + 15, rect.left, (rect.bottom + rect.top) / 2 + 25);
			//여기
			break;
		case 1:
			bmp.LoadBitmapW(IDB_OR_90);
			this->out = CRect((rect.left + rect.right) / 2 + 15, rect.bottom, (rect.left + rect.right) / 2 - 5, rect.bottom + 10);
			this->in1 = CRect((rect.left + rect.right) / 2 - 25, rect.top - 10, (rect.left + rect.right) / 2 - 15, rect.top);
			this->in2 = CRect((rect.left + rect.right) / 2 + 15, rect.top - 10, (rect.left + rect.right) / 2 + 25, rect.top);
			break;
		case 2:
			bmp.LoadBitmapW(IDB_OR_180);
			this->out = CRect(rect.left - 5, (rect.bottom + rect.top) / 2 - 5, rect.left + 5, (rect.bottom + rect.top) / 2 + 5);
			this->in1 = CRect(rect.right + 5, (rect.bottom + rect.top) / 2 - 25, rect.right + 15, (rect.bottom + rect.top) / 2 - 15);
			this->in2 = CRect(rect.right + 5, (rect.bottom + rect.top) / 2 + 15, rect.right + 15, (rect.bottom + rect.top) / 2 + 25);
			break;
		case 3:
			bmp.LoadBitmapW(IDB_OR_270);
			this->out = CRect((rect.left + rect.right) / 2 - 5, rect.top - 5, (rect.left + rect.right) / 2 + 5, rect.top + 5);
			this->in1 = CRect((rect.left + rect.right) / 2 - 25, rect.bottom, (rect.left + rect.right) / 2 - 15, rect.bottom + 10);
			this->in2 = CRect((rect.left + rect.right) / 2 + 15, rect.bottom, (rect.left + rect.right) / 2 + 25, rect.bottom + 10);

			break;
		}
		static_assert(sizeof(int) == sizeof(LONG), "이 플랫폼은 지원하지않습니다.");
		BITMAP bmpinfo;
		//CBitmap* oldbmp = memDC.SelectObject(&bmp);
		bmp.GetBitmap(&bmpinfo);
		memDC.SelectObject(&bmp);
		pDC->TransparentBlt(this->base_point.x, this->base_point.y, 60, 60, &memDC, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, RGB(255, 255, 255));
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
		switch (radius){
		case 0:
			pDC->MoveTo(out.left, (out.top + out.bottom) / 2);
			pDC->LineTo(out.right - out.Width() / 2, (out.top + out.bottom) / 2);

			pDC->MoveTo(in1.left + in1.Width() / 2, (in1.top + in1.bottom) / 2);
			pDC->LineTo(in1.right, (in1.top + in1.bottom) / 2);

			pDC->MoveTo(in2.left + in2.Width() / 2, (in2.top + in2.bottom) / 2);
			pDC->LineTo(in2.right, (in2.top + in2.bottom) / 2);
			break;
		case 1:
			pDC->MoveTo((out.left + out.right) / 2, out.top);
			pDC->LineTo(out.right - out.Width() / 2, (out.top + out.bottom) / 2);

			pDC->MoveTo((in1.left + in1.right) / 2, in1.top + in1.Height() / 2);
			pDC->LineTo((in1.left + in1.right) / 2, in1.top);

			pDC->MoveTo((in2.left + in2.right) / 2, in2.top + in2.Height() / 2);
			pDC->LineTo((in2.left + in2.right) / 2, in2.top);
			break;
		case 2:
			pDC->MoveTo(out.left, (out.top + out.bottom) / 2);
			pDC->LineTo(out.right - out.Width() / 2, (out.top + out.bottom) / 2);

			pDC->MoveTo(in1.left, (in1.top + in1.bottom) / 2);
			pDC->LineTo(in1.right - in1.Width() / 2, (in1.top + in1.bottom) / 2);

			pDC->MoveTo(in2.left, (in2.top + in2.bottom) / 2);
			pDC->LineTo(in2.right - in2.Width() / 2, (in2.top + in2.bottom) / 2);
			break;
		case 3:
			pDC->MoveTo((out.left + out.right) / 2, out.top);
			pDC->LineTo(out.right - out.Width() / 2, (out.top + out.bottom) / 2);

			pDC->MoveTo((in1.left + in1.right) / 2, in1.top + in1.Height() / 2);
			pDC->LineTo((in1.left + in1.right) / 2, in1.top);

			pDC->MoveTo((in2.left + in2.right) / 2, in2.top + in2.Height() / 2);
			pDC->LineTo((in2.left + in2.right) / 2, in2.top);
		}
		pDC->SelectObject(old);
		//글자를 그립니다
		CFont font;
		font.CreateFont(15,                     // 글자높이
			8,                     // 글자너비
			0,                      // 출력각도
			0,                      // 기준 선에서의각도
			FW_HEAVY,              // 글자굵기
			FALSE,                  // Italic 적용여부
			FALSE,                  // 밑줄적용여부
			FALSE,                  // 취소선적용여부
			DEFAULT_CHARSET,       // 문자셋종류
			OUT_DEFAULT_PRECIS,    // 출력정밀도
			CLIP_DEFAULT_PRECIS,   // 클리핑정밀도
			DEFAULT_QUALITY,       // 출력문자품질
			DEFAULT_PITCH,         // 글꼴Pitch
			_T("Time New Romans")           // 글꼴
			);
		pDC->SelectObject(&font);
		pDC->SetTextColor(RGB(255, 220, 200));
		pDC->SetBkMode(TRANSPARENT);
		pDC->DrawText(this->name, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	void Calculate() override{
		auto& db = SingleTon<GaiaDrawGrid>::use()->dBoard;
		if (db[this->in1.CenterPoint().x / 10][this->in1.CenterPoint().y / 10] == 1){
			db[this->out.CenterPoint().x / 10][this->out.CenterPoint().y / 10] = 1;
		}
		else if (db[this->in2.CenterPoint().x / 10][this->in2.CenterPoint().y / 10] == 1){
			db[this->out.CenterPoint().x / 10][this->out.CenterPoint().y / 10] = 1;
		}
		else if (db[this->in1.CenterPoint().x / 10][this->in1.CenterPoint().y / 10] == 0 && db[this->in2.CenterPoint().x / 10][this->in2.CenterPoint().y / 10] == 0){
			db[this->out.CenterPoint().x / 10][this->out.CenterPoint().y / 10] = 0;
		}
		else{
			db[this->out.CenterPoint().x / 10][this->out.CenterPoint().y / 10] = -1;
		}
	}

	//}
};

#endif