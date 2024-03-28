
// GrayScaleImageProcessingRC1View.cpp: CGrayScaleImageProcessingRC1View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "GrayScaleImageProcessingRC1.h"
#endif

#include "GrayScaleImageProcessingRC1Doc.h"
#include "GrayScaleImageProcessingRC1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGrayScaleImageProcessingRC1View

IMPLEMENT_DYNCREATE(CGrayScaleImageProcessingRC1View, CView)

BEGIN_MESSAGE_MAP(CGrayScaleImageProcessingRC1View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(IDM_EQUAL_IMAGE, &CGrayScaleImageProcessingRC1View::OnEqualImage)
	ON_COMMAND(IDM_ADD_IMAGE, &CGrayScaleImageProcessingRC1View::OnAddImage)
	ON_COMMAND(IDM_REV_IMAGE, &CGrayScaleImageProcessingRC1View::OnRevImage)
	ON_COMMAND(IDM_BW_IMAGE, &CGrayScaleImageProcessingRC1View::OnBwImage)
	ON_COMMAND(IDM_AVGBW_IMAGE, &CGrayScaleImageProcessingRC1View::OnAvgbwImage)
	ON_COMMAND(IDM_MEDBW_IMAGE, &CGrayScaleImageProcessingRC1View::OnMedbwImage)
	ON_COMMAND(IDM_GAM_IMAGE, &CGrayScaleImageProcessingRC1View::OnGamImage)
	ON_COMMAND(IDM_CAPPARA_IMAGE, &CGrayScaleImageProcessingRC1View::OnCapparaImage)
	ON_COMMAND(IDM_CUPPARA_IMAGE, &CGrayScaleImageProcessingRC1View::OnCupparaImage)
	ON_COMMAND(IDM_POSTER_IMAGE, &CGrayScaleImageProcessingRC1View::OnPosterImage)
	ON_COMMAND(IDM_STRESS_IMAGE, &CGrayScaleImageProcessingRC1View::OnStressImage)
	ON_COMMAND(IDM_ZOUT_IMAGE, &CGrayScaleImageProcessingRC1View::OnZoutImage)
	ON_COMMAND(IDM_ZIN_IMAGE, &CGrayScaleImageProcessingRC1View::OnZinImage)
	ON_COMMAND(IDM_ZIN2_IMAGE, &CGrayScaleImageProcessingRC1View::OnZin2Image)
	ON_COMMAND(IDM_ROT_IMAGE, &CGrayScaleImageProcessingRC1View::OnRotImage)
	ON_COMMAND(IDM_ROT2_IMAGE, &CGrayScaleImageProcessingRC1View::OnRot2Image)
	ON_COMMAND(IDM_MOVE_IMAGE, &CGrayScaleImageProcessingRC1View::OnMoveImage)
	ON_COMMAND(IDM_MIRRORLR, &CGrayScaleImageProcessingRC1View::OnMirrorlr)
	ON_COMMAND(IDM_MIRRORUD, &CGrayScaleImageProcessingRC1View::OnMirrorud)
	ON_COMMAND(IDM_MIRRORALL, &CGrayScaleImageProcessingRC1View::OnMirrorall)
	ON_COMMAND(IDM_HISTO_STRETCH, &CGrayScaleImageProcessingRC1View::OnHistoStretch)
	ON_COMMAND(IDM_END_IN, &CGrayScaleImageProcessingRC1View::OnEndIn)
	ON_COMMAND(IDM_HISTO_EQUAL, &CGrayScaleImageProcessingRC1View::OnHistoEqual)
	ON_COMMAND(IDM_EMBOSS, &CGrayScaleImageProcessingRC1View::OnEmboss)
	ON_COMMAND(IDM_BLUR, &CGrayScaleImageProcessingRC1View::OnBlur)
	ON_COMMAND(IDM_SHARPNING, &CGrayScaleImageProcessingRC1View::OnSharpning)
	ON_COMMAND(IDM_HPF_SHARP, &CGrayScaleImageProcessingRC1View::OnHpfSharp)
	ON_COMMAND(IDM_LPF_SHARP, &CGrayScaleImageProcessingRC1View::OnLpfSharp)
	ON_COMMAND(IDM_SMOOTHING, &CGrayScaleImageProcessingRC1View::OnSmoothing)
	ON_COMMAND(IDM_EDGE1, &CGrayScaleImageProcessingRC1View::OnEdge1)
	ON_COMMAND(IDM_EDGE2, &CGrayScaleImageProcessingRC1View::OnEdge2)
	ON_COMMAND(IDM_EDGE3, &CGrayScaleImageProcessingRC1View::OnEdge3)
	ON_COMMAND(IDM_R_ROW, &CGrayScaleImageProcessingRC1View::OnRRow)
	ON_COMMAND(IDM_R_COL, &CGrayScaleImageProcessingRC1View::OnRCol)
	ON_COMMAND(IDM_S_ROW, &CGrayScaleImageProcessingRC1View::OnSRow)
	ON_COMMAND(IDM_S_COL, &CGrayScaleImageProcessingRC1View::OnSCol)
	ON_COMMAND(IDM_P_ROW, &CGrayScaleImageProcessingRC1View::OnPRow)
	ON_COMMAND(IDM_P_COL, &CGrayScaleImageProcessingRC1View::OnPCol)
	ON_COMMAND(IDM_LAP1, &CGrayScaleImageProcessingRC1View::OnLap1)
	ON_COMMAND(IDM_LAP2, &CGrayScaleImageProcessingRC1View::OnLap2)
	ON_COMMAND(IDM_LAP3, &CGrayScaleImageProcessingRC1View::OnLap3)
END_MESSAGE_MAP()

// CGrayScaleImageProcessingRC1View 생성/소멸

CGrayScaleImageProcessingRC1View::CGrayScaleImageProcessingRC1View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CGrayScaleImageProcessingRC1View::~CGrayScaleImageProcessingRC1View()
{
}

BOOL CGrayScaleImageProcessingRC1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CGrayScaleImageProcessingRC1View 그리기

void CGrayScaleImageProcessingRC1View::OnDraw(CDC* pDC)
{
	CGrayScaleImageProcessingRC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	/*unsigned char R, G, B;
	for (int i = 0; i < pDoc->m_inH; i++) {
		for (int k = 0; k < pDoc->m_inW; k++) {
			R = G = B = pDoc->m_inImage[i][k];
			pDC->SetPixel(k + 5, i + 5, RGB(R, G, B));
		}
	}
	for (int i = 0; i < pDoc->m_outH; i++) {
		for (int k = 0; k < pDoc->m_outW; k++) {
			R = G = B = pDoc->m_outImage[i][k];
			pDC->SetPixel(k + pDoc->m_inW + 10, i + 5, RGB(R, G, B));
		}
	}*/
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

	// 메모리 DC에 그리기
	for (i = 0; i < pDoc->m_inH; i++) {
		for (k = 0; k < pDoc->m_inW; k++) {
			R = G = B = pDoc->m_inImage[i][k];
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

	// 메모리 DC에 그리기
	for (i = 0; i < pDoc->m_outH; i++) {
		for (k = 0; k < pDoc->m_outW; k++) {
			R = G = B = pDoc->m_outImage[i][k];
			memDC.SetPixel(k, i, RGB(R, G, B));
		}
	}
	// 메모리 DC를 화면 DC에 고속 복사
	pDC->BitBlt(pDoc->m_inW + 10, 5, pDoc->m_outW, pDoc->m_outH, &memDC, 0, 0, SRCCOPY);

	memDC.SelectObject(pOldBitmap);
	memDC.DeleteDC();
	bitmap.DeleteObject();
}


// CGrayScaleImageProcessingRC1View 인쇄

BOOL CGrayScaleImageProcessingRC1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CGrayScaleImageProcessingRC1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CGrayScaleImageProcessingRC1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CGrayScaleImageProcessingRC1View 진단

#ifdef _DEBUG
void CGrayScaleImageProcessingRC1View::AssertValid() const
{
	CView::AssertValid();
}

void CGrayScaleImageProcessingRC1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGrayScaleImageProcessingRC1Doc* CGrayScaleImageProcessingRC1View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGrayScaleImageProcessingRC1Doc)));
	return (CGrayScaleImageProcessingRC1Doc*)m_pDocument;
}
#endif //_DEBUG


// CGrayScaleImageProcessingRC1View 메시지 처리기


void CGrayScaleImageProcessingRC1View::OnEqualImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingRC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnEqualImage();
	Invalidate(TRUE);

}


void CGrayScaleImageProcessingRC1View::OnAddImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingRC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnAddImage();
	Invalidate(TRUE);
}


void CGrayScaleImageProcessingRC1View::OnRevImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingRC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnRevImage();
	Invalidate(TRUE);
}


void CGrayScaleImageProcessingRC1View::OnBwImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingRC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnBwImage();
	Invalidate(TRUE);
}


void CGrayScaleImageProcessingRC1View::OnAvgbwImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingRC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnAvgbwImage();
	Invalidate(TRUE);
}


void CGrayScaleImageProcessingRC1View::OnMedbwImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingRC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnMedbwImage();
	Invalidate(TRUE);
}


void CGrayScaleImageProcessingRC1View::OnGamImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingRC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnGamImage();
	Invalidate(TRUE);
}


void CGrayScaleImageProcessingRC1View::OnCapparaImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingRC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnCapparaImage();
	Invalidate(TRUE);
}


void CGrayScaleImageProcessingRC1View::OnCupparaImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingRC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnCupparaImage();
	Invalidate(TRUE);
}


void CGrayScaleImageProcessingRC1View::OnPosterImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingRC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnPosterImage();
	Invalidate(TRUE);
}


void CGrayScaleImageProcessingRC1View::OnStressImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingRC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnStressImage();
	Invalidate(TRUE);
}


void CGrayScaleImageProcessingRC1View::OnZoutImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingRC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnZoutImage();
	Invalidate(TRUE);
}


void CGrayScaleImageProcessingRC1View::OnZinImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingRC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnZinImage();
	Invalidate(TRUE);
}


void CGrayScaleImageProcessingRC1View::OnZin2Image()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingRC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnZin2Image();
	Invalidate(TRUE);
}


void CGrayScaleImageProcessingRC1View::OnRotImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingRC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnRotImage();
	Invalidate(TRUE);
}


void CGrayScaleImageProcessingRC1View::OnRot2Image()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingRC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnRot2Image();
	Invalidate(TRUE);
}


void CGrayScaleImageProcessingRC1View::OnMoveImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingRC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnMoveImage();
	Invalidate(TRUE);
}


void CGrayScaleImageProcessingRC1View::OnMirrorlr()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingRC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnMirrorlr();
	Invalidate(TRUE);
}


void CGrayScaleImageProcessingRC1View::OnMirrorud()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingRC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnMirrorud();
	Invalidate(TRUE);
}


void CGrayScaleImageProcessingRC1View::OnMirrorall()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingRC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnMirrorall();
	Invalidate(TRUE);
}


void CGrayScaleImageProcessingRC1View::OnHistoStretch()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingRC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnHistoStretch();
	Invalidate(TRUE);
}


void CGrayScaleImageProcessingRC1View::OnEndIn()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingRC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnEndIn();
	Invalidate(TRUE);
}


void CGrayScaleImageProcessingRC1View::OnHistoEqual()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingRC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnHistoEqual();
	Invalidate(TRUE);
}


void CGrayScaleImageProcessingRC1View::OnEmboss()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingRC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnEmboss();
	Invalidate(TRUE);
}


void CGrayScaleImageProcessingRC1View::OnBlur()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingRC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnBlur();
	Invalidate(TRUE);
}


void CGrayScaleImageProcessingRC1View::OnSharpning()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingRC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnSharpning();
	Invalidate(TRUE);
}


void CGrayScaleImageProcessingRC1View::OnHpfSharp()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingRC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnHpfSharp();
	Invalidate(TRUE);
}


void CGrayScaleImageProcessingRC1View::OnLpfSharp()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingRC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnLpfSharp();
	Invalidate(TRUE);
}


void CGrayScaleImageProcessingRC1View::OnSmoothing()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingRC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnSmoothing();
	Invalidate(TRUE);
}


void CGrayScaleImageProcessingRC1View::OnEdge1()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingRC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnEdge1();
	Invalidate(TRUE);
}


void CGrayScaleImageProcessingRC1View::OnEdge2()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingRC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnEdge2();
	Invalidate(TRUE);
}


void CGrayScaleImageProcessingRC1View::OnEdge3()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingRC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnEdge3();
	Invalidate(TRUE);
}


void CGrayScaleImageProcessingRC1View::OnRRow()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingRC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnRRow();
	Invalidate(TRUE);
}


void CGrayScaleImageProcessingRC1View::OnRCol()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingRC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnRCol();
	Invalidate(TRUE);
}


void CGrayScaleImageProcessingRC1View::OnSRow()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingRC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnSRow();
	Invalidate(TRUE);
}


void CGrayScaleImageProcessingRC1View::OnSCol()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingRC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnSCol();
	Invalidate(TRUE);
}


void CGrayScaleImageProcessingRC1View::OnPRow()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingRC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnPRow();
	Invalidate(TRUE);
}


void CGrayScaleImageProcessingRC1View::OnPCol()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingRC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnPCol();
	Invalidate(TRUE);
}


void CGrayScaleImageProcessingRC1View::OnLap1()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingRC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnLap1();
	Invalidate(TRUE);
}


void CGrayScaleImageProcessingRC1View::OnLap2()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingRC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnLap2();
	Invalidate(TRUE);
}


void CGrayScaleImageProcessingRC1View::OnLap3()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingRC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnLap3();
	Invalidate(TRUE);
}
