﻿#pragma once
#include "afxdialogex.h"


// CConstantDlg 대화 상자

class CConstantDlg : public CDialog
{
	DECLARE_DYNAMIC(CConstantDlg)

public:
	CConstantDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CConstantDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONSTANT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	double m_constant;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnEnChangeEditConstant();
};
