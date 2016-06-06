#include"stdafx.h"
#include"TFF.h"
#include"Resource.h"
//#include"GaiaObject.h"
TFF::TFF(){
	this->ins.assign(2, CRect());
	this->outs.assign(2, CRect());
	this->objKind = TFLIP;
	this->objSize = MID;
	this->trigger = RISING;
	this->name = _T("JK-FlipFlop");
	this->arrow = this->GetArrow();
	this->inputGraph.assign(1, deque<int>());
	this->outputGraph.assign(2, deque<int>());

}
void TFF::Draw(CDC* pDC){
	CRect rect(this->base_point.x, this->base_point.y, this->base_point.x + this->GetLength() * 10 - 20, this->base_point.y + this->GetLength() * 10 - 20);
	this->baseRect = rect;

	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CBitmap bmp;
	switch (radius){
	case 0:
		bmp.LoadBitmapW(IDB_TFF_0);
		this->ins[0].SetRect(rect.left - 10, (rect.bottom + rect.top) / 2 + 5, rect.left, (rect.bottom + rect.top) / 2 + 15);
		this->clk.SetRect(rect.left - 10, (rect.bottom + rect.top) / 2 - 15, rect.left, (rect.bottom + rect.top) / 2 - 5);
		this->outs[0] = CRect(rect.right - 5, (rect.bottom + rect.top) / 2 - 15, rect.right + 5, (rect.bottom + rect.top) / 2 - 5);
		this->outs[1] = CRect(rect.right - 5, (rect.bottom + rect.top) / 2 + 5, rect.right + 5, (rect.bottom + rect.top) / 2 + 15);
		break;
	case 1:
		bmp.LoadBitmapW(IDB_TFF_90);
		this->ins[0] = CRect((rect.left + rect.right) / 2 - 25, rect.top - 10, (rect.left + rect.right) / 2 - 15, rect.top);
		this->clk = CRect((rect.left + rect.right) / 2 + 15, rect.top - 10, (rect.left + rect.right) / 2 + 25, rect.top);
		this->outs[0] = CRect((rect.left + rect.right) / 2 - 25, rect.bottom - 3, (rect.left + rect.right) / 2 - 15, rect.bottom + 7);
		this->outs[1] = CRect((rect.left + rect.right) / 2 + 15, rect.bottom - 3, (rect.left + rect.right) / 2 + 25, rect.bottom + 7);
		break;
	case 2:
		bmp.LoadBitmapW(IDB_TFF_180);
		this->ins[0] = CRect(rect.right + 5, (rect.bottom + rect.top) / 2 - 25, rect.right + 15, (rect.bottom + rect.top) / 2 - 15);
		this->clk = CRect(rect.right + 5, (rect.bottom + rect.top) / 2 + 15, rect.right + 15, (rect.bottom + rect.top) / 2 + 25);
		this->outs[0] = CRect(rect.left - 5, rect.top + 5, rect.left + 5, rect.top + 15);
		this->outs[1] = CRect(rect.left - 5, rect.top + 45, rect.left + 5, rect.top + 55);
		break;
	case 3:
		bmp.LoadBitmapW(IDB_TFF_270);
		this->clk = CRect((rect.left + rect.right) / 2 - 25, rect.bottom + 4, (rect.left + rect.right) / 2 - 15, rect.bottom + 14);
		this->ins[0] = CRect((rect.left + rect.right) / 2 + 15, rect.bottom + 4, (rect.left + rect.right) / 2 + 25, rect.bottom + 14);
		this->outs[0] = CRect((rect.left + rect.right) / 2 - 25, rect.top - 5, (rect.left + rect.right) / 2 - 15, rect.top + 5);
		this->outs[1] = CRect((rect.left + rect.right) / 2 + 15, rect.top - 5, (rect.left + rect.right) / 2 + 25, rect.top + 5);
		break;
	}
	static_assert(sizeof(int) == sizeof(LONG), "이 플랫폼은 지원하지않습니다.");
	BITMAP bmpinfo;
	bmp.GetBitmap(&bmpinfo);
	memDC.SelectObject(&bmp);
	pDC->TransparentBlt(this->base_point.x, this->base_point.y, 60, 60, &memDC, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, RGB(0, 0, 0));
	//글자를 그립니다

}
void TFF::Calculate(){
	auto& db = SingleTon<GaiaDrawGrid>::use()->dBoard;
	int tC = this->prevC;

	if (db[this->outs[0].CenterPoint().x / 10][this->outs[0].CenterPoint().y / 10] == -1){
		db[this->outs[0].CenterPoint().x / 10][this->outs[0].CenterPoint().y / 10] = 0;
	}
	int curr = db[this->clk.CenterPoint().x / 10][this->clk.CenterPoint().y / 10];
	if (this->trigger == RISING){
		if (tC == 0 && curr == 1){
			if (db[this->ins[0].CenterPoint().x / 10][this->ins[0].CenterPoint().y / 10] == 1){
				db[this->outs[0].CenterPoint().x / 10][this->outs[0].CenterPoint().y / 10] ^= 1;
				db[this->outs[1].CenterPoint().x / 10][this->outs[1].CenterPoint().y / 10] = db[this->outs[0].CenterPoint().x / 10][this->outs[0].CenterPoint().y / 10] ^ 1;
			}
			else if (db[this->ins[0].CenterPoint().x / 10][this->ins[0].CenterPoint().y / 10] == 0){
				db[this->outs[0].CenterPoint().x / 10][this->outs[0].CenterPoint().y / 10] ^= 1;
				db[this->outs[1].CenterPoint().x / 10][this->outs[1].CenterPoint().y / 10] = db[this->outs[0].CenterPoint().x / 10][this->outs[0].CenterPoint().y / 10] ^ 1;
			}
		}
	}
	else if (this->trigger == FALLING){
		if (tC == 1 && curr == 0){
			if (db[this->ins[0].CenterPoint().x / 10][this->ins[0].CenterPoint().y / 10] == 1){
				db[this->outs[0].CenterPoint().x / 10][this->outs[0].CenterPoint().y / 10] ^= 1;
				db[this->outs[1].CenterPoint().x / 10][this->outs[1].CenterPoint().y / 10] = db[this->outs[0].CenterPoint().x / 10][this->outs[0].CenterPoint().y / 10] ^ 1;
			}
			else if (db[this->ins[0].CenterPoint().x / 10][this->ins[0].CenterPoint().y / 10] == 0){
				db[this->outs[0].CenterPoint().x / 10][this->outs[0].CenterPoint().y / 10] ^= 1;
				db[this->outs[1].CenterPoint().x / 10][this->outs[1].CenterPoint().y / 10] = db[this->outs[0].CenterPoint().x / 10][this->outs[0].CenterPoint().y / 10] ^ 1;
			}
		}
	}
	this->prevC = curr;
	if (inputGraph[0].size() > 15 || clkGraph.size() > 15 || outputGraph[0].size() > 15){
		inputGraph[0].clear();
		outputGraph[0].clear();
		outputGraph[1].clear();
		clkGraph.clear();
	}
	if (!inputGraph[0].empty() && !clkGraph.empty() && !outputGraph[0].empty()){
		if (inputGraph[0].back() == db[this->ins[0].CenterPoint().x / 10][this->ins[0].CenterPoint().y / 10] &&
			clkGraph.back() == db[this->clk.CenterPoint().x / 10][this->clk.CenterPoint().y / 10] &&
			outputGraph[0].back() == db[this->outs[0].CenterPoint().x / 10][this->outs[0].CenterPoint().y / 10]
			){
			return;
		}
	}
	if (db[this->ins[0].CenterPoint().x / 10][this->ins[0].CenterPoint().y / 10] == -1 && db[this->clk.CenterPoint().x / 10][this->clk.CenterPoint().y / 10] == -1){
		return;
	}
	outputGraph[1].push_back(db[this->outs[1].CenterPoint().x / 10][this->outs[1].CenterPoint().y / 10]);
	inputGraph[0].push_back(db[this->ins[0].CenterPoint().x / 10][this->ins[0].CenterPoint().y / 10]);
	clkGraph.push_back(db[this->clk.CenterPoint().x / 10][this->clk.CenterPoint().y / 10]);
	outputGraph[0].push_back(db[this->outs[0].CenterPoint().x / 10][this->outs[0].CenterPoint().y / 10]);
}
IMPLEMENT_SERIAL(TFF, GaiaLLogic, 11)
void TFF::Serialize(CArchive& ar){
	GaiaLLogic::Serialize(ar);
}