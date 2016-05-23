#pragma once
#ifndef GOEUN_EDITOR_GAIA_LLOGIC_H_INCLUDE
#define GOEUN_EDITOR_GAIA_LLOGIC_H INCLUDE
#include"stdafx.h"
#include"SingleTon.h"
#include"GaiaRepo.h"
#include"GaiaObject.h"
typedef int BOARD[GSIZE][GSIZE];
class GaiaLLogic : public GaiaObject {
public:
public:
	void SetPoint(CPoint p)override;
	void SetPoint(int x, int y)override;
	void SetPoint()override;
	void ClearPoint()override;
	void Draw(CDC* pDC)override{}
};
deque<CRect> DrawEdge(CDC* pDC, DblPoint _pt, CWnd* view, BOOL ad = TRUE);
bool DblCompare(double a, double b);
void DrawWay(CDC* pDC, deque<CRect>& way, bool b = true);
#endif