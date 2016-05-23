#pragma once
#include"GaiaCView.h"
#include"GaiaRepo.h"
#include"MenuElement.h"
#include"DblBufMaker.h"
#include<set>
#include<algorithm>
// GaiaMenuView ���Դϴ�.

class GaiaMenuView : public GaiaCView
{
	DECLARE_DYNCREATE(GaiaMenuView)

public:
	GaiaMenuView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~GaiaMenuView();

public:
	void DrawSplitterBar()override;
	virtual void OnDraw(CDC* pDC);      // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif
private:
	int currentID;
	set<MenuElement> menus;
	vector<const MenuElement*> vme;
	void InsertMenuElement(int pid, int mid, UINT bitmapID);
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnNcPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


