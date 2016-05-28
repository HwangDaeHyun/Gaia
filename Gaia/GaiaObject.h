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
enum ObjKind{ AND, OR, NOT, INBTN, OUTBTN, XOR, NOR, D, T, JK, SEG };
class GaiaObject{
public:
	CPoint base_point;
	int radius = 0; //{0,1,2,3};
	ObjKind kind;
	bool btn = false;
	int outCnt = 0; // out 에 연결된 선들의 수;
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
};


