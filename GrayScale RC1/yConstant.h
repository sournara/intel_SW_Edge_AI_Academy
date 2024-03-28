#pragma once
#include "afxdialogex.h"


// CyConstant 대화 상자

class CyConstant : public CDialog
{
	DECLARE_DYNAMIC(CyConstant)

public:
	CyConstant(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CyConstant();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Y_CONSTANT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	double m_yconstant;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
