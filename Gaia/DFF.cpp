#include"stdafx.h"
#include"DFF.h"
#include"Resource.h"
//#include"GaiaObject.h"
DFF::DFF(){
	this->ins.assign(1, CRect());
	this->outs.assign(2, CRect());
	this->objKind = DFLIP;

	this->name = _T("D-FlipFlop");
	this->arrow = this->GetArrow();
}
void DFF::Draw(CDC* pDC){
	CRect rect(this->base_point.x, this->base_point.y, this->base_point.x + this->GetLength() * 10 - 20, this->base_point.y + this->GetLength() * 10 - 20);
	this->baseRect = rect;
	CRect dR, qR, cR , nqR; 
	switch (radius){
	case 0:
		this->ins[0].SetRect(rect.left - 10, (rect.bottom + rect.top) / 2 + 5, rect.left, (rect.bottom + rect.top) / 2 + 15);
		this->clk.SetRect(rect.left - 10, (rect.bottom + rect.top) / 2 - 15, rect.left, (rect.bottom + rect.top) / 2 - 5);
		this->outs[0] = CRect(rect.right - 5, (rect.bottom + rect.top) / 2 - 15, rect.right + 5, (rect.bottom + rect.top) / 2 - 5);
		this->outs[1] = CRect(rect.right - 5, (rect.bottom + rect.top) / 2 + 5, rect.right + 5, (rect.bottom + rect.top) / 2 + 15);
		dR.SetRect(this->ins[0].left + 20, this->ins[0].top, this->ins[0].right + 20, this->ins[0].bottom);
		qR.SetRect(this->outs[0].left - 20, this->outs[0].top, this->outs[0].right - 20, this->outs[0].bottom);
		cR.SetRect(this->clk.left + 20, this->clk.top - 2, this->clk.right + 20, this->clk.bottom + 2);
		nqR.SetRect(this->outs[1].left - 20, this->outs[1].top, this->outs[1].right - 15, this->outs[1].bottom);
		break;
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	}
	static_assert(sizeof(int) == sizeof(LONG), "�� �÷����� ���������ʽ��ϴ�.");

	//���ڸ� �׸��ϴ�
	CFont font;
	CRect rect2(rect.left + 5, rect.top + 5, rect.right - 5, rect.bottom - 5);
	CBrush brush(RGB(187, 222, 251));
	CPen pen;
	pen.CreatePen(PS_SOLID, 2, RGB(63, 81, 181));
	font.CreateFont(16,                     // ���ڳ���
		8,                     // ���ڳʺ�
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
	pDC->DrawText(_T("Q`"), nqR, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}
void DFF::Calculate(){
	auto& db = SingleTon<GaiaDrawGrid>::use()->dBoard;
	int tC = this->prevC;
	int curr = db[this->clk.CenterPoint().x / 10][this->clk.CenterPoint().y / 10];
	//printf("%d , %d \n", tC, this->prevC);
	if (tC == 0 && curr == 1){
		if (db[this->ins[0].CenterPoint().x / 10][this->ins[0].CenterPoint().y / 10] == 1){
			db[this->outs[0].CenterPoint().x / 10][this->outs[0].CenterPoint().y / 10] = 1;
			db[this->outs[1].CenterPoint().x / 10][this->outs[1].CenterPoint().y / 10] = 0;
		}
		else if (db[this->ins[0].CenterPoint().x / 10][this->ins[0].CenterPoint().y / 10] == 0){
			db[this->outs[0].CenterPoint().x / 10][this->outs[0].CenterPoint().y / 10] = 0;
			db[this->outs[1].CenterPoint().x / 10][this->outs[1].CenterPoint().y / 10] = 1;
		}
	}
	this->prevC = curr;
}