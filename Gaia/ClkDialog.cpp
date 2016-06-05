// ClkDialog.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Gaia.h"
#include "ClkDialog.h"
#include "afxdialogex.h"


// ClkDialog 대화 상자입니다.

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


// ClkDialog 메시지 처리기입니다.


void ClkDialog::OnEnChangeEdit1()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
