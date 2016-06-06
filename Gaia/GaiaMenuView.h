#pragma once
#include"GaiaCView.h"
#include"GaiaRepo.h"
#include"MenuElement.h"
#include"DblBufMaker.h"
#include<set>
#include<algorithm>
// GaiaMenuView 뷰입니다.

class GaiaMenuView : public GaiaCView
{
	DECLARE_DYNCREATE(GaiaMenuView)

public:
	GaiaMenuView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~GaiaMenuView();

public:
	void DrawSplitterBar()override;
	void RotateSelObject()override;
	virtual void OnDraw(CDC* pDC);      // 이 뷰를 그리기 위해 재정의되었습니다.
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif
private:
	int sel = -1;
	int currentID;
	set<MenuElement> menus;
	vector<const MenuElement*> vme;
	void InsertMenuElement(int pid, int mid, UINT bitmapID1, UINT bitmapID2);
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnNcPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};


