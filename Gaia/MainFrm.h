
// MainFrm.h : MainFrame Ŭ������ �������̽�
//

#pragma once
#include<algorithm>

#define DRAW_SPLITTER_BAR_TIMER_ID	0x9a1a0001
#define DRAW_SPLITTER_BAR_TIMER_TIME	50
class MainFrame : public CFrameWnd
{
	
protected: // serialization������ ��������ϴ�.
	MainFrame();
	DECLARE_DYNCREATE(MainFrame)

// Ư���Դϴ�.
public:

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// �����Դϴ�.
public:
	virtual ~MainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


// ������ �޽��� �� �Լ�
protected:
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()

};


