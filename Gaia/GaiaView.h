
// GaiaView.h : GaiaView 클래스의 인터페이스
//

#pragma once
#include"GaiaSplitterWnd.h"
#include"GaiaCView.h"
#include"GaiaMainView.h"
#include"GaiaMenuView.h"
class GaiaView : public CView
{
protected: // serialization에서만 만들어집니다.
	GaiaView();
	DECLARE_DYNCREATE(GaiaView)

// 특성입니다.
public:
	GaiaDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	GaiaSplitterWnd m_wndSplitter;
	GaiaCView* m_mainview;
	GaiaCView* m_menuview;
// 구현입니다.
public:
	virtual ~GaiaView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
};

#ifndef _DEBUG  // GaiaView.cpp의 디버그 버전
inline GaiaDoc* GaiaView::GetDocument() const
   { return reinterpret_cast<GaiaDoc*>(m_pDocument); }
#endif

