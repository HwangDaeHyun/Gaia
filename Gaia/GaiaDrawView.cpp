#include "stdafx.h"
#include"GaiaDoc.h"
#include "Gaia.h"
#include "GaiaDrawView.h"
#include"DblBufMaker.h"
#include"GaiaObject.h"
#include"AndGate.h"
#include"OrGate.h"
#include"NotGate.h"
#include"XorGate.h"
#include"NandGate.h"
#include"NorGate.h"
#include"DFF.h"
#include"TFF.h"
#include"JKFF.h"
#include"LibBox.h"
#include"InputBtn.h"
#include "SevenSegment.h"
#include"OutLamp.h"
#include"ClockCycle.h"
#include"GaiaListInfo.h"
// GaiaDrawView
using namespace design_pattern;

IMPLEMENT_DYNCREATE(GaiaDrawView, GaiaCView)

GaiaDrawView::GaiaDrawView()
{
	SingleTon<GaiaObjectSizeInfo>::use()->SetLength(8);
	SingleTon<GaiaObjectSizeInfo>::use()->SetSmallLength(6);
	SingleTon<GaiaObjectSizeInfo>::use()->SetBigLength(10);
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
	ON_WM_SIZE()
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_EDIT_COPY, OnCopy)
	ON_COMMAND(ID_EDIT_CUT, OnCut)
	ON_COMMAND(ID_EDIT_PASTE, OnPaste)
	ON_WM_TIMER()
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
	CBrush brush(SingleTon<GaiaLayoutRepo>::use()->Getmidside());
	CRect rect;
	this->GetClientRect(&rect);

	pDC->FillRect(&rect, &brush);
	brush.DeleteObject();

	CPen pen;
	pen.CreatePen(PS_DOT, 3, RGB(0, 0, 0));
	auto& grid = SingleTon<GaiaDrawGrid>::use()->grid;
	for (int i = rect.left; i < rect.right; i += 10){
		for (int j = rect.top; j < rect.bottom; j += 10){
			COLORREF color = RGB(200, 198, 220);
			if (grid[i / 10][j / 10]){
				color = RGB(225, 135, 135);
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

	// 선택한 오브젝트의 테두리를 표시합니다
	auto& s = SingleTon<GaiaDrawGrid>::use()->sel_objects;
	if (s.empty() != TRUE){
		for (auto& elem : s){
			CPen p;
			CBrush b(RGB(255, 255, 255));
			p.CreatePen(PS_SOLID, 1, RGB(20, 20, 20));
			pDC->SelectObject(&p);
			pDC->SelectObject(&b);
			//pDC->MoveTo(elem->baseRect.left, elem->baseRect.top);
			int d = elem->baseRect.Height();
			int rec_sz = 8;
			pDC->Rectangle(elem->base_point.x, elem->base_point.y, elem->base_point.x + rec_sz, elem->base_point.y + rec_sz);
			pDC->Rectangle(elem->base_point.x + d, elem->base_point.y, elem->base_point.x + d + rec_sz, elem->base_point.y + rec_sz);
			pDC->Rectangle(elem->base_point.x, elem->base_point.y + d, elem->base_point.x + rec_sz, elem->base_point.y + d + rec_sz);
			pDC->Rectangle(elem->base_point.x + d, elem->base_point.y + d, elem->base_point.x + d + rec_sz, elem->base_point.y + d + rec_sz);
			p.DeleteObject();
			b.DeleteObject();
		}
	}
	// ===



	//pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &bDC, 0, 0, SRCCOPY);
}
void GaiaDrawView::OnPaint() {
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 GaiaCView::OnPaint()을(를) 호출하지 마십시오.
	CRect rect;
	this->GetClientRect(rect);
	DblBufMaker dm(&dc, rect);
	CDC& bDC = dm.GetDC();
	if (this->isLDown == FALSE){
		this->DrawArea(&bDC);
	}
	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &bDC, 0, 0, SRCCOPY);
}
void GaiaDrawView::OnNcPaint()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 GaiaCView::OnNcPaint()을(를) 호출하지 마십시오.
	CWindowDC dc(::AfxGetMainWnd());
	CBrush brush(SingleTon<GaiaLayoutRepo>::use()->Getmidside());
	CRect drawRect;
	CRect temp;
	this->GetWindowRect(&drawRect);
	drawRect.NormalizeRect();
	drawRect.OffsetRect(-drawRect.left, -drawRect.top);
	int captionHeight = ::GetSystemMetrics(SM_CYCAPTION) + ::GetSystemMetrics(SM_CYFRAME) + 5;
	int sheetWidth = SingleTon<GaiaSheetListRepo>::use()->Getwidth();
	drawRect.OffsetRect(8 + sheetWidth, captionHeight);
	drawRect.right += 10;
	drawRect.bottom += 7;
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
	temp.left = temp.right - 7;
	dc.FillRect(&temp, &brush);		//오른쪽 스플린터바 색칠
	brush.DeleteObject();

}

void GaiaDrawView::OnMouseMove(UINT nFlags, CPoint point)
{
	GaiaDoc* pDoc = (GaiaDoc*)GetDocument();
	point.x += 5;
	point.y += 5;
	point.x /= 10;
	point.y /= 10;
	point.x *= 10;
	point.y *= 10;

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
		int dx = point.x - clickPoint.x;
		int dy = point.y - clickPoint.y;
		bool possible = true;
		if (rect.left + 20 >= point.x){
			dx = 0;
			possible = false;
			CPoint temp = clickPoint;
			ClientToScreen(&temp);
			::SetCursorPos(temp.x, temp.y);
		}
		if (rect.top + 20 >= point.y){
			dy = 0;
			possible = false;
			CPoint temp = clickPoint;
			ClientToScreen(&temp);
			::SetCursorPos(temp.x, temp.y);
		}
		//가능한 곳인지 검사
		if (possible == true){
			auto& grid = SingleTon<GaiaDrawGrid>::use()->grid;
			int bx = e[sel]->base_point.x / 10;
			int by = e[sel]->base_point.y / 10;

			for (int i = by; i < by + e[sel]->GetLength(); i++){
				for (int j = bx; j < bx + e[sel]->GetLength(); j++){
					if (grid[j][i] == true){
						possible = false;
						goto LABEL1;
					}
				}
			}
		}
	LABEL1:{}
		//게이트를 옮길때 구동하는 함수

		this->MoveLogic(bDC, possible);
		//
		e[sel]->base_point.x = clickBase.x + dx;
		e[sel]->base_point.y = clickBase.y + dy;

	}
	else{
		this->DrawArea(&bDC);
		static CPoint before_pt = { 0, 0 };
		if (this->isLDown == TRUE){
			curr.second = point;
			way = DrawEdge(&bDC, curr, this);
		}
		for (auto& elem : e){
			CBrush temp(RGB(220, 100, 200));
			dc.SelectObject(&temp);
			auto& out = elem->outs;
			for (int i = 0; i < out.size(); i++){
				if (out[i].PtInRect(point) == TRUE){
					dc.Ellipse(out[i]);
					return;
				}
			}
			auto& in = elem->ins;
			for (int i = 0; i < in.size(); i++){
				if (in[i].PtInRect(point) == TRUE){
					dc.Ellipse(in[i]);
					return;
				}
			}
			if (elem->clk.PtInRect(point) == TRUE){
				dc.Ellipse(elem->clk);
				return;
			}
		}
	}
	if (this->isDrag){
		this->draggedRect = DrawDragRect(bDC, this->dragSrc, point);
	}
	//== 선택한 오브젝트 이미지가 마우스를 따라옵니다.
	//== AND 오브젝트만 있고 나머지는 추가해야함
	this->AddingLogic(bDC, point);
	//==
	brush.DeleteObject();
	pen.DeleteObject();
	SetCursor(LoadCursor(NULL, IDC_ARROW));
	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &bDC, 0, 0, SRCCOPY);
	GaiaCView::OnMouseMove(nFlags, point);
}

CRect GaiaDrawView::DrawDragRect(CDC& bDC, CPoint leftTop, CPoint rightBottom){
	Graphics graphics(bDC);
	SolidBrush  semiTransBrush(Color(100, 100, 100, 255));
	CRect tempRect(leftTop, rightBottom);
	CBrush brush(RGB(200, 200, 255));
	graphics.FillRectangle(&semiTransBrush, leftTop.x, leftTop.y, rightBottom.x - leftTop.x, rightBottom.y - leftTop.y);
	return tempRect;
}
void GaiaDrawView::AddingLogic(CDC& bDC, CPoint point){
	if (SingleTon<GaiaGateInfo>::use()->isDrawObject == TRUE && SingleTon<GaiaGateInfo>::use()->selObj != -1){
		CDC memDC;
		memDC.CreateCompatibleDC(&bDC);
		CBitmap bmp;
		auto& selNum = SingleTon<GaiaGateInfo>::use()->selObj;
		int w = 60;
		int h = 60;
		CBrush brush(RGB(200, 110, 111));
		CBrush brush2(RGB(0, 0, 100));
		CBrush brush3(RGB(255, 255, 255));
		CPen pen;
		pen.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));

		BOOL isBMP = TRUE;	// 비트맵이 아니라 다른거 그리려면 case에서 FALSE로
		if (selNum < 10 && selNum > 0){
			auto& lib = SingleTon<GaiaDrawGrid>::use()->lib_objects;
			drawObj = new LibBox(selNum - 1);
		}
		else{
			switch (SingleTon<GaiaGateInfo>::use()->selObj){
			case 10:
				drawObj = new AndGate();
				bmp.LoadBitmapW(IDB_AND_0);
				break;
			case 11:
				drawObj = new OrGate();
				bmp.LoadBitmapW(IDB_OR_0);
				break;
			case 12:	//Not
				drawObj = new NotGate();
				bmp.LoadBitmapW(IDB_NOT_0);
				break;
			case 13:	//Nand
				drawObj = new NandGate();
				bmp.LoadBitmapW(IDB_NAND_0);
				w = 70;
				break;
			case 14:	//Nor
				drawObj = new NorGate();
				bmp.LoadBitmapW(IDB_NOR_0);
				break;
			case 15:	//Xor
				drawObj = new XorGate();
				bmp.LoadBitmapW(IDB_XOR_0);
				break;
			case 26:	//D FF
				drawObj = new DFF();
				bmp.LoadBitmapW(IDB_DFF);
				break;
			case 27:	//T FF
				drawObj = new TFF();
				bmp.LoadBitmapW(IDB_TFF);
				break;
			case 28:	//JK FF
				drawObj = new JKFF();
				bmp.LoadBitmapW(IDB_JKFF_0);
				break;

				//case 39:	//7 Seg
				//	break;
			case 40:	//input
				isBMP = FALSE;
				drawObj = new InputBtn();
				bDC.SelectObject(&brush2);
				bDC.RoundRect(CRect(point.x - 20, point.y - 20, point.x + 10, point.y + 10), { 30, 30 });
				bDC.SelectObject(&brush);
				bDC.Ellipse(point.x - 18, point.y - 18, point.x + 8, point.y + 8);
				break;
			case 41:	//output
				isBMP = FALSE;
				bDC.SelectObject(&brush3);
				bDC.SelectObject(pen);
				drawObj = new OutLamp();
				bDC.Ellipse(point.x - 25, point.y - 25, point.x + 20, point.y + 20);
				break;
			}
			if (isBMP == TRUE){
				BITMAP bmpinfo;
				CBitmap* oldbmp = memDC.SelectObject(&bmp);
				bmp.GetBitmap(&bmpinfo);
				memDC.SelectObject(&bmp);
				bDC.TransparentBlt(point.x - 30, point.y - 30, w, h, &memDC, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, RGB(0, 0, 0));
				memDC.SelectObject(oldbmp);
			}
		}
	}
}
void GaiaDrawView::MoveLogic(CDC& bDC, bool& possible){

	auto& e = SingleTon<GaiaDrawGrid>::use()->objects;
	auto& edges = SingleTon<GaiaDrawGrid>::use()->edges;
	if (possible){
		DblPoint dPt;

		e[sel]->mv = RGB(178, 204, 255);
		if (inIdx.empty() && outIdx.empty()){
			inIdx.assign(e[sel]->ins.size(), -1);
			outIdx.assign(e[sel]->outs.size(), -1);
		}
		this->DrawArea(&bDC);
		if (tempEdges.empty()){
			for (int i = 0; i < edges.size(); i++){
				for (int j = 0; j < e[sel]->outs.size(); j++){
					if (e[sel]->outs[j].PtInRect(edges[i].first.first)){
						if (outIdx[j] != -1){
							dPt = { { e[sel]->outs[j].CenterPoint().x, e[sel]->outs[j].CenterPoint().y }, { edges[i].first.second.x, edges[i].first.second.y } };
							PaintGrid({ dPt.second.x / 10, dPt.second.y / 10 }, false);
							tempEdges.push_back(*(edges.begin() + i));
							edges.erase(edges.begin() + i);
							tempOut.push_back(pair<int, int>(tempEdges.size() - 1, j));
							i -= 1;
							goto L;
						}
						else{
							dPt = { { e[sel]->outs[j].CenterPoint().x, e[sel]->outs[j].CenterPoint().y }, { edges[i].first.second.x, edges[i].first.second.y } };
							PaintGrid({ dPt.second.x / 10, dPt.second.y / 10 }, false);
							tempEdges.push_back(*(edges.begin() + i));
							edges.erase(edges.begin() + i);
							outIdx[j] = tempEdges.size() - 1;
							i -= 1;
							goto L;
						}
					}
				}
				for (int j = 0; j < e[sel]->ins.size(); j++){
					if (e[sel]->ins[j].PtInRect(edges[i].first.second)){
						dPt = { { edges[i].first.first.x, edges[i].first.first.y }, { e[sel]->ins[j].CenterPoint().x, e[sel]->ins[j].CenterPoint().y } };
						PaintGrid({ dPt.second.x / 10, dPt.second.y / 10 }, false);
						tempEdges.push_back(*(edges.begin() + i));
						edges.erase(edges.begin() + i);
						inIdx[j] = tempEdges.size() - 1;
						i -= 1;
						goto L;
					}
				}
				if (e[sel]->clk.PtInRect(edges[i].first.second)){
					dPt = { { edges[i].first.first.x, edges[i].first.first.y }, { e[sel]->clk.CenterPoint().x, e[sel]->clk.CenterPoint().y } };
					PaintGrid({ dPt.second.x / 10, dPt.second.y / 10 }, false);
					tempEdges.push_back(*(edges.begin() + i));
					edges.erase(edges.begin() + i);
					this->clkIdx = tempEdges.size() - 1;
					i -= 1;
				}
			L:{};
			}
		}
		else{
			plusWays.clear();
			if (s_outIdx.empty() && s_inIdx.empty()){
				s_outIdx.assign(outIdx.size(), -1);
				s_inIdx.assign(inIdx.size(), -1);
				s_tempOut.assign(tempOut.size(), pair<int, int>(-1, -1));
			}

			for (int i = 0; i < tempEdges.size(); i++){
				DblPoint ddPt;
				deque<CRect> uWay;
				for (int j = 0; j < this->inIdx.size(); j++){
					if (i == inIdx[j]){
						ddPt = { tempEdges[i].first.first, { e[sel]->ins[j].CenterPoint().x, e[sel]->ins[j].CenterPoint().y } };
						uWay = DrawEdge(&bDC, ddPt, this);
						//this->s_inIdx[j] = i;
						uWay.push_front(e[sel]->ins[j]);
						goto L2;
					}
				}
				for (int j = 0; j < this->outIdx.size(); j++){
					if (i == outIdx[j]){
						ddPt = { { e[sel]->outs[j].CenterPoint().x, e[sel]->outs[j].CenterPoint().y }, { tempEdges[i].first.second } };
						uWay = DrawEdge(&bDC, ddPt, this);
						//this->s_outIdx[j] = i; 
						uWay.push_back(e[sel]->outs[j]);
						goto L2;
					}
				}
				for (int j = 0; j < this->tempOut.size(); j++){
					if (i == tempOut[j].first){
						ddPt = { { e[sel]->outs[tempOut[j].second].CenterPoint().x, e[sel]->outs[tempOut[j].second].CenterPoint().y }, { tempEdges[i].first.second } };
						uWay = DrawEdge(&bDC, ddPt, this);
						this->s_tempOut.push_back(pair<int, int>(j, i));
						uWay.push_back(e[sel]->outs[tempOut[j].second]);
						goto L2;
					}
				}
				if (i == this->clkIdx){
					ddPt = { tempEdges[i].first.first, { e[sel]->clk.CenterPoint().x, e[sel]->clk.CenterPoint().y } };
					uWay = DrawEdge(&bDC, ddPt, this);
					//PaintGrid(ddPt.second);
					//	this->sClkIdx = i;
					uWay.push_front(e[sel]->clk);
				}

			L2:{};
				plusWays.push_back(PDV(ddPt, uWay));
			}
		}
	}
	else{
		this->DrawArea(&bDC);
		e[sel]->mv = RGB(255, 167, 167);
	}
}
int GaiaDrawView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (GaiaCView::OnCreate(lpCreateStruct) == -1)
		return -1;
	auto& db = SingleTon<GaiaDrawGrid>::use()->dBoard;
	memset(db, -1, sizeof(int)*GSIZE*GSIZE);
	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	GaiaDoc* pDoc = (GaiaDoc*)GetDocument();
	pDoc->PushGaiaList();
	auto& obj = SingleTon<GaiaDrawGrid>::use()->objects;
	GaiaObject* p = new TFF();
	p->SetPoint(20, 20);
	obj.push_back(p);
	p = new ClockCycle(30, 30);
	obj.push_back(p);
	p = new InputBtn(50, 30);
	obj.push_back(p);
	p = new InputBtn(10, 10);
	obj.push_back(p);
	p = new OutLamp();
	p->SetPoint(30, 50);
	obj.push_back(p);

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
	GaiaDoc* pDoc = (GaiaDoc*)GetDocument();
	point.x += 5;
	point.y += 5;
	point.x /= 10;
	point.y /= 10;
	point.x *= 10;
	point.y *= 10;
	auto& e = SingleTon<GaiaDrawGrid>::use()->objects;
	CRect* rect = nullptr;
	//버튼이 눌렸는지 검사합니다.

	//
	for (auto& elem : e){
		for (int i = 0; i < elem->outs.size(); i++){
			if (elem->outs[i].PtInRect(point) == TRUE){
				rect = &elem->outs[i];
				goto R;
			}
		}
	}
R:{};
	if (rect != nullptr){
		if (pDoc->tempNode == nullptr){
			pDoc->SetTempGaiaListNode();
		}
		CPoint p = rect->CenterPoint();
		this->curr = { { p.x, p.y }, { 0, 0 } };
		this->isLDown = TRUE;
		return;
	}
	sel = -1;
	//오브젝트 하나를 선택합니다.
	for (int i = 0; i < e.size(); i++){
		if (e[i]->baseRect.PtInRect(point) == TRUE){
			sel = i;
			clickPoint = point;
			e[i]->ClearPoint();
			clickBase = e[i]->base_point;
			SingleTon<GaiaDrawGrid>::use()->sel_objects.clear();
			SingleTon<GaiaDrawGrid>::use()->sel_objects.push_back(e[i]);
			SingleTon<GaiaDrawGrid>::use()->sel_idx.clear();
			SingleTon<GaiaDrawGrid>::use()->sel_idx.push_back(i);
			break;
		}
	}

	if (sel != -1){

		auto& tbl = SingleTon<GaiaTableInfo>::use()->contents;
		
		while (tbl.size() > 2){
			tbl.pop_back();
		}
		
		SingleTon<GaiaTableInfo>::use()->title = e[sel]->name;
		tbl[0].second = e[sel]->arrow;
		tbl[1].second = e[sel]->name;
		auto& tdb = SingleTon<GaiaDrawGrid>::use()->dBoard;
		vector<SPAIR> temp;
		temp.assign(e[sel]->outs.size(), SPAIR());
		CString t_str;
		CString index;
		for (int i = 0; i < temp.size(); i++){
			t_str.Format(_T("%d"), tdb[e[sel]->outs[i].CenterPoint().x / 10][e[sel]->outs[i].CenterPoint().y / 10]);
			index.Format(_T("%d"), i+1);
			index = _T("out (") + index + _T(")");
			temp[i].first = index;
			temp[i].second = t_str;
			tbl.push_back(temp[i]);
		}
		CString trigger, clk_name;
		SPAIR tTable;
		tTable.first = _T("Trigger");
		if (e[sel]->trigger == RISING){
			clk_name = _T("RISING");
			tTable.second = clk_name;
			tbl.push_back(tTable);
		}
		else if (e[sel]->trigger == FALLING){
			clk_name = _T("FALLING");
			tTable.second = clk_name;
			tbl.push_back(tTable);
		}
		SingleTon<GaiaTableInfo>::use()->isSel = true;
		SingleTon<GaiaTableInfo>::use()->selNum = sel;
		SingleTon<GaiaLayoutRepo>::use()->views[3]->Invalidate(false);
		////
		auto& db = SingleTon<GaiaDrawGrid>::use()->dBoard;
		// ?? 무슨처리를 해놓은걵지 명시할것 옮기기전에 데이터 값들을 저장해놓습니다 . in -> out -> clk 순으로
		for (int i = 0; i < e[sel]->ins.size(); i++){
			prevData.push_back(db[e[sel]->ins[i].CenterPoint().x / 10][e[sel]->ins[i].CenterPoint().y / 10]);
			db[e[sel]->ins[i].CenterPoint().x / 10][e[sel]->ins[i].CenterPoint().y / 10] = -1;
		}
		for (int i = 0; i < e[sel]->outs.size(); i++){
			prevData.push_back(db[e[sel]->outs[i].CenterPoint().x / 10][e[sel]->outs[i].CenterPoint().y / 10]);
			db[e[sel]->outs[i].CenterPoint().x / 10][e[sel]->outs[i].CenterPoint().y / 10] = -1;
		}
		prevData.push_back(db[e[sel]->clk.CenterPoint().x / 10][e[sel]->clk.CenterPoint().y / 10]);
		db[e[sel]->clk.CenterPoint().x / 10][e[sel]->clk.CenterPoint().y / 10] = -1;

		auto& t = SingleTon<GaiaDrawGrid>::use()->inBtns;
		for (int i = 0; i < t.size(); i++){
			for (int j = 0; j < e[sel]->outs.size(); j++){
				if (t[i] == e[sel]->outs[j]){
					t.erase(t.begin() + i);
				}
			}
		}
	}
	else{
		SingleTon<GaiaDrawGrid>::use()->sel_objects.clear();
		this->isDrag = true;
		this->dragSrc = point;
	}
	//== Object를 그립니다
	if (SingleTon<GaiaGateInfo>::use()->isDrawObject == TRUE){

		pDoc->PushGaiaList();
		//
		e.push_back(drawObj);
		e.back()->SetPoint((point.x - 30) / 10, (point.y - 30) / 10);
		SingleTon < GaiaGateInfo>::use()->isDrawObject = FALSE;
		SingleTon<GaiaSheetListRepo>::use()->sel_btn = -1;

	}
	//==
	GaiaCView::OnLButtonDown(nFlags, point);
}


void GaiaDrawView::OnLButtonUp(UINT nFlags, CPoint point)
{
	GaiaDoc* pDoc = (GaiaDoc*)GetDocument();
	point.x += 5;
	point.y += 5;
	point.x /= 10;
	point.y /= 10;
	point.x *= 10;
	point.y *= 10;
	CClientDC dc(this);
	CRect rect;
	this->GetClientRect(rect);
	DblBufMaker dm(&dc, rect);
	CDC& bDC = dm.GetDC();
	////////////////////////////////////////////////
	fill(this->inIdx.begin(), this->inIdx.end(), -1);
	fill(this->outIdx.begin(), this->outIdx.end(), -1);
	this->clkIdx = -1;
	this->tempOut.clear();
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (this->isDrag && this->dragSrc != point){
		this->isDrag = false;
		auto& e = SingleTon<GaiaDrawGrid>::use()->objects;
		auto& s = SingleTon<GaiaDrawGrid>::use()->sel_objects;
		auto& sel_idx = SingleTon<GaiaDrawGrid>::use()->sel_idx;
		vector<int>* datas = SearchObjects(&bDC, this->draggedRect);
		for (int i = 0; i < datas->size(); i++){
			s.push_back(e[datas->at(i)]);
			sel_idx.push_back(datas->at(i));
		}
		datas->~vector();
	}
	else{
		this->isDrag = FALSE;
	}
	if (sel != -1){
		pDoc->PushGaiaList();
		auto& e = SingleTon<GaiaDrawGrid>::use()->objects;
		auto& edges = SingleTon<GaiaDrawGrid>::use()->edges;
		auto& grid = SingleTon<GaiaDrawGrid>::use()->grid;
		if (e[sel]->mv == RGB(255, 167, 167)){
			for (int i = 0; i < tempEdges.size(); i++){
				edges.push_back(tempEdges[i]);
			}
			e[sel]->base_point = clickBase;
		}
		else{
			pDoc->PushTempNode();
			if (!plusWays.empty()){
				for_each(plusWays.begin(), plusWays.end(), [&edges](PDV& i)->void{edges.push_back(i); });
				plusWays.clear();
			}
			this->isLDown = FALSE;
		}
		tempEdges.clear();
		e[sel]->SetPoint();
		e[sel]->mv = RGB(0, 0, 0);
		///////
		auto& db = SingleTon<GaiaDrawGrid>::use()->dBoard;
		int tCnt = 0;
		// in -> out -> clock 순
		for (int i = 0; i < e[sel]->ins.size(); i++){
			db[e[sel]->ins[i].CenterPoint().x / 10][e[sel]->ins[i].CenterPoint().y / 10] = prevData[tCnt];
			tCnt++;
		}
		for (int i = 0; i < e[sel]->outs.size(); i++){
			db[e[sel]->outs[i].CenterPoint().x / 10][e[sel]->outs[i].CenterPoint().y / 10] = prevData[tCnt];
			tCnt++;
		}
		db[e[sel]->clk.CenterPoint().x / 10][e[sel]->clk.CenterPoint().y / 10] = prevData[tCnt];
		auto& btn = SingleTon<GaiaDrawGrid>::use()->inBtns;
		if (e[sel]->objKind == INBUTTON){
			btn.push_back(e[sel]->outs[0]);
		}
		prevData.clear();
		//
		this->sel = -1;
	}
	else{
		if (this->isLDown == TRUE){
			auto& e = SingleTon<GaiaDrawGrid>::use()->objects;
			CRect* ptr = nullptr;
			for (auto& elem : e){
				for (int i = 0; i < elem->ins.size(); i++){
					if (elem->ins[i].PtInRect(point) == TRUE){
						ptr = &elem->ins[i];
						goto SPOT;
					}
				}
				if (elem->clk.PtInRect(point) == TRUE){
					ptr = &elem->clk;
					break;
				}
			}
		SPOT:{};
			if (ptr != nullptr&&  !way.empty()){
				curr.second = ptr->CenterPoint();
				//way.pop_front();
				way.push_front(*ptr);
				SingleTon<GaiaDrawGrid>::use()->edges.push_back(PDV(this->curr, way));
				int x = curr.second.x / 10;
				int y = curr.second.y / 10;
				CPoint clearPoint(x, y);
				PaintGrid(clearPoint);
				pDoc->PushTempNode();

			}

			this->isLDown = FALSE;
		}
	}
	UpdateDBoard();
	//auto& inBtns =SingleTon<GaiaDrawGrid>::use()->inBtns;

	auto& objs = SingleTon<GaiaDrawGrid>::use()->objects;
	for (int i = 0; i < objs.size(); i++){
		for (int j = 0; j < objs[i]->outs.size(); j++){
			Update(objs[i]->outs[j]);
		}
	}

	DrawArea(&bDC);
	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &bDC, 0, 0, SRCCOPY);
	GaiaCView::OnLButtonUp(nFlags, point);
}


void GaiaDrawView::OnSize(UINT nType, int cx, int cy)
{
	GaiaCView::OnSize(nType, cx, cy);
	if (cx > 0){
		SingleTon<GaiaDrawListRepo>::use()->Setwidth(cx + 10);
	}
	else if (SingleTon<GaiaLayoutRepo>::use()->GetspView() != nullptr && cx < 100){
		SingleTon<GaiaDrawListRepo>::use()->Setwidth(700);
		SingleTon<GaiaLayoutRepo>::use()->GetspView()->SetColumnInfo(0, SingleTon<GaiaDrawListRepo>::use()->Getwidth() - 10, 0);
		SingleTon<GaiaLayoutRepo>::use()->GetspView()->SetColumnInfo(1, SingleTon<GaiaToolListRepo>::use()->Getwidth() - 10, 0);
		auto v = SingleTon<GaiaLayoutRepo>::use()->GetspView();
		auto b = v->GetSafeHwnd();
	}
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


void GaiaDrawView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	CRect rect;
	this->GetClientRect(rect);
	DblBufMaker dm(&dc, rect);
	CDC& bDC = dm.GetDC();
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	auto& btn = SingleTon<GaiaDrawGrid>::use()->inBtns;
	auto& db = SingleTon<GaiaDrawGrid>::use()->dBoard;
	auto& objects = SingleTon<GaiaDrawGrid>::use()->objects;
	int len = SingleTon<GaiaObjectSizeInfo>::use()->GetSmallLength() * 10;
	for (int i = 0; i < objects.size(); i++){
		if (objects[i]->objKind == CLOCKCYCLE && objects[i]->baseRect.PtInRect(point)){
			this->StartClock(i);
			return;
		}
	}
	for (auto& b : btn){
		CRect t(b.left - len, b.top - len / 2, b.right, b.bottom + len / 2);
		if (t.PtInRect(point)){
			for (auto& obj : objects){
				CRect& temp = obj->baseRect;
				//CRect temp(obj.at(i)->in1.left, obj.at(i)->out.top - len / 2, obj.at(i)->out.right, obj.at(i)->out.bottom + len / 2);
				if (temp.PtInRect(point)){
					obj->btn = !obj->btn;
					if (obj->btn == true){
						db[obj->outs[0].CenterPoint().x / 10][obj->outs[0].CenterPoint().y / 10] = 1;
					}
					else{
						db[obj->outs[0].CenterPoint().x / 10][obj->outs[0].CenterPoint().y / 10] = 0;
					}
					goto W;
				}
			}
		}
	}
W:{};

	auto& objs = SingleTon<GaiaDrawGrid>::use()->objects;
	UpdateDBoard();
	for (int i = 0; i < objs.size(); i++){
		for (int j = 0; j < objs[i]->outs.size(); j++){
			Update(objs.at(i)->outs[j]);
		}
	}

	DrawArea(&bDC);
	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &bDC, 0, 0, SRCCOPY);
	GaiaCView::OnLButtonDblClk(nFlags, point);
}


void GaiaDrawView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CClientDC dc(this);
	CRect rect;
	this->GetClientRect(rect);
	DblBufMaker dm(&dc, rect);
	CDC& bDC = dm.GetDC();
	auto& obj = SingleTon<GaiaDrawGrid>::use()->objects;
	auto& db = SingleTon<GaiaDrawGrid>::use()->dBoard;
	int idx = SingleTon<GaiaClockInfo>::use()->clock_index;
	static int cnt = 0;
	if (obj[idx]->objKind == CLOCKCYCLE){
		if (db[obj[idx]->outs[0].CenterPoint().x / 10][obj[idx]->outs[0].CenterPoint().y / 10] == 0){
			db[obj[idx]->outs[0].CenterPoint().x / 10][obj[idx]->outs[0].CenterPoint().y / 10] = 1;
		}
		else{
			db[obj[idx]->outs[0].CenterPoint().x / 10][obj[idx]->outs[0].CenterPoint().y / 10] = 0;
		}
	}
	::Sleep(100);
	Update(obj[idx]->outs[0]);
	UpdateDBoard();
	DrawArea(&bDC);
	cnt++;
	if (cnt == 20){
		KillTimer(0);
		cnt = 0;
	}
	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &bDC, 0, 0, SRCCOPY);
	GaiaCView::OnTimer(nIDEvent);
	
}
void GaiaDrawView::StartClock(int index){
	int cycle = SingleTon<GaiaClockInfo>::use()->cycle;
	auto& idx = SingleTon<GaiaClockInfo>::use()->clock_index;
	idx = index;
	auto& id = SingleTon<GaiaClockInfo>::use()->timerId;
	if (cycle == -1){
		AfxMessageBox(L"아래 의 시계모양 버튼을 클릭하여 주기를 설정해주세요 ");
		return;
	}
	SetTimer(0, cycle, NULL);

}
void GaiaDrawView::OnCopy(){
	//GaiaDoc* pDoc = (GaiaDoc*)GetDocument();
	//pDoc->PushGaiaList();
	auto& sel_obj = SingleTon<GaiaDrawGrid>::use()->sel_objects;
	auto& tempV = SingleTon<GaiaTempRepo>::use()->tempV;
	auto& e = SingleTon<GaiaDrawGrid>::use()->objects;
	for (int i = 0; i < sel_obj.size(); i++){
		tempV.push_back(sel_obj[i]);
	}
}
void GaiaDrawView::OnPaste(){
	GaiaDoc* pDoc = (GaiaDoc*)GetDocument();
	pDoc->PushGaiaList();
	auto& tempV = SingleTon<GaiaTempRepo>::use()->tempV;
	auto& e = SingleTon<GaiaDrawGrid>::use()->objects;
	GaiaObject* obj;
	for (int i = 0; i < tempV.size(); i++){
		switch (tempV[i]->objKind){
		case ObjectKind::AND:
			obj = new AndGate();
			break;
		case ObjectKind::NOT:
			obj = new NotGate();
			break;
		case ObjectKind::NAND:
			obj = new NandGate();
			break;
		case ObjectKind::NOR:
			obj = new NorGate();
			break;
		case ObjectKind::XOR:
			obj = new XorGate();
			break;
		case ObjectKind::DFLIP:
			obj = new DFF();
			break;
		case ObjectKind::JKFLIP:
			obj = new JKFF();
			break;
		case ObjectKind::TFLIP:
			obj = new TFF();
			break;
		case ObjectKind::SEVENSEG:
			obj = new SevenSegment();
			break;
		case ObjectKind::INBUTTON:
			obj = new InputBtn();
			break;
		case ObjectKind::CLOCKCYCLE:
			obj = new ClockCycle(tempV[i]->base_point.x / 10 + 5, tempV[i]->base_point.y / 10 + 7);
			goto WHICH;
			break;
		case ObjectKind::OUTLAMP:
			obj = new OutLamp();
			break;
		case ObjectKind::OR:
			obj = new OrGate();
			break;
		}
		obj->SetPoint(tempV[i]->base_point.x/10 + 5, tempV[i]->base_point.y/10 + 7);
	WHICH:{};
		e.push_back(obj);
	}
	Invalidate(false);
}
void GaiaDrawView::OnCut(){
	GaiaDoc* pDoc = (GaiaDoc*)GetDocument();
	pDoc->PushGaiaList();
	auto& sel_idx = SingleTon<GaiaDrawGrid>::use()->sel_idx;
	auto& e = SingleTon<GaiaDrawGrid>::use()->objects;
	auto& temp = SingleTon<GaiaTempRepo>::use()->tempV;
	temp.clear();
	std::sort(sel_idx.begin(), sel_idx.end(), [](int i, int j)->bool{return  j<i; });
	
	for (int i = 0; i < sel_idx.size(); i++){
		e[sel_idx[i]]->ClearPoint();
		temp.push_back(e[sel_idx[i]]);
		e.erase(e.begin()+sel_idx[i]);
	}
	Invalidate(false);
}