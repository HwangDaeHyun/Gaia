#include "stdafx.h"
#include "Gaia.h"
#include "GaiaDrawView.h"
#include"DblBufMaker.h"
#include"AndGate.h"
#include"OrGate.h"
#include"XorGate.h"
#include"NandGate.h"
#include"NorGate.h"
#include"InputBtn.h"
#include"OutLamp.h"
#include"DFF.h"
// GaiaDrawView
using namespace design_pattern;

IMPLEMENT_DYNCREATE(GaiaDrawView, GaiaCView)

GaiaDrawView::GaiaDrawView()
{
	GaiaObjectSize.SetLength(8);
	GaiaObjectSize.SetSmallLength(6);
	GaiaObjectSize.SetBigLength(12);
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
END_MESSAGE_MAP()


// GaiaDrawView �׸����Դϴ�.

void GaiaDrawView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: ���⿡ �׸��� �ڵ带 �߰��մϴ�.
}


// GaiaDrawView �����Դϴ�.

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


// GaiaDrawView �޽��� ó�����Դϴ�.
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

	// ������ ������Ʈ�� �׵θ��� ǥ���մϴ�

	// ===



	//pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &bDC, 0, 0, SRCCOPY);
}
void GaiaDrawView::OnPaint() {
	CPaintDC dc(this); // device context for painting
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	// �׸��� �޽����� ���ؼ��� GaiaCView::OnPaint()��(��) ȣ������ ���ʽÿ�.
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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	// �׸��� �޽����� ���ؼ��� GaiaCView::OnNcPaint()��(��) ȣ������ ���ʽÿ�.
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
	dc.FillRect(&temp, &brush);		//���� ���ø��͹� ��ĥ
	temp = drawRect;
	temp.right = temp.left + 6;
	dc.FillRect(&temp, &brush);		//���� ���ø��͹� ��ĥ
	temp = drawRect;
	temp.top = temp.bottom - 4;
	dc.FillRect(&temp, &brush);		//�Ʒ��� ���ø��͹� ��ĥ
	temp = drawRect;
	temp.left = temp.right - 7;
	dc.FillRect(&temp, &brush);		//������ ���ø��͹� ��ĥ
	brush.DeleteObject();

}


void GaiaDrawView::OnMouseMove(UINT nFlags, CPoint point)
{
	point.x += 5;
	point.y += 5;
	point.x /= 10;
	point.y /= 10;
	point.x *= 10;
	point.y *= 10;

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
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
		//������ ������ �˻�
		if (possible == true){
			auto& grid = SingleTon<GaiaDrawGrid>::use()->grid;
			int bx = e[sel]->base_point.x / 10;
			int by = e[sel]->base_point.y / 10;

			for (int i = by; i < by +e[sel]->GetLength(); i++){
				for (int j = bx; j < bx +e[sel]->GetLength(); j++){
					if (grid[j][i] == true){
						possible = false;
						goto LABEL1;
					}
				}
			}
		}
	LABEL1:{}
		//����Ʈ�� �ȱ涧 �����ϴ� �Լ�
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
			else if (elem->clk.PtInRect(point) == TRUE){
				dc.Ellipse(elem->clk);
				return;
			}
		}
	}

	//== ������ ������Ʈ �̹����� ���콺�� ����ɴϴ�.
	//== AND ������Ʈ�� �ְ� �������� �߰��ؾ���
	this->AddingLogic(bDC, point);
	//==
	brush.DeleteObject();
	pen.DeleteObject();
	SetCursor(LoadCursor(NULL, IDC_ARROW));
	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &bDC, 0, 0, SRCCOPY);
	GaiaCView::OnMouseMove(nFlags, point);
}

void GaiaDrawView::AddingLogic(CDC& bDC ,CPoint point){
	if (SingleTon<GaiaGateInfo>::use()->isDrawObject == TRUE && SingleTon<GaiaGateInfo>::use()->selObj != -1){
		CDC memDC;
		memDC.CreateCompatibleDC(&bDC);
		CBitmap bmp;
		int w = 60;
		int h = 60;
		switch (SingleTon<GaiaGateInfo>::use()->selObj){
		case 10:
			drawObj = new AndGate();
			bmp.LoadBitmapW(IDB_AND_0);
			break;
		case 11:
			drawObj = new OrGate();
			bmp.LoadBitmapW(IDB_OR_0);
			break;
			//case 12:	//Not
			//	drawObj = new NotGate();
			//	drawObj->SetRadius();
			//	break;
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
			//case 26:	//D FF
			//	break;
			//case 27:	//T FF
			//	break;
			//case 28:	//JK FF
			//	break;

			//case 39:	//7 Seg
			//	break;
			//case 40:	//input
			//	break;
			//case 41:	//output
			//	break;
		}
		BITMAP bmpinfo;
		CBitmap* oldbmp = memDC.SelectObject(&bmp);
		bmp.GetBitmap(&bmpinfo);
		memDC.SelectObject(&bmp);
		bDC.TransparentBlt(point.x - 30, point.y - 30, w, h, &memDC, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, RGB(0, 0, 0));
		memDC.SelectObject(oldbmp);
	}
}
void GaiaDrawView::MoveLogic(CDC& bDC, bool& possible){
	auto& e = SingleTon<GaiaDrawGrid>::use()->objects;
	auto& edges = SingleTon<GaiaDrawGrid>::use()->edges;
	if (possible){
		DblPoint dPt;
		e[sel]->mv = RGB(178, 204, 255);
		this->DrawArea(&bDC);
		if (tempEdges.empty()){
			for (int i = 0; i < edges.size(); i++){
				if (e[sel]->out.PtInRect(edges[i].first.first)){
					dPt = { { e[sel]->out.CenterPoint().x, e[sel]->out.CenterPoint().y }, { edges[i].first.second.x, edges[i].first.second.y } };
					PaintGrid({ dPt.second.x / 10, dPt.second.y / 10 }, false);
					tempEdges.push_back(*(edges.begin() + i));
					edges.erase(edges.begin() + i);
					i -= 1;
				}
				else if (e[sel]->in1.PtInRect(edges[i].first.second)){
					dPt = { { edges[i].first.first.x, edges[i].first.first.y }, { e[sel]->in1.CenterPoint().x, e[sel]->in1.CenterPoint().y } };
					PaintGrid({ dPt.second.x / 10, dPt.second.y / 10 }, false);
					tempEdges.push_back(*(edges.begin() + i));
					edges.erase(edges.begin() + i);
					this->inIdx1 = tempEdges.size() - 1;
					i -= 1;
				}
				else if (e[sel]->in2.PtInRect(edges[i].first.second)){
					dPt = { { edges[i].first.first.x, edges[i].first.first.y }, { e[sel]->in2.CenterPoint().x, e[sel]->in2.CenterPoint().y } };
					PaintGrid({ dPt.second.x / 10, dPt.second.y / 10 }, false);
					tempEdges.push_back(*(edges.begin() + i));
					edges.erase(edges.begin() + i);
					this->inIdx2 = tempEdges.size() - 1;
					i -= 1;
				}
				else if (e[sel]->clk.PtInRect(edges[i].first.second)){
					dPt = { { edges[i].first.first.x, edges[i].first.first.y }, { e[sel]->clk.CenterPoint().x, e[sel]->clk.CenterPoint().y } };
					PaintGrid({ dPt.second.x / 10, dPt.second.y / 10 }, false);
					tempEdges.push_back(*(edges.begin() + i));
					edges.erase(edges.begin() + i);
					this->clkIdx = tempEdges.size() - 1;
					i -= 1;
				}	
			}
		}
		else{
			plusWays.clear();
			for (int i = 0; i < tempEdges.size(); i++){
				DblPoint ddPt;
				deque<CRect> uWay;
				if (i == this->inIdx1){
					ddPt = { tempEdges[i].first.first, { e[sel]->in1.CenterPoint().x, e[sel]->in1.CenterPoint().y } };
					uWay = DrawEdge(&bDC, ddPt, this);
					this->sIdx1 = i;
					uWay.push_front(e[sel]->in1);
				}
				else if (i == this->inIdx2){
					ddPt = { tempEdges[i].first.first, { e[sel]->in2.CenterPoint().x, e[sel]->in2.CenterPoint().y } };
					uWay = DrawEdge(&bDC, ddPt, this);
					this->sIdx2 = i;
					uWay.push_front(e[sel]->in2);
				}
				else if (i == this->clkIdx){
					ddPt = { tempEdges[i].first.first, { e[sel]->clk.CenterPoint().x, e[sel]->clk.CenterPoint().y } };
					uWay = DrawEdge(&bDC, ddPt, this);
					//PaintGrid(ddPt.second);
					this->sClkIdx = i;
					uWay.push_front(e[sel]->clk);
				}
				else{
					ddPt = { { e[sel]->out.CenterPoint().x, e[sel]->out.CenterPoint().y }, { tempEdges[i].first.second } };
					uWay = DrawEdge(&bDC, ddPt, this);
					uWay.push_front(CRect(tempEdges[i].first.second.x - 10, tempEdges[i].first.second.y - 10, tempEdges[i].first.second.x + 10, tempEdges[i].first.second.y + 10));
					uWay.push_back(e[sel]->out);
				}
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
	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.
	GaiaObject* p = new DFF();
	p->SetPoint(10, 10);
	p->SetRadius();
	SingleTon<GaiaDrawGrid>::use()->objects.push_back(p);

	p = new InputBtn(30, 30);
	SingleTon<GaiaDrawGrid>::use()->objects.push_back(p);

	p = new InputBtn(50, 30);
	SingleTon<GaiaDrawGrid>::use()->objects.push_back(p);

	p = new OutLamp();
	p->SetPoint(20, 20);
	p->SetRadius();
	SingleTon<GaiaDrawGrid>::use()->objects.push_back(p);
	return 0;




}


BOOL GaiaDrawView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	return TRUE;
	return GaiaCView::OnEraseBkgnd(pDC);
}


void GaiaDrawView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	point.x += 5;
	point.y += 5;
	point.x /= 10;
	point.y /= 10;
	point.x *= 10;
	point.y *= 10;
	auto& e = SingleTon<GaiaDrawGrid>::use()->objects;
	CRect* rect = nullptr;
	//��ư�� ���ȴ��� �˻��մϴ�.

	//
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
			SingleTon<GaiaDrawListRepo>::use()->selRect = e[i]->baseRect;	//������Ʈ�ϳ��� �����մϴ�.
			sel = i;
			clickPoint = point;
			e[i]->ClearPoint();
			clickBase = e[i]->base_point;

			break;
		}
	}

	if (sel != -1){
		auto& tbl = SingleTon<GaiaTableInfo>::use()->contents;
		SingleTon<GaiaTableInfo>::use()->title = e[sel]->name;
		tbl[0].second = e[sel]->arrow;
		tbl[1].second = e[sel]->name;
		auto& tdb = SingleTon<GaiaDrawGrid>::use()->dBoard;
		if (e[sel]->out != CRect()){
			if (tdb[e[sel]->out.CenterPoint().x / 10][e[sel]->out.CenterPoint().y / 10] == 0){
				tbl[2].second = _T("0");
			}
			else if (tdb[e[sel]->out.CenterPoint().x / 10][e[sel]->out.CenterPoint().y / 10] == 1){
				tbl[2].second = _T("1");
			}
			else{
				tbl[2].second = _T("-1");
			}
		}
		else{
			if (tdb[e[sel]->in1.CenterPoint().x / 10][e[sel]->in1.CenterPoint().y / 10] == 0){
				tbl[2].second = _T("0");
			}
			else if (tdb[e[sel]->in1.CenterPoint().x / 10][e[sel]->in1.CenterPoint().y / 10] == 1){
				tbl[2].second = _T("1");
			}
			else{
				tbl[2].second = _T("-1");
			}
		}
		SingleTon<GaiaLayoutRepo>::use()->views[3]->Invalidate(false);
		////
		auto& db = SingleTon<GaiaDrawGrid>::use()->dBoard;
		prevData.push_back(db[e[sel]->in1.CenterPoint().x / 10][e[sel]->in1.CenterPoint().y / 10]);
		prevData.push_back(db[e[sel]->in2.CenterPoint().x / 10][e[sel]->in2.CenterPoint().y / 10]);
		prevData.push_back(db[e[sel]->out.CenterPoint().x / 10][e[sel]->out.CenterPoint().y / 10]);
		prevData.push_back(db[e[sel]->clk.CenterPoint().x / 10][e[sel]->clk.CenterPoint().y / 10]);
		db[e[sel]->in1.CenterPoint().x / 10][e[sel]->in1.CenterPoint().y / 10] = -1;
		db[e[sel]->in2.CenterPoint().x / 10][e[sel]->in2.CenterPoint().y / 10] = -1;
		db[e[sel]->out.CenterPoint().x / 10][e[sel]->out.CenterPoint().y / 10] = -1;
		db[e[sel]->clk.CenterPoint().x / 10][e[sel]->clk.CenterPoint().y / 10] = -1;
		auto& t = SingleTon<GaiaDrawGrid>::use()->inBtns;
		for (int i = 0; i < t.size(); i++){
			if (t[i] == e[sel]->out){
				t.erase(t.begin() + i);
			}
		}
	}
	//== Object�� �׸��ϴ�
	if (SingleTon<GaiaGateInfo>::use()->isDrawObject == TRUE){
		e.push_back(drawObj);
		e.back()->SetPoint((point.x - 30) / 10, (point.y - 30) / 10);
		SingleTon < GaiaGateInfo>::use()->isDrawObject = FALSE;
		SingleTon<GaiaSheetListRepo>::use()->sel_btn = -1;
		SingleTon<GaiaLayoutRepo>::use()->views[2]->Invalidate();
	}
	//==
	SingleTon<GaiaDrawListRepo>::use()->selRect = nullptr;					//���õ� ������Ʈ�� �����ϴ�.
	GaiaCView::OnLButtonDown(nFlags, point);
}


void GaiaDrawView::OnLButtonUp(UINT nFlags, CPoint point)
{

	CClientDC dc(this);
	CRect rect;
	this->GetClientRect(rect);
	DblBufMaker dm(&dc, rect);
	CDC& bDC = dm.GetDC();
	////////////////////////////////////////////////
	this->inIdx1 = -1;
	this->inIdx2 = -1;
	this->clkIdx = -1;
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (sel != -1){
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
		db[e[sel]->in1.CenterPoint().x / 10][e[sel]->in1.CenterPoint().y / 10] = prevData[0];
		db[e[sel]->in2.CenterPoint().x / 10][e[sel]->in2.CenterPoint().y / 10] = prevData[1];
		db[e[sel]->out.CenterPoint().x / 10][e[sel]->out.CenterPoint().y / 10] = prevData[2];
		db[e[sel]->clk.CenterPoint().x / 10][e[sel]->clk.CenterPoint().y / 10] = prevData[3];
		auto& btn = SingleTon<GaiaDrawGrid>::use()->inBtns;
		if (e[sel]->objKind == INBUTTON){
			btn.push_back(e[sel]->out);
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
				if (elem->in1.PtInRect(point) == TRUE){
					ptr = &elem->in1;
					break;
				}
				else if (elem->in2.PtInRect(point) == TRUE){
					ptr = &elem->in2;
					break;
				}
				else if (elem->clk.PtInRect(point) == TRUE){
					ptr = &elem->clk;
					break;
				}
			}
			if (ptr != nullptr&&  !way.empty()){
				curr.second = ptr->CenterPoint();
				//way.pop_front();
				way.push_front(*ptr);
				SingleTon<GaiaDrawGrid>::use()->edges.push_back(PDV(this->curr, way));
				int x = curr.second.x / 10;
				int y = curr.second.y / 10;
				CPoint clearPoint(x, y);
				PaintGrid(clearPoint);
			}
			this->isLDown = FALSE;
		}
	}
	UpdateDBoard();
	//auto& inBtns =SingleTon<GaiaDrawGrid>::use()->inBtns;

	auto& objs = SingleTon<GaiaDrawGrid>::use()->objects;
	for (int i = 0; i < objs.size(); i++){
		Update(objs.at(i)->out);
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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}


void GaiaDrawView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	CRect rect;
	this->GetClientRect(rect);
	DblBufMaker dm(&dc, rect);
	CDC& bDC = dm.GetDC();
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	auto& btn = SingleTon<GaiaDrawGrid>::use()->inBtns;
	auto& db = SingleTon<GaiaDrawGrid>::use()->dBoard;
	auto& obj = SingleTon<GaiaDrawGrid>::use()->objects;
	int len = GaiaObjectSize.GetSmallLength() * 10;
	for (auto& b : btn){
		CRect t(b.left - len, b.top - len / 2, b.right, b.bottom + len / 2);
		if (t.PtInRect(point)){
			for (int i = 0; i < obj.size(); i++){
				CRect temp(obj.at(i)->in1.left, obj.at(i)->out.top - len / 2, obj.at(i)->out.right, obj.at(i)->out.bottom + len / 2);
				if (temp.PtInRect(point)){
					obj.at(i)->btn = !obj.at(i)->btn;
					if (obj.at(i)->btn == true){
						db[obj.at(i)->out.CenterPoint().x / 10][obj.at(i)->out.CenterPoint().y / 10] = 1;
					}
					else{
						db[obj.at(i)->out.CenterPoint().x / 10][obj.at(i)->out.CenterPoint().y / 10] = 0;
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
		Update(objs.at(i)->out);

	}

	DrawArea(&bDC);
	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &bDC, 0, 0, SRCCOPY);
	GaiaCView::OnLButtonDblClk(nFlags, point);
}
