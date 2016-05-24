// GaiaSheetView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Gaia.h"
#include "GaiaSheetView.h"


// GaiaSheetView
using namespace design_pattern;
IMPLEMENT_DYNCREATE(GaiaSheetView, GaiaCView)

GaiaSheetView::GaiaSheetView()
{

}

GaiaSheetView::~GaiaSheetView()
{
}
void GaiaSheetView::DrawSplitterBar() {
	this->OnNcPaint();
}
BEGIN_MESSAGE_MAP(GaiaSheetView, GaiaCView)
	ON_WM_NCPAINT()
	ON_WM_PAINT()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// GaiaSheetView 그리기입니다.

void GaiaSheetView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.
}


// GaiaSheetView 진단입니다.

#ifdef _DEBUG
void GaiaSheetView::AssertValid() const
{
	GaiaCView::AssertValid();
}

#ifndef _WIN32_WCE
void GaiaSheetView::Dump(CDumpContext& dc) const
{
	GaiaCView::Dump(dc);
}
#endif
#endif //_DEBUG


// GaiaSheetView 메시지 처리기입니다.


void GaiaSheetView::OnNcPaint()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 GaiaGaiaCView::OnNcPaint()을(를) 호출하지 마십시오.
	CWindowDC dc(::AfxGetMainWnd());
	CBrush brush(SingleTon<GaiaLayoutRepo>::use()->Getleftside());
	CRect sheetRect;
	CRect temp;
	this->GetWindowRect(&sheetRect);
	sheetRect.NormalizeRect();
	sheetRect.OffsetRect(-sheetRect.left, -sheetRect.top);
	int captionHeight = ::GetSystemMetrics(SM_CYCAPTION) + ::GetSystemMetrics(SM_CYFRAME) + 5;
	sheetRect.OffsetRect(8, captionHeight);
	sheetRect.right += 10;
	sheetRect.bottom += 7;
	temp = sheetRect;
	temp.bottom = temp.top + 5;
	dc.FillRect(&temp, &brush);		//위쪽 스플린터바 색칠
	temp = sheetRect;
	temp.right = temp.left + 6;
	dc.FillRect(&temp, &brush);		//왼쪽 스플린터바 색칠
	temp = sheetRect;
	temp.top = temp.bottom - 4;
	dc.FillRect(&temp, &brush);		//아래쪽 스플린터바 색칠
	temp = sheetRect;
	temp.left = temp.right - 4;
	dc.FillRect(&temp, &brush);		//오른쪽 스플린터바 색칠
	brush.DeleteObject();
}


void GaiaSheetView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 GaiaGaiaCView::OnPaint()을(를) 호출하지 마십시오.
	CBrush brush(SingleTon<GaiaLayoutRepo>::use()->Getleftside());
	CRect rect;
	this->GetClientRect(&rect);
	dc.FillRect(&rect, &brush);

	brush.DeleteObject();
}


void GaiaSheetView::OnSize(UINT nType, int cx, int cy)
{
	GaiaCView::OnSize(nType, cx, cy);
	if (cx > 0){
		SingleTon<GaiaSheetListRepo>::use()->Setwidth(cx + 10);
	}
	else if (SingleTon<GaiaLayoutRepo>::use()->GetspView() != nullptr  && cx<300){

		SingleTon<GaiaSheetListRepo>::use()->Setwidth(200);
		SingleTon<GaiaLayoutRepo>::use()->GetspView()->SetColumnInfo(0, SingleTon<GaiaSheetListRepo>::use()->Getwidth() - 10, 0);
		SingleTon<GaiaLayoutRepo>::use()->GetspView()->SetColumnInfo(1, SingleTon<GaiaDrawListRepo>::use()->Getwidth() - 10, 0);
		auto v = SingleTon<GaiaLayoutRepo>::use()->GetspView();
		auto b = v->GetSafeHwnd();
		static int i = 0;
		i++;
		if (i > 1){
			v->RecalcLayout();
		}
	}

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}
