#pragma once


// ClkDialog ��ȭ �����Դϴ�.

class ClkDialog : public CDialogEx
{
	DECLARE_DYNAMIC(ClkDialog)

public:
	ClkDialog(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~ClkDialog();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CString m_str;
	afx_msg void OnEnChangeEdit1();
};
