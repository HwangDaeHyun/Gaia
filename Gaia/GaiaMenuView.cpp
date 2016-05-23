// GaiaMenuView.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Gaia.h"
#include "GaiaMenuView.h"


// GaiaMenuView

IMPLEMENT_DYNCREATE(GaiaMenuView, GaiaCView)

GaiaMenuView::GaiaMenuView()
{
	this->currentID = 0;
}

GaiaMenuView::~GaiaMenuView()
{
}
void GaiaMenuView::DrawSplitterBar() {
	this->OnNcPaint();
}
void GaiaMenuView::InsertMenuElement(int pid, int mid, UINT bitmapID) {
	MenuElement me;
	me.parentID = pid;
	me.myID = mid;
	me.image = new CBitmap;
	VERIFY(me.image->LoadBitmapW(bitmapID) == TRUE);
	this->menus.insert(me);
}
BEGIN_MESSAGE_MAP(GaiaMenuView, GaiaCView)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_NCPAINT()
	ON_WM_CREATE()
END_MESSAGE_MAP()


// GaiaMenuView �׸����Դϴ�.

void GaiaMenuView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: ���⿡ �׸��� �ڵ带 �߰��մϴ�.
}


// GaiaMenuView �����Դϴ�.

#ifdef _DEBUG
void GaiaMenuView::AssertValid() const
{
	GaiaCView::AssertValid();
}

#ifndef _WIN32_WCE
void GaiaMenuView::Dump(CDumpContext& dc) const
{
	GaiaCView::Dump(dc);
}
#endif
#endif //_DEBUG


// GaiaMenuView �޽��� ó�����Դϴ�.


void GaiaMenuView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	// �׸��� �޽����� ���ؼ��� GaiaCView::OnPaint()��(��) ȣ������ ���ʽÿ�.
	CBrush brush(SingleTon<GaiaLayoutRepo>::use()->Gethighlight());
	CRect rect;
	this->GetClientRect(&rect);
	DblBufMaker bm(&dc, rect);
	CDC& bDC = bm.GetDC();
	bDC.FillRect(&rect, &brush);
	vme.clear();
	//�θ� �������϶� ����
	//�ڷᱸ�� deque ��� ���
	vector<const MenuElement*>& cvme = this->vme;
	int currID = this->currentID;
	if (currID != 0){
		auto it = find_if(menus.begin(), menus.end(), [currID](const MenuElement& e)->bool{return e.myID == currID; });
		cvme.push_back(&(*it));
	}
	for_each(menus.begin(), menus.end(), [&cvme, currID](const MenuElement& e)->void{
		if (e.parentID == currID){
			cvme.push_back(&e);
		}
	});
	for (auto it = vme.begin(); it != vme.end(); it++){
		int idx = it - vme.begin();
		CDC memDC;
		memDC.CreateCompatibleDC(&bDC);
		BITMAP bmpinfo;
		(*it)->image->GetBitmap(&bmpinfo);
		CBitmap* oldbmp = memDC.SelectObject((*it)->image);
		bDC.TransparentBlt(idx * 80, 8, bmpinfo.bmWidth, bmpinfo.bmHeight, &memDC, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, RGB(0, 0, 0));
		memDC.SelectObject(oldbmp);
	}
	if (currID != 0){
		CDC memDC;
		memDC.CreateCompatibleDC(&bDC);
		CBitmap bmp;
		if (bmp.LoadBitmapW(IDB_MENU_BACK) == TRUE){
			BITMAP bmpinfo;
			bmp.GetBitmap(&bmpinfo);
			CBitmap* oldbmp = memDC.SelectObject(&bmp);
			bDC.TransparentBlt(0, 8, bmpinfo.bmWidth, bmpinfo.bmHeight, &memDC, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, RGB(0, 0, 0));
			memDC.SelectObject(oldbmp);
		}
	}
	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &bDC, 0, 0, SRCCOPY);
	brush.DeleteObject();
}


void GaiaMenuView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	PRINT_POINT(point);
	for (auto it = this->vme.begin(); it != this->vme.end(); it++){
		int idx = it - this->vme.begin();
		int x = idx * 80 + 30;
		int y = 40;
		double distance = hypot(point.x - x, point.y - y);
		if (distance <= 30.0){
			if (idx == 0 && this->currentID != 0){
				this->currentID = (*it)->parentID;
			}
			else{
				MessageBox(L"menu click!!");
				this->currentID = (*it)->myID;
			}
			this->Invalidate();
			break;
		}
	}
	GaiaCView::OnLButtonDown(nFlags, point);
}


void GaiaMenuView::OnNcPaint()
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	// �׸��� �޽����� ���ؼ��� GaiaCView::OnNcPaint()��(��) ȣ������ ���ʽÿ�.
	CWindowDC dc(::AfxGetMainWnd());
	CBrush brush(SingleTon<GaiaLayoutRepo>::use()->Gethighlight());
	CRect menuRect;
	CRect mainFrmRect;
	CRect temp;
	this->GetWindowRect(&menuRect);
	menuRect.NormalizeRect();
	menuRect.OffsetRect(-menuRect.left, -menuRect.top);
	::AfxGetMainWnd()->GetWindowRect(&mainFrmRect);
	mainFrmRect.NormalizeRect();
	mainFrmRect.OffsetRect(-mainFrmRect.left, -mainFrmRect.top);
	int menuHeight = menuRect.Height();
	menuRect.top = mainFrmRect.bottom - menuHeight - 11;	//�̼�����
	menuRect.bottom = mainFrmRect.bottom;
	menuRect.OffsetRect(8, -8);
	menuRect.right += 8;

	temp = menuRect;
	temp.bottom = temp.top + 7;
	dc.FillRect(&temp, &brush);		//���� ���ø��͹� ��ĥ
	temp = menuRect;
	temp.right = temp.left + 4;
	dc.FillRect(&temp, &brush);		//���� ���ø��͹� ��ĥ
	temp = menuRect;
	temp.top = temp.bottom - 4;
	dc.FillRect(&temp, &brush);		//�Ʒ��� ���ø��͹� ��ĥ
	temp = menuRect;
	temp.left = temp.right - 4;
	dc.FillRect(&temp, &brush);		//������ ���ø��͹� ��ĥ
	brush.DeleteObject();

}


int GaiaMenuView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (GaiaCView::OnCreate(lpCreateStruct) == -1)
		return -1;
	this->ModifyStyle(WS_BORDER, NULL);
	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.
	this->InsertMenuElement(0, 1, IDB_MENU_FILE);
	{
		this->InsertMenuElement(1, 11, IDB_MENU_NEW);
	}
	this->InsertMenuElement(0, 2, IDB_MENU_EDIT);
	this->InsertMenuElement(0, 3, IDB_MENU_LOOK);

	return 0;
}
