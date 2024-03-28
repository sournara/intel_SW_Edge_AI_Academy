
// GrayScaleImageProcessingRC1View.h: CGrayScaleImageProcessingRC1View 클래스의 인터페이스
//

#pragma once


class CGrayScaleImageProcessingRC1View : public CView
{
protected: // serialization에서만 만들어집니다.
	CGrayScaleImageProcessingRC1View() noexcept;
	DECLARE_DYNCREATE(CGrayScaleImageProcessingRC1View)

// 특성입니다.
public:
	CGrayScaleImageProcessingRC1Doc* GetDocument() const;

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
	virtual ~CGrayScaleImageProcessingRC1View();
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
	afx_msg void OnAddImage();
	afx_msg void OnRevImage();
	afx_msg void OnBwImage();
	afx_msg void OnAvgbwImage();
	afx_msg void OnMedbwImage();
	afx_msg void OnGamImage();
	afx_msg void OnCapparaImage();
	afx_msg void OnCupparaImage();
	afx_msg void OnPosterImage();
	afx_msg void OnStressImage();
	afx_msg void OnZoutImage();
	afx_msg void OnZinImage();
	afx_msg void OnZin2Image();
	afx_msg void OnRotImage();
	afx_msg void OnRot2Image();
	afx_msg void OnMoveImage();
	afx_msg void OnMirrorlr();
	afx_msg void OnMirrorud();
	afx_msg void OnMirrorall();
	afx_msg void OnHistoStretch();
	afx_msg void OnEndIn();
	afx_msg void OnHistoEqual();
	afx_msg void OnEmboss();
	afx_msg void OnBlur();
	afx_msg void OnSharpning();
	afx_msg void OnHpfSharp();
	afx_msg void OnLpfSharp();
	afx_msg void OnSmoothing();
	afx_msg void OnEdge1();
	afx_msg void OnEdge2();
	afx_msg void OnEdge3();
	afx_msg void OnRRow();
	afx_msg void OnRCol();
	afx_msg void OnSRow();
	afx_msg void OnSCol();
	afx_msg void OnPRow();
	afx_msg void OnPCol();
	afx_msg void OnLap1();
	afx_msg void OnLap2();
	afx_msg void OnLap3();
};

#ifndef _DEBUG  // GrayScaleImageProcessingRC1View.cpp의 디버그 버전
inline CGrayScaleImageProcessingRC1Doc* CGrayScaleImageProcessingRC1View::GetDocument() const
   { return reinterpret_cast<CGrayScaleImageProcessingRC1Doc*>(m_pDocument); }
#endif

