#pragma once
#ifndef GAIA_LLOGIC_H_INCLUDE
#define GAIA_LLOGIC_H INCLUDE
#include"stdafx.h"
#include"SingleTon.h"
#include"GaiaRepo.h"
#include"GaiaObject.h"
typedef int BOARD[GSIZE][GSIZE];
typedef int DBOARD[GSIZE][GSIZE];
class GaiaLLogic : public GaiaObject {
public:
	//vector<int> inputs;

	static vector<int> outputs;
public:
	virtual void SetPoint(CPoint p)override;
	virtual void SetPoint(int x, int y)override;
	//¿©±â
	virtual void SetPoint()override;

	virtual void ClearPoint() override;
	virtual void Calculate()override{}
	virtual void Draw(CDC* pDC)override{}
};

bool DblCompare(double a, double b);
void DrawWay(CDC* pDC, deque<CRect>& way, bool b = true);
CPoint MediatePoint(CPoint& point);
void UpdateLines();
deque<CRect> DrawEdge(CDC* pDC, DblPoint _pt, CWnd* view, BOOL ad = TRUE);
void PaintGrid(CPoint pt, bool b = true);
void UpdateDBoard();
void Update(CRect& out);
vector<int>* SearchObjects(CDC* pDC, CRect bound);
#endif