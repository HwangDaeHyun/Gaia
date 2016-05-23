#pragma once
#include "GaiaRepo.h"
#include "GaiaCView.h"
#include"GaiaSplitterWnd.h"
#include"GaiaSheetView.h"
#include"GaiaToolView.h"
#include"GaiaDrawView.h"
class GaiaMainView : public GaiaCView
{
	DECLARE_DYNCREATE(GaiaMainView)
public:
	GaiaMainView();
	virtual ~GaiaMainView();
protected:
	GaiaCView* m_gaiaSheetView;
	GaiaCView* m_gaiaToolView;
	GaiaCView* m_gaiaDrawView;
	GaiaSplitterWnd m_wndSplitter;
public:
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
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnNcPaint();
};


