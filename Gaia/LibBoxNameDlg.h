#pragma once


// LibBoxNameDlg ��ȭ �����Դϴ�.

class LibBoxNameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(LibBoxNameDlg)

public:
	LibBoxNameDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~LibBoxNameDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CString libName;
	virtual BOOL OnInitDialog();
};
