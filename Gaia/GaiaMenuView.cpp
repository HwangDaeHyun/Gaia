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
	auto& n = SingleTon<GaiaGateInfo>::use()->libName;
	for (auto it = this->vme.begin(); it != this->vme.end(); it++){
		int idx = it - this->vme.begin();
		int x = idx * 80 + 30;
		int y = 40;
		double distance = hypot(point.x - x, point.y - y);
		if (distance <= 30.0){
			CString str;
			str.Format(_T("%d"), (*it)->myID);
			MessageBox(str);
			switch ((*it)->myID){
			case 1:		// ���̺귯�� �ڽ� �߰�
				n.push_back(_T("ADD"));
				break;
			case 4: // ���̺귯�� �ڽ� ����
				if (SingleTon<GaiaSheetListRepo>::use()->sel_lib > 0){
					n.erase(n.begin() + SingleTon<GaiaSheetListRepo>::use()->sel_lib);
					SingleTon<GaiaSheetListRepo>::use()->sel_lib = -1;
					SingleTon<GaiaGateInfo>::use()->selObj = -1;
					SingleTon<GaiaGateInfo>::use()->isDrawObject = FALSE;
					SingleTon<GaiaSheetListRepo>::use()->sel_btn = -1;
					printf("Menu : %d \n", SingleTon<GaiaSheetListRepo>::use()->sel_btn);
				}
				break;
			}

			this->Invalidate();
			break;
		}
	}
	SingleTon<GaiaLayoutRepo>::use()->views[2]->Invalidate();
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
	this->InsertMenuElement(0, 1, IDB_BTN_NEW);
	this->InsertMenuElement(0, 2, IDB_BTN_OPEN);
	this->InsertMenuElement(0, 3, IDB_BTN_SAVE);
	this->InsertMenuElement(0, 4, IDB_BTN_DELETE);
	this->InsertMenuElement(0, 5, IDB_BTN_COPY);
	this->InsertMenuElement(0, 6, IDB_BTN_CUT);
	this->InsertMenuElement(0, 7, IDB_BTN_PASTE);
	this->InsertMenuElement(0, 8, IDB_BTN_UNDO);
	this->InsertMenuElement(0, 9, IDB_BTN_REDO);


	return 0;
}
