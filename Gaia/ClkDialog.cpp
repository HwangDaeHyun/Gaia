// ClkDialog.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Gaia.h"
#include "ClkDialog.h"
#include "afxdialogex.h"


// ClkDialog ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(ClkDialog, CDialogEx)

ClkDialog::ClkDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(ClkDialog::IDD, pParent)
	, m_str(_T(""))
{

}

ClkDialog::~ClkDialog()
{
}

void ClkDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_str);
}


BEGIN_MESSAGE_MAP(ClkDialog, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT1, &ClkDialog::OnEnChangeEdit1)
END_MESSAGE_MAP()


// ClkDialog �޽��� ó�����Դϴ�.


void ClkDialog::OnEnChangeEdit1()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}
