// ConstantDlg.cpp: 구현 파일
//

#include "pch.h"
#include "GrayScaleImageProcessingRC1.h"
#include "afxdialogex.h"
#include "ConstantDlg.h"


// CConstantDlg 대화 상자

IMPLEMENT_DYNAMIC(CConstantDlg, CDialog)

CConstantDlg::CConstantDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CONSTANT, pParent)
	, m_constant(0)
{

}

CConstantDlg::~CConstantDlg()
{
}

void CConstantDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CONSTANT, m_constant);
	DDV_MinMaxDouble(pDX, m_constant, -255, 255);
}


BEGIN_MESSAGE_MAP(CConstantDlg, CDialog)
	ON_WM_CTLCOLOR()
	ON_EN_CHANGE(IDC_EDIT_CONSTANT, &CConstantDlg::OnEnChangeEditConstant)
END_MESSAGE_MAP()


// CConstantDlg 메시지 처리기



HBRUSH CConstantDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	// 다이얼로그 배경색 변경
	CBrush *brush;

	brush = new CBrush(RGB(255, 204, 204));

	// TODO:  여기서 DC의 특성을 변경합니다.

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.

	switch (nCtlColor) {

	case CTLCOLOR_DLG:
		pDC->SetTextColor(RGB(0, 255, 0));
		pDC->SelectStockObject(BLACK_BRUSH);
		pDC->SetBkColor(RGB(255, 204, 255));
		return (HBRUSH)(brush->GetSafeHandle());
	default:
		return CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	}

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


void CConstantDlg::OnEnChangeEditConstant()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

	
}
