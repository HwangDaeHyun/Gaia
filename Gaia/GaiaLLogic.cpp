#include"stdafx.h"
#include"GaiaLLogic.h"
void GaiaLLogic::SetPoint(CPoint p){
	this->base_point = CPoint(p.x * 10, p.y * 10);
	auto& grid = SingleTon<GaiaDrawGrid>::use()->grid;
	int len = 0;
	switch (this->objSize){
	case SMALL:
		len = SingleTon<GaiaObjectSizeInfo>::use()->GetSmallLength() - 1;
		break;
	case MID:
		len = SingleTon<GaiaObjectSizeInfo>::use()->GetLength() - 1;
		break;
	case BIG:
		len = SingleTon<GaiaObjectSizeInfo>::use()->GetBigLength();
		break;
	default:
		break;
	}
	int bx = this->base_point.x / 10;
	int by = this->base_point.y / 10;
	for (int i = by; i < by + len; i++){
		for (int j = bx; j < bx + len; j++){
			grid[j][i] = true;
		}
	}
}
void GaiaLLogic::SetPoint(int x, int y){
	this->SetPoint(CPoint(x, y));
}
void GaiaLLogic::SetPoint(){
	auto& grid = SingleTon<GaiaDrawGrid>::use()->grid;
	int bx = this->base_point.x / 10;
	int by = this->base_point.y / 10;
	int len = 0;
	switch (this->objSize){
	case SMALL:
		len = SingleTon<GaiaObjectSizeInfo>::use()->GetSmallLength() - 1;
		break;
	case MID:
		len = SingleTon<GaiaObjectSizeInfo>::use()->GetLength() - 1;
		break;
	case BIG:
		len = SingleTon<GaiaObjectSizeInfo>::use()->GetBigLength();
		break;
	default:
		break;
	}
	for (int i = by; i < by + len; i++){
		for (int j = bx; j < bx + len; j++){
			grid[j][i] = true;
		}
	}
}
void GaiaLLogic::ClearPoint(){
	auto& grid = SingleTon<GaiaDrawGrid>::use()->grid;
	int bx = this->base_point.x / 10;
	int by = this->base_point.y / 10;
	int len = 0;
	switch (this->objSize){
	case SMALL:
		len = SingleTon<GaiaObjectSizeInfo>::use()->GetSmallLength() - 1;
		break;
	case MID:
		len = SingleTon<GaiaObjectSizeInfo>::use()->GetLength() - 1;
		break;
	case BIG:
		len = SingleTon<GaiaObjectSizeInfo>::use()->GetBigLength();
		break;
	default:
		break;
	}
	for (int i = by; i < by + len; i++){
		for (int j = bx; j < bx + len; j++){
			grid[j][i] = false;
		}
	}
}
bool DblCompare(double a, double b){
	const double u = 0.0001;
	if (fabs(a - b) < u){
		return true;
	}
	else{
		return false;
	}
}
void DrawWay(CDC* pDC, deque<CRect>& way, bool b){
	{
		auto& db = SingleTon<GaiaDrawGrid>::use()->dBoard;
		CBrush brush(RGB(0, 0, 0));
		CArray<CPoint, CPoint&> lines;
		CPen pen;
		for (auto& e : way){
			lines.Add(e.CenterPoint());
		}
		if (db[lines[0].x / 10][lines[0].y / 10] == 0 || db[lines[lines.GetSize() - 1].x / 10][lines[lines.GetSize() - 1].y / 10] == 0 || db[lines[1].x / 10][lines[1].y / 10] == 0){
			pen.CreatePen(PS_SOLID, 4, RGB(200, 140, 150));
		}
		else if (db[lines[0].x / 10][lines[0].y / 10] == 1 || db[lines[lines.GetSize() - 1].x / 10][lines[lines.GetSize() - 1].y / 10] == 1 || db[lines[1].x / 10][lines[1].y / 10] == 1){
			pen.CreatePen(PS_SOLID, 4, RGB(150, 140, 200));
		}
		else{
			pen.CreatePen(PS_SOLID, 3, RGB(20, 20, 20));
		}


		pDC->SelectObject(&pen);
		if (b)pDC->Polyline(lines.GetData(), lines.GetSize());
		/*for (int i = 0; i < lines.GetSize() - 7; i++){
		if (DblCompare(hypot(lines[i].x - lines[i + 2].x, lines[i].y - lines[i + 2].y), sqrt(2) * 10)){
		SingleTon<GaiaDrawGrid>::use()->grid[lines[i + 1].x / 10][lines[i + 1].y / 10] = b;
		SingleTon<GaiaDrawGrid>::use()->grid[lines[i + 2].x / 10][lines[i + 2].y / 10] = b;
		SingleTon<GaiaDrawGrid>::use()->grid[lines[i].x / 10][lines[i].y / 10] = b;
		}
		}*/
	}
}
CPoint MediatePoint(CPoint& point){
	point.x += 5;
	point.y += 5;
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
deque<CRect> DrawEdge(CDC* pDC, DblPoint _pt, CWnd* view, BOOL ad){
	CPoint mpt;
	CRect rect;
	view->GetWindowRect(&rect);
	::GetCursorPos(&mpt);
	mpt.x -= rect.left;
	mpt.y -= rect.top;
	//CPoint temp=MediatePoint(_pt.first);
	//temp =MediatePoint(_pt.second);
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
		deq.pop_front();	//상하좌우
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
	CBrush brush(RGB(20, 110, 200));
	deque<CRect> way;
	while (board[point.x][point.y] != 0){
		pDC->FillRect(CRect(point.x * 10 - 3, point.y * 10 - 3, point.x * 10 + 3, point.y * 10 + 3), &brush);
		way.push_back(CRect(point.x * 10 - 5, point.y * 10 - 5, point.x * 10 + 5, point.y * 10 + 5));
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
void PaintGrid(CPoint pt, bool b){
	auto& grid = SingleTon<GaiaDrawGrid>::use()->grid;
	grid[pt.x][pt.y - 1] = b;
	grid[pt.x][pt.y] = b;
	grid[pt.x][pt.y + 1] = b;
	grid[pt.x - 1][pt.y - 1] = b;
	grid[pt.x - 1][pt.y] = b;
	grid[pt.x - 1][pt.y + 1] = b;
	grid[pt.x + 1][pt.y - 1] = b;
	grid[pt.x + 1][pt.y] = b;
	grid[pt.x + 1][pt.y + 1] = b;
}
void UpdateDBoard(){
	auto& objs = SingleTon<GaiaDrawGrid>::use()->objects;
	for (auto& obj : objs){
		obj->Calculate();
	}


}
void Update(CRect& out){
	auto& db = SingleTon<GaiaDrawGrid>::use()->dBoard;
	auto& inputs = SingleTon<GaiaDrawGrid>::use()->objects;
	auto& edges = SingleTon<GaiaDrawGrid>::use()->edges;
	for (auto& e : edges){
		for (int i = 0; i < inputs.size(); i++){
			if (inputs[i]->outs[0].PtInRect(e.first.first)){
				db[e.first.second.x / 10][e.first.second.y / 10] = db[inputs[i]->outs[0].CenterPoint().x / 10][inputs[i]->outs[0].CenterPoint().y / 10];
			}
			else if (inputs[i]->outs[0].PtInRect(e.first.second)){
				db[e.first.first.x / 10][e.first.first.y / 10] = db[inputs[i]->outs[0].CenterPoint().x / 10][inputs[i]->outs[0].CenterPoint().y / 10];
			}
		}
	}
	UpdateDBoard();
}
//선택된 영역에 그림을 아직 못그림 . 
vector<int>* SearchObjects(CDC* pDC, CRect bound){
	vector<int>* temp = new vector<int>();
	auto& obj = SingleTon<GaiaDrawGrid>::use()->objects;
	CBrush brush(RGB(200, 20, 20));
	pDC->SelectObject(&brush);
	for (int i = 0; i < obj.size(); i++){
		if (bound.PtInRect(obj[i]->baseRect.TopLeft()) && bound.PtInRect(obj[i]->baseRect.BottomRight())){
			pDC->Rectangle(obj[i]->baseRect);
			temp->push_back(i);
		}
	}
	brush.DeleteObject();
	return temp;
}