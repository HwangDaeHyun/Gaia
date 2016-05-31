
#ifndef DFF_H_INCLUDE
#define DFF_H_INCLUDE
#include"GaiaObject.h"
#include"GaiaLLogic.h"

class DFF :public GaiaLLogic
{
public:
	DFF(){
		this->name = _T("D-FlipFlop");
		this->arrow = this->GetArrow();
	}
	void Draw(CDC* pDC)override{
		CRect rect(this->base_point.x, this->base_point.y, this->base_point.x + this->GetLength() * 10 - 20, this->base_point.y + this->GetLength() * 10 - 20);
		this->baseRect = rect;
		CRect dR, qR, cR;
		switch (radius){
		case 0:
			this->in1.SetRect(rect.left - 10, (rect.bottom + rect.top) / 2 + 5, rect.left, (rect.bottom + rect.top) / 2 + 15);
			this->clk.SetRect(rect.left - 10, (rect.bottom + rect.top) / 2 - 15, rect.left, (rect.bottom + rect.top) / 2 - 5);
			this->in2 = CRect();
			this->out = CRect(rect.right - 5, (rect.bottom + rect.top) / 2 - 15, rect.right + 5, (rect.bottom + rect.top) / 2 - 5);
			dR.SetRect(this->in1.left + 20, this->in1.top, this->in1.right + 20, this->in1.bottom);
			qR.SetRect(this->out.left - 20, this->out.top, this->out.right - 20, this->out.bottom);
			cR.SetRect(this->clk.left + 20, this->clk.top - 2, this->clk.right + 20, this->clk.bottom + 2);
			break;
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		}
		static_assert(sizeof(int) == sizeof(LONG), "이 플랫폼은 지원하지않습니다.");

		//글자를 그립니다
		CFont font;
		CRect rect2(rect.left + 5, rect.top + 5, rect.right - 5, rect.bottom - 5);
		CBrush brush(RGB(187, 222, 251));
		CPen pen;
		pen.CreatePen(PS_SOLID, 2, RGB(63, 81, 181));
		font.CreateFont(16,                     // 글자높이
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

		pDC->SelectObject(&pen);
		pDC->SelectObject(&brush);
		pDC->RoundRect(&rect2, CPoint(20, 20));
		pDC->SelectObject(&font);
		pDC->SetTextColor(RGB(0, 0, 0));
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(63, 81, 181));

		pDC->MoveTo(cR.TopLeft());
		pDC->LineTo(cR.CenterPoint());
		pDC->MoveTo(cR.CenterPoint());
		pDC->LineTo(cR.left, cR.bottom);
		pDC->DrawText(_T("D"), dR, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		pDC->DrawText(_T("Q"), qR, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	}
	void Calculate() override{
		auto& db = SingleTon<GaiaDrawGrid>::use()->dBoard;
		int tC = this->prevC;

		int curr = db[this->clk.CenterPoint().x / 10][this->clk.CenterPoint().y / 10];
		printf("%d , %d \n", tC, this->prevC);
		if (tC == 0 && curr == 1){
			if (db[this->in1.CenterPoint().x / 10][this->in1.CenterPoint().y / 10] == 1){
				db[this->out.CenterPoint().x / 10][this->out.CenterPoint().y / 10] = 1;
			}
			else if (db[this->in1.CenterPoint().x / 10][this->in1.CenterPoint().y / 10] == 0){
				db[this->out.CenterPoint().x / 10][this->out.CenterPoint().y / 10] = 0;
			}
		}


		this->prevC = curr;
	}

};

#endif