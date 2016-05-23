#include "stdafx.h"
#include "Gaia.h"
#include "GaiaDrawView.h"
#include"DblBufMaker.h"
#include"AndGate.h"
// GaiaDrawView
using namespace design_pattern;

IMPLEMENT_DYNCREATE(GaiaDrawView, GaiaCView)

GaiaDrawView::GaiaDrawView()
{
	GaiaObjectSize.SetLength(10);
}

GaiaDrawView::~GaiaDrawView()
{
}
void GaiaDrawView::DrawSplitterBar() {
	this->OnNcPaint();
}
BEGIN_MESSAGE_MAP(GaiaDrawView, GaiaCView)
	ON_WM_PAINT()
	ON_WM_NCPAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


// GaiaDrawView 그리기입니다.

void GaiaDrawView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.
}


// GaiaDrawView 진단입니다.

#ifdef _DEBUG
void GaiaDrawView::AssertValid() const
{
	GaiaCView::AssertValid();
}

#ifndef _WIN32_WCE
void GaiaDrawView::Dump(CDumpContext& dc) const
{
	GaiaCView::Dump(dc);
}
#endif
#endif //_DEBUG


// GaiaDrawView 메시지 처리기입니다.
void GaiaDrawView::DrawArea(CDC* pDC){
	CBrush brush(SingleTon<GaiaLayoutRepo>::use()->Getrightside());
	CRect rect;
	this->GetClientRect(&rect);

	pDC->FillRect(&rect, &brush);
	brush.DeleteObject();

	CPen pen;
	pen.CreatePen(PS_DOT, 1, RGB(49, 49, 49));
	auto& grid = SingleTon<GaiaDrawGrid>::use()->grid;
	for (int i = rect.left; i < rect.right; i += 10){
		for (int j = rect.top; j < rect.bottom; j += 10){
			COLORREF color = RGB(83, 83, 83);
			if (grid[i / 10][j / 10]){
				color = RGB(255, 0, 0);
			}
			pDC->SetPixel(i + 1, j, color);
			pDC->SetPixel(i, j + 1, color);
			pDC->SetPixel(i - 1, j, color);
			pDC->SetPixel(i, j - 1, color);
		}
	}

	auto& e = SingleTon<GaiaDrawGrid>::use()->objects;
	for (auto& elem : e){
		elem->Draw(pDC);
	}
	auto& edges = SingleTon<GaiaDrawGrid>::use()->edges;
	for (auto& elem : edges){
		DrawWay(pDC, elem.second);
	}

	//pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &bDC, 0, 0, SRCCOPY);
}
void GaiaDrawView::OnPaint() {
	/*
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 GaiaCView::OnPaint()을(를) 호출하지 마십시오.
	CDC memDC;
	memDC.CreateCompatibleDC(&dc);
	CBitmap bmp;
	HBITMAP hBmp = (HBITMAP)::LoadImage(AfxGetInstanceHandle(),
	_T("hhh.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	bmp.Attach(hBmp);
	BITMAP bmpinfo;
	bmp.GetBitmap(&bmpinfo);

	if (hBmp)
	{
	::SelectObject(memDC, hBmp);
	dc.BitBlt(0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, &memDC, 0, 0, SRCCOPY);
	}*/
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 GaiaCView::OnPaint()을(를) 호출하지 마십시오.
	if (this->isLDown == FALSE){
		this->DrawArea(&dc);
	}
}


void GaiaDrawView::OnNcPaint()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 GaiaCView::OnNcPaint()을(를) 호출하지 마십시오.
	CWindowDC dc(::AfxGetMainWnd());
	CBrush brush(SingleTon<GaiaLayoutRepo>::use()->Getrightside());
	CRect drawRect;
	CRect temp;
	this->GetWindowRect(&drawRect);
	drawRect.NormalizeRect();
	drawRect.OffsetRect(-drawRect.left, -drawRect.top);
	int captionHeight = ::GetSystemMetrics(SM_CYCAPTION) + ::GetSystemMetrics(SM_CYFRAME) + 5;
	drawRect.OffsetRect(8, captionHeight);
	drawRect.right += 10;
	drawRect.bottom += 7;
	int mvcnt = SingleTon<GaiaSheetListRepo>::use()->Getwidth() + SingleTon<GaiaToolListRepo>::use()->Getwidth();
	drawRect.left += mvcnt;
	drawRect.right += mvcnt;

	temp = drawRect;
	temp.bottom = temp.top + 5;
	dc.FillRect(&temp, &brush);		//위쪽 스플린터바 색칠
	temp = drawRect;
	temp.right = temp.left + 6;
	dc.FillRect(&temp, &brush);		//왼쪽 스플린터바 색칠
	temp = drawRect;
	temp.top = temp.bottom - 4;
	dc.FillRect(&temp, &brush);		//아래쪽 스플린터바 색칠
	temp = drawRect;
	temp.left = temp.right - 10;
	dc.FillRect(&temp, &brush);		//오른쪽 스플린터바 색칠
	brush.DeleteObject();
}


void GaiaDrawView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CClientDC dc(this);
	CRect rect;
	this->GetClientRect(rect);
	DblBufMaker dm(&dc, rect);
	CDC& bDC = dm.GetDC();

	CBrush brush(RGB(103, 153, 255));
	CPen pen;
	pen.CreatePen(PS_NULL, 0, RGB(0, 0, 0));
	dc.SelectObject(&brush);
	dc.SelectObject(&pen);

	auto& e = SingleTon<GaiaDrawGrid>::use()->objects;



	if (this->sel != -1){
		auto& edges = SingleTon<GaiaDrawGrid>::use()->edges;

		for (auto& elem : edges){
			if (e[sel]->out.CenterPoint() == elem.first.first || e[sel]->out.CenterPoint() == elem.first.second){
				DrawWay(&bDC, elem.second, false);
			}
			if (e[sel]->in1.CenterPoint() == elem.first.first || e[sel]->in1.CenterPoint() == elem.first.second){
				DrawWay(&bDC, elem.second, false);
			}
			if (e[sel]->in2.CenterPoint() == elem.first.first || e[sel]->in2.CenterPoint() == elem.first.second){
				DrawWay(&bDC, elem.second, false);
			}
		}
		int dx = point.x - clickPoint.x;
		int dy = point.y - clickPoint.y;

		//가능한 곳인지 검사
		bool possible = true;
		auto& grid = SingleTon<GaiaDrawGrid>::use()->grid;
		int bx = e[sel]->base_point.x / 10;
		int by = e[sel]->base_point.y / 10;
		for (int i = by; i < by + GaiaObjectSize.GetLength(); i++){
			for (int j = bx; j < bx + GaiaObjectSize.GetLength(); j++){
				if (grid[j][i] == true){
					possible = false;
					goto LABEL1;
				}
			}
		}
	LABEL1:{}
		if (possible){
			e[sel]->mv = RGB(178, 204, 255);
		}
		else{
			e[sel]->mv = RGB(255, 167, 167);
		}
		e[sel]->base_point.x = clickBase.x + dx;
		e[sel]->base_point.y = clickBase.y + dy;
		printf("%d %d\n", dx, dy);
		this->DrawArea(&bDC);
	}
	else{
		this->DrawArea(&bDC);
		static CPoint before_pt = { 0, 0 };
		if (this->isLDown == TRUE){
			curr.second = point;
			way = DrawEdge(&bDC, curr, this);
		}
		for (auto& elem : e){
			if (elem->out.PtInRect(point) == TRUE){
				dc.Ellipse(elem->out);
				return;
			}
			else if (elem->in1.PtInRect(point) == TRUE){
				dc.Ellipse(elem->in1);
				return;
			}
			else if (elem->in2.PtInRect(point) == TRUE){
				dc.Ellipse(elem->in2);
				return;
			}
		}
	}
	brush.DeleteObject();
	pen.DeleteObject();
	SetCursor(LoadCursor(NULL, IDC_ARROW));
	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &bDC, 0, 0, SRCCOPY);
	GaiaCView::OnMouseMove(nFlags, point);
}


int GaiaDrawView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (GaiaCView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	GaiaObject* p = new AndGate();
	p->SetPoint(10, 10);
	SingleTon<GaiaDrawGrid>::use()->objects.push_back(p);
	p = new AndGate();
	p->SetPoint(20, 20);
	p->SetRadius(1);
	SingleTon<GaiaDrawGrid>::use()->objects.push_back(p);

	p = new AndGate();
	p->SetPoint(20, 40);
	p->SetRadius(0);
	SingleTon<GaiaDrawGrid>::use()->objects.push_back(p);

	p = new AndGate();
	p->SetPoint(40, 40);
	p->SetRadius(0);
	SingleTon<GaiaDrawGrid>::use()->objects.push_back(p);

	p = new AndGate();
	p->SetPoint(60, 40);
	p->SetRadius(0);
	SingleTon<GaiaDrawGrid>::use()->objects.push_back(p);
	p = new AndGate();
	p->SetPoint(60, 10);
	p->SetRadius(0);
	SingleTon<GaiaDrawGrid>::use()->objects.push_back(p);
	return 0;
}


BOOL GaiaDrawView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	return TRUE;
	return GaiaCView::OnEraseBkgnd(pDC);
}


void GaiaDrawView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	auto& e = SingleTon<GaiaDrawGrid>::use()->objects;
	CRect* rect = nullptr;
	for (auto& elem : e){
		if (elem->out.PtInRect(point) == TRUE){
			rect = &elem->out;
			break;
		}
	}
	if (rect != nullptr){
		CPoint p = rect->CenterPoint();
		this->curr = { { p.x, p.y }, { 0, 0 } };
		this->isLDown = TRUE;
		return;
	}
	sel = -1;
	for (int i = 0; i < e.size(); i++){
		if (e[i]->baseRect.PtInRect(point) == TRUE){
			sel = i;
			clickPoint = point;
			e[i]->ClearPoint();
			clickBase = e[i]->base_point;
			break;
		}
	}
	GaiaCView::OnLButtonDown(nFlags, point);
}


void GaiaDrawView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (sel != -1){
		auto& e = SingleTon<GaiaDrawGrid>::use()->objects;

		if (e[sel]->mv == RGB(255, 167, 167)){
			auto& grid = SingleTon<GaiaDrawGrid>::use()->grid;


			e[sel]->base_point = clickBase;
		}
		e[sel]->SetPoint();
		e[sel]->mv = RGB(0, 0, 0);
	}
	sel = -1;
	if (this->isLDown == TRUE){
		auto& e = SingleTon<GaiaDrawGrid>::use()->objects;
		CRect* ptr = nullptr;
		for (auto& elem : e){
			if (elem->in1.PtInRect(point) == TRUE){
				ptr = &elem->in1;
				break;
			}
			else if (elem->in2.PtInRect(point) == TRUE){
				ptr = &elem->in2;
				break;
			}
		}
		if (ptr != nullptr){
			curr.second = ptr->CenterPoint();
			way.pop_front();
			way.push_front(*ptr);

			SingleTon<GaiaDrawGrid>::use()->edges.push_back(PDV(this->curr, way));
			auto& grid = SingleTon<GaiaDrawGrid>::use()->grid;
			int x = curr.second.x / 10;
			int y = curr.second.y / 10;
			grid[x][y - 1] = true;
			grid[x][y] = true;
			grid[x][y + 1] = true;
			grid[x - 1][y - 1] = true;
			grid[x - 1][y] = true;
			grid[x - 1][y + 1] = true;
			grid[x + 1][y - 1] = true;
			grid[x + 1][y] = true;
			grid[x + 1][y + 1] = true;

		}
		this->isLDown = FALSE;
	}
	GaiaCView::OnLButtonUp(nFlags, point);
}
