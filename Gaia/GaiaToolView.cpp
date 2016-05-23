// GaiaToolView.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Gaia.h"
#include "GaiaToolView.h"


// GaiaToolView

IMPLEMENT_DYNCREATE(GaiaToolView, GaiaCView)

GaiaToolView::GaiaToolView()
{

}

GaiaToolView::~GaiaToolView()
{
}

BEGIN_MESSAGE_MAP(GaiaToolView, GaiaCView)
	ON_WM_NCPAINT()
	ON_WM_PAINT()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// GaiaToolView �׸����Դϴ�.

void GaiaToolView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: ���⿡ �׸��� �ڵ带 �߰��մϴ�.
}


// GaiaToolView �����Դϴ�.

#ifdef _DEBUG
void GaiaToolView::AssertValid() const
{
	GaiaCView::AssertValid();
}

#ifndef _WIN32_WCE
void GaiaToolView::Dump(CDumpContext& dc) const
{
	GaiaCView::Dump(dc);
}
#endif
#endif //_DEBUG


// GaiaToolView �޽��� ó�����Դϴ�.


void GaiaToolView::OnNcPaint()
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	// �׸��� �޽����� ���ؼ��� GaiaCView::OnNcPaint()��(��) ȣ������ ���ʽÿ�.
	CWindowDC dc(::AfxGetMainWnd());
	CBrush brush(SingleTon<GaiaLayoutRepo>::use()->Getmidside());
	CRect toolRect;
	CRect temp;
	this->GetWindowRect(&toolRect);
	toolRect.NormalizeRect();
	toolRect.OffsetRect(-toolRect.left, -toolRect.top);
	int captionHeight = ::GetSystemMetrics(SM_CYCAPTION) + ::GetSystemMetrics(SM_CYFRAME) + 5;
	int sheetWidth = SingleTon<GaiaSheetListRepo>::use()->Getwidth();
	toolRect.OffsetRect(8 + sheetWidth, captionHeight);
	toolRect.right += 10;
	toolRect.bottom += 7;

	temp = toolRect;
	temp.bottom = temp.top + 5;
	dc.FillRect(&temp, &brush);		//���� ���ø��͹� ��ĥ
	temp = toolRect;
	temp.right = temp.left + 6;
	dc.FillRect(&temp, &brush);		//���� ���ø��͹� ��ĥ
	temp = toolRect;
	temp.top = temp.bottom - 4;
	dc.FillRect(&temp, &brush);		//�Ʒ��� ���ø��͹� ��ĥ
	temp = toolRect;
	temp.left = temp.right - 7;
	dc.FillRect(&temp, &brush);		//������ ���ø��͹� ��ĥ
	brush.DeleteObject();
}


void GaiaToolView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	// �׸��� �޽����� ���ؼ��� GaiaCView::OnPaint()��(��) ȣ������ ���ʽÿ�.
	CBrush brush(SingleTon<GaiaLayoutRepo>::use()->Getmidside());
	CRect rect;
	this->GetClientRect(&rect);
	dc.FillRect(&rect, &brush);

	brush.DeleteObject();
}


void GaiaToolView::OnSize(UINT nType, int cx, int cy)
{
	GaiaCView::OnSize(nType, cx, cy);
	if (cx > 0){
		SingleTon<GaiaToolListRepo>::use()->Setwidth(cx + 10);
	}
	else if (SingleTon<GaiaLayoutRepo>::use()->GetspView() != nullptr && cx<300){
		SingleTon<GaiaToolListRepo>::use()->Setwidth(300);
		SingleTon<GaiaLayoutRepo>::use()->GetspView()->SetColumnInfo(0, SingleTon<GaiaSheetListRepo>::use()->Getwidth() - 10, 0);
		SingleTon<GaiaLayoutRepo>::use()->GetspView()->SetColumnInfo(1, SingleTon<GaiaToolListRepo>::use()->Getwidth() - 10, 0);
		auto v = SingleTon<GaiaLayoutRepo>::use()->GetspView();
		auto b = v->GetSafeHwnd();
		static int i = 0;
		i++;
		if (i > 1){
			v->RecalcLayout();
		}
		printf("%d\n", i);
	}
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}
