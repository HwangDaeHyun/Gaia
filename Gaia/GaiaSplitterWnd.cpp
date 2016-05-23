// GaiaSplitterWnd.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Gaia.h"
#include "GaiaSplitterWnd.h"


// GaiaSplitterWnd

IMPLEMENT_DYNAMIC(GaiaSplitterWnd, CSplitterWnd)

GaiaSplitterWnd::GaiaSplitterWnd()
{
	this->isLock = FALSE;
}

GaiaSplitterWnd::~GaiaSplitterWnd()
{
}
void GaiaSplitterWnd::SetLock() {
	this->isLock = TRUE;
}

BEGIN_MESSAGE_MAP(GaiaSplitterWnd, CSplitterWnd)
	ON_WM_LBUTTONDOWN()
	ON_WM_SETCURSOR()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()



// GaiaSplitterWnd 메시지 처리기입니다.




void GaiaSplitterWnd::OnLButtonDown(UINT nFlags, CPoint point) {
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (this->isLock == FALSE){
		CSplitterWnd::OnLButtonDown(nFlags, point);
	}
}


BOOL GaiaSplitterWnd::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) {
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (this->isLock == FALSE){
		return CSplitterWnd::OnSetCursor(pWnd, nHitTest, message);
	}
	else{
		return TRUE;
	}
}


void GaiaSplitterWnd::OnMouseMove(UINT nFlags, CPoint point) {
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (this->isLock == FALSE){
		CSplitterWnd::OnMouseMove(nFlags, point);
	}
}
