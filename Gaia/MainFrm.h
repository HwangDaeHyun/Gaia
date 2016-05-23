
// MainFrm.h : MainFrame 클래스의 인터페이스
//

#pragma once
#include<algorithm>

#define DRAW_SPLITTER_BAR_TIMER_ID	0x9a1a0001
#define DRAW_SPLITTER_BAR_TIMER_TIME	50
class MainFrame : public CFrameWnd
{
	
protected: // serialization에서만 만들어집니다.
	MainFrame();
	DECLARE_DYNCREATE(MainFrame)

// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 구현입니다.
public:
	virtual ~MainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


// 생성된 메시지 맵 함수
protected:
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()

};


