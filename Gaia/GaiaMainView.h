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
	GaiaView* m_gaiaSheetView;
	GaiaView* m_gaiaToolView;
	GaiaView* m_gaiaDrawView;
	GaiaSplitterWnd m_wndSplitter;
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
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
};
#ifndef _DEBUG  // GaiaStudioView.cpp�� ����� ����
inline GaiaDoc* GaiaView::GetDocument() const
{
	return reinterpret_cast<GaiaDoc*>(m_pDocument);
}
#endif


