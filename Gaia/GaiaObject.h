#pragma once
#include"stdafx.h"
#include<algorithm>
#include<vector>
#include"SingleTon.h"

using namespace design_pattern;
enum ObjectSize{ SMALL, MID, BIG };
enum ObjectKind{ NOTTHING, GATE, FF, INBUTTON, OUTPUT };

class GaiaObject{
public:
	ObjectSize objSize = MID;
	ObjectKind objKind = NOTTHING;
	CPoint base_point;
	CString name;
	CString arrow;
	bool btn = false;
	int outCnt = 0; // out �� ����� ������ ��;
	int radius = 0; //{0,1,2,3};
public:
	CRect baseRect;
	CRect clk = CRect();			//Ŭ��
	COLORREF basic;
	COLORREF mv;
	vector<CRect> outs;
	vector<CRect> ins;
	int prevC = -1;
	int outValue = -1;
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
	int GetLength();
	CString GetArrow();
};

