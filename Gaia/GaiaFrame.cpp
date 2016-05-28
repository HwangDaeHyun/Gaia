
#include "stdafx.h"
#include "Gaia.h"
#include "GaiaFrame.h"
#include"DBlBufMaker.h"

#include<iostream>
using namespace std;

using namespace design_pattern;
// GaiaFrame

IMPLEMENT_DYNCREATE(GaiaFrame, CFrameWnd)

GaiaFrame::GaiaFrame(){
	this->m_toolupBtnState = ToolUpBtnState::NONE;
	this->m_mouseTracking = FALSE;
	this->m_isClick = FALSE;
}

GaiaFrame::~GaiaFrame()
{
}
/**
*	@name : Draw bottom frame
*	@comment : 아래쪽 프레임을 색칠 합니다.
*/
void GaiaFrame::DrawBottomFrame(CRect rect, CDC* pDC) {
	COLORREF color = SingleTon<GaiaLayoutRepo>::use()->Gethighlight();
	rect.top = rect.bottom - SingleTon<GaiaLayoutRepo>::use()->frameThickness;
	CBrush brush;
	brush.CreateSolidBrush(color);
	pDC->FillRect(&rect, &brush);
	brush.DeleteObject();
}
/**
*	@name : Draw left frame
*	@comment : 왼쪽 프레임을 색칠 합니다.
*/
void GaiaFrame::DrawLeftFrame(CRect rect, CDC* pDC) {
	CBrush leftBrush;	//시트 탭 배경색
	CBrush hBrush;		//시트 탭 선택색
	leftBrush.CreateSolidBrush(SingleTon<GaiaLayoutRepo>::use()->Getleftside());
	hBrush.CreateSolidBrush(SingleTon<GaiaLayoutRepo>::use()->Gethighlight());
	int beginPt = SingleTon<GaiaSheetListRepo>::use()->GetSelectedSheetLeftTopPoint();	//선택 시트탭 시작 위치
	int tabHeight = SingleTon<GaiaSheetListRepo>::use()->sheetTabHeight;	//시트탭 높이
	int captionHeight = ::GetSystemMetrics(SM_CYCAPTION) + ::GetSystemMetrics(SM_CYFRAME) + 5;

	rect.right = rect.left + SingleTon<GaiaLayoutRepo>::use()->frameThickness;
	pDC->FillRect(&rect, &leftBrush);	//왼쪽배경색으로 모두 칠합니다.
	rect.top = rect.bottom - (SingleTon<GaiaLayoutRepo>::use()->menuHeight + SingleTon<GaiaLayoutRepo>::use()->frameThickness);
	pDC->FillRect(&rect, &hBrush);		//메뉴부분 색상을 칠합니다.
	rect.top = captionHeight + beginPt;
	rect.bottom = rect.top + tabHeight;
	pDC->FillRect(&rect, &hBrush);		//선택된 시트 탭 부분을 색칠 합니다.

	leftBrush.DeleteObject();
	hBrush.DeleteObject();
}
void GaiaFrame::DrawRightFrame(CRect rect, CDC* pDC) {
	CBrush leftBrush;	//시트 탭 배경색
	CBrush hBrush;		//시트 탭 선택색
	leftBrush.CreateSolidBrush(SingleTon<GaiaLayoutRepo>::use()->Getrightside());
	hBrush.CreateSolidBrush(SingleTon<GaiaLayoutRepo>::use()->Gethighlight());

	int tabHeight = SingleTon<GaiaSheetListRepo>::use()->sheetTabHeight;	//시트탭 높이
	int captionHeight = ::GetSystemMetrics(SM_CYCAPTION) + ::GetSystemMetrics(SM_CYFRAME) + 5;


	rect.left = rect.right - SingleTon<GaiaLayoutRepo>::use()->frameThickness;
	pDC->FillRect(&rect, &leftBrush);	//왼쪽배경색으로 모두 칠합니다.
	rect.top = rect.bottom - (SingleTon<GaiaLayoutRepo>::use()->menuHeight + SingleTon<GaiaLayoutRepo>::use()->frameThickness);
	pDC->FillRect(&rect, &hBrush);		//메뉴부분 색상을 칠합니다.


	leftBrush.DeleteObject();
	hBrush.DeleteObject();
}
void GaiaFrame::DrawTopFrame(CRect rect, CDC* pDC) {
	int captionHeight = ::GetSystemMetrics(SM_CYCAPTION) + ::GetSystemMetrics(SM_CYFRAME) + 5;
	rect.bottom = rect.top + captionHeight;
	CRect topRect = rect;
	DblBufMaker dbm(pDC, rect);
	CDC& bDC = dbm.GetDC();
	int maxRight = rect.right;
	CBrush leftBrush;	//시트 탭 배경색
	CBrush midBrush;
	CBrush rightBrush;
	leftBrush.CreateSolidBrush(SingleTon<GaiaLayoutRepo>::use()->Getleftside());
	midBrush.CreateSolidBrush(SingleTon<GaiaLayoutRepo>::use()->Getmidside());
	rightBrush.CreateSolidBrush(SingleTon<GaiaLayoutRepo>::use()->Getrightside());

	rect.right = SingleTon<GaiaLayoutRepo>::use()->frameThickness + SingleTon<GaiaSheetListRepo>::use()->Getwidth();
	bDC.FillRect(&rect, &leftBrush);	//왼쪽(시트바) 를 색칠 합니다.
	this->DrawIcon(&bDC);
	rect.left = rect.right;
	rect.right += SingleTon<GaiaDrawListRepo>::use()->Getwidth();
	bDC.FillRect(&rect, &midBrush);	//가운데(툴리스트)를 색칠 합니다.


	//==버튼구성
	CPoint point;
	CRect wRect;
	::GetCursorPos(&point);
	this->GetWindowRect(&wRect);
	point.x -= wRect.left;
	point.y -= wRect.top;
	if (this->m_isClick == TRUE){
		this->DrawToolUpBtn(&bDC, rect.left, IDB_TOOLUP_AFTER);
	}
	else if (this->m_btnRect.PtInRect(point) == FALSE){	//기본값
		this->DrawToolUpBtn(&bDC, rect.left, IDB_TOOLUP);
	}
	else{	//마우스가 버튼 안으로 들어옴
		this->DrawToolUpBtn(&bDC, rect.left, IDB_TOOLUP_HOVER);
	}
	//======
	rect.left = rect.right;
	CRect tmp;
	this->GetWindowRect(&tmp);
	rect.right = tmp.right + 1920;
	bDC.FillRect(&rect, &rightBrush);	//가운데(툴리스트)를 색칠 합니다.

	this->DrawSysBtns(&bDC);

	pDC->BitBlt(0, 0, topRect.Width(), topRect.Height(), &bDC, 0, 0, SRCCOPY);
	leftBrush.DeleteObject();
	midBrush.DeleteObject();


}
void GaiaFrame::DrawIcon(CDC* pDC) {
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CBitmap bmp;
	if (bmp.LoadBitmapW(IDB_ICON) == TRUE){
		BITMAP bmpinfo;
		bmp.GetBitmap(&bmpinfo);
		CBitmap* oldbmp = memDC.SelectObject(&bmp);

		pDC->TransparentBlt(10, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, &memDC, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, RGB(255, 255, 255));
		memDC.SelectObject(oldbmp);
	}
}
void GaiaFrame::DrawToolUpBtn(CDC* pDC, int begin, UINT id) {
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CBitmap bmp;
	if (bmp.LoadBitmapW(id) == TRUE){
		BITMAP bmpinfo;
		bmp.GetBitmap(&bmpinfo);
		CBitmap* oldbmp = memDC.SelectObject(&bmp);
		this->m_btnRect.left = begin + 20;
		this->m_btnRect.top = 0;
		this->m_btnRect.bottom = bmpinfo.bmHeight;
		this->m_btnRect.right = this->m_btnRect.left + bmpinfo.bmWidth;
		pDC->TransparentBlt(begin + 20, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, &memDC, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, RGB(255, 255, 255));
		memDC.SelectObject(oldbmp);
	}
}
void GaiaFrame::DrawSysBtns(CDC* pDC){
	//우측상단 버튼을 그립니다(최소화,최대화,종료).
	CRect r;
	int captionHeight = ::GetSystemMetrics(SM_CYCAPTION) + ::GetSystemMetrics(SM_CYFRAME) + 5;
	this->GetWindowRect(&r);
	r.NormalizeRect();
	r.OffsetRect(-r.left, -r.top);
	r.bottom = r.top + captionHeight;
	r.top += 5;
	r.bottom -= 5;
	r.right -= 10;
	CBrush b(RGB(255, 255, 255));
	int m = 0;
	for (auto& e : this->sys_btns){
		e = r;
		e.right -= m;
		e.left = e.right - e.Height();
		//		pDC->FillRect(e, &b);
		m += e.Height() + 2;
	}
	this->DrawSystemButton1(pDC);
	this->DrawSystemButton2(pDC);
	this->DrawSystemButton3(pDC);
}
VOID GaiaFrame::DrawSystemButton1(CDC* dc) {
	//종료버튼을 그립니다.
	CPen pen;
	pen.CreatePen(PS_SOLID, 2, RGB(49, 49, 49));
	CPen* old = dc->SelectObject(&pen);
	CPoint point;
	CRect wRect;
	::GetCursorPos(&point);
	this->GetWindowRect(&wRect);
	point.x -= wRect.left;
	point.y -= wRect.top;
	CBrush r = RGB(140, 140, 140);
	if (this->sys_btns[0].PtInRect(point) == TRUE){
		dc->FillRect(this->sys_btns[0], &r);
	}
	dc->MoveTo(this->sys_btns[0].left + 5, this->sys_btns[0].top + 5);
	dc->LineTo(this->sys_btns[0].right - 5, this->sys_btns[0].bottom - 5);
	dc->MoveTo(this->sys_btns[0].left + 5, this->sys_btns[0].bottom - 5);
	dc->LineTo(this->sys_btns[0].right - 5, this->sys_btns[0].top + 5);
	dc->SelectObject(old);
}

VOID GaiaFrame::DrawSystemButton2(CDC* dc) {
	// 최대화/복원 버튼을 그립니다.
	CPen pen;
	pen.CreatePen(PS_SOLID, 2, RGB(49, 49, 49));
	CPen* old = dc->SelectObject(&pen);
	CPoint point;
	CRect wRect;
	::GetCursorPos(&point);
	this->GetWindowRect(&wRect);
	point.x -= wRect.left;
	point.y -= wRect.top;
	CBrush r = RGB(140, 140, 140);
	if (this->sys_btns[1].PtInRect(point) == TRUE){
		dc->FillRect(this->sys_btns[1], &r);
	}
	if (this->m_isMaximize == TRUE){
		dc->MoveTo(this->sys_btns[1].left + 4, this->sys_btns[1].top + 9);
		dc->LineTo(this->sys_btns[1].left + 4, this->sys_btns[1].bottom - 3);
		dc->LineTo(this->sys_btns[1].right - 7, this->sys_btns[1].bottom - 3);
		dc->LineTo(this->sys_btns[1].right - 7, this->sys_btns[1].top + 9);
		dc->LineTo(this->sys_btns[1].left + 4, this->sys_btns[1].top + 8);
		dc->MoveTo(this->sys_btns[1].left + 7, this->sys_btns[1].top + 5);
		dc->LineTo(this->sys_btns[1].right - 4, this->sys_btns[1].top + 5);
		dc->LineTo(this->sys_btns[1].right - 4, this->sys_btns[1].bottom - 5);
	}
	else{
		dc->MoveTo(this->sys_btns[1].left + 5, this->sys_btns[1].top + 5);
		dc->LineTo(this->sys_btns[1].left + 5, this->sys_btns[1].bottom - 5);
		dc->LineTo(this->sys_btns[1].right - 5, this->sys_btns[1].bottom - 5);
		dc->LineTo(this->sys_btns[1].right - 5, this->sys_btns[1].top + 5);
		dc->LineTo(this->sys_btns[1].left + 4, this->sys_btns[1].top + 6);
		dc->MoveTo(this->sys_btns[1].left + 5, this->sys_btns[1].top + 8);
		dc->LineTo(this->sys_btns[1].right - 5, this->sys_btns[1].top + 8);
	}
	dc->SelectObject(old);
}

VOID GaiaFrame::DrawSystemButton3(CDC* dc) {
	//최소화버튼을 그립니다.
	CPen pen;
	pen.CreatePen(PS_SOLID, 2, RGB(49, 49, 49));
	CPen* old = dc->SelectObject(&pen);
	CPoint point;
	CRect wRect;
	::GetCursorPos(&point);
	this->GetWindowRect(&wRect);
	point.x -= wRect.left;
	point.y -= wRect.top;
	CBrush r = RGB(140, 140, 140);
	if (this->sys_btns[2].PtInRect(point) == TRUE){
		dc->FillRect(this->sys_btns[2], &r);
	}
	dc->MoveTo(this->sys_btns[2].left + 5, this->sys_btns[2].bottom - 8);
	dc->LineTo(this->sys_btns[2].right - 5, this->sys_btns[2].bottom - 8);
	dc->SelectObject(old);
}
//=====================================MESSAGE MAP METHOD================================================

BEGIN_MESSAGE_MAP(GaiaFrame, CFrameWnd)
	ON_WM_NCPAINT()
	ON_WM_SIZE()
	ON_WM_NCACTIVATE()
	ON_WM_NCLBUTTONDOWN()

	ON_WM_NCLBUTTONUP()
	ON_WM_TIMER()
	ON_WM_MOVE()
	ON_WM_GETMINMAXINFO()
END_MESSAGE_MAP()

void GaiaFrame::OnNcPaint() {
	// 그리기 메시지에 대해서는 CFrameWnd::OnNcPaint()을(를) 호출하지 마십시오.
	CWindowDC dc(this);


	CRect rect;
	this->GetWindowRect(&rect);
	rect.NormalizeRect();
	rect.OffsetRect(-rect.left, -rect.top);

	this->DrawTopFrame(rect, &dc);

	this->DrawBottomFrame(rect, &dc);
	this->DrawLeftFrame(rect, &dc);

	this->DrawRightFrame(rect, &dc);
}

/**
*	@name : On Size
*	@comment : 윈도우 창을 사각형으로 지정합니다.
*/

#define PRINT_RECT(R)	printf("rect : L(%d) R(%d) T(%d) B(%d)\n",(R).left,(R).right,(R).top,(R).bottom)
void GaiaFrame::OnSize(UINT nType, int cx, int cy) {
	CFrameWnd::OnSize(nType, cx, cy);
	CRect rect;
	this->GetWindowRect(rect);
	PRINT_RECT(rect);
	CRgn wrgn;
	wrgn.CreateRectRgn(0, 0, rect.Width(), rect.Height());
	this->SetWindowRgn(wrgn, 0);
}


BOOL GaiaFrame::OnNcActivate(BOOL bActive) {
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	this->OnNcPaint();
	return TRUE;
}


void GaiaFrame::OnNcLButtonDown(UINT nHitTest, CPoint point) {
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CRect rect;
	this->GetWindowRect(&rect);
	point.x -= rect.left;
	point.y -= rect.top;
	if (this->m_btnRect.PtInRect(point) == TRUE){
		this->m_isClick = TRUE;
		this->SetTimer(TOOLUP_BTN_CLICK_TIMER_ID, TOOLUP_BTN_CLICK_TIMER_TIME, nullptr);
		MessageBox(L"ToolUp");
		return;
	}
	else if (this->sys_btns[2].PtInRect(point) == TRUE){
		this->SendMessage(WM_SYSCOMMAND, (WPARAM)SC_MINIMIZE);
	}
	else if (this->sys_btns[1].PtInRect(point) == TRUE){
		WINDOWPLACEMENT place;
		place.length = (UINT)sizeof(WINDOWPLACEMENT);
		if (GetWindowPlacement(&place)){
			if (place.showCmd == SW_SHOWMAXIMIZED){   //최대화일때->크기를 줄임
				this->ModifyStyle(NULL, WS_THICKFRAME);
				this->SendMessage(WM_SYSCOMMAND, (WPARAM)SC_RESTORE);
				this->m_isMaximize = FALSE;
			}
			else if (place.showCmd == SW_SHOWNORMAL){                     //일반크기 일때
				this->ModifyStyle(WS_CAPTION, NULL, SWP_FRAMECHANGED);
				this->SendMessage(WM_SYSCOMMAND, (WPARAM)SC_MAXIMIZE);
				this->ModifyStyle(WS_THICKFRAME, WS_CAPTION, SWP_FRAMECHANGED);
				this->m_isMaximize = TRUE;
			}
		}
		this->OnNcPaint();
	}
	else if (this->sys_btns[0].PtInRect(point) == TRUE){
		this->SendMessage(WM_SYSCOMMAND, (WPARAM)SC_CLOSE);
	}
	CFrameWnd::OnNcLButtonDown(nHitTest, point);
}










void GaiaFrame::OnTimer(UINT_PTR nIDEvent) {
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nIDEvent == TOOLUP_BTN_CLICK_TIMER_ID){
		this->m_isClick = FALSE;
		this->KillTimer(TOOLUP_BTN_CLICK_TIMER_ID);
	}
	CFrameWnd::OnTimer(nIDEvent);
}


void GaiaFrame::OnMove(int x, int y)
{
	CFrameWnd::OnMove(x, y);
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


void GaiaFrame::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	lpMMI->ptMinTrackSize.x = 700;
	lpMMI->ptMinTrackSize.y = 700;
	CFrameWnd::OnGetMinMaxInfo(lpMMI);
}
