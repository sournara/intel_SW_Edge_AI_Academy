
// ColorImageProcessingVer2.0View.h: CColorImageProcessingVer20View 클래스의 인터페이스
//

#pragma once


class CColorImageProcessingVer20View : public CView
{
protected: // serialization에서만 만들어집니다.
	CColorImageProcessingVer20View() noexcept;
	DECLARE_DYNCREATE(CColorImageProcessingVer20View)

// 특성입니다.
public:
	CColorImageProcessingVer20Doc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CColorImageProcessingVer20View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEqualImage();
	afx_msg void OnGrayScale();
	afx_msg void OnAddImage();
	afx_msg void OnRevImage();
	afx_msg void OnBwImage();
	afx_msg void OnGamImage();
	afx_msg void OnCapparaImage();
	afx_msg void OnCupparaImage();
	afx_msg void OnPosterImage();
	afx_msg void OnStressImage();
	afx_msg void OnZoutImage();
	afx_msg void OnChangeSat();
	afx_msg void OnExtractColor();
	afx_msg void OnChangeHue();
	afx_msg void OnChangeInten();
	afx_msg void OnZinImage();
	afx_msg void OnZinImage2();
	afx_msg void OnRotImage();
	afx_msg void OnRotImage2();
	afx_msg void OnMoveImage();
	afx_msg void OnMirrorlrImage();
	afx_msg void OnMirrorudImage();
	afx_msg void OnMirrorallImage();
	afx_msg void OnHistoStretch();
	afx_msg void OnEndIn();
	afx_msg void OnHistoEqual();
	afx_msg void OnEmboss();
	afx_msg void OnEmbossHsi();
	afx_msg void OnBlur();
	afx_msg void OnBlurHsi();
	afx_msg void OnSharpning();
	afx_msg void OnSharpningHsi();
	afx_msg void OnHpfSharp();
	afx_msg void OnHpfsharpHsi();
	afx_msg void OnLpfSharp();
	afx_msg void OnLpfsharpHsi();
	afx_msg void OnSmoothing();
	afx_msg void OnSmoothingHsi();
	afx_msg void OnEdge1();
	afx_msg void OnEdge1Hsi();
	afx_msg void OnEdge2();
	afx_msg void OnEdge2Hsi();
	afx_msg void OnEdge3();
	afx_msg void OnEdge3Hsi();
	afx_msg void OnRrow();
	afx_msg void OnRrowHsi();
	afx_msg void OnRcol();
	afx_msg void OnRcolHsi();
	afx_msg void OnSrow();
	afx_msg void OnSrowHsi();
	afx_msg void OnScol();
	afx_msg void OnScolHsi();
	afx_msg void OnProw();
	afx_msg void OnProwHsi();
	afx_msg void OnPcol();
	afx_msg void OnPcolHsi();
	afx_msg void OnLap1();
	afx_msg void OnLap1Hsi();
	afx_msg void OnLap2();
	afx_msg void OnLap2Hsi();
	afx_msg void OnLap3();
	afx_msg void OnLap3Hsi();
	afx_msg void OnAndImage();
	afx_msg void OnOrImage();
	afx_msg void OnXorImage();
};

#ifndef _DEBUG  // ColorImageProcessingVer2.0View.cpp의 디버그 버전
inline CColorImageProcessingVer20Doc* CColorImageProcessingVer20View::GetDocument() const
   { return reinterpret_cast<CColorImageProcessingVer20Doc*>(m_pDocument); }
#endif

