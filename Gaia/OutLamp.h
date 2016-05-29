#ifndef OUTLAMP_H_INCLUDE
#define OUTLAMP_H_INCLUDE
#include "GaiaLLogic.h"
class OutLamp : public GaiaLLogic
{
public:
	OutLamp(){
		this->name = _T("LAMP");
		this->arrow = this->GetArrow();
	}
	void Draw(CDC* pDC)override{
		CRect rect(this->base_point.x + 5, this->base_point.y + 5, this->base_point.x + GaiaObjectSize.GetLength() * 10 - 25, this->base_point.y + GaiaObjectSize.GetLength() * 10 - 25);
		this->baseRect = rect;
		VERIFY(radius >= 0);
		VERIFY(radius <= 3);
		switch (radius){
		case 3:
			this->out = CRect();
			this->in1 = CRect((rect.left + rect.right) / 2 - 5, rect.bottom + 5, (rect.left + rect.right) / 2 + 5, rect.bottom + 15);
			this->in2 = CRect();
			break;
		case 0:
			this->out = CRect();
			this->in1 = CRect(rect.left - 15, (rect.top + rect.bottom) / 2 - 5, rect.left - 5, (rect.top + rect.bottom) / 2 + 5);
			this->in2 = CRect();
			break;
		case 1:
			this->out = CRect();
			this->in1 = CRect((rect.left + rect.right) / 2 - 5, rect.top - 15, (rect.left + rect.right) / 2 + 5, rect.top - 5);
			this->in2 = CRect();
		case 2:
			this->out = CRect();
			this->in1 = CRect(rect.right + 5, (rect.top + rect.bottom) / 2 - 5, rect.right + 15, (rect.top + rect.bottom) / 2 + 5);
			this->in2 = CRect();
			break;
		}
		pDC->Ellipse(this->in1);
		CBrush onB(RGB(220, 250, 0));
		CPen pen;
		pen.CreatePen(PS_SOLID, 2, RGB(15, 15, 0));
		pDC->SelectObject(&pen);
		auto& db = SingleTon<GaiaDrawGrid>::use()->dBoard;
		if (db[this->in1.CenterPoint().x / 10][this->in1.CenterPoint().y / 10] == 1){
			pDC->SelectObject(&onB);
		}
		else{
			pDC->SelectStockObject(WHITE_BRUSH);
		}
		CBrush br(RGB(0, 0, 0));
		CRect rect2;
		rect2.SetRect(rect.left + 1, rect.top + 1, rect.right - 1, rect.bottom - 1);
		pDC->Ellipse(&rect2);
		CRect brTemp;
		switch (radius){
		case 0:
			/*brTemp.SetRect(this->in1.right, this->in1.top - 5, rect2.left, this->in1.bottom + 5);
			pDC->SelectObject(&br);
			pDC->Rectangle(&brTemp);*/
			break;
		case 1:

			break;
		case 2:

			break;
		case 3:

			break;
		}
		//���ڸ� �׸��ϴ�
		CFont font;
		font.CreateFont(15,                     // ���ڳ���
			6,                     // ���ڳʺ�
			0,                      // ��°���
			0,                      // ���� �������ǰ���
			FW_HEAVY,              // ���ڱ���
			FALSE,                  // Italic ���뿩��
			FALSE,                  // �������뿩��
			FALSE,                  // ��Ҽ����뿩��
			DEFAULT_CHARSET,       // ���ڼ�����
			OUT_DEFAULT_PRECIS,    // ������е�
			CLIP_DEFAULT_PRECIS,   // Ŭ�������е�
			DEFAULT_QUALITY,       // ��¹���ǰ��
			DEFAULT_PITCH,         // �۲�Pitch
			_T("Time New Romans")           // �۲�
			);
		pDC->SelectObject(&font);
		pDC->SetTextColor(RGB(200, 20, 20));
		pDC->SetBkMode(TRANSPARENT);
		pDC->DrawText(this->name, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}

};

#endif