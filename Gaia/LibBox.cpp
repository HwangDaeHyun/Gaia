
#include "stdafx.h"
#include "LibBox.h"
#include <cmath>

LibBox::LibBox()
{
	mkLib();
	this->mx_sz = this->in_size > this->out_size ? this->in_size : this->out_size;
	if (mx_sz < 4){
		this->objSize = MID;
	}
	else if (mx_sz < 6){
		this->objSize = BIG;
	}
	else if (mx_sz < 9){
		this->objSize = LARG;
	}
	this->objKind = LIBBOX;
	this->ins.assign(this->in_size, CRect());
	this->outs.assign(this->out_size, CRect());
	this->name = _T("LibBox");
	
}
LibBox::LibBox(CString name)
{
	mkLib();
	this->mx_sz = this->in_size > this->out_size ? this->in_size : this->out_size;
	if (mx_sz < 4){
		this->objSize = BIG;
	}
	else if (mx_sz < 6){
		this->objSize = BIG;
	}
	else if (mx_sz < 9){
		this->objSize = LARG;
	}
	this->objKind = LIBBOX;
	this->ins.assign(this->in_size, CRect());
	this->outs.assign(this->out_size, CRect());
	this->name = name;
}

LibBox::LibBox(int sel){
	auto& lib = SingleTon<GaiaDrawGrid>::use()->lib_objects;
	this->result = lib[sel]->result;
	this->clk_result = lib[sel]->clk_result;
	this->in_size = lib[sel]->in_size;
	this->out_size = lib[sel]->out_size;
	this->clk_size = lib[sel]->clk_size;
	this->mx_sz = this->in_size > this->out_size ? this->in_size : this->out_size;
	this->objSize = lib[sel]->objSize;
	this->objKind = LIBBOX;
	this->lib_h = lib[sel]->lib_h;
	this->lib_w = lib[sel]->lib_w;
	if (mx_sz > 3){
		this->lib_h = mx_sz * 3;
	}
	this->ins.assign(this->in_size, CRect());
	this->outs.assign(this->out_size, CRect());
	this->name = lib[sel]->name;
}

void LibBox::Draw(CDC* pDC)
{
	CRect rect(this->base_point.x + 5, this->base_point.y + 5, this->base_point.x + this->GetLength() * 10 - 15, this->base_point.y + this->GetLength() * 10 - 15);
	this->baseRect = rect;
	CBrush b(RGB(0, 128, 255));
	pDC->SelectObject(&b);
	pDC->Rectangle(rect);
	switch (this->radius){
	case 0:	// 0
		for (int i = 0; i < this->ins.size(); i++) {	//input
			this->ins[i] = CRect(rect.left - 20, rect.top + 17 * (i + 1), rect.left - 10, rect.top + (i + 1) * 17 + 10);
			pDC->MoveTo(this->ins[i].left + 5, (this->ins[i].top + this->ins[i].bottom) / 2);
			pDC->LineTo(this->ins[i].right + 5, (this->ins[i].top + this->ins[i].bottom) / 2);
			//pDC->Ellipse(this->ins[i]);
		}
		for (int i = 0; i < this->outs.size(); i++) {
			this->outs[i] = CRect(rect.right + 17, rect.top + ((i + 1) * 17) + 5, rect.right + 27, rect.top + 15 + ((i + 1) * 17));
			pDC->MoveTo(this->outs[i].left - 13, (this->outs[i].top + this->outs[i].bottom) / 2 - 1);
			pDC->LineTo(this->outs[i].right - 7, (this->outs[i].top + this->outs[i].bottom) / 2 - 1);
			//pDC->Ellipse(this->outs[i]);
		}
		if (this->clk_size != 0){
			this->clk = CRect((rect.left + rect.right) / 2, rect.top - 15, ((rect.left + rect.right) / 2) + 10, rect.top - 5);
			pDC->Ellipse(this->clk);
		}
		break;
	case 1:	// 90
		for (int i = 0; i < this->ins.size(); i++) {	//input
			this->ins[i] = CRect(rect.left + 17 * (i + 1), rect.top - 15, rect.left + 17 * (i + 1) + 10, rect.top - 5);
			pDC->MoveTo((this->ins[i].left + this->ins[i].right) / 2, this->ins[i].top + 5);
			pDC->LineTo((this->ins[i].left + this->ins[i].right) / 2, this->ins[i].bottom);
			//pDC->Ellipse(this->ins[i]);
		}
		for (int i = 0; i < this->outs.size(); i++) {
			this->outs[i] = CRect(rect.left + 17 * (i + 1), rect.bottom + 15, rect.left + 17 * (i + 1) + 10, rect.bottom + 25);
			pDC->MoveTo((this->outs[i].left + this->outs[i].right) / 2 - 5, this->outs[i].top - 10);
			pDC->LineTo((this->outs[i].left + this->outs[i].right) / 2 - 5, this->outs[i].bottom - 10);
			//pDC->Ellipse(this->outs[i]);
		}
		if (this->clk_size != 0){
			this->clk = CRect(rect.right + 10, (rect.top + rect.bottom) / 2, rect.right + 20, (rect.top + rect.bottom) / 2 + 10);
			pDC->Ellipse(this->clk);
		}
		break;
	case 2:	//180
		for (int i = 0; i < this->ins.size(); i++) {	//input
			this->ins[i] = CRect(rect.right + 10, rect.top + 17 * (i + 1), rect.right + 20, rect.top + (i + 1) * 17 + 10);
			pDC->MoveTo(this->ins[i].left - 10, (this->ins[i].top + this->ins[i].bottom) / 2 - 1);
			pDC->LineTo(this->ins[i].right - 7, (this->ins[i].top + this->ins[i].bottom) / 2 - 1);
			//pDC->Ellipse(this->ins[i]);
		}
		for (int i = 0; i < this->outs.size(); i++) {
			this->outs[i] = CRect(rect.left - 30, rect.top + ((i + 1) * 17) + 5, rect.left - 20, rect.top + 15 + ((i + 1) * 17));
			pDC->MoveTo(this->outs[i].left + 15, (this->outs[i].top + this->outs[i].bottom) / 2);
			pDC->LineTo(this->outs[i].right + 15, (this->outs[i].top + this->outs[i].bottom) / 2);
			//pDC->Ellipse(this->outs[i]);
		}
		if (this->clk_size != 0){
			this->clk = CRect((rect.left + rect.right) / 2, rect.bottom + 10, ((rect.left + rect.right) / 2) + 10, rect.bottom + 20);
			pDC->Ellipse(this->clk);
		}
		break;
	case 3:	//270
		for (int i = 0; i < this->ins.size(); i++) {	//input
			this->ins[i] = CRect(rect.left + 17 * (i + 1), rect.bottom + 10, rect.left + 17 * (i + 1) + 10, rect.bottom + 20);
			pDC->MoveTo((this->ins[i].left + this->ins[i].right) / 2, this->ins[i].top - 10);
			pDC->LineTo((this->ins[i].left + this->ins[i].right) / 2, this->ins[i].bottom - 10);
			//pDC->Ellipse(this->ins[i]);
		}
		for (int i = 0; i < this->outs.size(); i++) {
			this->outs[i] = CRect(rect.left + 17 * (i + 1), rect.top - 30, rect.left + 17 * (i + 1) + 10, rect.top - 20);
			pDC->MoveTo((this->outs[i].left + this->outs[i].right) / 2 - 5, this->outs[i].top + 7);
			pDC->LineTo((this->outs[i].left + this->outs[i].right) / 2 - 5, this->outs[i].bottom + 10);
			//pDC->Ellipse(this->outs[i]);
		}
		if (this->clk_size != 0){
			this->clk = CRect(rect.left - 20, (rect.top + rect.bottom) / 2, rect.left - 10, (rect.top + rect.bottom) / 2 + 10);
			pDC->Ellipse(this->clk);
		}
		break;
	}


	//글자를 그립니다
	CFont font;
	font.CreateFont(15,        // 글자높이
		8,                     // 글자너비
		0,                     // 출력각도
		0,                     // 기준 선에서의각도
		FW_HEAVY,              // 글자굵기
		FALSE,                 // Italic 적용여부
		FALSE,                 // 밑줄적용여부
		FALSE,                 // 취소선적용여부
		DEFAULT_CHARSET,       // 문자셋종류
		OUT_DEFAULT_PRECIS,    // 출력정밀도
		CLIP_DEFAULT_PRECIS,   // 클리핑정밀도
		DEFAULT_QUALITY,       // 출력문자품질
		DEFAULT_PITCH,         // 글꼴Pitch
		_T("Time New Romans")  // 글꼴
		);
	pDC->SelectObject(&font);
	pDC->SetTextColor(RGB(200, 250, 200));
	pDC->SetBkMode(TRANSPARENT);
	pDC->DrawText(this->name, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}
void LibBox::Calculate(){
	vector<int> inCase;
	auto& db = SingleTon<GaiaDrawGrid>::use()->dBoard;
	inCase.assign(this->ins.size(), 0);
	for (int i = 0; i < this->ins.size(); i++){
		inCase[i] = db[this->ins[i].CenterPoint().x / 10][this->ins[i].CenterPoint().y / 10] + 1;
	}
	int cnt = 0;
	for (int i = 0; i < inCase.size(); i++){
		for (int j = 1; j < i + 1; j++){
			inCase[i] = inCase[i] * 3;
		}
		cnt = cnt + inCase[i];
	}
	if (this->clk_size != 0){
		if (this->prevC == 0 && db[this->clk.CenterPoint().x / 10][this->clk.CenterPoint().y / 10] == 1){
			for (int i = 0; i < this->outs.size(); i++){
				db[this->outs[i].CenterPoint().x / 10][this->outs[i].CenterPoint().y / 10] = this->clk_result[i][cnt];
			}
		}

		this->prevC = db[this->clk.CenterPoint().x / 10][this->clk.CenterPoint().y / 10];
	}
	else{
		for (int i = 0; i < this->outs.size(); i++){
			db[this->outs[i].CenterPoint().x / 10][this->outs[i].CenterPoint().y / 10] = result[i][cnt];
		}
	}
}
void LibBox::mkLib(){
	vector<CRect> cal_in;		//input 들의 위치
	vector<CRect> cal_out;		//out
	CRect cal_clk;				//clk
	auto& obj = SingleTon<GaiaDrawGrid>::use()->objects;
	auto& s = SingleTon<GaiaDrawGrid>::use()->sel_objects;
	auto& db = SingleTon<GaiaDrawGrid>::use()->dBoard;
	auto& edge = SingleTon<GaiaDrawGrid>::use()->edges;
	for (int i = 0; i < s.size(); i++){
		if (s[i]->objKind == INBUTTON){
			for (int j = 0; j < edge.size(); j++){
				if (s[i]->outs[0].PtInRect(edge[j].first.first)) {
					for (int k = 0; k < s.size(); k++){
						if (s[k]->clk.PtInRect(edge[j].first.second)){	//버튼 중 clk과 연결된 버튼을 찾습니다.
							cal_clk = s[k]->clk;
							this->clk_size++;
							goto COME;
						}
					}
				}
			}
			cal_in.push_back(s[i]->outs[0]);
			this->in_size++;
		}
		else if (s[i]->objKind == OUTLAMP){
			cal_out.push_back(s[i]->ins[0]);
			this->out_size++;
		}
	COME: {};
	}
	int tempPrev = -1;
	int nCase = (int)pow(3, this->clk_size + this->in_size);
	this->result.assign(this->out_size, vector<int>(nCase, -1));
	if (this->clk_size != 0){	// input에 clk이 있는경우
		clk_result.assign(this->out_size, vector<int>(nCase, -1));
		db[cal_clk.CenterPoint().x / 10][cal_clk.CenterPoint().y / 10] = 1;
		for (int i = 0; i < this->result.size(); i++){
			for (int j = 0; j < this->result[i].size(); j++){
				int temp_j = j;
				for (int k = 0; k < cal_in.size(); k++){
					db[cal_in[k].CenterPoint().x / 10][cal_in[k].CenterPoint().y / 10] = (temp_j % 3) - 1;
					temp_j = temp_j / 3;
					Update(cal_in[k]);
				}
				db[cal_clk.CenterPoint().x / 10][cal_clk.CenterPoint().y / 10] = 0;
				for (auto& o : obj){
					UpdateDBoard();
				}
				//
				printf("input : %d   ", db[cal_in[0].CenterPoint().x / 10][cal_in[0].CenterPoint().y / 10]);
				//
				this->result[i][j] = db[cal_out[i].CenterPoint().x / 10][cal_out[i].CenterPoint().y / 10];
				printf("result : %d   ", this->result[i][j]);
				db[cal_clk.CenterPoint().x / 10][cal_clk.CenterPoint().y / 10] = 1;
				
				for (auto& o : obj){
					UpdateDBoard();
				}
				this->clk_result[i][j] = db[cal_out[i].CenterPoint().x / 10][cal_out[i].CenterPoint().y / 10];
				printf("clkret: %d\n\n", this->clk_result[i][j]);
			}
		}

	}
	else{
		for (int i = 0; i < this->result.size(); i++){
			for (int j = 0; j < this->result[i].size(); j++){
				int temp_j = j;
				for (int k = 0; k < cal_in.size(); k++){
					db[cal_in[k].CenterPoint().x / 10][cal_in[k].CenterPoint().y / 10] = (temp_j % 3) - 1;
					temp_j = temp_j / 3;
					Update(cal_in[k]);
					
				}
				UpdateDBoard();
				for (int k = 0; k < cal_in.size(); k++){
					Update(cal_in[k]);
				}

				this->result[i][j] = db[cal_out[i].CenterPoint().x / 10][cal_out[i].CenterPoint().y / 10];
			}
		}
	}
	for (int i = 0; i < cal_out.size(); i++){
		db[cal_out[i].CenterPoint().x / 10][cal_out[i].CenterPoint().y / 10] = -1;
	}
	for (int i = 0; i < cal_in.size(); i++){
		db[cal_in[i].CenterPoint().x / 10][cal_in[i].CenterPoint().y / 10] = -1;
	}
	for (int i = 0; i < cal_in.size(); i++){
		Update(cal_in[i]);
	}
	for (int i = 0; i < cal_out.size(); i++){
		Update(cal_out[i]);
	}
	if (cal_clk != 0){
		db[cal_clk.CenterPoint().x / 10][cal_clk.CenterPoint().y / 10] = -1;
		Update(cal_clk);
	}
	UpdateDBoard();
}

IMPLEMENT_SERIAL(LibBox, GaiaLLogic, 3)
void LibBox::Serialize(CArchive& ar){
	GaiaLLogic::Serialize(ar);
}