#pragma once
#include "GaiaCView.h"
#include "SingleTon.h"
#include "GaiaRepo.h"

class GaiaDrawView :
	public GaiaCView
{
	DECLARE_DYNCREATE(GaiaDrawView)

public:
	GaiaDrawView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~GaiaDrawView();
protected:
	GaiaObject* drawObj;
	BOOL isLDown = FALSE;
	DblPoint curr;
	deque<CRect> way;
	int sel = -1;
	bool isDrag = false;
	CPoint clickPoint;
	CRect draggedRect;
	CPoint clickBase;
	int sel_index = -1;
	BOOL isSelec = FALSE;
public:
	vector<PDV> tempEdges;
	deque<PDV> plusWays;
	vector<int> inIdx, s_inIdx;
	vector<int> outIdx, s_outIdx;
	vector<pair<int, int>> tempOut;
	vector<pair<int, int>> s_tempOut;
	int clkIdx = -1;
	vector<int> prevData;
	CPoint dragSrc;
	//CRect& draggedRect;
	CRect DrawDragRect(CDC& bDC, CPoint leftTop, CPoint rightBottm);
	void MoveLogic(CDC& bDC, bool& possible);
	void AddingLogic(CDC& bDC, CPoint point);
	void StartClock(int index);
	void DrawSplitterBar()override;
	virtual void OnDraw(CDC* pDC);      // 이 뷰를 그리기 위해 재정의되었습니다.
	void OnCopy();
	void OnCut();
	void OnPaste();
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
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

