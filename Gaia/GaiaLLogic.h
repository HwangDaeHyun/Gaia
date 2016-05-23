#pragma once
#ifndef GOEUN_EDITOR_GAIA_LLOGIC_H_INCLUDE
#define GOEUN_EDITOR_GAIA_LLOGIC_H INCLUDE
#include"stdafx.h"
#include"SingleTon.h"
#include"GaiaRepo.h"
#include"GaiaObject.h"
typedef int BOARD[GSIZE][GSIZE];
class GaiaLLogic : public GaiaObject {
public:
public:
	void SetPoint(CPoint p)override{
		this->base_point = CPoint(p.x * 10, p.y * 10);
		auto& grid = SingleTon<GaiaDrawGrid>::use()->grid;

		int bx = this->base_point.x / 10;
		int by = this->base_point.y / 10;
		for (int i = by; i < by + GaiaObjectSize.GetLength(); i++){
			for (int j = bx; j < bx + GaiaObjectSize.GetLength(); j++){
				grid[j][i] = true;
			}
		}
	}
	void SetPoint(int x, int y)override{
		this->SetPoint(CPoint(x, y));
	}

	void SetPoint()override{
		auto& grid = SingleTon<GaiaDrawGrid>::use()->grid;
		int bx = this->base_point.x / 10;
		int by = this->base_point.y / 10;
		for (int i = by; i < by + GaiaObjectSize.GetLength(); i++){
			for (int j = bx; j < bx + GaiaObjectSize.GetLength(); j++){
				grid[j][i] = true;
			}
		}
	}

	void ClearPoint()override{
		auto& grid = SingleTon<GaiaDrawGrid>::use()->grid;
		int bx = this->base_point.x / 10;
		int by = this->base_point.y / 10;
		for (int i = by; i < by + GaiaObjectSize.GetLength(); i++){
			for (int j = bx; j < bx + GaiaObjectSize.GetLength(); j++){
				grid[j][i] = false;
			}
		}
	}

	virtual void Draw(CDC* pDC)override{}
};
bool DblCompare(double a, double b){
	const double u = 0.0001;
	if (fabs(a - b) < u){
		return true;
	}
	else{
		return false;
	}
}
void DrawWay(CDC* pDC, deque<CRect>& way, bool b = true){
	{
		CBrush brush(RGB(0, 0, 0));
		CArray<CPoint, CPoint&> lines;
		for (auto& e : way){
			lines.Add(e.CenterPoint());
		}
		CPen pen;
		pen.CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
		pDC->SelectObject(&pen);
		if (b)pDC->Polyline(lines.GetData(), lines.GetSize());
		for (int i = 0; i < lines.GetSize() - 7; i++){
			if (DblCompare(hypot(lines[i].x - lines[i + 2].x, lines[i].y - lines[i + 2].y), sqrt(2) * 10)){
				SingleTon<GaiaDrawGrid>::use()->grid[lines[i + 1].x / 10][lines[i + 1].y / 10] = b;
				SingleTon<GaiaDrawGrid>::use()->grid[lines[i + 2].x / 10][lines[i + 2].y / 10] = b;
				SingleTon<GaiaDrawGrid>::use()->grid[lines[i].x / 10][lines[i].y / 10] = b;
			}
		}
	}
}
CPoint MediatePoint(CPoint& point){
	point.x /= 10;
	point.y /= 10;
	point.x *= 10;
	point.y *= 10;
	return point;
}
void UpdateLines(){
	vector<PDV> temp;
	auto e = SingleTon<GaiaDrawGrid>::use()->edges;

}
deque<CRect> DrawEdge(CDC* pDC, DblPoint _pt, CWnd* view, BOOL ad = TRUE){
	CPoint mpt;
	CRect rect;
	view->GetWindowRect(&rect);
	::GetCursorPos(&mpt);
	mpt.x -= rect.left;
	mpt.y -= rect.top;
	CPoint temp=MediatePoint(_pt.first);
	temp =MediatePoint(_pt.second);
	auto grid = SingleTon<GaiaDrawGrid>::use()->grid;
	BOARD& board = SingleTon<GaiaDrawGrid>::use()->board;
	ZeroMemory(board, sizeof(int)*GSIZE*GSIZE);
	DblPoint pt = { { _pt.first.x / 10, _pt.first.y / 10 }, { _pt.second.x / 10, _pt.second.y / 10 } };
	if (grid[pt.second.x][pt.second.y] == true && ad == TRUE){
		return deque<CRect>();
	}
	deque<CPoint> deq;
	deq.push_back(pt.first);
	board[pt.first.x][pt.first.y] = 1;
	while (!deq.empty()){
		if (deq.empty()){
			puts("deq size");
			return deque<CRect>();
		}
		//printf("deque %d: %u\n", ssss,deq.size());
		CPoint point = deq[0];
		deq.pop_front();	//»óÇÏÁÂ¿ì
		int val = board[point.x][point.y];
		if (point.y > 0 && grid[point.x][point.y - 1] == false && board[point.x][point.y - 1] == 0){
			deq.push_back(CPoint(point.x, point.y - 1));
			board[point.x][point.y - 1] = val + 1;
			if (deq.back() == pt.second){
				break;
			}
		}
		if (point.y < GSIZE - 1 && grid[point.x][point.y + 1] == false && board[point.x][point.y + 1] == 0){
			deq.push_back(CPoint(point.x, point.y + 1));
			board[point.x][point.y + 1] = val + 1;
			if (deq.back() == pt.second){
				break;
			}
		}
		if (point.x > 0 && grid[point.x - 1][point.y] == false && board[point.x - 1][point.y] == 0){
			deq.push_back(CPoint(point.x - 1, point.y));
			board[point.x - 1][point.y] = val + 1;
			if (deq.back() == pt.second){
				break;
			}
		}
		if (point.x < GSIZE - 1 && grid[point.x + 1][point.y] == false && board[point.x + 1][point.y] == 0){
			deq.push_back(CPoint(point.x + 1, point.y));
			board[point.x + 1][point.y] = val + 1;
			if (deq.back() == pt.second){
				break;
			}
		}
	}
	CPoint point = deq.back();
	CBrush brush(RGB(202, 20, 20));
	deque<CRect> way;
	while (board[point.x][point.y] != 0){
		
		pDC->FillRect(CRect(point.x * 10, point.y * 10, point.x * 10 + 5, point.y * 10 + 5), &brush);
		way.push_back(CRect(point.x * 10, point.y * 10, point.x * 10 + 10, point.y * 10 + 10));
		int val = board[point.x][point.y] - 1;
		if (val == 0)break;
		vector<CPoint> poss;
		if (point.y > 0 && board[point.x][point.y - 1] == val){
			poss.push_back(CPoint(point.x, point.y - 1));
		}
		else if (point.y < GSIZE - 1 && board[point.x][point.y + 1] == val){
			poss.push_back(CPoint(point.x, point.y + 1));
		}
		else if (point.x > 0 && board[point.x - 1][point.y] == val){
			poss.push_back(CPoint(point.x - 1, point.y));
		}
		else if (point.x < GSIZE - 1 && board[point.x + 1][point.y] == val){
			poss.push_back(CPoint(point.x + 1, point.y));
		}
		else{
			VERIFY(FALSE);
		}
		if (poss.size() == 1){
			point = poss[0];
		}
		else{
			vector<int> eight;
			for (auto& e : poss){
				int c = 0;
				int x = e.x;
				int y = e.y;
				if (x > 0 && y > 0 && grid[x - 1][y - 1])c++;
				if (x > 0 && grid[x - 1][y])c++;
				if (x > 0 && y < GSIZE - 1 && grid[x - 1][y + 1])c++;
				if (y>0 && grid[x][y - 1])c++;
				if (y < GSIZE - 1 && grid[x][y + 1])c++;
				if (x <GSIZE - 1 && y >0 && grid[x + 1][y - 1])c++;
				if (x < GSIZE - 1 && grid[x + 1][y])c++;
				if (x < GSIZE - 1 && y < GSIZE - 1 && grid[x + 1][y + 1])c++;
				eight.push_back(c);
			}
			auto maxv = max_element(eight.begin(), eight.end());
			int idx = maxv - eight.begin();
			if (count(eight.begin(), eight.end(), *maxv) == 1){
				point = poss[idx];
			}
			else{
				vector<double> man;
				for (auto& e : poss){
					double mht = hypot(e.x - pt.first.x, e.y - pt.first.y);
					man.push_back(mht);
				}
				idx = max_element(man.begin(), man.end()) - man.begin();
				point = poss[idx];
			}
		}
	}

	return way;
}

#endif