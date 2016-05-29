#pragma once
#include"GaiaRepo.h"
#include"GaiaCView.h" 
#include"SheetElement.h"
#include"DblBufMaker.h"
// GaiaSheetView 뷰입니다.

class GaiaSheetView : public GaiaCView
{
	DECLARE_DYNCREATE(GaiaSheetView)

public:
	GaiaSheetView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~GaiaSheetView();

public:
	void DrawSplitterBar()override;
	virtual void OnDraw(CDC* pDC);      // 이 뷰를 그리기 위해 재정의되었습니다.
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


