#include "stdafx.h"
#include"OutLamp.h"

OutLamp::OutLamp(){
	this->objKind = OUTLAMP;
	this->outs.assign(1, CRect());
	this->ins.assign(1, CRect());
	this->name = _T("LAMP");
	this->arrow = this->GetArrow();
	this->inputGraph.assign(1, deque<int>());
}
void OutLamp::Draw(CDC* pDC){
	CRect rect(this->base_point.x + 5, this->base_point.y + 5, this->base_point.x + SingleTon<GaiaObjectSizeInfo>::use()->GetLength() * 10 - 25, this->base_point.y + SingleTon<GaiaObjectSizeInfo>::use()->GetLength() * 10 - 25);
	this->baseRect = rect;
	this->arrow = this->GetArrow();
	VERIFY(radius >= 0);
	VERIFY(radius <= 3);
	CBrush onB(RGB(220, 250, 0));
	CPen pen;
	pen.CreatePen(PS_SOLID, 2, RGB(15, 15, 0));
	CBrush b(RGB(20, 20, 0));
	pDC->SelectObject(&pen);
	switch (radius){
	case 0:
		this->ins[0] = CRect(rect.left - 15, (rect.top + rect.bottom) / 2 - 5, rect.left - 5, (rect.top + rect.bottom) / 2 + 5);
		break;
	case 1:
		this->ins[0] = CRect((rect.left + rect.right) / 2 - 3, rect.top - 18, (rect.left + rect.right) / 2 + 7, rect.top - 8);
		break;
	case 2:
		this->ins[0] = CRect(rect.right + 5, (rect.top + rect.bottom) / 2 - 5, rect.right + 15, (rect.top + rect.bottom) / 2 + 5);
		break;
	case 3:
		this->ins[0] = CRect((rect.left + rect.right) / 2 - 5, rect.bottom + 8, (rect.left + rect.right) / 2 + 5, rect.bottom + 18);
		break;
	}
	pDC->SelectObject(&b);
	pDC->Ellipse(this->ins[0]);
	auto& db = SingleTon<GaiaDrawGrid>::use()->dBoard;
	if (db[this->ins[0].CenterPoint().x / 10][this->ins[0].CenterPoint().y / 10] == 1){
		pDC->SelectObject(&onB);
	}
	else{
		pDC->SelectStockObject(WHITE_BRUSH);
	}
	CRect rect2;
	rect2.SetRect(rect.left + 1, rect.top + 1, rect.right - 1, rect.bottom - 1);
	pDC->Ellipse(&rect2);
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
	font.DeleteObject();
	pen.DeleteObject();
	onB.DeleteObject();
}

void OutLamp::Calculate(){
	auto& db = SingleTon<GaiaDrawGrid>::use()->dBoard;
	auto& edges = SingleTon<GaiaDrawGrid>::use()->edges;
	for (int i = 0; i < edges.size(); i++){
		if (this->ins[0].PtInRect(edges[i].first.second)){
			db[ins[0].CenterPoint().x / 10][ins[0].CenterPoint().y / 10] = db[edges[i].first.first.x / 10][edges[i].first.first.y / 10];
		}
		else if (this->ins[0].PtInRect(edges[i].first.first)){
			db[ins[0].CenterPoint().x / 10][ins[0].CenterPoint().y / 10] = db[edges[i].first.second.x / 10][edges[i].first.second.y / 10];
		}
	}
}
IMPLEMENT_SERIAL(OutLamp, GaiaLLogic, 15)
void OutLamp::Serialize(CArchive& ar){
	GaiaLLogic::Serialize(ar);
}