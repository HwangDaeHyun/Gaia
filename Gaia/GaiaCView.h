#pragma once


// GaiaView ���Դϴ�.

class GaiaCView : public CView
{
	DECLARE_DYNCREATE(GaiaCView)

public:
	GaiaCView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~GaiaCView();

public:
	virtual void DrawSplitterBar();
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
};


