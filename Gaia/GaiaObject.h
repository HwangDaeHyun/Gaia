#pragma once
#include"stdafx.h"
#include<algorithm>
#include<vector>
#include<deque>
#include"SingleTon.h"

using namespace design_pattern;
enum ObjectSize{ SMALL, MID, BIG, LARG };
enum ObjectKind{ NOTTHING, AND, OR, NOT, NAND, XOR, NOR, DFLIP, TFLIP, JKFLIP, INBUTTON, OUTLAMP, CLOCKCYCLE,SEVENSEG, LIBBOX };
enum ObjectTrigger{NOTCLK, RISING , FALLING};
class GaiaObject : public CObject{
	DECLARE_SERIAL(GaiaObject)
public:
	virtual void Serialize(CArchive& ar);
public:
	int lib_h;
	int lib_w;
	ObjectSize objSize = MID;
	ObjectKind objKind = NOTTHING;
	ObjectTrigger trigger = NOTCLK;
	CPoint base_point;
	CString name;
	CString arrow;
	bool btn = false;
	int radius = 0; //{0,1,2,3};
public:
	int in_size = 0;
	int out_size = 0;
	int clk_size = 0;
	int mx_sz;
	vector<vector<int>> result;
	vector<vector<int>> clk_result;
public:
	CRect baseRect;
	CRect clk = CRect();			//Å¬·°
	COLORREF basic;
	COLORREF mv;
	vector<CRect> outs;
	vector<CRect> ins;
	int prevC = -1;
	vector<deque<int>> inputGraph;
	vector<deque<int>> outputGraph;
	deque<int> clkGraph = deque<int>();
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
	int GetRadius();
	CString GetArrow();
};

