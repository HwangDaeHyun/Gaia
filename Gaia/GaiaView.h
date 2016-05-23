
// GaiaView.h : GaiaView Ŭ������ �������̽�
//

#pragma once
#include"GaiaSplitterWnd.h"
#include"GaiaCView.h"
#include"GaiaMainView.h"
#include"GaiaMenuView.h"
class GaiaView : public CView
{
protected: // serialization������ ��������ϴ�.
	GaiaView();
	DECLARE_DYNCREATE(GaiaView)

// Ư���Դϴ�.
public:
	GaiaDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	GaiaSplitterWnd m_wndSplitter;
	GaiaCView* m_mainview;
	GaiaCView* m_menuview;
// �����Դϴ�.
public:
	virtual ~GaiaView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
};

#ifndef _DEBUG  // GaiaView.cpp�� ����� ����
inline GaiaDoc* GaiaView::GetDocument() const
   { return reinterpret_cast<GaiaDoc*>(m_pDocument); }
#endif

