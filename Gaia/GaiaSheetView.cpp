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
void GaiaSheetView::creatTree(){
	auto& names = SingleTon<GaiaGateInfo>::use()->names;
	auto& lnames = SingleTon<GaiaGateInfo>::use()->libName;
	this->InsertSheetElement(1, 0, 3000, _T("Library"), RGB(40, 40, 40));
	static int i = 0;
	for (int i = 0; i < lnames.size(); i++){
		this->InsertSheetElement(0, 3000, i, lnames[i], RGB(40, 40, 40));
	}

	this->InsertSheetElement(1, 0, 100, _T("Gates"), RGB(240, 0, 0));
	for (int i = 0; i < 6; i++){
		this->InsertSheetElement(0, 100, i + 10, names[i], SingleTon<GaiaGateInfo>::use()->colors[i]);
	}
	this->InsertSheetElement(1, 0, 200, _T("Memmory"), RGB(240, 240, 0));
	for (int i = 6; i < 9; i++){
		this->InsertSheetElement(0, 200, i + 20, names[i], SingleTon<GaiaGateInfo>::use()->colors[i]);
	}
	this->InsertSheetElement(1, 0, 300, _T("Button"), RGB(0, 0, 240));
	for (int i = 9; i < 12; i++){
		this->InsertSheetElement(0, 300, i + 30, names[i], SingleTon<GaiaGateInfo>::use()->colors[i]);
	}
}
void GaiaSheetView::InsertSheetElement(int tid, int pid, int mid, CString name, COLORREF col) {
	SheetElement me;
	me.topID = tid;
	me.parentID = pid;
	me.myID = mid;
	me.color = col;
	me.name = name;
	this->elems.push_back(me);
}
void GaiaSheetView::AddSheetElement(int tid, int pid, int mid, CString name, COLORREF col) {
	SheetElement me;
	me.topID = tid;
	me.parentID = pid;
	me.myID = mid;
	me.color = col;
	me.name = name;
	this->elems.insert(elems.begin() + 2, me);
}

BEGIN_MESSAGE_MAP(GaiaSheetView, GaiaCView)
	ON_WM_NCPAINT()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_CREATE()
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
//this->AddSheetElement(0, 2012, 2017, _T("eee"), RGB(40,40,40));	LibraryBox �߰�
//elems.erase(elems.begin() + selNum);								LibraryBox ����
void GaiaSheetView::OnPaint()
{
	this->creatTree();
	CPaintDC dc(this); // device context for painting
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	// �׸��� �޽����� ���ؼ��� GaiaGaiaCView::OnPaint()��(��) ȣ������ ���ʽÿ�.
	CRect _rect;
	this->GetClientRect(&_rect);
	DblBufMaker dm(&dc, _rect);
	CDC& bDC = dm.GetDC();
	CBrush brush(SingleTon<GaiaLayoutRepo>::use()->Getleftside());
	CRect rect;
	this->GetClientRect(&rect);
	bDC.FillRect(&rect, &brush);
	/////////////////////////
	CFont hfont;
	CFont cfont;
	hfont.CreateFont(20,                     // ���ڳ���
		8,                     // ���ڳʺ�
		0,                      // ��°���
		0,                      // ���� �������ǰ���
		FW_HEAVY,              // ���ڱ���
		FALSE,                  // Italic ���뿩��
		FALSE,                  // �������뿩��
		FALSE,                  // ��Ҽ����뿩��
		DEFAULT_CHARSET,       // ���ڼ�����
		OUT_DEFAULT_PRECIS,    // ������е�
		CLIP_DEFAULT_PRECIS,   // Ŭ�������е�
		DEFAULT_QUALITY,       // ��¹���ǰ��
		DEFAULT_PITCH,         // �۲�Pitch
		_T("Time New Romans")           // �۲�
		);
	cfont.CreateFont(15,                     // ���ڳ���
		7,                     // ���ڳʺ�
		0,                      // ��°���
		0,                      // ���� �������ǰ���
		FW_HEAVY,              // ���ڱ���
		FALSE,                  // Italic ���뿩��
		FALSE,                  // �������뿩��
		FALSE,                  // ��Ҽ����뿩��
		DEFAULT_CHARSET,       // ���ڼ�����
		OUT_DEFAULT_PRECIS,    // ������е�
		CLIP_DEFAULT_PRECIS,   // Ŭ�������е�
		DEFAULT_QUALITY,       // ��¹���ǰ��
		DEFAULT_PITCH,         // �۲�Pitch
		_T("Time New Romans")           // �۲�
		);
	bDC.SetTextColor(RGB(222, 200, 200));
	bDC.SetBkMode(TRANSPARENT);
	bDC.SelectStockObject(NULL_PEN);
	/////////////////////////
	this->btnRect.clear();
	this->velem.clear();
	vector<const SheetElement*>& cvme = this->velem;
	int currID = this->currentID;
	if (currID == 0){
		for (vector<SheetElement>::iterator iter = elems.begin(); iter != elems.end(); ++iter){
			if (iter->parentID == 0)
				cvme.push_back(&(*iter));
		}
	}
	else{
		for (vector<SheetElement>::iterator iter = elems.begin(); iter != elems.end(); ++iter){
			if (iter->parentID == 0 || iter->parentID == currID)
				cvme.push_back(&(*iter));
		}
	}
	CRect myRect(CPoint(5, 10), CPoint(25, 30));
	CRect a(CPoint(55, 10), CPoint(135, 30));
	CRect b(CPoint(35, 10), CPoint(115, 30));
	int m = 20;
	for (int i = 0; i < velem.size(); i++){
		CBrush _brush(velem[i]->color);
		bDC.SelectObject(&_brush);
		CRect temp = velem[i]->topID != 1 ? a : b;
		temp.top = temp.top + m - 20;
		temp.bottom = temp.top + 20;
		btnRect.push_back(temp);
		if (velem[i]->topID == 0){
			m = temp.Height() + m + 10;
			bDC.SelectObject(&cfont);
		}
		else{
			bDC.SelectObject(&hfont);
			m = temp.Height() + m + 20;
		}
		if (flag != -1 && seln == i){
			bDC.SetTextColor(velem[i]->color);
			flag = -1;
		}
		if (selNum == i&& velem[i]->topID != 1){
			CDC memDC;
			memDC.CreateCompatibleDC(&bDC);
			CBitmap bmp;
			bmp.LoadBitmapW(IDB_CHECK);
			BITMAP bmpinfo;
			bmp.GetBitmap(&bmpinfo);
			memDC.SelectObject(&bmp);
			bDC.TransparentBlt(btnRect[selNum].right + 25, btnRect[selNum].top - 10, 25, 25, &memDC, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, RGB(0, 0, 0));
			bDC.SetTextColor(velem[i]->color);
		}
		bDC.TextOutW(btnRect[i].left, btnRect[i].top, velem[i]->name);
		bDC.SetTextColor(RGB(222, 200, 200));
		bDC.RoundRect(btnRect[i].left - 30, btnRect[i].top, btnRect[i].left - 10, btnRect[i].bottom, 5, 5);
		_brush.DeleteObject();
	}
	this->elems.clear();
	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &bDC, 0, 0, SRCCOPY);
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
void GaiaSheetView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CClientDC dc(this);
	CRect temp;
	this->GetClientRect(&temp);
	DblBufMaker dm(&dc, temp);
	CDC& bDC = dm.GetDC();
	auto& name = SingleTon<GaiaGateInfo>::use()->names;
	for (int i = 0; i < velem.size(); i++) {
		if (this->btnRect[i].PtInRect(point) == TRUE) {
			seln = i;
			flag = 1;
			SetCursor(LoadCursor(NULL, IDC_HAND));
			break;
		}
		else{
			SetCursor(LoadCursor(NULL, IDC_ARROW));
		}
	}
	Invalidate(false);
	GaiaCView::OnMouseMove(nFlags, point);
}
void GaiaSheetView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	auto& sel = SingleTon<GaiaGateInfo>::use()->selObj;
	CRect a(CPoint(55, 30), CPoint(135, 50));
	CRect b(CPoint(35, 30), CPoint(115, 50));
	int m = 0;
	int id = 0;
	for (auto it = this->velem.begin(); it != this->velem.end(); it++){
		CRect index = a;
		CBrush b((*it)->color);
		index.top = index.top + m - 20;
		index.bottom = index.top + 20;
		m = index.Height() + m + 20;
		if (index.PtInRect(point) == TRUE) {
			if ((*it)->parentID == 0){	//�θ� 0�� ģ����
				if (sprd == -1){
					this->currentID = (*it)->myID;
					sprd = 1;
				}
				else {
					this->currentID = (*it)->parentID;
					sprd = -1;
				}
			}
			else{
				sel = (*it)->myID;
				CString str;
				str.Format(_T("%d"), sel);
				SingleTon<GaiaSheetListRepo>::use()->sel_lib = (*it)->myID;
				MessageBox(str);
			}
			selNum = id;
			if ((*it)->topID != 1){
				SingleTon<GaiaGateInfo>::use()->isDrawObject = TRUE;
			}
			break;
		}
		else{
			if ((*it)->topID == 0){
				sel = -2;
			}
			SingleTon<GaiaGateInfo>::use()->isDrawObject = FALSE;
			selNum = -1;
		}
		id++;
	}
	this->Invalidate(FALSE);
	GaiaCView::OnLButtonDown(nFlags, point);
}
int GaiaSheetView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (GaiaCView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.
}
