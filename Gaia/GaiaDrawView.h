#pragma once
#include "GaiaCView.h"
#include "SingleTon.h"
#include "GaiaRepo.h"
class GaiaDrawView :
	public GaiaCView
{
	DECLARE_DYNCREATE(GaiaDrawView)

public:
	GaiaDrawView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~GaiaDrawView();
protected:
	BOOL isLDown = FALSE;
	DblPoint curr;
	deque<CRect> way;
	int sel = -1;
	CPoint clickPoint;
	CPoint clickBase;
public:
	vector<PDV> tempEdges;
	deque<PDV> plusWays;
	int inIdx1 = -1;
	int inIdx2 = -1;
	vector<int> prevData;
	int sIdx1 = -1;
	int sIdx2 = -1;
	void DrawSplitterBar()override;
	virtual void OnDraw(CDC* pDC);      // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif
protected:
	void DrawImageCenter(CDC* pDC) {

	}
	void DrawArea(CDC* pDC);
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnNcPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
};

