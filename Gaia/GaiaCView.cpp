// GaiaCView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Gaia.h"
#include "GaiaCView.h"


// GaiaCView

IMPLEMENT_DYNCREATE(GaiaCView, CView)

GaiaCView::GaiaCView()
{

}

GaiaCView::~GaiaCView()
{
}

BEGIN_MESSAGE_MAP(GaiaCView, CView)
END_MESSAGE_MAP()


// GaiaCView 그리기입니다.

void GaiaCView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.
}


// GaiaCView 진단입니다.

#ifdef _DEBUG
void GaiaCView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void GaiaCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// GaiaCView 메시지 처리기입니다.
