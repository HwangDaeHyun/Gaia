#include"stdafx.h"
#include"AndGate.h"
#include"Resource.h"
AndGate::AndGate(){
	this->ins.assign(2, CRect());
	this->outs.assign(1, CRect());
	this->name = _T("AND");
	this->arrow = this->GetArrow();
	this->objKind = AND;
	this->objSize = MID;
	this->inputGraph.assign(2, deque<int>());
	this->outputGraph.assign(1, deque<int>());
}
void AndGate::Draw(CDC* pDC){
	CRect rect(this->base_point.x, this->base_point.y, this->base_point.x + this->GetLength() * 10 - 20, this->base_point.y + this->GetLength() * 10 - 20);
	this->baseRect = rect;
	this->arrow = GetArrow();
	VERIFY(radius >= 0);
	VERIFY(radius <= 3);
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CBitmap bmp;
	switch (radius){
	case 0:
		bmp.LoadBitmapW(IDB_AND_0);
		this->outs[0] = CRect(rect.right, (rect.bottom + rect.top) / 2 - 5, rect.right + 10, (rect.bottom + rect.top) / 2 + 5);
		this->ins[0] = CRect(rect.left - 10, (rect.bottom + rect.top) / 2 - 25, rect.left, (rect.bottom + rect.top) / 2 - 15);
		this->ins[1] = CRect(rect.left - 10, (rect.bottom + rect.top) / 2 + 15, rect.left, (rect.bottom + rect.top) / 2 + 25);
		//여기
		break;
	case 1:
		bmp.LoadBitmapW(IDB_AND_90);
		this->outs[0] = CRect((rect.left + rect.right) / 2 - 5, rect.bottom - 3, (rect.left + rect.right) / 2 + 5, rect.bottom + 7);
		this->ins[0] = CRect((rect.left + rect.right) / 2 - 25, rect.top - 10, (rect.left + rect.right) / 2 - 15, rect.top);
		this->ins[1] = CRect((rect.left + rect.right) / 2 + 15, rect.top - 10, (rect.left + rect.right) / 2 + 25, rect.top);
		break;
	case 2:
		bmp.LoadBitmapW(IDB_AND_180);
		this->outs[0] = CRect(rect.left - 5, (rect.bottom + rect.top) / 2 - 5, rect.left + 5, (rect.bottom + rect.top) / 2 + 5);
		this->ins[0] = CRect(rect.right + 5, (rect.bottom + rect.top) / 2 - 25, rect.right + 15, (rect.bottom + rect.top) / 2 - 15);
		this->ins[1] = CRect(rect.right + 5, (rect.bottom + rect.top) / 2 + 15, rect.right + 15, (rect.bottom + rect.top) / 2 + 25);
		break;
	case 3:
		bmp.LoadBitmapW(IDB_AND_270);
		this->outs[0] = CRect((rect.left + rect.right) / 2 - 5, rect.top - 5, (rect.left + rect.right) / 2 + 5, rect.top + 5);
		this->ins[0] = CRect((rect.left + rect.right) / 2 - 25, rect.bottom, (rect.left + rect.right) / 2 - 15, rect.bottom + 10);
		this->ins[1] = CRect((rect.left + rect.right) / 2 + 15, rect.bottom, (rect.left + rect.right) / 2 + 25, rect.bottom + 10);
		break;

	}
	static_assert(sizeof(int) == sizeof(LONG), "이 플랫폼은 지원하지않습니다.");
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

		pDC->MoveTo(ins[1].left + ins[1].Width() / 2, (ins[1].top + ins[1].bottom) / 2);
		pDC->LineTo(ins[1].right, (ins[1].top + ins[1].bottom) / 2);
		break;
	case 1:
		pDC->MoveTo((outs[0].left + outs[0].right) / 2, outs[0].top);
		pDC->LineTo(outs[0].right - outs[0].Width() / 2, (outs[0].top + outs[0].bottom) / 2);

		pDC->MoveTo((ins[0].left + ins[0].right) / 2, ins[0].top + ins[0].Height() / 2);
		pDC->LineTo((ins[0].left + ins[0].right) / 2, ins[0].top);

		pDC->MoveTo((ins[1].left + ins[1].right) / 2, ins[1].top + ins[1].Height() / 2);
		pDC->LineTo((ins[1].left + ins[1].right) / 2, ins[1].top);
		break;
	case 2:
		pDC->MoveTo(outs[0].left, (outs[0].top + outs[0].bottom) / 2);
		pDC->LineTo(outs[0].right - outs[0].Width() / 2, (outs[0].top + outs[0].bottom) / 2);

		pDC->MoveTo(ins[0].left, (ins[0].top + ins[0].bottom) / 2);
		pDC->LineTo(ins[0].right - ins[0].Width() / 2, (ins[0].top + ins[0].bottom) / 2);

		pDC->MoveTo(ins[1].left, (ins[1].top + ins[1].bottom) / 2);
		pDC->LineTo(ins[1].right - ins[1].Width() / 2, (ins[1].top + ins[1].bottom) / 2);
		break;
	case 3:
		pDC->MoveTo((outs[0].left + outs[0].right) / 2, outs[0].top);
		pDC->LineTo(outs[0].right - outs[0].Width() / 2, (outs[0].top + outs[0].bottom) / 2);

		pDC->MoveTo((ins[0].left + ins[0].right) / 2, ins[0].top + ins[0].Height() / 2);
		pDC->LineTo((ins[0].left + ins[0].right) / 2, ins[0].top);

		pDC->MoveTo((ins[1].left + ins[1].right) / 2, ins[1].top + ins[1].Height() / 2);
		pDC->LineTo((ins[1].left + ins[1].right) / 2, ins[1].top);
	}
	pen2.DeleteObject();
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
	pDC->SetTextColor(RGB(250, 250, 250));
	pDC->SetBkMode(TRANSPARENT);
	pDC->DrawText(this->name, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	font.DeleteObject();
}
void AndGate::Calculate(){
	auto& db = SingleTon<GaiaDrawGrid>::use()->dBoard;
	if (db[this->ins[0].CenterPoint().x / 10][this->ins[0].CenterPoint().y / 10] == 0){
		db[this->outs[0].CenterPoint().x / 10][this->outs[0].CenterPoint().y / 10] = 0;
	}
	else if (db[this->ins[1].CenterPoint().x / 10][this->ins[1].CenterPoint().y / 10] == 0){
		db[this->outs[0].CenterPoint().x / 10][this->outs[0].CenterPoint().y / 10] = 0;
	}
	else if (db[this->ins[0].CenterPoint().x / 10][this->ins[0].CenterPoint().y / 10] == 1 && db[this->ins[1].CenterPoint().x / 10][this->ins[1].CenterPoint().y / 10] == 1){
		db[this->outs[0].CenterPoint().x / 10][this->outs[0].CenterPoint().y / 10] = 1;
	}
	else{
		db[this->outs[0].CenterPoint().x / 10][this->outs[0].CenterPoint().y / 10] = -1;
	}
	if (inputGraph[0].size() > 15 || inputGraph[1].size() > 15 || outputGraph[0].size() > 15){
		inputGraph[0].clear();
		outputGraph[0].clear();
		inputGraph[1].clear();
	}
	if (!inputGraph[0].empty() && !inputGraph[1].empty() && !outputGraph[0].empty()){
		if (inputGraph[0].back() == db[this->ins[0].CenterPoint().x / 10][this->ins[0].CenterPoint().y / 10] &&
			inputGraph[1].back() == db[this->ins[1].CenterPoint().x / 10][this->ins[1].CenterPoint().y / 10] &&
			outputGraph[0].back() == db[this->outs[0].CenterPoint().x / 10][this->outs[0].CenterPoint().y / 10]
			){
			return;
		}
	}
	if (db[this->ins[0].CenterPoint().x / 10][this->ins[0].CenterPoint().y / 10] == -1 && db[this->ins[1].CenterPoint().x / 10][this->ins[1].CenterPoint().y / 10] == -1 && db[this->outs[0].CenterPoint().x / 10][this->outs[0].CenterPoint().y / 10] == -1){
		return;
	}

	inputGraph[0].push_back(db[this->ins[0].CenterPoint().x / 10][this->ins[0].CenterPoint().y / 10]);
	inputGraph[1].push_back(db[this->ins[1].CenterPoint().x / 10][this->ins[1].CenterPoint().y / 10]);
	outputGraph[0].push_back(db[this->outs[0].CenterPoint().x / 10][this->outs[0].CenterPoint().y / 10]);
}
IMPLEMENT_SERIAL(AndGate, GaiaLLogic, 2)
void AndGate::Serialize(CArchive& ar){
	GaiaLLogic::Serialize(ar);
}