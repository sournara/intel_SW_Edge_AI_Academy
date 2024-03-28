#pragma once
#include "afxdialogex.h"


// CxConstant 대화 상자

class CxConstant : public CDialog
{
	DECLARE_DYNAMIC(CxConstant)

public:
	CxConstant(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CxConstant();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_X_CONSTANT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	double m_xconstant;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
