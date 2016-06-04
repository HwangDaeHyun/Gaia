// GaiaToolView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Gaia.h"
#include "GaiaToolView.h"
#include "DblBufMaker.h"

// GaiaToolView

IMPLEMENT_DYNCREATE(GaiaToolView, GaiaCView)

GaiaToolView::GaiaToolView()
{

}

GaiaToolView::~GaiaToolView()
{
}
void GaiaToolView::DrawSplitterBar() {
	this->OnNcPaint();

}
BEGIN_MESSAGE_MAP(GaiaToolView, GaiaCView)
	ON_WM_NCPAINT()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_CHAR()
END_MESSAGE_MAP()


// GaiaToolView 그리기입니다.

void GaiaToolView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.
}


// GaiaToolView 진단입니다.

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


// GaiaToolView 메시지 처리기입니다.


void GaiaToolView::OnNcPaint()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 GaiaCView::OnNcPaint()을(를) 호출하지 마십시오.

	CWindowDC dc(::AfxGetMainWnd());

	CBrush brush(SingleTon<GaiaLayoutRepo>::use()->Getrightside());
	CRect toolRect;
	CRect temp;
	this->GetWindowRect(&toolRect);
	toolRect.NormalizeRect();
	toolRect.OffsetRect(-toolRect.left, -toolRect.top);
	int captionHeight = ::GetSystemMetrics(SM_CYCAPTION) + ::GetSystemMetrics(SM_CYFRAME) + 5;
	toolRect.OffsetRect(8, captionHeight);
	toolRect.right += 10;
	toolRect.bottom += 7;
	int mvcnt = SingleTon<GaiaSheetListRepo>::use()->Getwidth() + SingleTon<GaiaDrawListRepo>::use()->Getwidth();
	toolRect.left += mvcnt;
	toolRect.right += mvcnt;

	temp = toolRect;
	temp.bottom = temp.top + 5;
	dc.FillRect(&temp, &brush);		//위쪽 스플린터바 색칠
	temp = toolRect;
	temp.right = temp.left + 6;
	dc.FillRect(&temp, &brush);		//왼쪽 스플린터바 색칠
	temp = toolRect;
	temp.top = temp.bottom - 4;
	dc.FillRect(&temp, &brush);		//아래쪽 스플린터바 색칠
	temp = toolRect;
	temp.left = temp.right - 10;
	dc.FillRect(&temp, &brush);		//오른쪽 스플린터바 색칠
	brush.DeleteObject();

}


void GaiaToolView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 GaiaCView::OnPaint()을(를) 호출하지 마십시오.

	CBrush brush(SingleTon<GaiaLayoutRepo>::use()->Getrightside());
	CRect rect;
	this->GetClientRect(&rect);
	DblBufMaker dm(&dc, rect);
	CDC& bDC = dm.GetDC();
	bDC.FillRect(&rect, &brush);
	CFont font;
	font.CreateFont(20,                     // 글자높이
		8,                     // 글자너비
		0,                      // 출력각도
		0,                      // 기준 선에서의각도
		FW_HEAVY,              // 글자굵기
		FALSE,                  // Italic 적용여부
		FALSE,                  // 밑줄적용여부
		FALSE,                  // 취소선적용여부
		DEFAULT_CHARSET,       // 문자셋종류
		OUT_DEFAULT_PRECIS,    // 출력정밀도
		CLIP_DEFAULT_PRECIS,   // 클리핑정밀도
		DEFAULT_QUALITY,       // 출력문자품질
		DEFAULT_PITCH,         // 글꼴Pitch
		_T("Time New Romans")           // 글꼴
		);
	CPen pen, pen2;
	CBrush first(RGB(89, 168, 222));
	bDC.SetTextColor(RGB(255,255, 255));
	bDC.SelectObject(&font);
	bDC.SetBkMode(TRANSPARENT);
	pen.CreatePen(PS_DOT, 2, RGB(0, 122, 204));
	int width = SingleTon<GaiaToolListRepo>::use()->Getwidth();

	int h = 10;
	CRect table(width / 10, h, width / 10 * 9, h + 40); // title
	h += 80;
	bDC.SelectObject(&pen);
	CBrush fBrush(RGB(200, 220, 200));
	bDC.SelectObject(&fBrush);
	//
	Graphics graphics(bDC);
	SolidBrush  semiTransBrush(Color(100, 0, 124, 255));
	SolidBrush  semiTransBrush2(Color(180, 100, 181, 246));
	SolidBrush  semiTransBrush3(Color(50, 187, 222, 251));
	graphics.FillRectangle(&semiTransBrush, table.TopLeft().x, table.TopLeft().y, table.Width(), table.Height());
	//
	bDC.SelectObject(&pen);
	bDC.DrawText(_T("INFOMATION"), &table, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	/*bDC.MoveTo(table.left, table.bottom+20);
	bDC.LineTo(table.right, table.bottom+20);*/
	bDC.SetTextColor(RGB(252, 250, 255));
	CRect inven;

	auto& contents = SingleTon<GaiaTableInfo>::use()->contents;
	auto& cRect = SingleTon<GaiaTableInfo>::use()->invenRect;
	pen2.CreatePen(PS_DOT, 2, RGB(250, 250, 255));
	bool isPush = false;
	if (cRect.empty()){
		isPush = true;
	}
	for (int i = 0; i < contents.size(); i++){
		bDC.SelectObject(&first);
		inven.SetRect(width / 8, h, width / 8 * 3, h + 40);
		graphics.FillRectangle(&semiTransBrush2,inven.TopLeft().x, inven.TopLeft().y, inven.Width(), inven.Height());
		//bDC.RoundRect(&inven, CPoint(5, 5));
		CRect temp = inven;
		bDC.DrawText(contents[i].first, &inven, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		bDC.SelectStockObject(NULL_BRUSH);
		//bDC.SetTextColor(RGB(200, 200, 222));
		inven.SetRect(width / 8 * 3, h, width / 8 * 7, h + 40);

		graphics.FillRectangle(&semiTransBrush3, inven.TopLeft().x, inven.TopLeft().y, inven.Width(), inven.Height());
		bDC.DrawText(contents[i].second, &inven, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		h += 50;
		if (isPush == true)
			cRect.push_back(CRect(temp.left, temp.top, inven.right, inven.bottom));
	}
	if (this->lighting != -1){
		bDC.SelectObject(&pen2);
		bDC.RoundRect(cRect[lighting], CPoint(5, 5));
	}
	brush.DeleteObject();
	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &bDC, 0, 0, SRCCOPY);

}


void GaiaToolView::OnSize(UINT nType, int cx, int cy)
{
	GaiaCView::OnSize(nType, cx, cy);
	auto& cRect = SingleTon<GaiaTableInfo>::use()->invenRect;
	cRect.clear();
	if (cx > 0){
		SingleTon<GaiaToolListRepo>::use()->Setwidth(cx + 10);
	}
	else if (SingleTon<GaiaLayoutRepo>::use()->GetspView() != nullptr && cx < 100){
		SingleTon<GaiaToolListRepo>::use()->Setwidth(250);
		SingleTon<GaiaLayoutRepo>::use()->GetspView()->SetColumnInfo(0, SingleTon<GaiaSheetListRepo>::use()->Getwidth() - 10, 0);
		SingleTon<GaiaLayoutRepo>::use()->GetspView()->SetColumnInfo(1, SingleTon<GaiaToolListRepo>::use()->Getwidth() - 10, 0);
		auto v = SingleTon<GaiaLayoutRepo>::use()->GetspView();
		auto b = v->GetSafeHwnd();
	}
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


void GaiaToolView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	CRect rect;
	this->GetClientRect(&rect);
	DblBufMaker dm(&dc, rect);
	CDC& bDC = dm.GetDC();
	auto& cRect = SingleTon<GaiaTableInfo>::use()->invenRect;
	CBrush pen;
	bDC.SetDCPenColor(RGB(100, 100, 156));
	bDC.SelectStockObject(NULL_BRUSH);
	for (int i = 0; i < cRect.size(); i++){
		if (cRect[i].PtInRect(point)){
			this->lighting = i;
		}
	}

	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &bDC, 0, 0, SRCCOPY);
	Invalidate(false);
	GaiaCView::OnLButtonDown(nFlags, point);
}


void GaiaToolView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	auto&e = SingleTon<GaiaDrawGrid>::use()->objects;
	int sel = SingleTon<GaiaTableInfo>::use()->selNum;
	auto& ct = SingleTon<GaiaTableInfo>::use()->contents;
	if (lighting == 2){
		if (nChar == _T('\b')){
			if (ct[lighting].second.GetLength() > 0){
				ct[lighting].second.Delete(ct[lighting].second.GetLength() - 1);
			}
		}
		else{
			ct[lighting].second.AppendChar(nChar);
		}
	}
	if (sel != -1){
		e[sel]->name.SetString(ct[2].second);
	}
	Invalidate(false);
	GaiaCView::OnChar(nChar, nRepCnt, nFlags);
}
