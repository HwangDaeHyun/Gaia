
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
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_DESTROY()
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


int GaiaView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.
	if (!this->m_wndSplitter.CreateStatic(this, 2, 1)) {
		return FALSE;
	}
	this->m_wndSplitter.SetLock();
	CCreateContext context;
	context.m_pCurrentDoc = this->GetDocument();
	this->m_mainview = new GaiaMainView;
	this->m_menuview = new GaiaMenuView;
	SingleTon<GaiaLayoutRepo>::use()->views.push_back(this->m_mainview);
	SingleTon<GaiaLayoutRepo>::use()->views.push_back(this->m_menuview);
	this->m_mainview->Create(nullptr, _T("mainview"), WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), &this->m_wndSplitter, m_wndSplitter.IdFromRowCol(0, 0), (CCreateContext*)&context);

	this->m_menuview->Create(nullptr, _T("menuview"), WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), &this->m_wndSplitter, m_wndSplitter.IdFromRowCol(1, 0), (CCreateContext*)&context);

	this->m_mainview->SendMessage(WM_INITIALUPDATE);
	this->m_menuview->SendMessage(WM_INITIALUPDATE);

	this->ModifyStyle(WS_BORDER, NULL);
	return 0;
}


void GaiaView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	if (m_wndSplitter.GetSafeHwnd() != NULL) {
		m_wndSplitter.SetWindowPos(this, 0, 0, cx, cy, SWP_NOACTIVATE | SWP_NOZORDER | SWP_NOREDRAW);
		CRect rect;
		this->GetClientRect(&rect);
		m_wndSplitter.SetRowInfo(0, max(rect.Height() - 80, 0), 0);	//���� ���
		m_wndSplitter.RecalcLayout();
	}
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}


void GaiaView::OnDestroy()
{
	CView::OnDestroy();
	if (this->m_mainview != nullptr){
		delete this->m_mainview;
	}
	if (this->m_menuview != nullptr){
		delete this->m_menuview;
	}
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}
