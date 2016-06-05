// GaiaMenuView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Gaia.h"
#include"GaiaDoc.h"
#include"LibBox.h"
#include "GaiaMenuView.h"
#include"LibBoxNameDlg.h"

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
void GaiaMenuView::InsertMenuElement(int pid, int mid, UINT bitmapID1, UINT bitmapID2) {
	MenuElement me;
	me.parentID = pid;
	me.myID = mid;
	me.image = new CBitmap;
	me.hover_image = new CBitmap;
	VERIFY(me.image->LoadBitmapW(bitmapID1) == TRUE);
	VERIFY(me.hover_image->LoadBitmapW(bitmapID2) == TRUE);
	this->menus.insert(me);
}
BEGIN_MESSAGE_MAP(GaiaMenuView, GaiaCView)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_NCPAINT()
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// GaiaMenuView 그리기입니다.

void GaiaMenuView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.
}


// GaiaMenuView 진단입니다.

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


// GaiaMenuView 메시지 처리기입니다.


void GaiaMenuView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 GaiaCView::OnPaint()을(를) 호출하지 마십시오.
	CBrush brush(SingleTon<GaiaLayoutRepo>::use()->Gethighlight());
	CRect rect;
	this->GetClientRect(&rect);
	DblBufMaker bm(&dc, rect);
	CDC& bDC = bm.GetDC();

	//graphics.FillRectangle(&semiTransBrush, table.TopLeft().x, table.TopLeft().y, table.Width(), table.Height());
	bDC.FillRect(&rect, &brush);
	vme.clear();
	//부모가 여러개일때 수정
	//자료구조 deque 사용 고려
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
	for (int i = 0; i < vme.size(); i++){
		CDC memDC;
		memDC.CreateCompatibleDC(&bDC);
		BITMAP bmpinfo;
		//	CBitmap img = sel == i ? vme[sel]->image : vme[i]->image;
		vme[i]->hover_image->GetBitmap(&bmpinfo);
		vme[i]->image->GetBitmap(&bmpinfo);
		CBitmap* oldbmp;
		if (sel == i)
			oldbmp = memDC.SelectObject(vme[i]->hover_image);
		else
			oldbmp = memDC.SelectObject(vme[i]->image);
		bDC.TransparentBlt(i * 80, 8, bmpinfo.bmWidth, bmpinfo.bmHeight, &memDC, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, RGB(0, 0, 0));
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
	////
	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &bDC, 0, 0, SRCCOPY);
	brush.DeleteObject();
}


void GaiaMenuView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

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
			//MessageBox(str);
			if ((*it)->myID == 1){ //새로만들기

				if (IDYES == AfxMessageBox(L"현재 내용을 저장하시겠습니까 ?", MB_YESNO)){
					GaiaDoc* pDoc = (GaiaDoc*)GetDocument();
					pDoc->OnSaveDocument();
				}
				SingleTon<GaiaDrawGrid>::use()->edges.clear();
				SingleTon<GaiaDrawGrid>::use()->objects.clear();
				memset(SingleTon<GaiaDrawGrid>::use()->dBoard, -1, sizeof(GSIZE*GSIZE));
				SingleTon<GaiaDrawGrid>::use()->grid.assign(GSIZE, vector<bool>(GSIZE, false));
				SingleTon<GaiaDrawGrid>::use()->inBtns.clear();
				SingleTon<GaiaLayoutRepo>::use()->views[0]->Invalidate(false);
			}
			else if ((*it)->myID == 3){	//저장
				GaiaDoc* pDoc = (GaiaDoc*)GetDocument();
				pDoc->OnSaveDocument();
			}
			else if ((*it)->myID == 2){			//불러오기
				auto& e = SingleTon<GaiaDrawGrid>::use()->objects;
				e.clear();
				GaiaDoc* pDoc = (GaiaDoc*)GetDocument();
				pDoc->OnOpenDocument();
				
				SingleTon<GaiaLayoutRepo>::use()->views[0]->Invalidate();
			}
			else if ((*it)->myID == 4){		//라이브러리박스 추가
				auto& s = SingleTon<GaiaDrawGrid>::use()->sel_objects;
				if (s.empty() == FALSE){
					auto& lib = SingleTon<GaiaDrawGrid>::use()->lib_objects;
					LibBoxNameDlg dlg;
					if (dlg.DoModal() == IDOK){
						n.push_back(dlg.libName);
						LibBox* lbox = new LibBox(dlg.libName);
						lib.push_back(lbox);
						s.clear();
						printf("lib size %d L name size : %d\n", lib.size(), n.size());

					}
				}
				else{
					MessageBox(_T("선택된 개체가 없습니다."));
				}
			}
			else if ((*it)->myID == 5){		// 라이브러리 박스 삭제
				if (SingleTon<GaiaSheetListRepo>::use()->sel_lib > 0){
					auto& lib = SingleTon<GaiaDrawGrid>::use()->lib_objects;
					n.erase(n.begin() + SingleTon<GaiaSheetListRepo>::use()->sel_lib);
					lib.erase(lib.begin() + SingleTon<GaiaSheetListRepo>::use()->sel_lib - 1);
					SingleTon<GaiaSheetListRepo>::use()->sel_lib = -1;
					SingleTon<GaiaGateInfo>::use()->selObj = -1;
					SingleTon<GaiaGateInfo>::use()->isDrawObject = FALSE;
					SingleTon<GaiaSheetListRepo>::use()->sel_btn = -1;
				}
			}
			else if ((*it)->myID == 6){


			}
			else if ((*it)->myID == 7){


			}
			else if ((*it)->myID == 8){
				GaiaDoc* pDoc = (GaiaDoc*)GetDocument();
				pDoc->Undo();

			}
			else if ((*it)->myID == 9){
				GaiaDoc* pDoc = (GaiaDoc*)GetDocument();
				pDoc->Redo();

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
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 GaiaCView::OnNcPaint()을(를) 호출하지 마십시오.
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
	menuRect.top = mainFrmRect.bottom - menuHeight - 11;	//미세조정
	menuRect.bottom = mainFrmRect.bottom;
	menuRect.OffsetRect(8, -8);
	menuRect.right += 8;

	temp = menuRect;
	temp.bottom = temp.top + 7;
	dc.FillRect(&temp, &brush);		//위쪽 스플린터바 색칠
	temp = menuRect;
	temp.right = temp.left + 4;
	dc.FillRect(&temp, &brush);		//왼쪽 스플린터바 색칠
	temp = menuRect;
	temp.top = temp.bottom - 4;
	dc.FillRect(&temp, &brush);		//아래쪽 스플린터바 색칠
	temp = menuRect;
	temp.left = temp.right - 4;
	dc.FillRect(&temp, &brush);		//오른쪽 스플린터바 색칠
	brush.DeleteObject();

}


int GaiaMenuView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (GaiaCView::OnCreate(lpCreateStruct) == -1)
		return -1;
	this->ModifyStyle(WS_BORDER, NULL);
	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	this->InsertMenuElement(0, 1, IDB_BTN_NEW, IDB_BTN_NEW_HOVER);
	this->InsertMenuElement(0, 2, IDB_BTN_OPEN, IDB_BTN_OPEN_HOVER);
	this->InsertMenuElement(0, 3, IDB_BTN_SAVE, IDB_BTN_SAVE_HOVER);
	this->InsertMenuElement(0, 4, IDB_BTN_ADD, IDB_BTN_ADD_HOVER);
	this->InsertMenuElement(0, 5, IDB_BTN_DELETE, IDB_BTN_DELETE_HOVER);
	this->InsertMenuElement(0, 6, IDB_BTN_COPY, IDB_BTN_COPY_HOVER);
	this->InsertMenuElement(0, 7, IDB_BTN_CUT, IDB_BTN_CUT_HOVER);
	this->InsertMenuElement(0, 8, IDB_BTN_PASTE, IDB_BTN_PASTE_HOVER);
	this->InsertMenuElement(0, 9, IDB_BTN_UNDO, IDB_BTN_UNDO_HOVER);
	this->InsertMenuElement(0, 10, IDB_BTN_REDO, IDB_BTN_REDO_HOVER);
	this->InsertMenuElement(0, 11, IDB_BTN_CLK, IDB_BTN_CLK_HOVER);
	this->InsertMenuElement(0, 12, IDB_BTN_ROTATE, IDB_BTN_ROTATE_HOVER);
	return 0;
}



void GaiaMenuView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	auto& n = SingleTon<GaiaGateInfo>::use()->libName;
	for (auto it = this->vme.begin(); it != this->vme.end(); it++){
		int idx = it - this->vme.begin();
		int x = idx * 80 + 30;
		int y = 40;
		double distance = hypot(point.x - x, point.y - y);
		if (distance <= 30.0){
			sel = (*it)->myID - 1;
			SetCursor(LoadCursor(NULL, IDC_HAND));
			break;
		}
		else{
			sel = -1;
			SetCursor(LoadCursor(NULL, IDC_ARROW));
		}
	}
	this->Invalidate(FALSE);
	GaiaCView::OnMouseMove(nFlags, point);
}
