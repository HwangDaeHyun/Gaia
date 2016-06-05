#include"stdafx.h"
#include"JKFF.h"
#include"Resource.h"
//#include"GaiaObject.h"
JKFF::JKFF(){
	this->ins.assign(2, CRect());
	this->outs.assign(2, CRect());
	this->objKind = JKFLIP;
	this->objSize = MID;
	this->name = _T("JK-FlipFlop");
	this->arrow = this->GetArrow();
	this->inputGraph.assign(1, deque<int>());
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
		bmp.LoadBitmapW(IDB_DFF);
		//
		//this->ins[0].SetRect(rect.left - 10, (rect.bottom + rect.top) / 2 + 5, rect.left, (rect.bottom + rect.top) / 2 + 15);
		//this->clk.SetRect(rect.left - 10, (rect.bottom + rect.top) / 2 - 15, rect.left, (rect.bottom + rect.top) / 2 - 5);
		//this->outs[0] = CRect(rect.right - 5, (rect.bottom + rect.top) / 2 - 15, rect.right + 5, (rect.bottom + rect.top) / 2 - 5);
		//this->outs[1] = CRect(rect.right - 5, (rect.bottom + rect.top) / 2 + 5, rect.right + 5, (rect.bottom + rect.top) / 2 + 15);
		break;
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	}
	static_assert(sizeof(int) == sizeof(LONG), "�� �÷����� ���������ʽ��ϴ�.");
	BITMAP bmpinfo;
	bmp.GetBitmap(&bmpinfo);
	memDC.SelectObject(&bmp);
	pDC->TransparentBlt(this->base_point.x, this->base_point.y, 60, 60, &memDC, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, RGB(0, 0, 0));
	//���ڸ� �׸��ϴ�

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
IMPLEMENT_SERIAL(JKFF, GaiaLLogic, 2)
void JKFF::Serialize(CArchive& ar){
	GaiaLLogic::Serialize(ar);
}