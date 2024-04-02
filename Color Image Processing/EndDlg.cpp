// EndDlg.cpp: 구현 파일
//

#include "pch.h"
#include "ColorImageProcessingVer2.0.h"
#include "afxdialogex.h"
#include "EndDlg.h"


// CEndDlg 대화 상자

IMPLEMENT_DYNAMIC(CEndDlg, CDialog)

CEndDlg::CEndDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_END_DLG, pParent)
	, m_end(0)
{

}

CEndDlg::~CEndDlg()
{
}

void CEndDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_END, m_end);
}


BEGIN_MESSAGE_MAP(CEndDlg, CDialog)
END_MESSAGE_MAP()


// CEndDlg 메시지 처리기
