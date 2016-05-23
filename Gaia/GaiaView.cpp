
// GaiaView.cpp : GaiaView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "Gaia.h"
#endif

#include "GaiaDoc.h"
#include "GaiaView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// GaiaView

IMPLEMENT_DYNCREATE(GaiaView, CView)

BEGIN_MESSAGE_MAP(GaiaView, CView)
END_MESSAGE_MAP()

// GaiaView ����/�Ҹ�

GaiaView::GaiaView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

GaiaView::~GaiaView()
{
}

BOOL GaiaView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// GaiaView �׸���

void GaiaView::OnDraw(CDC* /*pDC*/)
{
	GaiaDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}


// GaiaView ����

#ifdef _DEBUG
void GaiaView::AssertValid() const
{
	CView::AssertValid();
}

void GaiaView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

GaiaDoc* GaiaView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(GaiaDoc)));
	return (GaiaDoc*)m_pDocument;
}
#endif //_DEBUG


// GaiaView �޽��� ó����
