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
//색상, 레이아웃에 대한 싱글톤 입니다.
CREATE_SINGLETON(GaiaLayoutRepo) {
	CREATE_VALUE(GaiaLayoutRepo, COLORREF, highlight);	//앱의 하이라이팅 색 입니다.
	CREATE_VALUE(GaiaLayoutRepo, COLORREF, leftside);	//앱의 왼쪽 배경색 입니다.
	CREATE_VALUE(GaiaLayoutRepo, COLORREF, midside);	//앱의 가운데 배경색 입니다.
	CREATE_VALUE(GaiaLayoutRepo, COLORREF, rightside);	//앱의 오른쪽 배경색 입니다.
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

	const int sheetTabHeight = 50;	//시트 선택 블럭의 높이입니다.



	//이 함수는 스크롤에 따른 App의 절대 위치를 반환합니다.
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