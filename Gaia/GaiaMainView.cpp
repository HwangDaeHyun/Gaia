#include "stdafx.h"
#include "Gaia.h"
#include "GaiaMainView.h"

IMPLEMENT_DYNCREATE(GaiaMainView, GaiaCView)
GaiaMainView::GaiaMainView()
{
}


GaiaMainView::~GaiaMainView()
{
}
void GaiaMainView::DrawSplitterBar() {
	this->OnNcPaint();
}
BEGIN_MESSAGE_MAP(GaiaMainView, GaiaCView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_NCPAINT()
END_MESSAGE_MAP()

void GaiaMainView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.
}


// GaiaMainView 진단입니다.

#ifdef _DEBUG
void GaiaMainView::AssertValid() const
{
	GaiaCView::AssertValid();
}

#ifndef _WIN32_WCE
void GaiaMainView::Dump(CDumpContext& dc) const
{
	GaiaCView::Dump(dc);
}
#endif
#endif //_DEBUG


// GaiaMainView 메시지 처리기입니다.


int GaiaMainView::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	if (GaiaCView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	if (!this->m_wndSplitter.CreateStatic(this, 1, 3)) {
		return FALSE;
	}
	SingleTon<GaiaLayoutRepo>::use()->SetspView(&this->m_wndSplitter);
	CCreateContext context;
	context.m_pCurrentDoc = this->GetDocument();
	this->m_gaiaSheetView = new GaiaSheetView;
	this->m_gaiaToolView = new GaiaToolView;
	this->m_gaiaDrawView = new GaiaDrawView;
	SingleTon<GaiaLayoutRepo>::use()->views.push_back(this->m_gaiaSheetView);
	SingleTon<GaiaLayoutRepo>::use()->views.push_back(this->m_gaiaToolView);
	SingleTon<GaiaLayoutRepo>::use()->views.push_back(this->m_gaiaDrawView);
	this->m_gaiaSheetView->Create(nullptr, _T("sheetview"), WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), &this->m_wndSplitter, m_wndSplitter.IdFromRowCol(0, 0), (CCreateContext*)&context);
	this->m_gaiaToolView->Create(nullptr, _T("toolview"), WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), &this->m_wndSplitter, m_wndSplitter.IdFromRowCol(0, 2), (CCreateContext*)&context);
	this->m_gaiaDrawView->Create(nullptr, _T("drawview"), WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), &this->m_wndSplitter, m_wndSplitter.IdFromRowCol(0, 1), (CCreateContext*)&context);
	this->m_gaiaSheetView->SendMessage(WM_INITIALUPDATE);
	this->m_gaiaToolView->SendMessage(WM_INITIALUPDATE);
	this->m_gaiaDrawView->SendMessage(WM_INITIALUPDATE);
	this->ModifyStyle(WS_BORDER, NULL);
	return 0;
}


void GaiaMainView::OnDestroy() {
	GaiaCView::OnDestroy();
	if (this->m_gaiaSheetView != nullptr){
		delete this->m_gaiaSheetView;
	}
	if (this->m_gaiaToolView != nullptr){
		delete this->m_gaiaToolView;
	}
	if (this->m_gaiaDrawView != nullptr){
		delete this->m_gaiaDrawView;
	}
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


void GaiaMainView::OnSize(UINT nType, int cx, int cy) {
	GaiaCView::OnSize(nType, cx, cy);
	if (m_wndSplitter.GetSafeHwnd() != NULL) {
		m_wndSplitter.SetWindowPos(this, 0, 0, cx, cy, SWP_NOACTIVATE | SWP_NOZORDER | SWP_NOREDRAW);
		CRect rect;
		this->GetClientRect(&rect);
		m_wndSplitter.SetColumnInfo(0, SingleTon<GaiaSheetListRepo>::use()->Getwidth() - 10, 0);
		m_wndSplitter.SetColumnInfo(1, SingleTon<GaiaToolListRepo>::use()->Getwidth() - 10, 0);
		m_wndSplitter.RecalcLayout();
	}
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


void GaiaMainView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 GaiaCView::OnPaint()을(를) 호출하지 마십시오.
	CBrush brush(SingleTon<GaiaLayoutRepo>::use()->Getrightside());
	CRect rect;
	this->GetClientRect(&rect);
	dc.FillRect(&rect, &brush);

	brush.DeleteObject();
}


void GaiaMainView::OnNcPaint()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 GaiaCView::OnNcPaint()을(를) 호출하지 마십시오.

}
