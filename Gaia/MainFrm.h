
// MainFrm.h : MainFrame Ŭ������ �������̽�
//

#pragma once
#include<algorithm>
#include"GaiaFrame.h"
#define DRAW_SPLITTER_BAR_TIMER_ID	0x9a1a0001
#define DRAW_SPLITTER_BAR_TIMER_TIME	50
class MainFrame : public GaiaFrame
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

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};


