#include"stdafx.h"
#include"JKFF.h"
#include"Resource.h"
//#include"GaiaObject.h"
JKFF::JKFF(){
	this->ins.assign(2, CRect());
	this->outs.assign(2, CRect());
	this->objKind = JKFLIP;
	this->objSize = MID;
	this->trigger = RISING;
	this->name = _T("JK-FlipFlop");
	this->arrow = this->GetArrow();
	this->inputGraph.assign(2, deque<int>());
	this->outputGraph.assign(2, deque<int>());

}
void JKFF::Draw(CDC* pDC){
	CRect rect(this->base_point.x, this->base_point.y, this->base_point.x + this->GetLength() * 10 - 20, this->base_point.y + this->GetLength() * 10 - 20);
	this->baseRect = rect;

	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CBitmap bmp;

	switch (radius){
	case 0:
		bmp.LoadBitmapW(IDB_JKFF_0);
		this->ins[0] = CRect(rect.left - 10, rect.top + 5, rect.left, rect.top + 15);
		this->ins[1] = CRect(rect.left - 10, rect.top + 50, rect.left, rect.top + 60);
		this->outs[0] = CRect(rect.right, rect.top + 5, rect.right + 10, rect.top + 15);
		this->outs[1] = CRect(rect.right, rect.top + 45, rect.right + 10, rect.top + 55);
		this->clk = CRect(rect.left - 10, (rect.top + rect.bottom) / 2 - 5, rect.left, (rect.top + rect.bottom) / 2 + 5);
		break;
	case 1:
//		bmp.LoadBitmapW(IDB_JKFF_90);
		this->ins[0] = CRect((rect.left + rect.right) / 2 - 30, rect.top - 10, (rect.left + rect.right) / 2 - 20, rect.top);
		this->ins[1] = CRect((rect.left + rect.right) / 2 + 20, rect.top - 10, (rect.left + rect.right) / 2 + 30, rect.top);
		this->outs[0] = CRect((rect.left + rect.right) / 2 - 25, rect.bottom - 3, (rect.left + rect.right) / 2 - 15, rect.bottom + 7);
		this->outs[1] = CRect((rect.left + rect.right) / 2 + 15, rect.bottom - 3, (rect.left + rect.right) / 2 + 25, rect.bottom + 7);
		this->clk = CRect((rect.left + rect.right) / 2 - 5, rect.top - 10, (rect.left + rect.right) / 2 + 5, rect.top);
		break;
	case 2:
	//	bmp.LoadBitmapW(IDB_JKFF_180);
		this->ins[0] = CRect(rect.right + 5, rect.top + 5, rect.right + 15, rect.top + 15);
		this->ins[1] = CRect(rect.right + 5, rect.top + 50, rect.right + 15, rect.top + 60);
		this->outs[0] = CRect(rect.left - 5, rect.top + 5, rect.left + 5, rect.top + 15);
		this->outs[1] = CRect(rect.left - 5, rect.top + 45, rect.left + 5, rect.top + 55);
		this->clk = CRect(rect.right + 5, (rect.top + rect.bottom) / 2 - 5, rect.right + 15, (rect.top + rect.bottom) / 2 + 5);
		break;
	case 3:
	//	bmp.LoadBitmapW(IDB_JKFF_270);
		this->ins[0] = CRect((rect.left + rect.right) / 2 - 30, rect.bottom + 5, (rect.left + rect.right) / 2 - 20, rect.bottom + 15);
		this->ins[1] = CRect((rect.left + rect.right) / 2 + 20, rect.bottom + 5, (rect.left + rect.right) / 2 + 30, rect.bottom + 15);
		this->outs[0] = CRect((rect.left + rect.right) / 2 - 25, rect.top - 5, (rect.left + rect.right) / 2 - 15, rect.top + 5);
		this->outs[1] = CRect((rect.left + rect.right) / 2 + 15, rect.top - 5, (rect.left + rect.right) / 2 + 25, rect.top + 5);
		this->clk = CRect((rect.left + rect.right) / 2 - 5, rect.bottom + 5, (rect.left + rect.right) / 2 + 5, rect.bottom + 15);
		break;
	}
	pDC->Ellipse(this->ins[0]);
	pDC->Ellipse(this->outs[0]);
	pDC->Ellipse(this->ins[1]);
	pDC->Ellipse(this->outs[1]);
	pDC->Ellipse(this->clk);

	static_assert(sizeof(int) == sizeof(LONG), "이 플랫폼은 지원하지않습니다.");
	BITMAP bmpinfo;
	bmp.GetBitmap(&bmpinfo);
	memDC.SelectObject(&bmp);
	pDC->TransparentBlt(this->base_point.x, this->base_point.y, 60, 60, &memDC, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, RGB(0, 0, 0));
	//글자를 그립니다

}
void JKFF::Calculate(){
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

	if (!inputGraph[0].empty() && !clkGraph.empty() && !outputGraph[0].empty()){
		if (inputGraph[0].back() == db[this->ins[0].CenterPoint().x / 10][this->ins[0].CenterPoint().y / 10] &&
			clkGraph.back() == db[this->clk.CenterPoint().x / 10][this->clk.CenterPoint().y / 10] &&
			outputGraph[0].back() == db[this->outs[0].CenterPoint().x / 10][this->outs[0].CenterPoint().y / 10]
			){
			return;
		}
	}
	if (db[this->ins[0].CenterPoint().x / 10][this->ins[0].CenterPoint().y / 10] == -1 && db[this->clk.CenterPoint().x / 10][this->clk.CenterPoint().y / 10] == -1 && db[this->outs[0].CenterPoint().x / 10][this->outs[0].CenterPoint().y / 10] == -1){
		return;
	}
	outputGraph[1].push_back(db[this->outs[1].CenterPoint().x / 10][this->outs[1].CenterPoint().y / 10]);
	inputGraph[0].push_back(db[this->ins[0].CenterPoint().x / 10][this->ins[0].CenterPoint().y / 10]);
	clkGraph.push_back(db[this->clk.CenterPoint().x / 10][this->clk.CenterPoint().y / 10]);
	outputGraph[0].push_back(db[this->outs[0].CenterPoint().x / 10][this->outs[0].CenterPoint().y / 10]);
}
IMPLEMENT_SERIAL(JKFF, GaiaLLogic, 10)
void JKFF::Serialize(CArchive& ar){
	GaiaLLogic::Serialize(ar);
}