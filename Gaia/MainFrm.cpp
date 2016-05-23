
// MainFrm.cpp : MainFrame Ŭ������ ����
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

// MainFrame ����/�Ҹ�

MainFrame::MainFrame()
{
	// TODO: ���⿡ ��� �ʱ�ȭ �ڵ带 �߰��մϴ�.
}

MainFrame::~MainFrame()
{
}

BOOL MainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!GaiaFrame::PreCreateWindow(cs))
		return FALSE;
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.
	if (cs.hMenu != nullptr){
		::DestroyMenu(cs.hMenu);
		cs.hMenu = nullptr;
	}
	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		| WS_THICKFRAME;

	return TRUE;
}

// MainFrame ����

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


// MainFrame �޽��� ó����


int MainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	if (GaiaFrame::OnCreate(lpCreateStruct) == -1)
		return -1;
	if (AllocConsole() == TRUE){
#pragma warning(disable:4996)
		freopen("CONOUT$", "wt", stdout);
	}
	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.
	this->SetTimer(DRAW_SPLITTER_BAR_TIMER_ID, DRAW_SPLITTER_BAR_TIMER_TIME, nullptr);
	return 0;
}


void MainFrame::OnDestroy() {
	GaiaFrame::OnDestroy();
	FreeConsole();
	this->KillTimer(DRAW_SPLITTER_BAR_TIMER_ID);
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}


void MainFrame::OnTimer(UINT_PTR nIDEvent) {
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

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
