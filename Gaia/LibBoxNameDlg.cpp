// LibBoxNameDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Gaia.h"
#include "LibBoxNameDlg.h"
#include "afxdialogex.h"


// LibBoxNameDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(LibBoxNameDlg, CDialogEx)

LibBoxNameDlg::LibBoxNameDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(LibBoxNameDlg::IDD, pParent)
	, libName(_T(""))
{

}

LibBoxNameDlg::~LibBoxNameDlg()
{
}

void LibBoxNameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, libName);
}


BEGIN_MESSAGE_MAP(LibBoxNameDlg, CDialogEx)
END_MESSAGE_MAP()


// LibBoxNameDlg �޽��� ó�����Դϴ�.


BOOL LibBoxNameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	this->libName = L"LibBox";
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
