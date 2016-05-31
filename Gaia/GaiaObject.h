#pragma once
#include"stdafx.h"
#include<algorithm>
#include"SingleTon.h"
using namespace design_pattern;
enum ObjectSize{SMALL, MID, BIG};
static class{
	int length;
	int sLen;		//small length
	int bLen;		//big length
public:
	void SetLength(int l){
		this->length = l;
	}
	int GetLength(){
		return this->length;
	}
	void SetSmallLength(int l){
		this->sLen = l;
	}
	int GetSmallLength(){
		return this->sLen;
	}
	void SetBigLength(int l){
		this->bLen = l;
	}
	int GetBigLength(){
		return this->bLen;
	}
}GaiaObjectSize = {};

class GaiaObject{
public:
	ObjectSize objSize = MID;
	CPoint base_point;
	int radius = 0; //{0,1,2,3};
	bool btn = false;
	int outCnt = 0; // out 에 연결된 선들의 수;
	CString name;
	CString arrow;
public:
	CRect out, in1, in2;
	CRect clk = CRect();			//클럭
	int prevC = -1;
	//vector<CRect> inputs;
	//	vector<int> inValues;
	int outValue = -1;
	CRect baseRect;
	COLORREF basic;
	COLORREF mv;

public:
	GaiaObject();
	virtual ~GaiaObject();
	virtual void SetPoint(CPoint p){}
	virtual void SetPoint(int x, int y){}
	virtual void SetPoint(){}
	virtual void ClearPoint(){}
	virtual void Calculate(){}
	virtual void Draw(CDC* pDC);
	void SetRadius(int r = 0);
	int GetLength(){
		int len = 0;
		switch (this->objSize){
		case SMALL:
			return len = GaiaObjectSize.GetSmallLength();
			
		case MID:
			return len = GaiaObjectSize.GetLength();
			
		case BIG:
			return len = GaiaObjectSize.GetBigLength();
		
		default:
			return 0;
		}
		
	}
	CString GetArrow(){
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
};


