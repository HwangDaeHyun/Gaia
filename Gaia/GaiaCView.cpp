// GaiaCView.cpp : ���� �����Դϴ�.
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


// GaiaCView �׸����Դϴ�.

void GaiaCView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: ���⿡ �׸��� �ڵ带 �߰��մϴ�.
}


// GaiaCView �����Դϴ�.

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


// GaiaCView �޽��� ó�����Դϴ�.
