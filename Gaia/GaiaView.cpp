
// GaiaView.cpp : GaiaView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
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

// GaiaView 생성/소멸

GaiaView::GaiaView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

GaiaView::~GaiaView()
{
}

BOOL GaiaView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// GaiaView 그리기

void GaiaView::OnDraw(CDC* /*pDC*/)
{
	GaiaDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// GaiaView 진단

#ifdef _DEBUG
void GaiaView::AssertValid() const
{
	CView::AssertValid();
}

void GaiaView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

GaiaDoc* GaiaView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(GaiaDoc)));
	return (GaiaDoc*)m_pDocument;
}
#endif //_DEBUG


// GaiaView 메시지 처리기


int GaiaView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
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
		m_wndSplitter.SetRowInfo(0, max(rect.Height() - 80, 0), 0);	//높이 계산
		m_wndSplitter.RecalcLayout();
	}
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
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
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}
