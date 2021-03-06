#pragma once
#include"GaiaCView.h"
#include"GaiaRepo.h"
// GaiaToolView 뷰입니다.

class GaiaToolView : public GaiaCView
{
	DECLARE_DYNCREATE(GaiaToolView)

public:
	GaiaToolView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~GaiaToolView();
	int lighting = -1;
public:
	vector<CRect> infosRect;
	void DrawGraph(Graphics* graphics, int y);
	void DrawSplitterBar()override;
	virtual void OnDraw(CDC* pDC);      // 이 뷰를 그리기 위해 재정의되었습니다.
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNcPaint();
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
};


