#ifndef GAIA_GAIAFRAME_H
#define GAIA_GAIAFRAME_H
#pragma once
#include"GaiaRepo.h"
#include"DblBufMaker.h"
#include <iostream>
#define TOOLUP_BTN_CLICK_TIMER_ID	0x9a1a0002
#define TOOLUP_BTN_CLICK_TIMER_TIME 300

enum ToolUpBtnState{
	NONE, HOVER, CLICK
};
class GaiaFrame : public CFrameWnd
{
	DECLARE_DYNCREATE(GaiaFrame)
protected:
	GaiaFrame();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~GaiaFrame();
private:
	CRect m_btnRect;
	ToolUpBtnState m_toolupBtnState;
	BOOL m_isClick;

	BOOL m_mouseTracking;
	BOOL m_isMaximize = FALSE;
private:
	void DrawBottomFrame(CRect rect, CDC* pDC);
	void DrawLeftFrame(CRect rect, CDC* pDC);
	void DrawRightFrame(CRect rect, CDC* pDC);
	void DrawTopFrame(CRect rect, CDC* pDC);
	void DrawIcon(CDC* pDC);
	void DrawToolUpBtn(CDC* pDC, int begin, UINT id);
	void DrawSysBtns(CDC* pDC);
	void DrawSystemButton1(CDC* dc);
	void DrawSystemButton2(CDC* dc, BOOL redraw);
	void DrawSystemButton3(CDC* dc);
protected:
	CRect sys_btns[3];	//min,max,exit
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNcPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnNcActivate(BOOL bActive);
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
};


#endif