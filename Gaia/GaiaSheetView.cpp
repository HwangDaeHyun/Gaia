// GaiaSheetView.cpp : ���� �����Դϴ�.
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


// GaiaSheetView �׸����Դϴ�.

void GaiaSheetView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: ���⿡ �׸��� �ڵ带 �߰��մϴ�.
}


// GaiaSheetView �����Դϴ�.

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


// GaiaSheetView �޽��� ó�����Դϴ�.


void GaiaSheetView::OnNcPaint()
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	// �׸��� �޽����� ���ؼ��� GaiaGaiaCView::OnNcPaint()��(��) ȣ������ ���ʽÿ�.
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
	dc.FillRect(&temp, &brush);		//���� ���ø��͹� ��ĥ
	temp = sheetRect;
	temp.right = temp.left + 6;
	dc.FillRect(&temp, &brush);		//���� ���ø��͹� ��ĥ
	temp = sheetRect;
	temp.top = temp.bottom - 4;
	dc.FillRect(&temp, &brush);		//�Ʒ��� ���ø��͹� ��ĥ
	temp = sheetRect;
	temp.left = temp.right - 4;
	dc.FillRect(&temp, &brush);		//������ ���ø��͹� ��ĥ
	brush.DeleteObject();
}


void GaiaSheetView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	// �׸��� �޽����� ���ؼ��� GaiaGaiaCView::OnPaint()��(��) ȣ������ ���ʽÿ�.
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

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}
