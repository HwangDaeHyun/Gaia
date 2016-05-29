#pragma once
#include"GaiaRepo.h"
#include"GaiaCView.h" 
#include"SheetElement.h"
#include"DblBufMaker.h"
// GaiaSheetView ���Դϴ�.

class GaiaSheetView : public GaiaCView
{
	DECLARE_DYNCREATE(GaiaSheetView)

public:
	GaiaSheetView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~GaiaSheetView();

public:
	void DrawSplitterBar()override;
	virtual void OnDraw(CDC* pDC);      // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif
protected:

protected:
	DECLARE_MESSAGE_MAP()
private:
	int sprd = -1;
	int flag = -1;
	int& selNum = SingleTon<GaiaSheetListRepo>::use()->sel_btn;
	int seln = -1;
	vector<CRect> btnRect;
	int currentID;
	vector<SheetElement> elems;
	vector<const SheetElement*> velem;
	void creatTree();
	void InsertSheetElement(int tid, int pid, int mid, CString name, COLORREF col);
	void AddSheetElement(int tid, int pid, int mid, CString name, COLORREF col);
public:
	afx_msg void OnNcPaint();
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


