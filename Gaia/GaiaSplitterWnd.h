#pragma once


// GaiaSplitterWnd

class GaiaSplitterWnd : public CSplitterWnd
{
	DECLARE_DYNAMIC(GaiaSplitterWnd)

public:
	GaiaSplitterWnd();
	virtual ~GaiaSplitterWnd();
	BOOL isLock;

public:
	void SetLock();
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};


