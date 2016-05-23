#pragma once
#include"GaiaRepo.h"
#include"GaiaCView.h"

// GaiaSheetView ���Դϴ�.

class GaiaSheetView : public GaiaCView
{
	DECLARE_DYNCREATE(GaiaSheetView)

protected:
	GaiaSheetView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~GaiaSheetView();

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
};


