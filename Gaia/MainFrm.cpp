
// MainFrm.cpp : MainFrame 클래스의 구현
//

#include "stdafx.h"
#include "Gaia.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// MainFrame
using namespace std;
IMPLEMENT_DYNCREATE(MainFrame, GaiaFrame)

BEGIN_MESSAGE_MAP(MainFrame, GaiaFrame)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// MainFrame 생성/소멸

MainFrame::MainFrame()
{
	// TODO: 여기에 멤버 초기화 코드를 추가합니다.
}

MainFrame::~MainFrame()
{
}

BOOL MainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!GaiaFrame::PreCreateWindow(cs))
		return FALSE;
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.
	if (cs.hMenu != nullptr){
		::DestroyMenu(cs.hMenu);
		cs.hMenu = nullptr;
	}
	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		| WS_THICKFRAME;

	return TRUE;
}

// MainFrame 진단

#ifdef _DEBUG
void MainFrame::AssertValid() const
{
	GaiaFrame::AssertValid();
}

void MainFrame::Dump(CDumpContext& dc) const
{
	GaiaFrame::Dump(dc);
}
#endif //_DEBUG


// MainFrame 메시지 처리기


int MainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	if (GaiaFrame::OnCreate(lpCreateStruct) == -1)
		return -1;
	if (AllocConsole() == TRUE){
#pragma warning(disable:4996)
		freopen("CONOUT$", "wt", stdout);
	}
	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	this->SetTimer(DRAW_SPLITTER_BAR_TIMER_ID, DRAW_SPLITTER_BAR_TIMER_TIME, nullptr);
	return 0;
}


void MainFrame::OnDestroy() {
	GaiaFrame::OnDestroy();
	FreeConsole();
	this->KillTimer(DRAW_SPLITTER_BAR_TIMER_ID);
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


void MainFrame::OnTimer(UINT_PTR nIDEvent) {
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (nIDEvent == DRAW_SPLITTER_BAR_TIMER_ID){
		vector<GaiaCView*>& views = SingleTon<GaiaLayoutRepo>::use()->views;
		this->OnNcPaint();
		for_each(views.begin(), views.end(), [](GaiaCView* v)->void{v->DrawSplitterBar(); });
	}
	CFont f;
	f.CreatePointFont(14, L"Arial");
	vector<CFont*> vf;
	vf.push_back(&f);
	GaiaFrame::OnTimer(nIDEvent);
}
