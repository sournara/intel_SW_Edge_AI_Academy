
// ColorImageProcessingVer2.0View.cpp: CColorImageProcessingVer20View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ColorImageProcessingVer2.0.h"
#endif

#include "ColorImageProcessingVer2.0Doc.h"
#include "ColorImageProcessingVer2.0View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CColorImageProcessingVer20View

IMPLEMENT_DYNCREATE(CColorImageProcessingVer20View, CView)

BEGIN_MESSAGE_MAP(CColorImageProcessingVer20View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(IDM_EQUAL_IMAGE, &CColorImageProcessingVer20View::OnEqualImage)
	ON_COMMAND(IDM_GRAY_SCALE, &CColorImageProcessingVer20View::OnGrayScale)
	ON_COMMAND(IDM_ADD_IMAGE, &CColorImageProcessingVer20View::OnAddImage)
	ON_COMMAND(IDM_REV_IMAGE, &CColorImageProcessingVer20View::OnRevImage)
	ON_COMMAND(IDM_BW_IMAGE, &CColorImageProcessingVer20View::OnBwImage)
	ON_COMMAND(IDM_GAM_IMAGE, &CColorImageProcessingVer20View::OnGamImage)
	ON_COMMAND(IDM_CAPPARA_IMAGE, &CColorImageProcessingVer20View::OnCapparaImage)
	ON_COMMAND(IDM_CUPPARA_IMAGE, &CColorImageProcessingVer20View::OnCupparaImage)
	ON_COMMAND(IDM_POSTER_IMAGE, &CColorImageProcessingVer20View::OnPosterImage)
	ON_COMMAND(IDM_STRESS_IMAGE, &CColorImageProcessingVer20View::OnStressImage)
	ON_COMMAND(IDM_ZOUT_IMAGE, &CColorImageProcessingVer20View::OnZoutImage)
	ON_COMMAND(IDM_CHANGE_SAT, &CColorImageProcessingVer20View::OnChangeSat)
	ON_COMMAND(IDM_EXTRACT_COLOR, &CColorImageProcessingVer20View::OnExtractColor)
	ON_COMMAND(IDM_CHANGE_HUE, &CColorImageProcessingVer20View::OnChangeHue)
	ON_COMMAND(IDM_CHANGE_INTEN, &CColorImageProcessingVer20View::OnChangeInten)
	ON_COMMAND(IDM_ZIN_IMAGE, &CColorImageProcessingVer20View::OnZinImage)
	ON_COMMAND(IDM_ZIN_IMAGE2, &CColorImageProcessingVer20View::OnZinImage2)
	ON_COMMAND(IDM_ROT_IMAGE, &CColorImageProcessingVer20View::OnRotImage)
	ON_COMMAND(IDM_ROT_IMAGE2, &CColorImageProcessingVer20View::OnRotImage2)
	ON_COMMAND(IDM_MOVE_IMAGE, &CColorImageProcessingVer20View::OnMoveImage)
	ON_COMMAND(IDM_MIRRORLR_IMAGE, &CColorImageProcessingVer20View::OnMirrorlrImage)
	ON_COMMAND(IDM_MIRRORUD_IMAGE, &CColorImageProcessingVer20View::OnMirrorudImage)
	ON_COMMAND(IDM_MIRRORALL_IMAGE, &CColorImageProcessingVer20View::OnMirrorallImage)
	ON_COMMAND(IDM_HISTO_STRETCH, &CColorImageProcessingVer20View::OnHistoStretch)
	ON_COMMAND(IDM_END_IN, &CColorImageProcessingVer20View::OnEndIn)
	ON_COMMAND(IDM_HISTO_EQUAL, &CColorImageProcessingVer20View::OnHistoEqual)
	ON_COMMAND(IDM_EMBOSS, &CColorImageProcessingVer20View::OnEmboss)
	ON_COMMAND(IDM_EMBOSS_HSI, &CColorImageProcessingVer20View::OnEmbossHsi)
	ON_COMMAND(IDM_BLUR, &CColorImageProcessingVer20View::OnBlur)
	ON_COMMAND(IDM_BLUR_HSI, &CColorImageProcessingVer20View::OnBlurHsi)
	ON_COMMAND(IDM_SHARPNING, &CColorImageProcessingVer20View::OnSharpning)
	ON_COMMAND(IDM_SHARPNING_HSI, &CColorImageProcessingVer20View::OnSharpningHsi)
	ON_COMMAND(IDM_HPF_SHARP, &CColorImageProcessingVer20View::OnHpfSharp)
	ON_COMMAND(IDM_HPFSHARP_HSI, &CColorImageProcessingVer20View::OnHpfsharpHsi)
	ON_COMMAND(IDM_LPF_SHARP, &CColorImageProcessingVer20View::OnLpfSharp)
	ON_COMMAND(IDM_LPFSHARP_HSI, &CColorImageProcessingVer20View::OnLpfsharpHsi)
	ON_COMMAND(IDM_SMOOTHING, &CColorImageProcessingVer20View::OnSmoothing)
	ON_COMMAND(IDM_SMOOTHING_HSI, &CColorImageProcessingVer20View::OnSmoothingHsi)
	ON_COMMAND(IDM_EDGE1, &CColorImageProcessingVer20View::OnEdge1)
	ON_COMMAND(IDM_EDGE1_HSI, &CColorImageProcessingVer20View::OnEdge1Hsi)
	ON_COMMAND(IDM_EDGE2, &CColorImageProcessingVer20View::OnEdge2)
	ON_COMMAND(IDM_EDGE2_HSI, &CColorImageProcessingVer20View::OnEdge2Hsi)
	ON_COMMAND(IDM_EDGE3, &CColorImageProcessingVer20View::OnEdge3)
	ON_COMMAND(IDM_EDGE3_HSI, &CColorImageProcessingVer20View::OnEdge3Hsi)
	ON_COMMAND(IDM_RROW, &CColorImageProcessingVer20View::OnRrow)
	ON_COMMAND(IDM_RROW_HSI, &CColorImageProcessingVer20View::OnRrowHsi)
	ON_COMMAND(IDM_RCOL, &CColorImageProcessingVer20View::OnRcol)
	ON_COMMAND(IDM_RCOL_HSI, &CColorImageProcessingVer20View::OnRcolHsi)
	ON_COMMAND(IDM_SROW, &CColorImageProcessingVer20View::OnSrow)
	ON_COMMAND(IDM_SROW_HSI, &CColorImageProcessingVer20View::OnSrowHsi)
	ON_COMMAND(IDM_SCOL, &CColorImageProcessingVer20View::OnScol)
	ON_COMMAND(IDM_SCOL_HSI, &CColorImageProcessingVer20View::OnScolHsi)
	ON_COMMAND(IDM_PROW, &CColorImageProcessingVer20View::OnProw)
	ON_COMMAND(IDM_PROW_HSI, &CColorImageProcessingVer20View::OnProwHsi)
	ON_COMMAND(IDM_PCOL, &CColorImageProcessingVer20View::OnPcol)
	ON_COMMAND(IDM_PCOL_HSI, &CColorImageProcessingVer20View::OnPcolHsi)
	ON_COMMAND(IDM_LAP1, &CColorImageProcessingVer20View::OnLap1)
	ON_COMMAND(IDM_LAP1_HSI, &CColorImageProcessingVer20View::OnLap1Hsi)
	ON_COMMAND(IDM_LAP2, &CColorImageProcessingVer20View::OnLap2)
	ON_COMMAND(IDM_LAP2_HSI, &CColorImageProcessingVer20View::OnLap2Hsi)
	ON_COMMAND(IDM_LAP3, &CColorImageProcessingVer20View::OnLap3)
	ON_COMMAND(IDM_LAP3_HSI, &CColorImageProcessingVer20View::OnLap3Hsi)
	ON_COMMAND(IDM_AND_IMAGE, &CColorImageProcessingVer20View::OnAndImage)
	ON_COMMAND(IDM_OR_IMAGE, &CColorImageProcessingVer20View::OnOrImage)
	ON_COMMAND(IDM_XOR_IMAGE, &CColorImageProcessingVer20View::OnXorImage)
END_MESSAGE_MAP()

// CColorImageProcessingVer20View 생성/소멸

CColorImageProcessingVer20View::CColorImageProcessingVer20View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CColorImageProcessingVer20View::~CColorImageProcessingVer20View()
{
}

BOOL CColorImageProcessingVer20View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CColorImageProcessingVer20View 그리기

void CColorImageProcessingVer20View::OnDraw(CDC* pDC)
{
	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	///////////////////
	/// ** 더블 버퍼링 **
	///////////////////
	CColorImageProcessingVer20Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	/////////////////////
	/// 성능 개선을 위한 더블 버퍼링 
	////////////////////
	int i, k;
	unsigned char R, G, B;
	// 메모리 DC 선언
	CDC memDC;
	CBitmap* pOldBitmap, bitmap;

	// 화면 DC와 호환되는 메모리 DC 객체를 생성
	memDC.CreateCompatibleDC(pDC);

	// 마찬가지로 화면 DC와 호환되는 Bitmap 생성
	bitmap.CreateCompatibleBitmap(pDC, pDoc->m_inW, pDoc->m_inH);

	pOldBitmap = memDC.SelectObject(&bitmap);
	memDC.PatBlt(0, 0, pDoc->m_inW, pDoc->m_inH, WHITENESS); // 흰색으로 초기화

	// 출력 영상의 크기를 자동 조절
	double MAXSIZE = 800; // 필요 시 실 모니터 또는 화면의 해상도에 따라서 변경 가능 !
	int inH = pDoc->m_inH;
	int inW = pDoc->m_inW;
	double hop = 1.0; // 기본
	
	if (inH > MAXSIZE || inW > MAXSIZE) {
		// hop을 새로 계산
		if (inW > inH)
			hop = (inW / MAXSIZE);
		else
			hop = (inH / MAXSIZE);

		inW = (int)(inW / hop);
		inH = (int)(inH / hop);
	}

	// 메모리 DC에 그리기
	for (i = 0; i < inH; i++) {
		for (k = 0; k < inW; k++) {
			R = pDoc->m_inImageR[(int)(i * hop)][(int)(k * hop)];
			G = pDoc->m_inImageG[(int)(i * hop)][(int)(k * hop)];
			B = pDoc->m_inImageB[(int)(i * hop)][(int)(k * hop)];
			memDC.SetPixel(k, i, RGB(R, G, B));
		}
	}
	// 메모리 DC를 화면 DC에 고속 복사
	pDC->BitBlt(5, 5, pDoc->m_inW, pDoc->m_inH, &memDC, 0, 0, SRCCOPY);

	memDC.SelectObject(pOldBitmap);
	memDC.DeleteDC();
	bitmap.DeleteObject();

	///////////////////

	// 화면 DC와 호환되는 메모리 DC 객체를 생성
	memDC.CreateCompatibleDC(pDC);

	// 마찬가지로 화면 DC와 호환되는 Bitmap 생성
	bitmap.CreateCompatibleBitmap(pDC, pDoc->m_outW, pDoc->m_outH);

	pOldBitmap = memDC.SelectObject(&bitmap);
	memDC.PatBlt(0, 0, pDoc->m_outW, pDoc->m_outH, WHITENESS); // 흰색으로 초기화

	int outH = pDoc->m_outH;
	int outW = pDoc->m_outW;
	hop = 1.0; // 기본

	if (outH > MAXSIZE || outW > MAXSIZE) {
		// hop을 새로 계산
		if (outW > outH)
			hop = (outW / MAXSIZE);
		else
			hop = (outH / MAXSIZE);

		outW = (int)(outW / hop);
		outH = (int)(outH / hop);
	}

	// 메모리 DC에 그리기
	for (i = 0; i < outH; i++) {
		for (k = 0; k < outW; k++) {
			R = pDoc->m_outImageR[(int)(i * hop)][(int)(k * hop)];
			G = pDoc->m_outImageG[(int)(i * hop)][(int)(k * hop)];
			B = pDoc->m_outImageB[(int)(i * hop)][(int)(k * hop)];
			memDC.SetPixel(k, i, RGB(R, G, B));
		}
	}
	// 메모리 DC를 화면 DC에 고속 복사
	pDC->BitBlt(inW + 10, 5, outW, outH, &memDC, 0, 0, SRCCOPY);

	memDC.SelectObject(pOldBitmap);
	memDC.DeleteDC();
	bitmap.DeleteObject();
}


// CColorImageProcessingVer20View 인쇄

BOOL CColorImageProcessingVer20View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CColorImageProcessingVer20View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CColorImageProcessingVer20View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CColorImageProcessingVer20View 진단

#ifdef _DEBUG
void CColorImageProcessingVer20View::AssertValid() const
{
	CView::AssertValid();
}

void CColorImageProcessingVer20View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CColorImageProcessingVer20Doc* CColorImageProcessingVer20View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CColorImageProcessingVer20Doc)));
	return (CColorImageProcessingVer20Doc*)m_pDocument;
}
#endif //_DEBUG


// CColorImageProcessingVer20View 메시지 처리기


void CColorImageProcessingVer20View::OnEqualImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingVer20Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEqualImage();
	Invalidate(TRUE);
}


void CColorImageProcessingVer20View::OnGrayScale()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingVer20Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnGrayScale();
	Invalidate(TRUE);
}


void CColorImageProcessingVer20View::OnAddImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingVer20Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnAddImage();
	Invalidate(TRUE);
}


void CColorImageProcessingVer20View::OnRevImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingVer20Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnRevImage();
	Invalidate(TRUE);
}


void CColorImageProcessingVer20View::OnBwImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingVer20Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnBwImage();
	Invalidate(TRUE);
}


void CColorImageProcessingVer20View::OnGamImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingVer20Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnGamImage();
	Invalidate(TRUE);
}


void CColorImageProcessingVer20View::OnCapparaImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingVer20Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnCapparaImage();
	Invalidate(TRUE);
}


void CColorImageProcessingVer20View::OnCupparaImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingVer20Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnCupparaImage();
	Invalidate(TRUE);
}


void CColorImageProcessingVer20View::OnPosterImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingVer20Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnPosterImage();
	Invalidate(TRUE);
}


void CColorImageProcessingVer20View::OnStressImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingVer20Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnStressImage();
	Invalidate(TRUE);
}


void CColorImageProcessingVer20View::OnAndImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingVer20Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnAndImage();
	Invalidate(TRUE);
}


void CColorImageProcessingVer20View::OnOrImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingVer20Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnOrImage();
	Invalidate(TRUE);
}


void CColorImageProcessingVer20View::OnXorImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingVer20Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnXorImage();
	Invalidate(TRUE);
}


void CColorImageProcessingVer20View::OnChangeSat()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingVer20Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnChangeSat();
	Invalidate(TRUE);
}


void CColorImageProcessingVer20View::OnExtractColor()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingVer20Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnExtractColor();
	Invalidate(TRUE);
}


void CColorImageProcessingVer20View::OnChangeHue()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingVer20Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnChangeHue();
	Invalidate(TRUE);
}


void CColorImageProcessingVer20View::OnChangeInten()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingVer20Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnChangeInten();
	Invalidate(TRUE);
}


void CColorImageProcessingVer20View::OnZoutImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingVer20Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnZoutImage();
	Invalidate(TRUE);
}


void CColorImageProcessingVer20View::OnZinImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingVer20Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnZinImage();
	Invalidate(TRUE);
}


void CColorImageProcessingVer20View::OnZinImage2()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingVer20Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnZinImage2();
	Invalidate(TRUE);
}


void CColorImageProcessingVer20View::OnRotImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingVer20Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnRotImage();
	Invalidate(TRUE);
}


void CColorImageProcessingVer20View::OnRotImage2()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingVer20Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnRotImage2();
	Invalidate(TRUE);
}


void CColorImageProcessingVer20View::OnMoveImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingVer20Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnMoveImage();
	Invalidate(TRUE);
}


void CColorImageProcessingVer20View::OnMirrorlrImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingVer20Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnMirrorlrImage();
	Invalidate(TRUE);
}


void CColorImageProcessingVer20View::OnMirrorudImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingVer20Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnMirrorudImage();
	Invalidate(TRUE);
}


void CColorImageProcessingVer20View::OnMirrorallImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingVer20Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnMirrorallImage();
	Invalidate(TRUE);
}


void CColorImageProcessingVer20View::OnHistoStretch()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingVer20Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnHistoStretch();
	Invalidate(TRUE);
}


void CColorImageProcessingVer20View::OnEndIn()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingVer20Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEndIn();
	Invalidate(TRUE);
}


void CColorImageProcessingVer20View::OnHistoEqual()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingVer20Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnHistoEqual();
	Invalidate(TRUE);
}


void CColorImageProcessingVer20View::OnEmboss()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingVer20Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEmboss();
	Invalidate(TRUE);
}


void CColorImageProcessingVer20View::OnEmbossHsi()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingVer20Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEmbossHsi();
	Invalidate(TRUE);
}


void CColorImageProcessingVer20View::OnBlur()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingVer20Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnBlur();
	Invalidate(TRUE);
}


void CColorImageProcessingVer20View::OnBlurHsi()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingVer20Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnBlurHsi();
	Invalidate(TRUE);
}


void CColorImageProcessingVer20View::OnSharpning()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingVer20Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnSharpning();
	Invalidate(TRUE);
}


void CColorImageProcessingVer20View::OnSharpningHsi()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingVer20Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnSharpningHsi();
	Invalidate(TRUE);
}


void CColorImageProcessingVer20View::OnHpfSharp()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingVer20Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnHpfSharp();
	Invalidate(TRUE);
}


void CColorImageProcessingVer20View::OnHpfsharpHsi()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingVer20Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnHpfsharpHsi();
	Invalidate(TRUE);
}


void CColorImageProcessingVer20View::OnLpfSharp()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingVer20Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnLpfSharp();
	Invalidate(TRUE);
}


void CColorImageProcessingVer20View::OnLpfsharpHsi()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingVer20Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnLpfsharpHsi();
	Invalidate(TRUE);
}


void CColorImageProcessingVer20View::OnSmoothing()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingVer20Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnSmoothing();
	Invalidate(TRUE);
}


void CColorImageProcessingVer20View::OnSmoothingHsi()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingVer20Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnSmoothingHsi();
	Invalidate(TRUE);
}


void CColorImageProcessingVer20View::OnEdge1()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingVer20Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEdge1();
	Invalidate(TRUE);
}


void CColorImageProcessingVer20View::OnEdge1Hsi()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingVer20Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEdge1Hsi();
	Invalidate(TRUE);
}


void CColorImageProcessingVer20View::OnEdge2()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingVer20Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEdge2();
	Invalidate(TRUE);
}


void CColorImageProcessingVer20View::OnEdge2Hsi()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingVer20Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEdge2Hsi();
	Invalidate(TRUE);
}


void CColorImageProcessingVer20View::OnEdge3()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingVer20Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEdge3();
	Invalidate(TRUE);
}


void CColorImageProcessingVer20View::OnEdge3Hsi()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingVer20Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEdge3Hsi();
	Invalidate(TRUE);
}


void CColorImageProcessingVer20View::OnRrow()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingVer20Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnRrow();
	Invalidate(TRUE);
}


void CColorImageProcessingVer20View::OnRrowHsi()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingVer20Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnRrowHsi();
	Invalidate(TRUE);
}


void CColorImageProcessingVer20View::OnRcol()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingVer20Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnRcol();
	Invalidate(TRUE);
}


void CColorImageProcessingVer20View::OnRcolHsi()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingVer20Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnRcolHsi();
	Invalidate(TRUE);
}


void CColorImageProcessingVer20View::OnSrow()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingVer20Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnSrow();
	Invalidate(TRUE);
}


void CColorImageProcessingVer20View::OnSrowHsi()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingVer20Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnSrowHsi();
	Invalidate(TRUE);
}


void CColorImageProcessingVer20View::OnScol()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingVer20Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnScol();
	Invalidate(TRUE);
}


void CColorImageProcessingVer20View::OnScolHsi()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingVer20Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnScolHsi();
	Invalidate(TRUE);
}


void CColorImageProcessingVer20View::OnProw()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingVer20Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnProw();
	Invalidate(TRUE);
}


void CColorImageProcessingVer20View::OnProwHsi()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingVer20Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnProwHsi();
	Invalidate(TRUE);
}


void CColorImageProcessingVer20View::OnPcol()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingVer20Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnPcol();
	Invalidate(TRUE);
}


void CColorImageProcessingVer20View::OnPcolHsi()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingVer20Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnPcolHsi();
	Invalidate(TRUE);
}


void CColorImageProcessingVer20View::OnLap1()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingVer20Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnLap1();
	Invalidate(TRUE);
}


void CColorImageProcessingVer20View::OnLap1Hsi()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingVer20Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnLap1Hsi();
	Invalidate(TRUE);
}


void CColorImageProcessingVer20View::OnLap2()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingVer20Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnLap2();
	Invalidate(TRUE);
}


void CColorImageProcessingVer20View::OnLap2Hsi()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingVer20Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnLap2Hsi();
	Invalidate(TRUE);
}


void CColorImageProcessingVer20View::OnLap3()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingVer20Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnLap3();
	Invalidate(TRUE);
}


void CColorImageProcessingVer20View::OnLap3Hsi()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingVer20Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnLap3Hsi();
	Invalidate(TRUE);
}
