// GaiaSplitterWnd.cpp : ���� �����Դϴ�.
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



// GaiaSplitterWnd �޽��� ó�����Դϴ�.




void GaiaSplitterWnd::OnLButtonDown(UINT nFlags, CPoint point) {
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (this->isLock == FALSE){
		CSplitterWnd::OnLButtonDown(nFlags, point);
	}
}


BOOL GaiaSplitterWnd::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) {
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (this->isLock == FALSE){
		return CSplitterWnd::OnSetCursor(pWnd, nHitTest, message);
	}
	else{
		return TRUE;
	}
}


void GaiaSplitterWnd::OnMouseMove(UINT nFlags, CPoint point) {
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (this->isLock == FALSE){
		CSplitterWnd::OnMouseMove(nFlags, point);
	}
}
