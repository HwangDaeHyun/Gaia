#ifndef GAIA_REPO_H_INCLUDED
#define GAIA_REPO_H_INCLUDED
#pragma once

#include"SingleTon.h"
#include"GaiaCView.h"
#include"GaiaSplitterWnd.h"
#include"GaiaObject.h"
#include<deque>
#include<vector>
#include<list>
#include<string>
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
		this->highlight = RGB(0, 122, 204);
		this->leftside = RGB(34, 34, 34);
		this->midside = RGB(255, 255, 255);
		this->rightside = RGB(60, 60, 60);
		this->spView = nullptr;
	}
};
CREATE_SINGLETON(GaiaSheetListRepo) {
	//vector
	CREATE_VALUE(GaiaSheetListRepo, int, width);
private:
	int index;
public:
	int sel_btn = -1;
	int sel_lib = -1;
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
CREATE_SINGLETON(GaiaDrawListRepo) {
	CREATE_VALUE(GaiaDrawListRepo, int, width);
public:
	CRect selRect;
	GaiaObject* selected;
	CPoint selPoint;
	GaiaDrawListRepo() {
		this->selected = nullptr;
		this->width = 700;
	}
};
typedef pair<CPoint, CPoint> DblPoint;
typedef pair<DblPoint, deque<CRect>> PDV;
#define GSIZE 150

CREATE_SINGLETON(GaiaDrawGrid){
public:
	vector<vector<bool>> grid;
	vector<GaiaObject*> objects;
	vector<GaiaObject*> sel_objects;
	vector<GaiaObject*> lib_objects;
	vector<PDV> edges;
	vector<CRect> inBtns;
	int board[GSIZE][GSIZE];
	int dBoard[GSIZE][GSIZE];
public:
	GaiaDrawGrid(){
		this->grid.assign(GSIZE, vector<bool>());
		for (auto& e : this->grid){
			e.assign(GSIZE, false);
		}
	}
};

CREATE_SINGLETON(GaiaGateInfo){
public:
	// color -> and , or , not 순
	int size = 3;
	int selObj;
	BOOL isDrawObject;
	vector<CRect> rec;
	vector<COLORREF> tColors;
	vector<COLORREF> colors;// = { RGB(100, 10, 200), RGB(200, 100, 10), RGB(200, 200, 10) };
	vector<CString> names;// = { _T("And Gate"), _T("Or Gate"), _T("Not Gate") };
	vector<CString> libName;
public:
	GaiaGateInfo(){
		isDrawObject = FALSE;
		colors.push_back(RGB(0, 166, 81));
		colors.push_back(RGB(200, 100, 10));
		colors.push_back(RGB(200, 200, 10));
		colors.push_back(RGB(120, 200, 122));
		colors.push_back(RGB(222, 12, 222));
		colors.push_back(RGB(222, 12, 222));
		colors.push_back(RGB(200, 100, 10));
		colors.push_back(RGB(200, 200, 10));
		colors.push_back(RGB(120, 200, 122));
		colors.push_back(RGB(222, 12, 222));
		colors.push_back(RGB(222, 12, 222));
		colors.push_back(RGB(222, 12, 22));
		names.push_back(_T("And Gate"));
		names.push_back(_T("Or Gate"));
		names.push_back(_T("Not Gate"));
		names.push_back(_T("Nand Gate"));
		names.push_back(_T("XOR Gate"));
		names.push_back(_T("NOR Gate"));
		names.push_back(_T("D Flip-Flop"));
		names.push_back(_T("T Flip-Flop"));
		names.push_back(_T("JK Flip-Flop"));
		names.push_back(_T("7-Segment"));
		names.push_back(_T("Input Button"));
		names.push_back(_T("Output Lamp"));
		libName.push_back(_T("Main"));
	}
};
typedef pair<CRect, CRect> RPAIR; //rect pair
typedef pair<CString, CString> SPAIR; // string pair
CREATE_SINGLETON(GaiaTableInfo){
public:
	bool isSel = false;
	int selNum = -1;
	CString title;
	vector<CRect> invenRect;
	vector<SPAIR> contents;
public:
	GaiaTableInfo(){
		int width = SingleTon<GaiaToolListRepo>::use()->Getwidth();
		SPAIR temp(_T("Facing"), _T(""));
		contents.push_back(temp);

		SPAIR temp2(_T("Label"), _T(""));
		contents.push_back(temp2);
;


	}
};
CREATE_SINGLETON(GaiaObjectSizeInfo){
	int length;
	int sLen;		//small length
	int bLen;		//big length

	void SetLength(int l){
		this->length = l;
	}
	int GetLength(){
		return this->length;
	}
	void SetSmallLength(int l){
		this->sLen = l;
	}
	int GetSmallLength(){
		return this->sLen;
	}
	void SetBigLength(int l){
		this->bLen = l;
	}
	int GetBigLength(){
		return this->bLen;
	}
};

CREATE_SINGLETON(GaiaClockInfo){
public:
	int clock_index = -1;
	int cycle;
	vector<int> timerId;
	vector<int> cnt;
};
#endif