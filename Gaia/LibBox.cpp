
#include "stdafx.h"
#include "LibBox.h"
#include <cmath>

LibBox::LibBox()
{
	mkLib();
	this->mx_sz = this->in_size > this->out_size ? this->in_size : this->out_size;
	this->objSize = LIB;
	this->objKind = LIBBOX;
	this->lib_h = 8;
	this->lib_w = 8;
	if (mx_sz > 3){
		this->lib_h = mx_sz * 3;
	}
	this->ins.assign(this->in_size, CRect());
	this->outs.assign(this->out_size, CRect());
	this->name = _T("LibBox");
}
LibBox::LibBox(CString name)
{
	mkLib();
	this->mx_sz = this->in_size > this->out_size ? this->in_size : this->out_size;
	this->objSize = LIB;
	this->lib_h = 8;
	this->lib_w = 8;
	if (this->radius % 2 == 0){// 0, 180
		if (mx_sz > 3){
			this->lib_h = mx_sz * 3;
		}
	}
	else{// 90, 270
		if (mx_sz > 3){
			this->lib_w = mx_sz * 3;
		}
	}
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
	this->objSize = LIB;
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
	CRect rect(this->base_point.x, this->base_point.y, this->base_point.x + this->lib_w * 10 - 10 + 1, this->base_point.y + this->lib_h * 10 - 10 + 1);
	CRect rec(this->base_point.x, this->base_point.y, this->base_point.x + this->lib_h * 10 - 10 + 1, this->base_point.y + this->lib_w * 10 - 10 + 1);
	int temp;
	switch (this->radius){
	case 0:	// 0
		this->baseRect = rect;
		pDC->RoundRect(rect, CPoint(5, 5));
		for (int i = 0; i < this->ins.size(); i++) {	//input
			this->ins[i] = CRect(rect.left - 10, rect.top + 20 * (i + 1), rect.left, rect.top + (i + 1) * 20 + 10);
			pDC->Ellipse(this->ins[i]);
		}
		for (int i = 0; i < this->outs.size(); i++) {
			this->outs[i] = CRect(rect.right, rect.top + ((i + 1) * 20) + 5, rect.right + 10, rect.top + 15 + ((i + 1) * 20));
			pDC->Ellipse(this->outs[i]);
		}
		if (this->clk_size != 0){
			this->clk = CRect((rect.left + rect.right) / 2, rect.top - 10, ((rect.left + rect.right) / 2) + 10, rect.top);
			pDC->Ellipse(this->clk);
		}
		break;
	case 1:	// 90
		this->baseRect = rec;
		pDC->RoundRect(rec, CPoint(5, 5));
		for (int i = 0; i < this->ins.size(); i++){	//input
			//	CBrush b(RGB(255, 0, 0));
			//	pDC->FillRect(rect, &b);
			//this->ins[i] = CRect(this->baseRect.left - 10, this->baseRect.top + 20 * (i + 1), this->baseRect.left, this->baseRect.top + (i + 1) * 20 + 10);
			this->ins[i] = CRect(rec.left + 20 * (i + 1), rec.top - 20, rec.left + 20 * (i + 1) + 20, rec.top - 10);
			//this->ins[i] = CRect(rec.left - 10, rec.top + 20 * (i + 1), rec.left, rec.top + (i + 1) * 20 + 10);
			pDC->Ellipse(this->ins[i]);
		}
		for (int i = 0; i < this->outs.size(); i++){
			//this->outs[i] = CRect(rect.right, rect.top + ((i + 1) * 20) + 10, rect.right + 10, rect.top + 20 + ((i + 1) * 20));
			//this->outs[i] = CRect(rec.top, rec.left + ((i + 1) * 20) + 10, rec.top + 10, rec.left + 20 + ((i + 1) * 20));
			this->outs[i] = CRect(rec.right, rec.top + ((i + 1) * 20) + 5, rec.right + 10, rec.top + 15 + ((i + 1) * 20));
			pDC->Ellipse(this->outs[i]);
		}
		if (this->clk_size != 0){
			this->clk = CRect(rec.right + 10, ((rec.top + rec.bottom) / 2) + 10, rec.right + 20, ((rec.top + rec.bottom) / 2) + 20);
			pDC->Ellipse(this->clk);
		}
		break;
	case 2:	//180
		this->baseRect = rect;
		pDC->RoundRect(rect, CPoint(5, 5));
		for (int i = 0; i < this->ins.size(); i++){	//input
			//this->ins[i] = CRect(this->baseRect.left - 10, this->baseRect.top + 20 * (i + 1), this->baseRect.left, this->baseRect.top + (i + 1) * 20 + 10);
			this->ins[i] = CRect(this->baseRect.right, this->baseRect.top + 20 * (i + 1), this->baseRect.right + 10, this->baseRect.top + (i + 1) * 20 + 10);
			pDC->Ellipse(this->ins[i]);
		}
		for (int i = 0; i < this->outs.size(); i++){
			// this->outs[i] = CRect(rect.right, rect.top + ((i + 1) * 20) + 10, rect.right + 10, rect.top + 20 + ((i + 1) * 20));
			this->outs[i] = CRect(this->baseRect.left - 20, rect.top + ((i + 1) * 20) + 10, this->baseRect.left - 10, rect.top + 20 + ((i + 1) * 20));
			pDC->Ellipse(this->outs[i]);
		}
		if (this->clk_size != 0){
			this->clk = CRect((rect.left + rect.right) / 2, this->baseRect.bottom - 10, ((rect.left + rect.right) / 2) + 10, this->baseRect.bottom);
			pDC->Ellipse(this->clk);
		}
		break;
	case 3:	//270
		temp = this->lib_h;
		this->lib_h = this->lib_w;
		this->lib_w = temp;
		this->baseRect = rec;
		pDC->RoundRect(rec, CPoint(5, 5));
		for (int i = 0; i < this->ins.size(); i++){	//input
			//this->ins[i] = CRect(this->baseRect.top - 10, this->baseRect.left + 20 * (i + 1), this->baseRect.top, this->baseRect.left + (i + 1) * 20 + 10);
			this->ins[i] = CRect(this->baseRect.bottom - 10, this->baseRect.left + 20 * (i + 1), this->baseRect.bottom, this->baseRect.left + (i + 1) * 20 + 10);
			pDC->Ellipse(this->ins[i]);
		}
		for (int i = 0; i < this->outs.size(); i++){
			//this->outs[i] = CRect(rect.bottom, rect.left + ((i + 1) * 20) + 10, rect.bottom + 10, rect.left + 20 + ((i + 1) * 20));
			this->outs[i] = CRect(rect.top, rect.left + ((i + 1) * 20) + 10, rect.top + 10, rect.left + 20 + ((i + 1) * 20));
			pDC->Ellipse(this->outs[i]);
		}
		if (this->clk_size != 0){
			this->clk = CRect((rect.top + rect.bottom) / 2, this->baseRect.right - 10, ((rect.top + rect.bottom) / 2) + 10, this->baseRect.right);
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
				this->result[i][j] = db[cal_out[i].CenterPoint().x / 10][cal_out[i].CenterPoint().y / 10];
				db[cal_clk.CenterPoint().x / 10][cal_clk.CenterPoint().y / 10] = 1;
				for (auto& o : obj){
					UpdateDBoard();
				}
				this->clk_result[i][j] = db[cal_out[i].CenterPoint().x / 10][cal_out[i].CenterPoint().y / 10];
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