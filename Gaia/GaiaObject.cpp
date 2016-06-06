#include "stdafx.h"
#include "GaiaObject.h"
#include"GaiaRepo.h"

GaiaObject::GaiaObject()
{
	this->basic = RGB(103, 153, 255);
	this->mv = RGB(0, 0, 0);

}
GaiaObject::~GaiaObject()
{
}
void GaiaObject::SetRadius(int r){
	VERIFY(r >= 0);
	VERIFY(r < 4);
	this->radius = r;
}
int GaiaObject::GetLength(){
	int len = 0;
	switch (this->objSize){
	case SMALL:
		return len = SingleTon<GaiaObjectSizeInfo>::use()->GetSmallLength();
	case MID:
		return len = SingleTon<GaiaObjectSizeInfo>::use()->GetLength();

	case BIG:
		return len = SingleTon<GaiaObjectSizeInfo>::use()->GetBigLength();
	case LARG:
		return len = SingleTon<GaiaObjectSizeInfo>::use()->GetLargLength();
	case SUPER:
		return len =  SingleTon<GaiaObjectSizeInfo>::use()->GetSuperLength();	
	default:
		return 0;
	}
}
CString GaiaObject::GetArrow(){
	CString temp;
	switch (this->radius){
	case 0:
		temp = _T("EAST");
		break;
	case 1:
		temp = _T("DOWN");
		break;
	case 2:
		temp = _T("LEFT");
		break;
	case 3:
		temp = _T("UP");
		break;
	default:
		break;
	}
	return temp;
}
void GaiaObject::Draw(CDC* pDC){

}
int GaiaObject::GetRadius(){
	return this->radius;
}

IMPLEMENT_SERIAL(GaiaObject, CObject, 1)
void GaiaObject::Serialize(CArchive& ar){
	CObject::Serialize(ar);
	if (ar.IsStoring()){
		ar << (int)this->objSize;
		ar << (int)this->objKind;
		ar << this->base_point;
		ar << this->name;
		ar << this->arrow;
		ar << this->btn;
		ar << this->radius;
		ar << this->baseRect;
		ar << this->clk;
		ar << this->basic;
		ar << this->mv;
		int outSize = this->outs.size();
		ar << outSize;
		for (int i = 0; i < outSize; i++){
			ar << this->outs[i];
		}
		int insSize = this->ins.size();
		ar << insSize;
		for (int i = 0; i < insSize; i++){
			ar << this->ins[i];
		}
		ar << this->prevC;

		ar << this->in_size;
		ar << this->out_size;
		ar << this->clk_size;
		ar << this->result.size();
		for (int i = 0; i < this->result.size(); i++){
			ar << this->result[i].size();
			for (int j = 0; j < this->result[i].size(); j++){
				ar << this->result[i][j];
			}
		}
		ar << this->clk_result.size();
		for (int i = 0; i < this->clk_result.size(); i++){
			ar << this->clk_result[i].size();
			for (int j = 0; j < this->clk_result[i].size(); j++){
				ar << this->clk_result[i][j];
			}
		}
	}
	else{
		int o_S;	//objectSize
		int o_K;	//objectKind
		ar >> o_S;
		this->objSize = (ObjectSize)o_S;
		ar >> o_K;
		this->objKind = (ObjectKind)o_K;
		CPoint point;
		ar >> this->base_point;
		ar >> this->name;
		ar >> this->arrow;
		ar >> this->btn;
		ar >> this->radius;
		ar >> this->baseRect;
		ar >> this->clk;
		ar >> this->basic;
		ar >> this->mv;
		int outSize;
		this->outs.clear();
		ar >> outSize;
		CRect tempOut;
		for (int i = 0; i < outSize; i++){
			ar >> tempOut;
			this->outs.push_back(tempOut);
		}
		int insSize;
		ar >> insSize;
		CRect tempIn;
		for (int i = 0; i < insSize; i++){
			ar >> tempIn;
			this->ins.push_back(tempIn);
		}
		ar >> prevC;
		ar >> this->in_size;
		ar >> this->out_size;
		ar >> this->clk_size;
		int ResSize;
		ar >> ResSize;
		this->result.assign(ResSize, vector<int>());
		for (int i = 0; i < ResSize; i++){
			int rSize;
			ar >> rSize;
			this->result[i].assign(rSize,0);
			for (int j = 0; j < rSize; j++){
				ar >> this->result[i][j];
			}
		}
		int clkSize;
		ar >> clkSize;
		this->clk_result.assign(clkSize, vector<int>());
		for (int i = 0; i < clkSize; i++){
			int cSize;
			ar >> cSize;
			this->clk_result[i].assign(cSize, 0);
			for (int j = 0; j < cSize; j++){
				ar >> this->clk_result[i][j];
			}
		}
	}
}