#pragma once
#include"stdafx.h"
#include<algorithm>
#include"SingleTon.h"
using namespace design_pattern;
static class{
	int length;
public :
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
	int ior;	//in,out의 동그라미 반지름
public:
	CRect out, in1, in2;
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
	virtual void Draw(CDC* pDC);
	void SetRadius(int r);
};


