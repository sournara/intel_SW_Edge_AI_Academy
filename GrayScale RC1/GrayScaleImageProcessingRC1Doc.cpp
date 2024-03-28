
// GrayScaleImageProcessingRC1Doc.cpp: CGrayScaleImageProcessingRC1Doc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "GrayScaleImageProcessingRC1.h"
#endif

#include "GrayScaleImageProcessingRC1Doc.h"

#include <propkey.h>
#include "ConstantDlg.h"
#include "StartDlg.h"
#include "EndDlg.h"
#include "xConstant.h"
#include "yConstant.h"
#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CGrayScaleImageProcessingRC1Doc

IMPLEMENT_DYNCREATE(CGrayScaleImageProcessingRC1Doc, CDocument)

BEGIN_MESSAGE_MAP(CGrayScaleImageProcessingRC1Doc, CDocument)
END_MESSAGE_MAP()


// CGrayScaleImageProcessingRC1Doc 생성/소멸

CGrayScaleImageProcessingRC1Doc::CGrayScaleImageProcessingRC1Doc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CGrayScaleImageProcessingRC1Doc::~CGrayScaleImageProcessingRC1Doc()
{
}

BOOL CGrayScaleImageProcessingRC1Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CGrayScaleImageProcessingRC1Doc serialization

void CGrayScaleImageProcessingRC1Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CGrayScaleImageProcessingRC1Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CGrayScaleImageProcessingRC1Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CGrayScaleImageProcessingRC1Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CGrayScaleImageProcessingRC1Doc 진단

#ifdef _DEBUG
void CGrayScaleImageProcessingRC1Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGrayScaleImageProcessingRC1Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CGrayScaleImageProcessingRC1Doc 명령


unsigned char** CGrayScaleImageProcessingRC1Doc::OnMalloc2D(int h, int w, int initVal)
{
	// TODO: 여기에 구현 코드 추가.
	unsigned char** retMemory;
	retMemory = new unsigned char* [h];
	for (int i = 0; i < h; i++)
		retMemory[i] = new unsigned char[w];
	return retMemory;
}


void CGrayScaleImageProcessingRC1Doc::OnFree2D(unsigned char** memory, int h)
{
	// TODO: 여기에 구현 코드 추가.
	if (memory == NULL)
		return;
	for (int i = 0; i < h; i++)
		delete memory[i];
	delete[] memory;
}


BOOL CGrayScaleImageProcessingRC1Doc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	// 선택한 파일 열기
	CFile File;
	File.Open(lpszPathName, CFile::modeRead | CFile::typeBinary);
	// (수정) 2차원배열로사용하기위함- 정방형이미지만다룸.
	double fLength = (double)File.GetLength();
	double log2Value = log(sqrt(fLength)) / log(2.0);
	if (log2Value != (int)log2Value)
	{
		AfxMessageBox(L"정방향크기의 이미지만 지원함");
		return 0;
	}
	// 기존의 메모리는 모두 해제하고, 관련값 초기화.
	OnFree2D(m_inImage, m_inH);
	m_inImage = NULL;
	m_inH = m_inW = 0;
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 입력 이미지 크기 결정 및 메모리 할당
	m_inH = m_inW = (long)sqrt(fLength);
	m_inImage = OnMalloc2D(m_inH, m_inW, 0); // 메모리 할당
	for (int i = 0; i < m_inH; i++)
		File.Read(m_inImage[i], m_inW);
	File.Close();
	return TRUE;
}


void CGrayScaleImageProcessingRC1Doc::OnCloseDocument()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	// 기존의 메모리는 모두 해제하고, 관련값 초기화.
	OnFree2D(m_inImage, m_inH);
	m_inImage = NULL;
	m_inH = m_inW = 0;
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;

	CDocument::OnCloseDocument();
}


void CGrayScaleImageProcessingRC1Doc::OnEqualImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 여러 번 실행할 때, 출력 이미지 메모리 해제
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 메모리 크기 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	// 출력 이미지 영상 처리 <핵심 알고리즘>
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			m_outImage[i][k] = m_inImage[i][k];
		}
	}
}


void CGrayScaleImageProcessingRC1Doc::OnAddImage()
{
	// TODO: 여기에 구현 코드 추가.

	CConstantDlg dlg;
	if (dlg.DoModal() == IDOK) {
		OnFree2D(m_outImage, m_outH);
		m_outImage = NULL;
		m_outH = m_outW = 0;
		// (중요!) 출력 메모리 크기 결정 --> 알고리즘에 의존
		m_outH = m_inH;
		m_outW = m_inW;
		// 출력이미지 메모리 할당
		m_outImage = OnMalloc2D(m_outH, m_outW, 0);
		// 출력 이미지 영상 처리 <핵심 알고리즘>
		int value = (int)dlg.m_constant;

		for (int i = 0; i < m_outH; i++) {
			for (int k = 0; k < m_outW; k++) {
				if (m_inImage[i][k] + value > 255)
					m_outImage[i][k] = 255;
				else if (m_inImage[i][k] + value < 0)
					m_outImage[i][k] = 0;
				else
					m_outImage[i][k] = m_inImage[i][k] + value;
			}
		}
	}
}


BOOL CGrayScaleImageProcessingRC1Doc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CFile File;
	CFileDialog SaveDlg(FALSE, L"raw", NULL, OFN_HIDEREADONLY);

	if (SaveDlg.DoModal() == IDOK) {
		File.Open(SaveDlg.GetPathName(), CFile::modeCreate | CFile::modeWrite);
		for (int i = 0; i < m_outH; i++)
			File.Write(m_outImage[i], m_inW);
		File.Close();
	}
	return true;
}


void CGrayScaleImageProcessingRC1Doc::OnRevImage()
{
	// TODO: 여기에 구현 코드 추가.

	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 메모리 크기 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	// 출력 이미지 영상 처리 <핵심 알고리즘>
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			m_outImage[i][k] = 255 - m_inImage[i][k];
		}
	}
}


void CGrayScaleImageProcessingRC1Doc::OnBwImage()
{
	// TODO: 여기에 구현 코드 추가.

	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 메모리 크기 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	// 출력 이미지 영상 처리 <핵심 알고리즘>
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (m_inImage[i][k] < 127)
				m_outImage[i][k] = 0;
			else
				m_outImage[i][k] = 255;
		}
	}
}


void CGrayScaleImageProcessingRC1Doc::OnAvgbwImage()
{
	// TODO: 여기에 구현 코드 추가.
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 메모리 크기 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	// 출력 이미지 영상 처리 <핵심 알고리즘>
	int avg;
	int hap = 0;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			hap += m_inImage[i][k];
		}
	}
	avg = hap / (m_inH * m_inW);
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (m_inImage[i][k] < avg)
				m_outImage[i][k] = 0;
			else
				m_outImage[i][k] = 255;
		}
	}
}


void CGrayScaleImageProcessingRC1Doc::OnMedbwImage()
{
	// TODO: 여기에 구현 코드 추가.
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 메모리 크기 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	// 출력 이미지 영상 처리 <핵심 알고리즘>
	int med;
	int cnt = 0;
	int size = m_inH * m_inW;
	unsigned char* arr;
	arr =(unsigned char*) new unsigned char[size];
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			arr[cnt] = m_inImage[i][k];
			cnt++;
		}
	}
	std::sort(arr, arr + cnt);
	med = arr[size / 2];
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (m_inImage[i][k] < med)
				m_outImage[i][k] = 0;
			else
				m_outImage[i][k] = 255;
		}
	}
}


int CGrayScaleImageProcessingRC1Doc::compare(const int* a, const int* b)
{
	// TODO: 여기에 구현 코드 추가.
	return (*a - *b);
}


void CGrayScaleImageProcessingRC1Doc::OnGamImage()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDlg dlg;
	if (dlg.DoModal() == IDOK) {
		OnFree2D(m_outImage, m_outH);
		m_outImage = NULL;
		m_outH = m_outW = 0;
		// (중요!) 출력 메모리 크기 결정 --> 알고리즘에 의존
		m_outH = m_inH;
		m_outW = m_inW;
		// 출력이미지 메모리 할당
		m_outImage = OnMalloc2D(m_outH, m_outW, 0);
		// 출력 이미지 영상 처리 <핵심 알고리즘>
		double gamma = dlg.m_constant;

		for (int i = 0; i < m_outH; i++) {
			for (int k = 0; k < m_outW; k++) {
				m_outImage[i][k] = 255 * pow(m_inImage[i][k] / 255., 1 / gamma);
			}
		}
	}

}


void CGrayScaleImageProcessingRC1Doc::OnCapparaImage()
{
	// TODO: 여기에 구현 코드 추가.
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 메모리 크기 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	// 출력 이미지 영상 처리 <핵심 알고리즘>
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			m_outImage[i][k] = 255 * pow(m_inImage[i][k] / 127 - 1, 2);
		}
	}
}


void CGrayScaleImageProcessingRC1Doc::OnCupparaImage()
{
	// TODO: 여기에 구현 코드 추가.
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 메모리 크기 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	// 출력 이미지 영상 처리 <핵심 알고리즘>
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			m_outImage[i][k] = 255 - 255 * pow(m_inImage[i][k] / 127 - 1, 2);
		}
	}
}


void CGrayScaleImageProcessingRC1Doc::OnPosterImage()
{
	// TODO: 여기에 구현 코드 추가.
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 메모리 크기 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	// 출력 이미지 영상 처리 <핵심 알고리즘>
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (m_inImage[i][k] <= 0) 
				m_outImage[i][k] = 0;
			else if ((0 < m_inImage[i][k]) && (m_inImage[i][k] <= 32))
				m_outImage[i][k] = 16;
			else if ((32 < m_inImage[i][k]) && (m_inImage[i][k] <= 64))
				m_outImage[i][k] = 48;
			else if ((64 < m_inImage[i][k]) && (m_inImage[i][k] <= 96))
				m_outImage[i][k] = 80;
			else if ((96 < m_inImage[i][k]) && (m_inImage[i][k] <= 128))
				m_outImage[i][k] = 112;
			else if ((128 < m_inImage[i][k]) && (m_inImage[i][k] <= 160))
				m_outImage[i][k] = 144;
			else if ((160 < m_inImage[i][k]) && (m_inImage[i][k] <= 192))
				m_outImage[i][k] = 176;
			else if ((192 < m_inImage[i][k]) && (m_inImage[i][k] <= 224))
				m_outImage[i][k] = 208;
			else if ((224 < m_inImage[i][k]) && (m_inImage[i][k] <= 255))
				m_outImage[i][k] = 240;
		
		}
	}
}


void CGrayScaleImageProcessingRC1Doc::OnStressImage()
{
	// TODO: 여기에 구현 코드 추가.

	CStartDlg dlg1;
	CEndDlg dlg2;
	if (dlg1.DoModal() == IDOK && dlg2.DoModal() == IDOK) {
		OnFree2D(m_outImage, m_outH);
		m_outImage = NULL;
		m_outH = m_outW = 0;
		// (중요!) 출력 메모리 크기 결정 --> 알고리즘에 의존
		m_outH = m_inH;
		m_outW = m_inW;
		// 출력이미지 메모리 할당
		m_outImage = OnMalloc2D(m_outH, m_outW, 0);
		// 출력 이미지 영상 처리 <핵심 알고리즘>
		int start = (int)dlg1.m_start;
		int end = (int)dlg2.m_end;

		for (int i = 0; i < m_inH; i++) {
			for (int k = 0; k < m_inW; k++) {
				if (start <= m_inImage[i][k] && m_inImage[i][k] <= end)
					m_outImage[i][k] = 255;
				else
					m_outImage[i][k] = m_inImage[i][k];
			}
		}
	}
}


void CGrayScaleImageProcessingRC1Doc::OnZoutImage()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDlg dlg;
	if (dlg.DoModal() == IDOK) {
		int scale = (int)dlg.m_constant;
		OnFree2D(m_outImage, m_outH);
		m_outImage = NULL;
		m_outH = m_outW = 0;
		// (중요!) 출력 메모리 크기 결정 --> 알고리즘에 의존
		m_outH = (int)(m_inH / scale);
		m_outW = (int)(m_inW / scale);
		// 출력이미지 메모리 할당
		m_outImage = OnMalloc2D(m_outH, m_outW, 0);
		// 출력 이미지 영상 처리 <핵심 알고리즘>
		for (int i = 0; i < m_inH; i++) {
			for (int k = 0; k < m_inW; k++) {
				m_outImage[(int)(i / scale)][(int)(k / scale)] = m_inImage[i][k];
			}
		}
	}
}


void CGrayScaleImageProcessingRC1Doc::OnZinImage()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDlg dlg;
	if (dlg.DoModal() == IDOK) {
		int scale = (int)dlg.m_constant;
		OnFree2D(m_outImage, m_outH);
		m_outImage = NULL;
		m_outH = m_outW = 0;
		// (중요!) 출력 메모리 크기 결정 --> 알고리즘에 의존
		m_outH = (int)(m_inH * scale);
		m_outW = (int)(m_inW * scale);
		// 출력이미지 메모리 할당
		m_outImage = OnMalloc2D(m_outH, m_outW, 0);
		// 출력 이미지 영상 처리 <핵심 알고리즘>
		for (int i = 0; i < m_inH; i++) {
			for (int k = 0; k < m_inW; k++) {
				m_outImage[(int)(i * scale)][(int)(k * scale)] = m_inImage[i][k];
			}
		}
	}
}


void CGrayScaleImageProcessingRC1Doc::OnZin2Image()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDlg dlg;
	if (dlg.DoModal() == IDOK) {
		int scale = (int)dlg.m_constant;
		OnFree2D(m_outImage, m_outH);
		m_outImage = NULL;
		m_outH = m_outW = 0;
		// (중요!) 출력 메모리 크기 결정 --> 알고리즘에 의존
		m_outH = (int)(m_inH * scale);
		m_outW = (int)(m_inW * scale);
		// 출력이미지 메모리 할당
		m_outImage = OnMalloc2D(m_outH, m_outW, 0);
		// 출력 이미지 영상 처리 <핵심 알고리즘>
		for (int i = 0; i < m_outH; i++) {
			for (int k = 0; k < m_outW; k++) {
				m_outImage[i][k] = m_inImage[(int)(i / scale)][(int)(k / scale)];
			}
		}
	}
}


void CGrayScaleImageProcessingRC1Doc::OnRotImage()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDlg dlg;
	if (dlg.DoModal() == IDOK) {
		OnFree2D(m_outImage, m_outH);
		m_outImage = NULL;
		m_outH = m_outW = 0;
		// (중요!) 출력 메모리 크기 결정 --> 알고리즘에 의존
		m_outH = m_inH;
		m_outW = m_inW;
		// 출력이미지 메모리 할당
		m_outImage = OnMalloc2D(m_outH, m_outW, 0);
		// 출력 이미지 영상 처리 <핵심 알고리즘>
		int degree = (int)dlg.m_constant;
		double radian = degree * 3.141592 / 180.0;
		for (int i = 0; i < m_outH; i++) {
			for (int k = 0; k < m_outW; k++) {
				int xs = i;
				int ys = k;
				int xd = (int)(cos(radian) * xs - sin(radian) * ys);
				int yd = (int)(sin(radian) * xs + cos(radian) * ys);
				if ((0 <= xd && xd < m_outH) && (0 <= yd && yd < m_outW))
					m_outImage[xd][yd] = m_inImage[xs][ys];
			}
		}
	}
}


void CGrayScaleImageProcessingRC1Doc::OnRot2Image()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDlg dlg;
	if (dlg.DoModal() == IDOK) {
		OnFree2D(m_outImage, m_outH);
		m_outImage = NULL;
		m_outH = m_outW = 0;
		// (중요!) 출력 메모리 크기 결정 --> 알고리즘에 의존
		m_outH = m_inH;
		m_outW = m_inW;
		// 출력이미지 메모리 할당
		m_outImage = OnMalloc2D(m_outH, m_outW, 0);
		// 출력 이미지 영상 처리 <핵심 알고리즘>
		int degree = (int)dlg.m_constant;
		double radian = degree * 3.141592 / 180.0;
		int cx = m_inH / 2;
		int cy = m_inW / 2;
		for (int i = 0; i < m_outH; i++) {
			for (int k = 0; k < m_outW; k++) {
				int xd = i;
				int yd = k;
				int xs = (int)(cos(radian) * (xd - cx) + sin(radian) * (yd - cy));
				int ys = (int)(-sin(radian) * (xd - cx) + cos(radian) * (yd - cy));
				xs += cx;
				ys += cy;
				if ((0 <= xs && xs < m_outH) && (0 <= ys && ys < m_outW))
					m_outImage[xd][yd] = m_inImage[xs][ys];
			}
		}
	}
}


void CGrayScaleImageProcessingRC1Doc::OnMoveImage()
{
	// TODO: 여기에 구현 코드 추가.
	CxConstant dlg1;
	CyConstant dlg2;
	if (dlg1.DoModal() == IDOK && dlg2.DoModal() == IDOK) {
		OnFree2D(m_outImage, m_outH);
		m_outImage = NULL;
		m_outH = m_outW = 0;
		// (중요!) 출력 메모리 크기 결정 --> 알고리즘에 의존
		m_outH = m_inH;
		m_outW = m_inW;
		// 출력이미지 메모리 할당
		m_outImage = OnMalloc2D(m_outH, m_outW, 0);
		// 출력 이미지 영상 처리 <핵심 알고리즘>
		int x = (int)dlg1.m_xconstant;
		int y = (int)dlg2.m_yconstant;

		for (int i = 0; i < m_inH; i++) {
			for (int k = 0; k < m_inW; k++) {
				if ((0 <= x + k && x + k < m_inH) && (0 <= y + i && y + i < m_inW))
					m_outImage[i + y][k + x] = m_inImage[i][k];
			}
		}
	}
}


void CGrayScaleImageProcessingRC1Doc::OnMirrorlr()
{
	// TODO: 여기에 구현 코드 추가.
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 메모리 크기 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	// 출력 이미지 영상 처리 <핵심 알고리즘>
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			m_outImage[i][k] = m_inImage[i][m_inW - k - 1];
		}
	}
}


void CGrayScaleImageProcessingRC1Doc::OnMirrorud()
{
	// TODO: 여기에 구현 코드 추가.
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 메모리 크기 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	// 출력 이미지 영상 처리 <핵심 알고리즘>
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			m_outImage[i][k] = m_inImage[m_inH - 1 - i][k];
		}
	}
}


void CGrayScaleImageProcessingRC1Doc::OnMirrorall()
{
	// TODO: 여기에 구현 코드 추가.
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 메모리 크기 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	// 출력 이미지 영상 처리 <핵심 알고리즘>
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			m_outImage[i][k] = m_inImage[m_inH - 1 - i][m_inW - k - 1];
		}
	}
}


void CGrayScaleImageProcessingRC1Doc::OnHistoStretch()
{
	// TODO: 여기에 구현 코드 추가.
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 메모리 크기 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);

	int high = m_inImage[0][0], low = m_inImage[0][0];
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			if (m_inImage[i][k] < low)
				low = m_inImage[i][k];
			if (m_inImage[i][k] > high)
				high = m_inImage[i][k];
		}
	}
	int old, sero;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			old = m_inImage[i][k];
			sero = (int)((double)(old - low) / (double)(high - low) * 255.0);
			if (sero > 255)
				sero = 255;
			if (sero < 0)
				sero = 0;
			m_outImage[i][k] = sero;
		}
	}
}


void CGrayScaleImageProcessingRC1Doc::OnEndIn()
{
	// TODO: 여기에 구현 코드 추가.
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 메모리 크기 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);

	int high = m_inImage[0][0], low = m_inImage[0][0];
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			if (m_inImage[i][k] < low)
				low = m_inImage[i][k];
			if (m_inImage[i][k] > high)
				high = m_inImage[i][k];
		}
	}

	high -= 50;
	low += 50;

	int old, sero;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			old = m_inImage[i][k];
			sero = (int)((double)(old - low) / (double)(high - low) * 255.0);
			if (sero > 255)
				sero = 255;
			if (sero < 0)
				sero = 0;
			m_outImage[i][k] = sero;
		}
	}
}


void CGrayScaleImageProcessingRC1Doc::OnHistoEqual()
{
	// TODO: 여기에 구현 코드 추가.
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 메모리 크기 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);

	// 1단계 : 빈도수 세기(=히스토그램) histo[256]
	int histo[256] = { 0, };
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
			histo[m_inImage[i][k]]++;
	// 2단계 : 누적히스토그램 생성
	int sumHisto[256] = { 0, };
	sumHisto[0] = histo[0];
	for (int i = 1; i < 256; i++)
		sumHisto[i] = sumHisto[i - 1] + histo[i];
	// 3단계 : 정규화된 히스토그램 생성  normalHisto = sumHisto * (1.0 / (inH*inW) ) * 255.0;
	double normalHisto[256] = { 1.0, };
	for (int i = 0; i < 256; i++) {
		normalHisto[i] = sumHisto[i] * (1.0 / (m_inH * m_inW)) * 255.0;
	}
	// 4다녜 : inImage를 정규화된 값으로 치환
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			m_outImage[i][k] = (unsigned char)normalHisto[m_inImage[i][k]];
		}
	}
}


void CGrayScaleImageProcessingRC1Doc::OnEmboss()
{
	// TODO: 여기에 구현 코드 추가.
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 메모리 크기 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);

	double mask[3][3] = { {-1.0, 0.0, 0.0}, // 엠보싱 마스크
						  { 0.0, 0.0, 0.0},
						  { 0.0, 0.0, 1.0} };
	// 임시 메모리 할당(실수형)
	double** tmpInImage = OnDoubleMalloc(m_inH + 2, m_inW + 2);
	double** tmpOutImage = OnDoubleMalloc(m_outH, m_outW);
	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpInImage[i][k] = 127;

	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
			tmpInImage[i + 1][k + 1] = m_inImage[i][k];

	// *** 회선 연산 ***
	double S;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			// 마스크(3x3) 와 한점을 중심으로한 3x3을 곱하기
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값.

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}
	// 후처리 (마스크 값의 합계에 따라서...)
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++)
			tmpOutImage[i][k] += 127.0;

	// 임시 출력 영상--> 출력 영상. 
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				m_outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				m_outImage[i][k] = 255;
			else
				m_outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	OnDoubleFree(tmpInImage, m_inH + 2);
	OnDoubleFree(tmpOutImage, m_outH);
}


double** CGrayScaleImageProcessingRC1Doc::OnDoubleMalloc(int h, int w)
{
	// TODO: 여기에 구현 코드 추가.
	double** retMemory;
	retMemory = new double* [h];
	for (int i = 0; i < h; i++)
		retMemory[i] = new double[w];
	return retMemory;
}


void CGrayScaleImageProcessingRC1Doc::OnDoubleFree(double** memory, int h)
{
	// TODO: 여기에 구현 코드 추가.
	if (memory == NULL)
		return;
	for (int i = 0; i < h; i++)
		delete memory[i];
	delete memory;

}


void CGrayScaleImageProcessingRC1Doc::OnBlur()
{
	// TODO: 여기에 구현 코드 추가.

	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 메모리 크기 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);

	double mask[3][3] = { {1. / 9, 1. / 9, 1. / 9}, // 블러링 마스크
						  {1. / 9, 1. / 9, 1. / 9},
						  {1. / 9, 1. / 9, 1. / 9} };
	// 임시 메모리 할당(실수형)
	double** tmpInImage = OnDoubleMalloc(m_inH + 2, m_inW + 2);
	double** tmpOutImage = OnDoubleMalloc(m_outH, m_outW);

	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpInImage[i][k] = 127;

	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
			tmpInImage[i + 1][k + 1] = m_inImage[i][k];

	// *** 회선 연산 ***
	double S;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			// 마스크(3x3) 와 한점을 중심으로한 3x3을 곱하기
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값.

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}
	// 후처리 (마스크 값의 합계에 따라서...)
	//for (int i = 0; i < m_outH; i++)
	//	for (int k = 0; k < m_outW; k++)
	//		tmpOutImage[i][k] += 127.0;

	// 임시 출력 영상--> 출력 영상. 
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				m_outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				m_outImage[i][k] = 255;
			else
				m_outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	OnDoubleFree(tmpInImage, m_inH + 2);
	OnDoubleFree(tmpOutImage, m_outH);
}


void CGrayScaleImageProcessingRC1Doc::OnSharpning()
{
	// TODO: 여기에 구현 코드 추가.

	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 메모리 크기 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);

	double mask[3][3] = { {0.0, -1.0, 0.0}, // 샤프닝 마스크
								 {-1.0, 5.0, -1.0},
								 {0.0, -1.0, 0.0} };
	// 임시 메모리 할당(실수형)
	double** tmpInImage = OnDoubleMalloc(m_inH + 2, m_inW + 2);
	double** tmpOutImage = OnDoubleMalloc(m_outH, m_outW);
	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpInImage[i][k] = 127;

	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
			tmpInImage[i + 1][k + 1] = m_inImage[i][k];

	// *** 회선 연산 ***
	double S;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			// 마스크(3x3) 와 한점을 중심으로한 3x3을 곱하기
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값.

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}
	// 후처리 (마스크 값의 합계에 따라서...)
	//for (int i = 0; i < m_outH; i++)
	//	for (int k = 0; k < m_outW; k++)
	//		tmpOutImage[i][k] += 127.0;

	// 임시 출력 영상--> 출력 영상. 
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				m_outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				m_outImage[i][k] = 255;
			else
				m_outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	OnDoubleFree(tmpInImage, m_inH + 2);
	OnDoubleFree(tmpOutImage, m_outH);
}


void CGrayScaleImageProcessingRC1Doc::OnHpfSharp()
{
	// TODO: 여기에 구현 코드 추가.

	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 메모리 크기 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);

	double mask[3][3] = { {-1. / 9, -1. / 9, -1. / 9}, // 고주파필터 샤프닝 마스크
								 {-1. / 9, 8. / 9, -1. / 9},
								 {-1. / 9, -1. / 9, -1. / 9} };
	// 임시 메모리 할당(실수형)
	double** tmpInImage = OnDoubleMalloc(m_inH + 2, m_inW + 2);
	double** tmpOutImage = OnDoubleMalloc(m_outH, m_outW);
	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpInImage[i][k] = 127;

	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
			tmpInImage[i + 1][k + 1] = m_inImage[i][k];

	// *** 회선 연산 ***
	double S;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			// 마스크(3x3) 와 한점을 중심으로한 3x3을 곱하기
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값.

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}
	// 후처리 (마스크 값의 합계에 따라서...)
	//for (int i = 0; i < m_outH; i++)
	//	for (int k = 0; k < m_outW; k++)
	//		tmpOutImage[i][k] += 127.0;

	// 임시 출력 영상--> 출력 영상. 
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				m_outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				m_outImage[i][k] = 255;
			else
				m_outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	OnDoubleFree(tmpInImage, m_inH + 2);
	OnDoubleFree(tmpOutImage, m_outH);
}


void CGrayScaleImageProcessingRC1Doc::OnLpfSharp()
{
	// TODO: 여기에 구현 코드 추가.
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 메모리 크기 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);

	double mask[3][3] = { {1. / 9, 1. / 9, 1. / 9}, // 저주파필터 샤프닝 마스크
								 {1. / 9, 1. / 9, 1. / 9},
								 {1. / 9, 1. / 9, 1. / 9} };
	// 임시 메모리 할당(실수형)
	double** tmpInImage = OnDoubleMalloc(m_inH + 2, m_inW + 2);
	double** tmpOutImage = OnDoubleMalloc(m_outH, m_outW);
	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpInImage[i][k] = 127;

	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
			tmpInImage[i + 1][k + 1] = m_inImage[i][k];

	// *** 회선 연산 ***
	double S;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			// 마스크(3x3) 와 한점을 중심으로한 3x3을 곱하기
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값.

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}
	// 후처리 (마스크 값의 합계에 따라서...)
	//for (int i = 0; i < m_outH; i++)
	//	for (int k = 0; k < m_outW; k++)
	//		tmpOutImage[i][k] += 127.0;

	// 임시 출력 영상--> 출력 영상. 
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				m_outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				m_outImage[i][k] = 255;
			else
				m_outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	OnDoubleFree(tmpInImage, m_inH + 2);
	OnDoubleFree(tmpOutImage, m_outH);
}


void CGrayScaleImageProcessingRC1Doc::OnSmoothing()
{
	// TODO: 여기에 구현 코드 추가.
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 메모리 크기 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);

	double mask[3][3] = { {1. / 16, 1. / 8, 1. / 16}, // 가우시안 스무딩 마스크
								 {1. / 8, 1. / 4, 1. / 8},
								 {1. / 16, 1. / 8, 1. / 16} };
	// 임시 메모리 할당(실수형)
	double** tmpInImage = OnDoubleMalloc(m_inH + 2, m_inW + 2);
	double** tmpOutImage = OnDoubleMalloc(m_outH, m_outW);
	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpInImage[i][k] = 127;

	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
			tmpInImage[i + 1][k + 1] = m_inImage[i][k];

	// *** 회선 연산 ***
	double S;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			// 마스크(3x3) 와 한점을 중심으로한 3x3을 곱하기
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값.

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}
	// 후처리 (마스크 값의 합계에 따라서...)
	//for (int i = 0; i < m_outH; i++)
	//	for (int k = 0; k < m_outW; k++)
	//		tmpOutImage[i][k] += 127.0;

	// 임시 출력 영상--> 출력 영상. 
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				m_outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				m_outImage[i][k] = 255;
			else
				m_outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	OnDoubleFree(tmpInImage, m_inH + 2);
	OnDoubleFree(tmpOutImage, m_outH);
}


void CGrayScaleImageProcessingRC1Doc::OnEdge1()
{
	// TODO: 여기에 구현 코드 추가.
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 메모리 크기 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);

	double mask[3][3] = { {0.0, 0.0, 0.0}, // 수직검출 마스크
						  {-1.0, 1.0, 0.0},
						  {0.0, 0.0, 0.0} };
	// 임시 메모리 할당(실수형)
	double** tmpInImage = OnDoubleMalloc(m_inH + 2, m_inW + 2);
	double** tmpOutImage = OnDoubleMalloc(m_outH, m_outW);
	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpInImage[i][k] = 127;

	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
			tmpInImage[i + 1][k + 1] = m_inImage[i][k];

	// *** 회선 연산 ***
	double S;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			// 마스크(3x3) 와 한점을 중심으로한 3x3을 곱하기
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값.

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}
	// 후처리 (마스크 값의 합계에 따라서...)
	//for (int i = 0; i < m_outH; i++)
	//	for (int k = 0; k < m_outW; k++)
	//		tmpOutImage[i][k] += 127.0;

	// 임시 출력 영상--> 출력 영상. 
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				m_outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				m_outImage[i][k] = 255;
			else
				m_outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	OnDoubleFree(tmpInImage, m_inH + 2);
	OnDoubleFree(tmpOutImage, m_outH);
}


void CGrayScaleImageProcessingRC1Doc::OnEdge2()
{
	// TODO: 여기에 구현 코드 추가.
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 메모리 크기 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);

	double mask[3][3] = { {0.0, -1.0, 0.0}, // 수평검출 마스크
						  {0.0, 1.0, 0.0},
						  {0.0, 0.0, 0.0} };
	// 임시 메모리 할당(실수형)
	double** tmpInImage = OnDoubleMalloc(m_inH + 2, m_inW + 2);
	double** tmpOutImage = OnDoubleMalloc(m_outH, m_outW);
	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpInImage[i][k] = 127;

	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
			tmpInImage[i + 1][k + 1] = m_inImage[i][k];

	// *** 회선 연산 ***
	double S;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			// 마스크(3x3) 와 한점을 중심으로한 3x3을 곱하기
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값.

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}
	// 후처리 (마스크 값의 합계에 따라서...)
	//for (int i = 0; i < m_outH; i++)
	//	for (int k = 0; k < m_outW; k++)
	//		tmpOutImage[i][k] += 127.0;

	// 임시 출력 영상--> 출력 영상. 
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				m_outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				m_outImage[i][k] = 255;
			else
				m_outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	OnDoubleFree(tmpInImage, m_inH + 2);
	OnDoubleFree(tmpOutImage, m_outH);
}


void CGrayScaleImageProcessingRC1Doc::OnEdge3()
{
	// TODO: 여기에 구현 코드 추가.
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 메모리 크기 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);

	double mask[3][3] = { {1.0, 1.0, 1.0}, // 유사연산자 마스크
						  {1.0, 1.0, 1.0},
						  {1.0, 1.0, 1.0} };
	// 임시 메모리 할당(실수형)
	double** tmpInImage = OnDoubleMalloc(m_inH + 2, m_inW + 2);
	double** tmpOutImage = OnDoubleMalloc(m_outH, m_outW);
	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpInImage[i][k] = 127;

	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
			tmpInImage[i + 1][k + 1] = m_inImage[i][k];

	// *** 회선 연산 ***
	double S, dif;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			// 마스크(3x3) 와 한점을 중심으로한 3x3을 곱하기
			dif = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값.

			for (int m = 0; m < 3; m++) {
				for (int n = 0; n < 3; n++) {
					S = tmpInImage[i + 1][k + 1] - tmpInImage[i + m][k + n];
					if (S > dif)
						dif = S;
				}
			}
			tmpOutImage[i][k] = dif;
		}
	}
	// 후처리 (마스크 값의 합계에 따라서...)
	//for (int i = 0; i < outH; i++)
	//	for (int k = 0; k < outW; k++)
	//		tmpOutImage[i][k] += 127.0;

	// 임시 출력 영상--> 출력 영상. 
	double t;
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			t = tmpOutImage[i][k];
			if (t < 0.0)
				t = 0.0;
			else if (t > 255.0)
				t = 255.0;
			else
				m_outImage[i][k] = (unsigned char)tmpOutImage[i][k] * (t / 255);
		}
	}
	OnDoubleFree(tmpInImage, m_inH + 2);
	OnDoubleFree(tmpOutImage, m_outH);
}


void CGrayScaleImageProcessingRC1Doc::OnRRow()
{
	// TODO: 여기에 구현 코드 추가.
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 메모리 크기 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);

	double mask[3][3] = { {-1.0, 0.0, 0.0}, // 로버츠(행 검출) 마스크
						  {0.0, 1.0, 0.0},
						  {0.0, 0.0, 0.0} };
	// 임시 메모리 할당(실수형)
	double** tmpInImage = OnDoubleMalloc(m_inH + 2, m_inW + 2);
	double** tmpOutImage = OnDoubleMalloc(m_outH, m_outW);
	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpInImage[i][k] = 127;

	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
			tmpInImage[i + 1][k + 1] = m_inImage[i][k];

	// *** 회선 연산 ***
	double S;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			// 마스크(3x3) 와 한점을 중심으로한 3x3을 곱하기
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값.

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}
	// 후처리 (마스크 값의 합계에 따라서...)
	//for (int i = 0; i < m_outH; i++)
	//	for (int k = 0; k < m_outW; k++)
	//		tmpOutImage[i][k] += 127.0;

	// 임시 출력 영상--> 출력 영상. 
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				m_outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				m_outImage[i][k] = 255;
			else
				m_outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	OnDoubleFree(tmpInImage, m_inH + 2);
	OnDoubleFree(tmpOutImage, m_outH);
}


void CGrayScaleImageProcessingRC1Doc::OnRCol()
{
	// TODO: 여기에 구현 코드 추가.
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 메모리 크기 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);

	double mask[3][3] = { {0.0, 0.0, -1.0}, // 로버츠(열 검출) 마스크
						  {0.0, 1.0, 0.0},
						  {0.0, 0.0, 0.0} };
	// 임시 메모리 할당(실수형)
	double** tmpInImage = OnDoubleMalloc(m_inH + 2, m_inW + 2);
	double** tmpOutImage = OnDoubleMalloc(m_outH, m_outW);
	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpInImage[i][k] = 127;

	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
			tmpInImage[i + 1][k + 1] = m_inImage[i][k];

	// *** 회선 연산 ***
	double S;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			// 마스크(3x3) 와 한점을 중심으로한 3x3을 곱하기
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값.

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}
	// 후처리 (마스크 값의 합계에 따라서...)
	//for (int i = 0; i < m_outH; i++)
	//	for (int k = 0; k < m_outW; k++)
	//		tmpOutImage[i][k] += 127.0;

	// 임시 출력 영상--> 출력 영상. 
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				m_outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				m_outImage[i][k] = 255;
			else
				m_outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	OnDoubleFree(tmpInImage, m_inH + 2);
	OnDoubleFree(tmpOutImage, m_outH);
}


void CGrayScaleImageProcessingRC1Doc::OnSRow()
{
	// TODO: 여기에 구현 코드 추가.
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 메모리 크기 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);

	double mask[3][3] = { {-1.0, -1.0, -1.0}, // 소벨(행 검출) 마스크
						  {0.0, 0.0, 0.0},
						  {1.0, 1.0, 1.0} };
	// 임시 메모리 할당(실수형)
	double** tmpInImage = OnDoubleMalloc(m_inH + 2, m_inW + 2);
	double** tmpOutImage = OnDoubleMalloc(m_outH, m_outW);
	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpInImage[i][k] = 127;

	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
			tmpInImage[i + 1][k + 1] = m_inImage[i][k];

	// *** 회선 연산 ***
	double S;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			// 마스크(3x3) 와 한점을 중심으로한 3x3을 곱하기
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값.

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}
	// 후처리 (마스크 값의 합계에 따라서...)
	//for (int i = 0; i < m_outH; i++)
	//	for (int k = 0; k < m_outW; k++)
	//		tmpOutImage[i][k] += 127.0;

	// 임시 출력 영상--> 출력 영상. 
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				m_outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				m_outImage[i][k] = 255;
			else
				m_outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	OnDoubleFree(tmpInImage, m_inH + 2);
	OnDoubleFree(tmpOutImage, m_outH);
}


void CGrayScaleImageProcessingRC1Doc::OnSCol()
{
	// TODO: 여기에 구현 코드 추가.
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 메모리 크기 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);

	double mask[3][3] = { {1.0, 0.0, -1.0}, // 소벨(열 검출) 마스크
						  {1.0, 0.0, -1.0},
						  {1.0, 0.0, -1.0} };
	// 임시 메모리 할당(실수형)
	double** tmpInImage = OnDoubleMalloc(m_inH + 2, m_inW + 2);
	double** tmpOutImage = OnDoubleMalloc(m_outH, m_outW);
	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpInImage[i][k] = 127;

	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
			tmpInImage[i + 1][k + 1] = m_inImage[i][k];

	// *** 회선 연산 ***
	double S;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			// 마스크(3x3) 와 한점을 중심으로한 3x3을 곱하기
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값.

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}
	// 후처리 (마스크 값의 합계에 따라서...)
	//for (int i = 0; i < m_outH; i++)
	//	for (int k = 0; k < m_outW; k++)
	//		tmpOutImage[i][k] += 127.0;

	// 임시 출력 영상--> 출력 영상. 
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				m_outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				m_outImage[i][k] = 255;
			else
				m_outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	OnDoubleFree(tmpInImage, m_inH + 2);
	OnDoubleFree(tmpOutImage, m_outH);
}


void CGrayScaleImageProcessingRC1Doc::OnPRow()
{
	// TODO: 여기에 구현 코드 추가.
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 메모리 크기 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);

	double mask[3][3] = { {-1.0, -2.0, -1.0}, // 프리윗(행 검출) 마스크
						  {0.0, 0.0, 0.0},
						  {1.0, 2.0, 1.0} };
	// 임시 메모리 할당(실수형)
	double** tmpInImage = OnDoubleMalloc(m_inH + 2, m_inW + 2);
	double** tmpOutImage = OnDoubleMalloc(m_outH, m_outW);
	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpInImage[i][k] = 127;

	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
			tmpInImage[i + 1][k + 1] = m_inImage[i][k];

	// *** 회선 연산 ***
	double S;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			// 마스크(3x3) 와 한점을 중심으로한 3x3을 곱하기
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값.

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}
	// 후처리 (마스크 값의 합계에 따라서...)
	//for (int i = 0; i < m_outH; i++)
	//	for (int k = 0; k < m_outW; k++)
	//		tmpOutImage[i][k] += 127.0;

	// 임시 출력 영상--> 출력 영상. 
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				m_outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				m_outImage[i][k] = 255;
			else
				m_outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	OnDoubleFree(tmpInImage, m_inH + 2);
	OnDoubleFree(tmpOutImage, m_outH);
}


void CGrayScaleImageProcessingRC1Doc::OnPCol()
{
	// TODO: 여기에 구현 코드 추가.
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 메모리 크기 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);

	double mask[3][3] = { {1.0, 0.0, -1.0}, // 프리윗(열 검출) 마스크
						  {2.0, 0.0, -2.0},
						  {1.0, 0.0, -1.0} };
	// 임시 메모리 할당(실수형)
	double** tmpInImage = OnDoubleMalloc(m_inH + 2, m_inW + 2);
	double** tmpOutImage = OnDoubleMalloc(m_outH, m_outW);
	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpInImage[i][k] = 127;

	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
			tmpInImage[i + 1][k + 1] = m_inImage[i][k];

	// *** 회선 연산 ***
	double S;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			// 마스크(3x3) 와 한점을 중심으로한 3x3을 곱하기
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값.

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}
	// 후처리 (마스크 값의 합계에 따라서...)
	//for (int i = 0; i < m_outH; i++)
	//	for (int k = 0; k < m_outW; k++)
	//		tmpOutImage[i][k] += 127.0;

	// 임시 출력 영상--> 출력 영상. 
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				m_outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				m_outImage[i][k] = 255;
			else
				m_outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	OnDoubleFree(tmpInImage, m_inH + 2);
	OnDoubleFree(tmpOutImage, m_outH);
}


void CGrayScaleImageProcessingRC1Doc::OnLap1()
{
	// TODO: 여기에 구현 코드 추가.
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 메모리 크기 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);

	double mask[3][3] = { {0.0, -1.0, 0.0}, // 라플라시안(1) 마스크
						  {-1.0, 4.0, -1.0},
						  {0.0, -1.0, 0.0} };
	// 임시 메모리 할당(실수형)
	double** tmpInImage = OnDoubleMalloc(m_inH + 2, m_inW + 2);
	double** tmpOutImage = OnDoubleMalloc(m_outH, m_outW);
	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpInImage[i][k] = 127;

	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
			tmpInImage[i + 1][k + 1] = m_inImage[i][k];

	// *** 회선 연산 ***
	double S;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			// 마스크(3x3) 와 한점을 중심으로한 3x3을 곱하기
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값.

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}
	// 후처리 (마스크 값의 합계에 따라서...)
	//for (int i = 0; i < m_outH; i++)
	//	for (int k = 0; k < m_outW; k++)
	//		tmpOutImage[i][k] += 127.0;

	// 임시 출력 영상--> 출력 영상. 
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				m_outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				m_outImage[i][k] = 255;
			else
				m_outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	OnDoubleFree(tmpInImage, m_inH + 2);
	OnDoubleFree(tmpOutImage, m_outH);
}


void CGrayScaleImageProcessingRC1Doc::OnLap2()
{
	// TODO: 여기에 구현 코드 추가.
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 메모리 크기 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);

	double mask[3][3] = { {1.0, 1.0, 1.0}, // 라플라시안(2) 마스크
						  {1.0, -8.0, 1.0},
						  {1.0, 1.0, 1.0} };
	// 임시 메모리 할당(실수형)
	double** tmpInImage = OnDoubleMalloc(m_inH + 2, m_inW + 2);
	double** tmpOutImage = OnDoubleMalloc(m_outH, m_outW);
	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpInImage[i][k] = 127;

	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
			tmpInImage[i + 1][k + 1] = m_inImage[i][k];

	// *** 회선 연산 ***
	double S;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			// 마스크(3x3) 와 한점을 중심으로한 3x3을 곱하기
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값.

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}
	// 후처리 (마스크 값의 합계에 따라서...)
	//for (int i = 0; i < m_outH; i++)
	//	for (int k = 0; k < m_outW; k++)
	//		tmpOutImage[i][k] += 127.0;

	// 임시 출력 영상--> 출력 영상. 
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				m_outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				m_outImage[i][k] = 255;
			else
				m_outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	OnDoubleFree(tmpInImage, m_inH + 2);
	OnDoubleFree(tmpOutImage, m_outH);
}


void CGrayScaleImageProcessingRC1Doc::OnLap3()
{
	// TODO: 여기에 구현 코드 추가.
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 메모리 크기 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);

	double mask[3][3] = { {-1.0, -1.0, -1.0}, // 라플라시안(3) 마스크
						  {-1.0, 8.0, -1.0},
						  {-1.0, -1.0, -1.0} };
	// 임시 메모리 할당(실수형)
	double** tmpInImage = OnDoubleMalloc(m_inH + 2, m_inW + 2);
	double** tmpOutImage = OnDoubleMalloc(m_outH, m_outW);
	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpInImage[i][k] = 127;

	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
			tmpInImage[i + 1][k + 1] = m_inImage[i][k];

	// *** 회선 연산 ***
	double S;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			// 마스크(3x3) 와 한점을 중심으로한 3x3을 곱하기
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값.

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}
	// 후처리 (마스크 값의 합계에 따라서...)
	//for (int i = 0; i < m_outH; i++)
	//	for (int k = 0; k < m_outW; k++)
	//		tmpOutImage[i][k] += 127.0;

	// 임시 출력 영상--> 출력 영상. 
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				m_outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				m_outImage[i][k] = 255;
			else
				m_outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	OnDoubleFree(tmpInImage, m_inH + 2);
	OnDoubleFree(tmpOutImage, m_outH);
}
