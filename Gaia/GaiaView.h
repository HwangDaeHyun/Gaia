
// GaiaView.h : GaiaView Ŭ������ �������̽�
//

#pragma once


class GaiaView : public CView
{
protected: // serialization������ ��������ϴ�.
	GaiaView();
	DECLARE_DYNCREATE(GaiaView)

// Ư���Դϴ�.
public:
	GaiaDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// �����Դϴ�.
public:
	virtual ~GaiaView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // GaiaView.cpp�� ����� ����
inline GaiaDoc* GaiaView::GetDocument() const
   { return reinterpret_cast<GaiaDoc*>(m_pDocument); }
#endif

