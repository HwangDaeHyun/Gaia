#pragma once
#include"GaiaCView.h"
#include"GaiaRepo.h"
// GaiaToolView ���Դϴ�.

class GaiaToolView : public GaiaCView
{
	DECLARE_DYNCREATE(GaiaToolView)

public:
	GaiaToolView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~GaiaToolView();
	int lighting = -1;
public:
	void DrawSplitterBar()override;
	virtual void OnDraw(CDC* pDC);      // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
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
};


