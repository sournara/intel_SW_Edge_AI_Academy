#pragma once
#include "afxdialogex.h"


// CEndDlg 대화 상자

class CEndDlg : public CDialog
{
	DECLARE_DYNAMIC(CEndDlg)

public:
	CEndDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CEndDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_END };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	double m_end;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
