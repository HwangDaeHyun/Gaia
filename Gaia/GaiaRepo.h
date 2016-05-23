#ifndef GAIA_REPO_H_INCLUDED
#define GAIA_REPO_H_INCLUDED
#pragma once

#include"SingleTon.h"
#include"GaiaCView.h"
#include"GaiaSplitterWnd.h"
#include"GaiaObject.h"
#include<deque>
#include<vector>

using namespace std;
using namespace design_pattern;
#define PRINT_POINT(PT)	printf("(%d,%d)\n",(PT).x,(PT).y)
#define PRINT_RECT(RT)	printf("(%d ,%d ,%d ,%d)\n",(RT).left,(RT).top,(RT).right,(RT).bottom)
//����, ���̾ƿ��� ���� �̱��� �Դϴ�.
CREATE_SINGLETON(GaiaLayoutRepo) {
	CREATE_VALUE(GaiaLayoutRepo, COLORREF, highlight);	//���� ���̶����� �� �Դϴ�.
	CREATE_VALUE(GaiaLayoutRepo, COLORREF, leftside);	//���� ���� ���� �Դϴ�.
	CREATE_VALUE(GaiaLayoutRepo, COLORREF, midside);	//���� ��� ���� �Դϴ�.
	CREATE_VALUE(GaiaLayoutRepo, COLORREF, rightside);	//���� ������ ���� �Դϴ�.
	CREATE_VALUE(GaiaLayoutRepo, GaiaSplitterWnd*, spView);
public:
	const int frameThickness = 8;
	const int menuHeight = 80;
	vector<GaiaCView*> views;

	GaiaLayoutRepo() {
		this->highlight = RGB(0, 130, 153);
		this->leftside = RGB(49, 49, 49);
		this->midside = RGB(83, 83, 83);
		this->rightside = RGB(199, 199, 199);
		this->spView = nullptr;
	}
};
CREATE_SINGLETON(GaiaSheetListRepo) {
	//vector
	CREATE_VALUE(GaiaSheetListRepo, int, width);
private:
	int index;
public:
	vector<HBITMAP> images;

	const int sheetTabHeight = 50;	//��Ʈ ���� ���� �����Դϴ�.



	//�� �Լ��� ��ũ�ѿ� ���� App�� ���� ��ġ�� ��ȯ�մϴ�.
	int GetSelectedSheetLeftTopPoint() {
		return 0;
	}
	GaiaSheetListRepo() {
		this->index = 0;
		this->width = 300;
	}
};
CREATE_SINGLETON(GaiaToolListRepo) {
	CREATE_VALUE(GaiaToolListRepo, int, width);
public:
	GaiaToolListRepo() {
		this->width = 300;
	}
};
typedef pair<CPoint, CPoint> DblPoint;
typedef pair<DblPoint, deque<CRect>> PDV;
#define GSIZE 200

CREATE_SINGLETON(GaiaDrawGrid){
public:
	vector<vector<bool>> grid;
	vector<GaiaObject*> objects;
	vector<PDV> edges;
	int board[GSIZE][GSIZE];
public:
	GaiaDrawGrid(){
		this->grid.assign(GSIZE, vector<bool>());
		for (auto& e : this->grid){
			e.assign(GSIZE, false);
		}
	}
};

#endif