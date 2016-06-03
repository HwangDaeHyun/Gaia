#pragma once
#include"stdafx.h"
#include<algorithm>
#include<vector>
#include"SingleTon.h"

using namespace design_pattern;
enum ObjectSize{ SMALL, MID, BIG };
enum ObjectKind{ NOTTHING, AND, OR, NOT, NAND,XOR,NOR , DFLIP,TFLIP,JKFLIP, INBUTTON, OUTLAMP, SEVENSEG };

class GaiaObject : public CObject{
	DECLARE_SERIAL(GaiaObject)
public:
	virtual void Serialize(CArchive& ar);
public:
	ObjectSize objSize = MID;
	ObjectKind objKind = NOTTHING;
	CPoint base_point;
	CString name;
	CString arrow;
	bool btn = false;
	int radius = 0; //{0,1,2,3};
public:
	CRect baseRect;
	CRect clk = CRect();			//Å¬·°
	COLORREF basic;
	COLORREF mv;
	vector<CRect> outs;
	vector<CRect> ins;
	int prevC = -1;

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

