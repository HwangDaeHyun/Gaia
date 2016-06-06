#include"stdafx.h"
#include"NotGate.h"
#include"Resource.h"

NotGate::NotGate(){
	this->ins.assign(1, CRect());
	this->outs.assign(1, CRect());
	this->name = _T("NOT");
	this->arrow = this->GetArrow();
	this->objKind = NOT;
	this->objSize = MID;
	this->inputGraph.assign(1, deque<int>());
	this->outputGraph.assign(1, deque<int>());
}
void NotGate::Draw(CDC* pDC){
	CRect rect(this->base_point.x, this->base_point.y, this->base_point.x + this->GetLength() * 10 - 20, this->base_point.y + this->GetLength() * 10 - 20);
	this->baseRect = rect;
	this->arrow = this->GetArrow();
	VERIFY(radius >= 0);
	VERIFY(radius <= 3);
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CBitmap bmp;
	switch (radius){
	case 0:
		bmp.LoadBitmapW(IDB_NOT_0);
		this->outs[0] = CRect(rect.right + 3, (rect.bottom + rect.top) / 2 - 5, rect.right + 13, (rect.bottom + rect.top) / 2 + 5);
		this->ins[0] = CRect(rect.left - 10, (rect.bottom + rect.top) / 2 - 5, rect.left, (rect.bottom + rect.top) / 2 + 3);
		//����
		break;
	case 1:
		bmp.LoadBitmapW(IDB_NOT_90);
		this->outs[0] = CRect((rect.left + rect.right) / 2 - 5, rect.bottom + 3, (rect.left + rect.right) / 2 + 5, rect.bottom + 13);
		this->ins[0] = CRect((rect.left + rect.right) / 2 - 5, rect.top - 10, (rect.left + rect.right) / 2 + 5, rect.top);
		break;
	case 2:
		bmp.LoadBitmapW(IDB_NOT_180);
		this->outs[0] = CRect(rect.left - 5, (rect.bottom + rect.top) / 2 - 5, rect.left + 5, (rect.bottom + rect.top) / 2 + 5);
		this->ins[0] = CRect(rect.right + 3, (rect.bottom + rect.top) / 2 - 5, rect.right + 13, (rect.bottom + rect.top) / 2 + 5);
		break;
	case 3:
		bmp.LoadBitmapW(IDB_NOT_270);
		this->outs[0] = CRect((rect.left + rect.right) / 2 - 5, rect.top - 5, (rect.left + rect.right) / 2 + 5, rect.top + 5);
		this->ins[0] = CRect((rect.left + rect.right) / 2 - 5, rect.bottom + 3, (rect.left + rect.right) / 2 + 5, rect.bottom + 13);
		break;

	}
	static_assert(sizeof(int) == sizeof(LONG), "�� �÷����� ���������ʽ��ϴ�.");
	BITMAP bmpinfo;
	bmp.GetBitmap(&bmpinfo);
	memDC.SelectObject(&bmp);
	pDC->TransparentBlt(this->base_point.x, this->base_point.y, 60, 60, &memDC, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, RGB(0, 0, 0));
	CPen pen2;
	pen2.CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
	pDC->SelectObject(pen2);
	switch (radius){
	case 0:
		pDC->MoveTo(outs[0].left, (outs[0].top + outs[0].bottom) / 2);
		pDC->LineTo(outs[0].right - outs[0].Width() / 2, (outs[0].top + outs[0].bottom) / 2);

		pDC->MoveTo(ins[0].left + ins[0].Width() / 2, (ins[0].top + ins[0].bottom) / 2);
		pDC->LineTo(ins[0].right, (ins[0].top + ins[0].bottom) / 2);
		break;
	case 1:
		pDC->MoveTo((outs[0].left + outs[0].right) / 2, outs[0].top);
		pDC->LineTo(outs[0].right - outs[0].Width() / 2, (outs[0].top + outs[0].bottom) / 2);

		pDC->MoveTo((ins[0].left + ins[0].right) / 2, ins[0].top + ins[0].Height() / 2);
		pDC->LineTo((ins[0].left + ins[0].right) / 2, ins[0].top);
		break;
	case 2:
		pDC->MoveTo(outs[0].left, (outs[0].top + outs[0].bottom) / 2);
		pDC->LineTo(outs[0].right - outs[0].Width() / 2, (outs[0].top + outs[0].bottom) / 2);

		pDC->MoveTo(ins[0].left, (ins[0].top + ins[0].bottom) / 2);
		pDC->LineTo(ins[0].right - ins[0].Width() / 2, (ins[0].top + ins[0].bottom) / 2);
		break;
	case 3:
		pDC->MoveTo((outs[0].left + outs[0].right) / 2, outs[0].top);
		pDC->LineTo(outs[0].right - outs[0].Width() / 2, (outs[0].top + outs[0].bottom) / 2);

		pDC->MoveTo((ins[0].left + ins[0].right) / 2, ins[0].top + ins[0].Height() / 2);
		pDC->LineTo((ins[0].left + ins[0].right) / 2, ins[0].top);
	}
	pen2.DeleteObject();
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
	pDC->SetTextColor(RGB(250, 250, 250));
	pDC->SetBkMode(TRANSPARENT);
	pDC->DrawText(this->name, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	font.DeleteObject();
}
void NotGate::Calculate(){
	auto& db = SingleTon<GaiaDrawGrid>::use()->dBoard;
	if (db[this->ins[0].CenterPoint().x / 10][this->ins[0].CenterPoint().y / 10] == 1){
		db[this->outs[0].CenterPoint().x / 10][this->outs[0].CenterPoint().y / 10] = 0;
	}
	else if (db[this->ins[0].CenterPoint().x / 10][this->ins[0].CenterPoint().y / 10] == 0){
		db[this->outs[0].CenterPoint().x / 10][this->outs[0].CenterPoint().y / 10] = 1;
	}
	else{
		db[this->outs[0].CenterPoint().x / 10][this->outs[0].CenterPoint().y / 10] = -1;
	}
	if (inputGraph[0].size() > 15 || outputGraph[0].size() > 15){
		inputGraph[0].clear();
		outputGraph[0].clear();
	}
	if (!inputGraph[0].empty() && !outputGraph[0].empty()){
		if (inputGraph[0].back() == db[this->ins[0].CenterPoint().x / 10][this->ins[0].CenterPoint().y / 10] &&
			outputGraph[0].back() == db[this->outs[0].CenterPoint().x / 10][this->outs[0].CenterPoint().y / 10]
			){
			return;
		}
	}
	if (db[this->ins[0].CenterPoint().x / 10][this->ins[0].CenterPoint().y / 10] == -1 && db[this->outs[0].CenterPoint().x / 10][this->outs[0].CenterPoint().y / 10] == -1){
		return;
	}
	inputGraph[0].push_back(db[this->ins[0].CenterPoint().x / 10][this->ins[0].CenterPoint().y / 10]);
	outputGraph[0].push_back(db[this->outs[0].CenterPoint().x / 10][this->outs[0].CenterPoint().y / 10]);
}
IMPLEMENT_SERIAL(NotGate, GaiaLLogic, 6)
void NotGate::Serialize(CArchive& ar){
	GaiaLLogic::Serialize(ar);
}