
// ColorImageProcessingVer2.0Doc.h: CColorImageProcessingVer20Doc 클래스의 인터페이스
//


#pragma once


class CColorImageProcessingVer20Doc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CColorImageProcessingVer20Doc() noexcept;
	DECLARE_DYNCREATE(CColorImageProcessingVer20Doc)

// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CColorImageProcessingVer20Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	unsigned char** m_inImageR = NULL;
	unsigned char** m_inImageG = NULL;
	unsigned char** m_inImageB = NULL;

	unsigned char** m_outImageR = NULL;
	unsigned char** m_outImageG = NULL;
	unsigned char** m_outImageB = NULL;

	int m_inH;
	int m_inW;
	int m_outH;
	int m_outW;
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	unsigned char** OnMalloc2D(int h, int w);
	
	template <typename T>
	void OnFree2D(T** memory, int h);
	
	virtual void OnCloseDocument();
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	void OnFreeOutImage();
	void OnEqualImage();
	void OnGrayScale();
	void OnAddImage();
	void OnRevImage();
	void OnBwImage();
	void OnGamImage();
	void OnCapparaImage();
	void OnCupparaImage();
	void OnPosterImage();
	void OnStressImage();
	void OnZoutImage();
	void OnChangeSat();
	double* RGB2HSI(int R, int G, int B);
	unsigned char* HSI2RGB(double H, double S, double I);
	void OnExtractColor();
	void OnChangeHue();
	void OnChangeInten();
	void OnZinImage();
	void OnZinImage2();
	void OnRotImage();
	void OnRotImage2();
	void OnMoveImage();
	void OnMirrorlrImage();
	void OnMirrorudImage();
	void OnMirrorallImage();
	void OnHistoStretch();
	void OnEndIn();
	void OnHistoEqual();
	void OnEmboss();
	double** OnMalloc2D_double(int h, int w);
	void OnEmbossHsi();
	void OnBlur();
	void OnBlurHsi();
	void OnSharpning();
	void OnSharpningHsi();
	void OnHpfSharp();
	void OnHpfsharpHsi();
	void OnLpfSharp();
	void OnLpfsharpHsi();
	void OnSmoothing();
	void OnSmoothingHsi();
	void OnEdge1();
	void OnEdge1Hsi();
	void OnEdge2();
	void OnEdge2Hsi();
	void OnEdge3();
	void OnEdge3Hsi();
	void OnRrow();
	void OnRrowHsi();
	void OnRcol();
	void OnRcolHsi();
	void OnSrow();
	void OnSrowHsi();
	void OnScol();
	void OnScolHsi();
	void OnProw();
	void OnProwHsi();
	void OnPcol();
	void OnPcolHsi();
	void OnLap1();
	void OnLap1Hsi();
	void OnLap2();
	void OnLap2Hsi();
	void OnLap3();
	void OnLap3Hsi();
	void OnAndImage();
	void OnOrImage();
	void OnXorImage();
};
