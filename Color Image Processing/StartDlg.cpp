// StartDlg.cpp: 구현 파일
//

#include "pch.h"
#include "ColorImageProcessingVer2.0.h"
#include "afxdialogex.h"
#include "StartDlg.h"


// CStartDlg 대화 상자

IMPLEMENT_DYNAMIC(CStartDlg, CDialog)

CStartDlg::CStartDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_START_DLG, pParent)
	, m_start(0)
{

}

CStartDlg::~CStartDlg()
{
}

void CStartDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_START, m_start);
}


BEGIN_MESSAGE_MAP(CStartDlg, CDialog)
END_MESSAGE_MAP()


// CStartDlg 메시지 처리기
