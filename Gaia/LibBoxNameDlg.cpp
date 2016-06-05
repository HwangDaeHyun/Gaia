// LibBoxNameDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Gaia.h"
#include "LibBoxNameDlg.h"
#include "afxdialogex.h"


// LibBoxNameDlg 대화 상자입니다.

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


// LibBoxNameDlg 메시지 처리기입니다.


BOOL LibBoxNameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	this->libName = L"LibBox";
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
