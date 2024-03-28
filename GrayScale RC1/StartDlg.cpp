// StartDlg.cpp: 구현 파일
//

#include "pch.h"
#include "GrayScaleImageProcessingRC1.h"
#include "afxdialogex.h"
#include "StartDlg.h"


// CStartDlg 대화 상자

IMPLEMENT_DYNAMIC(CStartDlg, CDialog)

CStartDlg::CStartDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_START, pParent)
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
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CStartDlg 메시지 처리기


HBRUSH CStartDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	CBrush* brush;

	brush = new CBrush(RGB(255, 204, 102));

	// TODO:  여기서 DC의 특성을 변경합니다.

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.

	switch (nCtlColor) {

	case CTLCOLOR_DLG:
		pDC->SetTextColor(RGB(0, 255, 0));
		pDC->SelectStockObject(BLACK_BRUSH);
		pDC->SetBkColor(RGB(49, 49, 49));
		return (HBRUSH)(brush->GetSafeHandle());
	default:
		return CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	}
	return hbr;
}
