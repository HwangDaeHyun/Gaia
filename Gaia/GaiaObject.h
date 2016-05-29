#pragma once
#include"stdafx.h"
#include<algorithm>
#include"SingleTon.h"
using namespace design_pattern;
static class{
	int length;
public:
	void SetLength(int l){
		this->length = l;
	}
	int GetLength(){
		return this->length;
	}
}GaiaObjectSize = {};

class GaiaObject{
public:
	CPoint base_point;
	int radius = 0; //{0,1,2,3};
	bool btn = false;
	int outCnt = 0; // out 에 연결된 선들의 수;
	CString name;
	CString arrow;
public:
	CRect out, in1, in2;
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


