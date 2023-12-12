
// ImageProc_20180781View.cpp: CImageProc20180781View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ImageProc_20180781.h"
#endif

#include "ImageProc_20180781Doc.h"
#include "ImageProc_20180781View.h"

#include <vfw.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImageProc20180781View

IMPLEMENT_DYNCREATE(CImageProc20180781View, CScrollView)

BEGIN_MESSAGE_MAP(CImageProc20180781View, CScrollView)
	ON_COMMAND(ID_PIXEL_ADD, &CImageProc20180781View::OnPixelAdd)
	ON_COMMAND(ID_PIXEL_SUB, &CImageProc20180781View::OnPixelSub)
	ON_COMMAND(ID_PIXEL_MUL, &CImageProc20180781View::OnPixelMul)
	ON_COMMAND(ID_PIXEL_DIV, &CImageProc20180781View::OnPixelDiv)
	ON_COMMAND(ID_PIXEL_HISTO_EQ, &CImageProc20180781View::OnPixelHistoEq)
	ON_COMMAND(ID_PIXEL_CONTRAST_STRETCHING, &CImageProc20180781View::OnPixelContrastStretching)
	ON_COMMAND(ID_PIXEL_BINARIZATION, &CImageProc20180781View::OnPixelBinarization)
	ON_COMMAND(ID_PIXEL_TWO_IMAGE_ADD, &CImageProc20180781View::OnPixelTwoImageAdd)
	ON_COMMAND(ID_PIXEL_TWO_IMAGE_SUB, &CImageProc20180781View::OnPixelTwoImageSub)
	ON_COMMAND(ID_REGION_SMOOTHING, &CImageProc20180781View::OnRegionSmoothing)
	ON_COMMAND(ID_REGION_SHARPENING, &CImageProc20180781View::OnRegionSharpening)
	ON_COMMAND(ID_REGION_EMBOSSING, &CImageProc20180781View::OnRegionEmbossing)
	ON_COMMAND(ID_REGION_PREWITT, &CImageProc20180781View::OnRegionPrewitt)
	ON_COMMAND(ID_REGION_SOBEL, &CImageProc20180781View::OnRegionSobel)
	ON_COMMAND(ID_REGION_ROBERTS, &CImageProc20180781View::OnRegionRoberts)
	ON_COMMAND(ID_REGION_AVERAGEFILTERING, &CImageProc20180781View::OnRegionAveragefiltering)
	ON_COMMAND(ID_REGION_MEDIANFILTERING, &CImageProc20180781View::OnRegionMedianfiltering)
	ON_COMMAND(ID_MOPOLOGY_COLOR_GRAY, &CImageProc20180781View::OnMopologyColorGray)
	ON_COMMAND(ID_MOPOLOGY_BINARYZATION, &CImageProc20180781View::OnMopologyBinaryzation)
	ON_COMMAND(ID_MOPOLOGY_EROSION, &CImageProc20180781View::OnMopologyErosion)
	ON_COMMAND(ID_MOPOLOGY_DILATION, &CImageProc20180781View::OnMopologyDilation)
	ON_COMMAND(ID_MOPOLOGY_OPENING, &CImageProc20180781View::OnMopologyOpening)
	ON_COMMAND(ID_MOPOLOGY_CLOSING, &CImageProc20180781View::OnMopologyClosing)
	ON_COMMAND(ID_GEOMETRY_ZOOMIN_PIXEL_COPY, &CImageProc20180781View::OnGeometryZoominPixelCopy)
	ON_COMMAND(ID_GEOMETRY_ZOOMIN_BILINEARINTERPOLATION, &CImageProc20180781View::OnGeometryZoominBilinearinterpolation)
	ON_COMMAND(ID_GEOMETRY_TRYZOOMOUT_SUBSAMPLING, &CImageProc20180781View::OnGeometryTryzoomoutSubsampling)
	ON_COMMAND(ID_GEOMETRY_ZOOMOUT_MEANSUB, &CImageProc20180781View::OnGeometryZoomoutMeansub)
	ON_COMMAND(ID_GEOMETRY_AVG_FILTERING, &CImageProc20180781View::OnGeometryAvgFiltering)
	ON_COMMAND(ID_GEOMETRY_ROTATION, &CImageProc20180781View::OnGeometryRotation)
	ON_COMMAND(ID_GEOMETRY_HORIZONTAL_FLIP, &CImageProc20180781View::OnGeometryHorizontalFlip)
	ON_COMMAND(ID_GEOMETRY_VERTICAL_FLIP, &CImageProc20180781View::OnGeometryVerticalFlip)
	ON_COMMAND(ID_GEOMETRY_WARPING, &CImageProc20180781View::OnGeometryWarping)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_AVI_VIEW, &CImageProc20180781View::OnAviView)
END_MESSAGE_MAP()

// CImageProc20180781View 생성/소멸

CImageProc20180781View::CImageProc20180781View() noexcept
{
	bAVIMode = false;
}

CImageProc20180781View::~CImageProc20180781View()
{
}

BOOL CImageProc20180781View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CScrollView::PreCreateWindow(cs);
}

// CImageProc20180781View 그리기

void CImageProc20180781View::OnDraw(CDC* pDC)
{
	CImageProc20180781Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (bAVIMode) {
		//재생
		LoadAviFile(pDC);
		bAVIMode = false;
		return;
	}

	int x, y;
	//흑백일경우
	if (pDoc->InputImg != NULL) {
		if (pDoc->depth == 1) {
			for (y = 0; y < pDoc->ImageHeight; y++) {
				for (x = 0; x < pDoc->ImageWidth; x++) {
					pDC->SetPixel(x, y, RGB(pDoc->InputImg[y][x], pDoc->InputImg[y][x], pDoc->InputImg[y][x]));
				}
			}
		}
		//칼라일경우
		else {
			for (y = 0; y < pDoc->ImageHeight; y++) {
				for (x = 0; x < pDoc->ImageWidth; x++) {
					pDC->SetPixel(x, y, RGB(pDoc->InputImg[y][3*x+0], pDoc->InputImg[y][3 * x + 1], pDoc->InputImg[y][3 * x + 2]));
				}
			}
		}
	}

	if (pDoc->ResultImg != NULL) {
		if (pDoc->depth == 1) {
			for (y = 0; y < pDoc->ImageHeight; y++) {
				for (x = 0; x < pDoc->ImageWidth; x++) {
					pDC->SetPixel(pDoc->ImageWidth + 20 + x, y, RGB(pDoc->ResultImg[y][x], pDoc->ResultImg[y][x], pDoc->ResultImg[y][x]));
				}
			}
		}
		else {
			for (y = 0; y < pDoc->ImageHeight; y++) {
				for (x = 0; x < pDoc->ImageWidth; x++) {
					pDC->SetPixel(pDoc->ImageWidth + 20 + x, y, RGB(pDoc->ResultImg[y][3*x+0], pDoc->ResultImg[y][3 * x + 1], pDoc->ResultImg[y][3 * x + 2]));
				}
			}
		}
	}

	if (pDoc->InputImg2 != NULL) {
		if (pDoc->depth == 1) {
			for (y = 0; y < pDoc->ImageHeight; y++) {
				for (x = 0; x < pDoc->ImageWidth; x++) {
					pDC->SetPixel(2 * (pDoc->ImageWidth + 20) + x, y, RGB(pDoc->InputImg2[y][x], pDoc->InputImg2[y][x], pDoc->InputImg2[y][x]));
				}
			}
		}
		else {
			for (y = 0; y < pDoc->ImageHeight; y++) {
				for (x = 0; x < pDoc->ImageWidth; x++) {
					pDC->SetPixel(2 * (pDoc->ImageWidth + 20) + x, y, RGB(pDoc->InputImg2[y][3*x+0], pDoc->InputImg2[y][3 * x + 1], pDoc->InputImg2[y][3 * x + 2]));
				}
			}
		}
	}

	if (pDoc->gResultImg != NULL) {
		if (pDoc->depth == 1) {
			for (y = 0; y < pDoc->gImageHeight; y++) {
				for (x = 0; x < pDoc->gImageWidth; x++) {
					pDC->SetPixel(x, pDoc->ImageHeight + 20 + y, RGB(pDoc->gResultImg[y][x], pDoc->gResultImg[y][x], pDoc->gResultImg[y][x]));
				}
			}
		}
		else {
			for (y = 0; y < pDoc->gImageHeight; y++) {
				for (x = 0; x < pDoc->gImageWidth; x++) {
					pDC->SetPixel(x, pDoc->ImageHeight + 20 + y, RGB(pDoc->gResultImg[y][3 * x + 0], pDoc->gResultImg[y][3 * x + 1], pDoc->gResultImg[y][3 * x + 2]));
				}
			}
		}
	}
}

void CImageProc20180781View::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 이 뷰의 전체 크기를 계산합니다.
	sizeTotal.cx = sizeTotal.cy = 2048;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CImageProc20180781View 진단

#ifdef _DEBUG
void CImageProc20180781View::AssertValid() const
{
	CScrollView::AssertValid();
}

void CImageProc20180781View::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CImageProc20180781Doc* CImageProc20180781View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageProc20180781Doc)));
	return (CImageProc20180781Doc*)m_pDocument;
}
#endif //_DEBUG


// CImageProc20180781View 메시지 처리기


void CImageProc20180781View::OnPixelAdd()
{
	CImageProc20180781Doc* pDoc = GetDocument();

	if (pDoc->InputImg == NULL)
		return;

	int x, y, value;

	for (y = 0; y < pDoc->ImageHeight; y++) {
		for (x = 0; x < pDoc->ImageWidth * pDoc->depth; x++) {			
			value = pDoc->InputImg[y][x] + 50;
			if (value > 255) value = 255;
			else if (value < 0)	value = 0;
			pDoc->ResultImg[y][x] = value;						
		}
	}
	Invalidate();
}


void CImageProc20180781View::OnPixelSub()
{
	CImageProc20180781Doc* pDoc = GetDocument();

	int x, y, value;

	for (y = 0; y < pDoc->ImageHeight; y++) {
		for (x = 0; x < pDoc->ImageWidth * pDoc->depth; x++) {
			value = pDoc->InputImg[y][x] - 50;
			if (value > 255) value = 255;
			else if (value < 0)	value = 0;
			pDoc->ResultImg[y][x] = value;
		}
	}
	Invalidate();
}


void CImageProc20180781View::OnPixelMul()
{
	CImageProc20180781Doc* pDoc = GetDocument();

	int x, y, value;

	for (y = 0; y < pDoc->ImageHeight; y++) {
		for (x = 0; x < pDoc->ImageWidth * pDoc->depth; x++) {
			value = pDoc->InputImg[y][x] * 1.5;
			if (value > 255) value = 255;
			else if (value < 0)	value = 0;
			pDoc->ResultImg[y][x] = value;
		}
	}
	Invalidate();
}


void CImageProc20180781View::OnPixelDiv()
{
	CImageProc20180781Doc* pDoc = GetDocument();

	int x, y, value;

	for (y = 0; y < pDoc->ImageHeight; y++) {
		for (x = 0; x < pDoc->ImageWidth * pDoc->depth; x++) {
			value = pDoc->InputImg[y][x] / 1.5;
			if (value > 255) value = 255;
			else if (value < 0)	value = 0;
			pDoc->ResultImg[y][x] = value;
		}
	}
	Invalidate();
}

//히스토그램 구하기 depth 안곱함
void CImageProc20180781View::OnPixelHistoEq()
{
	CImageProc20180781Doc* pDoc = GetDocument();

	int x, y, k;
	int acc_hist;
	float N = pDoc->ImageHeight * pDoc->ImageWidth;		//imageheight imagewidth로 변경, 256*256에서 변경
	int hist[256], sum[256];	

	for (int i = 0; i < 256; i++) {		//밝기라 수정x
		hist[i] = 0;
	}

	//히스토그램 구하기
	for (y = 0; y < pDoc->ImageHeight; y++) {			//imageheight 수정
		for (x = 0; x < pDoc->ImageWidth; x++) {		// depth 안함
			k = pDoc->InputImg[y][x];
			hist[k]++;
		}
	}

	//누적분포 구하기
	acc_hist = 0;
	for (int i = 0; i < 256; i++) {		//밝기라 수정x
		acc_hist += hist[i];
		sum[i] = acc_hist;
	}

	//평활화 화소값저장
	for (y = 0; y < pDoc->ImageHeight; y++) {			//가로 세로 수정
		for (x = 0; x < pDoc->ImageWidth * pDoc->depth; x++) {
			k = pDoc->InputImg[y][x];
			pDoc->ResultImg[y][x] = (float)sum[k] / N * 255;		//최대밝기값 수정x
		}
	}

	Invalidate();
}


//가로 세로 수정 완
void CImageProc20180781View::OnPixelContrastStretching()
{
	CImageProc20180781Doc* pDoc = GetDocument();

	int x, y;
	int min = 255; 
	int max = 0;	
		
	//최소값
	for (y = 0; y < pDoc->ImageHeight; y++) {
		for (x = 0; x < pDoc->ImageWidth * pDoc->depth; x++) {
			if (pDoc->InputImg[y][x] < min) {
				min = pDoc->InputImg[y][x];
			}
		}
	}

	//최대값
	for (y = 0; y < pDoc->ImageHeight; y++) {
		for (x = 0; x < pDoc->ImageWidth * pDoc->depth; x++) {
			if (pDoc->InputImg[y][x] > max) {
				max = pDoc->InputImg[y][x];
			}
		}
	}

	//명암대비 스트레칭 계산
	for (y = 0; y < pDoc->ImageHeight; y++) {
		for (x = 0; x < pDoc->ImageWidth * pDoc->depth; x++) {
			pDoc->ResultImg[y][x] = (pDoc->InputImg[y][x] - min) / (float)(max - min) * 255;
		}
	}
	Invalidate();
}


void CImageProc20180781View::OnPixelBinarization()
{
	CImageProc20180781Doc* pDoc = GetDocument();

	int x, y, value;
	int threshHold = 128;		//기준값을 128로 설정

	for (y = 0; y < pDoc->ImageHeight; y++) {			//가로세로 수정
		for (x = 0; x < pDoc->ImageWidth * pDoc->depth; x++) {
			value = pDoc->InputImg[y][x];
			if (value > threshHold) {
				pDoc->ResultImg[y][x] = 255;		//밝기값 수정x
			}
			else {
				pDoc->ResultImg[y][x] = 0;			//밝기값 수정x
			}
		}
	}
	Invalidate();
}


void CImageProc20180781View::OnPixelTwoImageAdd()
{	
	CImageProc20180781Doc* pDoc = GetDocument();
	
	CFileDialog dlg(TRUE);

	//취소를 눌렀을 때
	if (dlg.DoModal() != IDOK) {
		return;
	}

	CFile file;
	file.Open(dlg.GetPathName(), CFile::modeRead);
	CArchive ar(&file, CArchive::load);
	pDoc->LoadSecondImageFile(ar);
	file.Close();
	//LoadTwoImage();

	int x, y, value;

	for (y = 0; y < pDoc->ImageHeight; y++) {				//가로 세로 수정
		for (x = 0; x < pDoc->ImageWidth; x++) {
			value = 0.7 * pDoc->InputImg[y][x] + 0.3 * pDoc->InputImg2[y][x];		//비율에 따라 한쪽 비율이 달라짐
			if (value > 255) {
				value = 255;
			}
			else if (value < 0) {
				value = 0;
			}
			pDoc->ResultImg[y][x] = value;
		}
	}

	Invalidate();
}

//커스텀 메뉴 클릭시에 파일 불러오기
//PPM PGM 메모리확보 등 새로운 데이터를 InputImg2에 저장하게 메모리 할당하게
void CImageProc20180781View::LoadTwoImage()
{
	CImageProc20180781Doc* pDoc = GetDocument();

	CFileDialog dlg(TRUE);

	if (dlg.DoModal() == IDOK) {
		CFile file;
		file.Open(dlg.GetPathName(), CFile::modeRead);
		file.Read(pDoc->InputImg2, 256 * 256);
		file.Close();
	}
	//Invalidate();
}


void CImageProc20180781View::OnPixelTwoImageSub()
{
	CImageProc20180781Doc* pDoc = GetDocument();

	CFileDialog dlg(TRUE);

	//취소를 눌렀을 때
	if (dlg.DoModal() != IDOK) {
		return;
	}

	CFile file;
	file.Open(dlg.GetPathName(), CFile::modeRead);
	CArchive ar(&file, CArchive::load);
	pDoc->LoadSecondImageFile(ar);
	file.Close();

	int x, y, value;

	for (y = 0; y < pDoc->ImageHeight; y++) {
		for (x = 0; x < pDoc->ImageWidth; x++) {
			value = (pDoc->InputImg[y][x] - pDoc->InputImg2[y][x]);		//비율에 따라 한쪽 비율이 달라짐
			
			
			if (value > 255) {
				value = 255;
			}
			else if(value < 0){
				value = 0;
			}
			
			//아래 if는 필요없음
			/*
			if (value > 255) {
				value = 255;
			}
			else if (value < 0) {
				value = 0;
			}
			*/
			pDoc->ResultImg[y][x] = value;
		}
	}

	Invalidate();
}


void CImageProc20180781View::OnRegionSmoothing()
{
	CImageProc20180781Doc* pDoc = GetDocument();

	float kernel[3][3] = { {1 / 9.0, 1 / 9.0, 1 / 9.0},
							{1 / 9.0, 1 / 9.0, 1 / 9.0},
							{1 / 9.0, 1 / 9.0, 1 / 9.0}};

	Convolve(pDoc->InputImg, pDoc->ResultImg, pDoc->ImageWidth, pDoc->ImageHeight, kernel, 0, pDoc->depth);

	Invalidate();
}


void CImageProc20180781View::Convolve(unsigned char** InImg, unsigned char** OutImg, int cols, int rows, float mask[][3], int bias, int depth)
{
	int x, y, value, i ,j;
	float sum, redsum, greensum, bluesum;

	for (y = 1; y < rows -1; y++) {			//테두리 값은 계산하지 않음
		for (x = 1; x < cols - 1; x++) {
			if (depth == 1) {
				sum = 0;
				for (j = 0; j < 3; j++) {
					for (i = 0; i < 3; i++) {
						sum += InImg[y - 1 + j][x - 1 + i] * mask[j][i];
					}
				}
				sum += bias;

				if (sum > 255)
					sum = 255;
				else if (sum < 0)
					sum = 0;
				OutImg[y][x] = sum;
			}
			else {
				redsum = 0;
				greensum = 0;
				bluesum = 0;
				for (j = 0; j < 3; j++) {
					for (i = 0; i < 3; i++) {
						redsum += InImg[y - 1 + j][3*(x - 1 + i)+0] * mask[j][i];
						greensum += InImg[y - 1 + j][3*(x - 1 + i)+1] * mask[j][i];
						bluesum += InImg[y - 1 + j][3*(x - 1 + i)+2] * mask[j][i];
					}
				}
				redsum += bias;
				greensum += bias;
				bluesum += bias;

				if (redsum > 255)		redsum = 255;
				else if (redsum < 0)	redsum = 0;

				if (greensum > 255)		greensum = 255;
				else if (greensum < 0)	greensum = 0;

				if (bluesum > 255)		bluesum = 255;
				else if (bluesum < 0)	bluesum = 0;

				OutImg[y][3*x+0] = redsum;
				OutImg[y][3*x+1] = greensum;
				OutImg[y][3*x+2] = bluesum;
			}
		}
	}
}


void CImageProc20180781View::OnRegionSharpening()
{
	CImageProc20180781Doc* pDoc = GetDocument();

	float kernel[3][3] = { {0, -1, 0},
							{-1, 5, -1},
							{0, -1, 0} };

	Convolve(pDoc->InputImg, pDoc->ResultImg, pDoc->ImageWidth, pDoc->ImageHeight, kernel, 0, pDoc->depth);

	Invalidate();
}


void CImageProc20180781View::OnRegionEmbossing()
{
	CImageProc20180781Doc* pDoc = GetDocument();

	float kernel[3][3] = { {-1, 0, 0},
							{0, 0, 0},
							{0, 0, 1} };

	Convolve(pDoc->InputImg, pDoc->ResultImg, pDoc->ImageWidth, pDoc->ImageHeight, kernel, 0, pDoc->depth);

	Invalidate();
}


void CImageProc20180781View::OnRegionPrewitt()
{
	CImageProc20180781Doc* pDoc = GetDocument();

	float Hmask[3][3] =		{ {-1, -1, -1},
							{0, 0, 0},
							{1, 1, 1} };

	float Vmask[3][3] =		{ {-1, 0, 1},
							{-1, 0, 1},
							{-1, 0, 1} };

	unsigned char** Er, **Ec;
	int value;

	//메모리할당
	Er = (unsigned char**)malloc(pDoc->ImageHeight * sizeof(unsigned char*));
	Ec = (unsigned char**)malloc(pDoc->ImageHeight * sizeof(unsigned char*));
	for (int i = 0; i < pDoc->ImageHeight; i++) {
		Er[i] = (unsigned char*)malloc(pDoc->ImageWidth * pDoc->depth);
		Ec[i] = (unsigned char*)malloc(pDoc->ImageWidth * pDoc->depth);
	}

	Convolve(pDoc->InputImg, Er, pDoc->ImageWidth, pDoc->ImageHeight, Hmask, 0, pDoc->depth);
	Convolve(pDoc->InputImg, Ec, pDoc->ImageWidth, pDoc->ImageHeight, Vmask, 0, pDoc->depth);

	for (int y = 0; y < pDoc->ImageHeight; y++) {
		for (int x = 0; x < pDoc->ImageWidth; x++) {
			if (pDoc->depth == 1) {
				value = sqrt(Er[y][x] * Er[y][x] + Ec[y][x] * Ec[y][x]);
				if (value > 255) {
					value = 255;
				}
				else if (value < 0) {
					value = 0;
				}
				pDoc->ResultImg[y][x] = value;
			}
			else {				
				value = sqrt(Er[y][3 * x + 0] * Er[y][3 * x + 0] + Ec[y][3 * x + 0] * Ec[y][3 * x + 0]);
				if (value > 255) {
					value = 255;
				}
				else if (value < 0) {
					value = 0;
				}
				pDoc->ResultImg[y][3 * x + 0] = value;

				value = sqrt(Er[y][3 * x + 1] * Er[y][3 * x + 1] + Ec[y][3 * x + 1] * Ec[y][3 * x + 1]);
				if (value > 255) {
					value = 255;
				}
				else if (value < 0) {
					value = 0;
				}
				pDoc->ResultImg[y][3 * x + 1] = value;

				value = sqrt(Er[y][3 * x + 2] * Er[y][3 * x + 2] + Ec[y][3 * x + 2] * Ec[y][3 * x + 2]);
				if (value > 255) {
					value = 255;
				}
				else if (value < 0) {
					value = 0;
				}
				pDoc->ResultImg[y][3 * x + 2] = value;

				/*
				value = sqrt(pDoc->ResultImg[y][3 * x + 0] * pDoc->ResultImg[y][3 * x + 0] +
							 pDoc->ResultImg[y][3 * x + 1] * pDoc->ResultImg[y][3 * x + 1] +
							 pDoc->ResultImg[y][3 * x + 2] * pDoc->ResultImg[y][3 * x + 2]);
				if (value > 255)	value = 255;
				else if (value < 0) value = 0;

				pDoc->ResultImg[y][3 * x + 0] = value;
				pDoc->ResultImg[y][3 * x + 1] = value;
				pDoc->ResultImg[y][3 * x + 2] = value;
				*/
			}
		}
	}

	//메모리 해제
	for (int i = 0; i < pDoc->ImageHeight; i++) {
		free(Er[i]);
		free(Ec[i]);
	}
	free(Er);
	free(Ec);

	Invalidate();
}

void CImageProc20180781View::OnRegionRoberts()
{
	CImageProc20180781Doc* pDoc = GetDocument();

	float Hmask[3][3] = { {-1, 0, 0},
							{0, 1, 0},
							{0, 0, 0} };

	float Vmask[3][3] = { {0, -1, 0},
							{1, 0, 0},
							{0, 0, 0} };

	unsigned char** Er, ** Ec;
	int value;

	//메모리할당
	Er = (unsigned char**)malloc(pDoc->ImageHeight * sizeof(unsigned char*));
	Ec = (unsigned char**)malloc(pDoc->ImageHeight * sizeof(unsigned char*));
	for (int i = 0; i < pDoc->ImageHeight; i++) {
		Er[i] = (unsigned char*)malloc(pDoc->ImageWidth * pDoc->depth);
		Ec[i] = (unsigned char*)malloc(pDoc->ImageWidth * pDoc->depth);
	}

	Convolve(pDoc->InputImg, Er, pDoc->ImageWidth, pDoc->ImageHeight, Hmask, 0, pDoc->depth);
	Convolve(pDoc->InputImg, Ec, pDoc->ImageWidth, pDoc->ImageHeight, Vmask, 0, pDoc->depth);

	for (int y = 0; y < pDoc->ImageHeight; y++) {
		for (int x = 0; x < pDoc->ImageWidth * pDoc->depth; x++) {
			value = sqrt(Er[y][x] * Er[y][x] + Ec[y][x] * Ec[y][x]);
			if (value > 255) {
				value = 255;
			}
			else if (value < 0) {
				value = 0;
			}
			pDoc->ResultImg[y][x] = value;
		}
	}

	//메모리 해제
	for (int i = 0; i < pDoc->ImageHeight; i++) {
		free(Er[i]);
		free(Ec[i]);
	}
	free(Er);
	free(Ec);

	Invalidate();
}

void CImageProc20180781View::OnRegionSobel()
{
	CImageProc20180781Doc* pDoc = GetDocument();

	float Hmask[3][3] = { {-1, -2, -1},
							{0, 0, 0},
							{1, 2, 1} };

	float Vmask[3][3] = { {-1, 0, 1},
							{-2, 0, 2},
							{-1, 0, 1} };

	unsigned char** Er, ** Ec;
	int value;

	//메모리할당
	Er = (unsigned char**)malloc(pDoc->ImageHeight * sizeof(unsigned char*));
	Ec = (unsigned char**)malloc(pDoc->ImageHeight * sizeof(unsigned char*));
	for (int i = 0; i < pDoc->ImageHeight; i++) {
		Er[i] = (unsigned char*)malloc(pDoc->ImageWidth * pDoc->depth);
		Ec[i] = (unsigned char*)malloc(pDoc->ImageWidth * pDoc->depth);
	}

	Convolve(pDoc->InputImg, Er, pDoc->ImageWidth, pDoc->ImageHeight, Hmask, 0, pDoc->depth);
	Convolve(pDoc->InputImg, Ec, pDoc->ImageWidth, pDoc->ImageHeight, Vmask, 0, pDoc->depth);

	for (int y = 0; y < pDoc->ImageHeight; y++) {
		for (int x = 0; x < pDoc->ImageWidth * pDoc->depth; x++) {
			value = sqrt(Er[y][x] * Er[y][x] + Ec[y][x] * Ec[y][x]);
			if (value > 255) {
				value = 255;
			}
			else if (value < 0) {
				value = 0;
			}
			pDoc->ResultImg[y][x] = value;
		}
	}

	//메모리 해제
	for (int i = 0; i < pDoc->ImageHeight; i++) {
		free(Er[i]);
		free(Ec[i]);
	}
	free(Er);
	free(Ec);

	Invalidate();
}



//중간값 필터링
void CImageProc20180781View::OnRegionAveragefiltering()
{
	CImageProc20180781Doc* pDoc = GetDocument();
	int x, y, i, j;
	int xcur, ycur;
	int sum, count, rsum, gsum, bsum;

	for (y = 0; y < pDoc->ImageHeight; y++) {
		for (x = 0; x < pDoc->ImageWidth; x++) {
			if (pDoc->depth == 1) {
				sum = 0;
				count = 0;
				for (j = -2; j <= 2; j++)				//1로 바꾸면 흐리게하기랑 똑같음
					for (i = -2; i <= 2; i++) {
						ycur = y + j;
						xcur = x + i;

						//영역안에 포함되어있는지 확인
						if (ycur >= 0 && ycur <= pDoc->ImageHeight - 1 && xcur >= 0 && xcur <= pDoc->ImageWidth - 1) {
							sum += pDoc->InputImg[ycur][xcur];			//하나의 픽셀을 가져옴
							count++;
						}
					}
				pDoc->ResultImg[y][x] = sum / count;
			}
			else {
				rsum = 0, gsum = 0, bsum = 0;
				count = 0;
				for (j = -2; j <= 2; j++)				//1로 바꾸면 흐리게하기랑 똑같음
					for (i = -2; i <= 2; i++) {
						ycur = y + j;
						xcur = x + i;

						//영역안에 포함되어있는지 확인
						if (ycur >= 0 && ycur <= pDoc->ImageHeight - 1 && xcur >= 0 && xcur <= pDoc->ImageWidth - 1) {
							rsum += pDoc->InputImg[ycur][3 * xcur + 0];
							gsum += pDoc->InputImg[ycur][3 * xcur + 1];
							bsum += pDoc->InputImg[ycur][3 * xcur + 2];						
							count++;
						}
					}
				pDoc->ResultImg[y][3 * x + 0] = rsum / count;
				pDoc->ResultImg[y][3 * x + 1] = gsum / count;
				pDoc->ResultImg[y][3 * x + 2] = bsum / count;
			}
		}
	}
	Invalidate();
}


void CImageProc20180781View::OnRegionMedianfiltering()
{
	CImageProc20180781Doc* pDoc = GetDocument();
	int x, y, i ,j, temp;
	int n[9];

	for (y = 1; y < pDoc->ImageHeight-1; y++)			//테두리 데이터 제외
		for (x = 1; x < pDoc->ImageWidth-1; x++) {
			if (pDoc->depth == 1) {
				n[0] = pDoc->InputImg[y - 1][x - 1];
				n[1] = pDoc->InputImg[y - 1][x - 0];
				n[2] = pDoc->InputImg[y - 1][x + 1];
				n[3] = pDoc->InputImg[y - 0][x - 1];
				n[4] = pDoc->InputImg[y - 0][x - 0];
				n[5] = pDoc->InputImg[y - 0][x + 1];
				n[6] = pDoc->InputImg[y + 1][x - 1];
				n[7] = pDoc->InputImg[y + 1][x - 0];
				n[8] = pDoc->InputImg[y + 1][x + 1];

				//sorting
				for (i = 8; i > 0; i--)
					for (j = 0; j < i; j++) {
						if (n[j] > n[j + 1]) {
							temp = n[j + 1];
							n[j + 1] = n[j];
							n[j] = temp;
						}
					}
				pDoc->ResultImg[y][x] = n[4];
			}
			else {
				n[0] = pDoc->InputImg[y - 1][3 * (x - 1) + 0];
				n[1] = pDoc->InputImg[y - 1][3 * (x - 0) + 0];
				n[2] = pDoc->InputImg[y - 1][3 * (x + 1) + 0];
				n[3] = pDoc->InputImg[y - 0][3 * (x - 1) + 0];
				n[4] = pDoc->InputImg[y - 0][3 * (x - 0) + 0];
				n[5] = pDoc->InputImg[y - 0][3 * (x + 1) + 0];
				n[6] = pDoc->InputImg[y + 1][3 * (x - 1) + 0];
				n[7] = pDoc->InputImg[y + 1][3 * (x - 0) + 0];
				n[8] = pDoc->InputImg[y + 1][3 * (x + 1) + 0];

				//sorting
				for (i = 8; i > 0; i--)
					for (j = 0; j < i; j++) {
						if (n[j] > n[j + 1]) {
							temp = n[j + 1];
							n[j + 1] = n[j];
							n[j] = temp;
						}
					}
				pDoc->ResultImg[y][3 * x + 0] = n[4];

				n[0] = pDoc->InputImg[y - 1][3 * (x - 1) + 1];
				n[1] = pDoc->InputImg[y - 1][3 * (x - 0) + 1];
				n[2] = pDoc->InputImg[y - 1][3 * (x + 1) + 1];
				n[3] = pDoc->InputImg[y - 0][3 * (x - 1) + 1];
				n[4] = pDoc->InputImg[y - 0][3 * (x - 0) + 1];
				n[5] = pDoc->InputImg[y - 0][3 * (x + 1) + 1];
				n[6] = pDoc->InputImg[y + 1][3 * (x - 1) + 1];
				n[7] = pDoc->InputImg[y + 1][3 * (x - 0) + 1];
				n[8] = pDoc->InputImg[y + 1][3 * (x + 1) + 1];

				//sorting
				for (i = 8; i > 0; i--)
					for (j = 0; j < i; j++) {
						if (n[j] > n[j + 1]) {
							temp = n[j + 1];
							n[j + 1] = n[j];
							n[j] = temp;
						}
					}
				pDoc->ResultImg[y][3 * x + 1] = n[4];

				n[0] = pDoc->InputImg[y - 1][3 * (x - 1) + 2];
				n[1] = pDoc->InputImg[y - 1][3 * (x - 0) + 2];
				n[2] = pDoc->InputImg[y - 1][3 * (x + 1) + 2];
				n[3] = pDoc->InputImg[y - 0][3 * (x - 1) + 2];
				n[4] = pDoc->InputImg[y - 0][3 * (x - 0) + 2];
				n[5] = pDoc->InputImg[y - 0][3 * (x + 1) + 2];
				n[6] = pDoc->InputImg[y + 1][3 * (x - 1) + 2];
				n[7] = pDoc->InputImg[y + 1][3 * (x - 0) + 2];
				n[8] = pDoc->InputImg[y + 1][3 * (x + 1) + 2];

				//sorting
				for (i = 8; i > 0; i--)
					for (j = 0; j < i; j++) {
						if (n[j] > n[j + 1]) {
							temp = n[j + 1];
							n[j + 1] = n[j];
							n[j] = temp;
						}
					}
				pDoc->ResultImg[y][3 * x + 2] = n[4];
			}
		}
	Invalidate();
}


void CImageProc20180781View::OnMopologyColorGray()
{
	CImageProc20180781Doc* pDoc = GetDocument();
	if (pDoc->depth == 1) return;

	int x, y;
	int gray;

	for (y = 0; y < pDoc->ImageHeight; y++)		
		for (x = 0; x < pDoc->ImageWidth; x++) {
			gray = (pDoc->InputImg[y][3 * x + 0] + pDoc->InputImg[y][3 * x + 1] + pDoc->InputImg[y][3 * x + 2]) / 3;

			pDoc->InputImg[y][3 * x + 0] = gray;
			pDoc->InputImg[y][3 * x + 1] = gray;
			pDoc->InputImg[y][3 * x + 2] = gray;
		}
	Invalidate();
}


void CImageProc20180781View::OnMopologyBinaryzation()
{
	CImageProc20180781Doc* pDoc = GetDocument();

	int x, y;
	int thresh = 128;

	for (y = 0; y < pDoc->ImageHeight; y++)		
		for (x = 0; x < pDoc->ImageWidth; x++) {
			if (pDoc->depth == 1){
				if (pDoc->InputImg[y][x] > thresh) {
					pDoc->InputImg[y][x] = 255;
				}
				else{
					pDoc->InputImg[y][x] = 0;
				}
			}	
			else {
				if ((pDoc->InputImg[y][3 * x + 0] + pDoc->InputImg[y][3 * x + 1] + pDoc->InputImg[y][3 * x + 2]) / 3 > thresh) {
					pDoc->InputImg[y][3 * x + 0] = 255;
					pDoc->InputImg[y][3 * x + 1] = 255;
					pDoc->InputImg[y][3 * x + 2] = 255;
				}
				else {
					pDoc->InputImg[y][3 * x + 0] = 0;
					pDoc->InputImg[y][3 * x + 1] = 0;
					pDoc->InputImg[y][3 * x + 2] = 0;
				}
			}
		}
	Invalidate();
}

//침식연산
void CImageProc20180781View::OnMopologyErosion()
{
	CImageProc20180781Doc* pDoc = GetDocument();

	int x, y, j, i;	
	int min, rmin, gmin, bmin = 255;


	for (y = 1; y < pDoc->ImageHeight - 1; y++)
		for (x = 1; x < pDoc->ImageWidth - 1; x++) {
			if (pDoc->depth == 1) {
				min = 255;
				for (j = -1; j <= 1; j++)
					for (i = -1; i <= 1; i++) {
						if (pDoc->InputImg[y + j][x + i] < min)
							min = pDoc->InputImg[y + j][x + i];
					}
				pDoc->ResultImg[y][x] = min;
			}
			else {
				rmin = 255;	gmin = 255;	bmin = 255;
				for (j = -1; j <= 1; j++)
					for (i = -1; i <= 1; i++) {
						if (pDoc->InputImg[y + j][3 * (x + i) + 0] < rmin)
							rmin = pDoc->InputImg[y + j][3 * (x + i) + 0];
						if (pDoc->InputImg[y + j][3 * (x + i) + 1] < gmin)
							gmin = pDoc->InputImg[y + j][3 * (x + i) + 1];
						if (pDoc->InputImg[y + j][3 * (x + i) + 2] < bmin)
							bmin = pDoc->InputImg[y + j][3 * (x + i) + 2];
					}
				pDoc->ResultImg[y][3 * x + 0] = rmin;
				pDoc->ResultImg[y][3 * x + 1] = gmin;
				pDoc->ResultImg[y][3 * x + 2] = bmin;
			}
		}
	Invalidate();
}


void CImageProc20180781View::OnMopologyDilation()
{
	CImageProc20180781Doc* pDoc = GetDocument();

	int x, y, j, i;
	int max, rmax, gmax, bmax = 0;


	for (y = 1; y < pDoc->ImageHeight - 1; y++)
		for (x = 1; x < pDoc->ImageWidth - 1; x++) {
			if (pDoc->depth == 1) {
				max = 0;
				for (j = -1; j <= 1; j++)
					for (i = -1; i <= 1; i++) {
						if (pDoc->InputImg[y + j][x + i] > max)
							max = pDoc->InputImg[y + j][x + i];
					}
				pDoc->ResultImg[y][x] = max;
			}
			else {
				rmax = 0;	gmax = 0;	bmax = 0;
				for (j = -1; j <= 1; j++)
					for (i = -1; i <= 1; i++) {
						if (pDoc->InputImg[y + j][3 * (x + i) + 0] > rmax)
							rmax = pDoc->InputImg[y + j][3 * (x + i) + 0];
						if (pDoc->InputImg[y + j][3 * (x + i) + 1] > gmax)
							gmax = pDoc->InputImg[y + j][3 * (x + i) + 1];
						if (pDoc->InputImg[y + j][3 * (x + i) + 2] > bmax)
							bmax = pDoc->InputImg[y + j][3 * (x + i) + 2];
					}
				pDoc->ResultImg[y][3 * x + 0] = rmax;
				pDoc->ResultImg[y][3 * x + 1] = gmax;
				pDoc->ResultImg[y][3 * x + 2] = bmax;
			}
		}
	Invalidate();
}

//열림연산
void CImageProc20180781View::OnMopologyOpening()
{
	OnMopologyErosion();
	CopyResultToInput();

	OnMopologyErosion();
	CopyResultToInput();

	OnMopologyErosion();
	CopyResultToInput();


	OnMopologyDilation();
	CopyResultToInput();

	OnMopologyDilation();
	CopyResultToInput();

	OnMopologyDilation();
	
}


void CImageProc20180781View::CopyResultToInput()
{
	CImageProc20180781Doc* pDoc = GetDocument();

	int x, y;
	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth * pDoc->depth; x++) {	//RGB값에 동일한 연산은 depth 곱하기?
			pDoc->InputImg[y][x] = pDoc->ResultImg[y][x];
		}
}

//닫힘연산
void CImageProc20180781View::OnMopologyClosing()
{
	OnMopologyDilation();
	CopyResultToInput();

	OnMopologyDilation();
	CopyResultToInput();

	OnMopologyDilation();
	CopyResultToInput();


	OnMopologyErosion();
	CopyResultToInput();

	OnMopologyErosion();
	CopyResultToInput();

	OnMopologyErosion();
}

//픽셀 복제 방법을 이용한 확대
void CImageProc20180781View::OnGeometryZoominPixelCopy()
{
	CImageProc20180781Doc* pDoc = GetDocument();

	int x, y;
	int xscale = 3;
	int yscale = 2;

	if (pDoc->gResultImg != NULL) {
		for (int i = 0; i < pDoc->gImageHeight; i++) {
			free(pDoc->gResultImg[i]);
		}
		free(pDoc->gResultImg);
	}

	pDoc->gImageWidth = pDoc->ImageWidth * xscale;
	pDoc->gImageHeight = pDoc->ImageHeight * yscale;

	// 메모리할당
	pDoc->gResultImg = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));
	for (int i = 0; i < pDoc->gImageHeight; i++) {		
		pDoc->gResultImg[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);
	}

	//역방향사상
	for(y = 0; y < pDoc->gImageHeight; y++)
		for (x = 0; x < pDoc->gImageWidth; x++) {
			if(pDoc->depth ==1)
			pDoc->gResultImg[y][x] = pDoc->InputImg[y/yscale][x/xscale];
			else {
				pDoc->gResultImg[y][3*x+0] = pDoc->InputImg[y / yscale][3*(x / xscale)+0];
				pDoc->gResultImg[y][3*x+1] = pDoc->InputImg[y / yscale][3*(x / xscale)+1];
				pDoc->gResultImg[y][3*x+2] = pDoc->InputImg[y / yscale][3*(x / xscale)+2];
			}
		}
	
	/*
	//전방향사상
	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++) {			
				pDoc->gResultImg[y*yscale][x*xscale] = pDoc->InputImg[y][x];
		}
	*/
	Invalidate();
}

//양선형 보간법을 이용한 확대
void CImageProc20180781View::OnGeometryZoominBilinearinterpolation()
{
	CImageProc20180781Doc* pDoc = GetDocument();

	int x, y;
	float xscale = 2.3;
	float yscale = 1.5;
	float src_x, src_y;
	float alpha, beta;
	int Ax, Ay, Bx, By, Cx, Cy, Dx, Dy;
	int E, F;

	if (pDoc->gResultImg != NULL) {
		for (int i = 0; i < pDoc->gImageHeight; i++) {
			free(pDoc->gResultImg[i]);
		}
		free(pDoc->gResultImg);
	}

	pDoc->gImageWidth = pDoc->ImageWidth * xscale + 0.5;
	pDoc->gImageHeight = pDoc->ImageHeight * yscale + 0.5;

	// 메모리할당
	pDoc->gResultImg = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));
	for (int i = 0; i < pDoc->gImageHeight; i++) {
		pDoc->gResultImg[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);
	}

	//역방향사상
	for (y = 0; y < pDoc->gImageHeight; y++)
		for (x = 0; x < pDoc->gImageWidth; x++) {
			src_x = x / xscale;
			src_y = y / yscale;
			alpha = src_x - (int)src_x;		//ex) 10.3 - 10 = 0.3 alpha 저장
			beta = src_y - (int)src_y;		//ex) 10.3 - 10 = 0.3 beta 저장

			Ax = (int)src_x;
			Ay = (int)src_y;
			Bx = Ax + 1;
			By = Ay;
			Cx = Ax;
			Cy = Ay + 1;
			Dx = Ax + 1;
			Dy = Ay + 1;

			if (Bx > pDoc->ImageWidth - 1) Bx = pDoc->ImageWidth - 1;
			if (Cy > pDoc->ImageHeight - 1) Cy = pDoc->ImageHeight - 1;
			if (Dx > pDoc->ImageWidth - 1) Dx = pDoc->ImageWidth - 1;
			if (Dy > pDoc->ImageHeight - 1) Dy = pDoc->ImageHeight - 1;

			if (pDoc->depth == 1) {
				E = (1 - alpha) * pDoc->InputImg[Ay][Ax] + alpha * pDoc->InputImg[By][Bx];
				F = (1 - alpha) * pDoc->InputImg[Cy][Cx] + alpha * pDoc->InputImg[Dy][Dx];

				pDoc->gResultImg[y][x] = (1 - beta) * E + beta * F;
			}
			else {
				E = (1 - alpha) * pDoc->InputImg[Ay][3 * Ax + 0] + alpha * pDoc->InputImg[By][3 * Bx + 0];
				F = (1 - alpha) * pDoc->InputImg[Cy][3 * Cx + 0] + alpha * pDoc->InputImg[Dy][3 * Dx + 0];
				pDoc->gResultImg[y][3 * x + 0] = (1 - beta) * E + beta * F;

				E = (1 - alpha) * pDoc->InputImg[Ay][3 * Ax + 1] + alpha * pDoc->InputImg[By][3 * Bx + 1];
				F = (1 - alpha) * pDoc->InputImg[Cy][3 * Cx + 1] + alpha * pDoc->InputImg[Dy][3 * Dx + 1];
				pDoc->gResultImg[y][3 * x + 1] = (1 - beta) * E + beta * F;

				E = (1 - alpha) * pDoc->InputImg[Ay][3 * Ax + 2] + alpha * pDoc->InputImg[By][3 * Bx + 2];
				F = (1 - alpha) * pDoc->InputImg[Cy][3 * Cx + 2] + alpha * pDoc->InputImg[Dy][3 * Dx + 2];
				pDoc->gResultImg[y][3 * x + 2] = (1 - beta) * E + beta * F;
			}
		}
	Invalidate();
}


void CImageProc20180781View::OnGeometryTryzoomoutSubsampling()
{
	CImageProc20180781Doc* pDoc = GetDocument();

	int xscale = 3;
	int yscale = 2;
	int x, y;

	if (pDoc->gResultImg != NULL) {
		for (int i = 0; i < pDoc->gImageHeight; i++) {
			free(pDoc->gResultImg[i]);
		}
		free(pDoc->gResultImg);
	}

	pDoc->gImageWidth = pDoc->ImageWidth / xscale;
	pDoc->gImageHeight = pDoc->ImageHeight / yscale;

	// 메모리할당
	pDoc->gResultImg = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));
	for (int i = 0; i < pDoc->gImageHeight; i++) {
		pDoc->gResultImg[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);
	}

	//역방향 사상
	for (y = 0; y < pDoc->gImageHeight; y++) {
		for (x = 0; x < pDoc->gImageWidth; x++) {
			if (pDoc->depth == 1) {
				pDoc->gResultImg[y][x] = pDoc->InputImg[y * yscale][x * xscale];
			}
			else {
				pDoc->gResultImg[y][3 * x + 0] = pDoc->InputImg[y * yscale][3 * (x * xscale) + 0];
				pDoc->gResultImg[y][3 * x + 1] = pDoc->InputImg[y * yscale][3 * (x * xscale) + 1];
				pDoc->gResultImg[y][3 * x + 2] = pDoc->InputImg[y * yscale][3 * (x * xscale) + 2];
			}
		}


		Invalidate();
	}
}


void CImageProc20180781View::OnGeometryZoomoutMeansub()
{
	OnRegionSmoothing();
	CopyResultToInput();
	OnGeometryTryzoomoutSubsampling();
}


void CImageProc20180781View::OnGeometryAvgFiltering()
{
	CImageProc20180781Doc* pDoc = GetDocument();

	int xscale = 3;
	int yscale = 2;
	int x, y, i, j;
	int sum, rsum, gsum, bsum;
	int src_x, src_y;

	if (pDoc->gResultImg != NULL) {
		for (int i = 0; i < pDoc->gImageHeight; i++) {
			free(pDoc->gResultImg[i]);
		}
		free(pDoc->gResultImg);
	}

	pDoc->gImageWidth = pDoc->ImageWidth / xscale;
	pDoc->gImageHeight = pDoc->ImageHeight / yscale;

	// 메모리할당
	pDoc->gResultImg = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));
	for (int i = 0; i < pDoc->gImageHeight; i++) {
		pDoc->gResultImg[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);
	}

	//전방향사상
	for (y = 0; y < pDoc->ImageHeight; y += yscale) 
		for (x = 0; x < pDoc->ImageWidth; x += xscale) {
			if (pDoc->depth == 1) {
				sum = 0;
				for (j = 0; j < yscale; j++)
					for (i = 0; i < xscale; i++) {
						src_x = x + i;
						src_y = y + j;

						sum += pDoc->InputImg[src_y][src_x];
					}
				pDoc->gResultImg[y / yscale][x / xscale] = sum / (yscale * xscale);
			}
			else {
				rsum = 0;	gsum = 0;	bsum = 0;
				for (j = 0; j < yscale; j++)
					for (i = 0; i < xscale; i++) {
						src_x = x + i;
						src_y = y + j;

						rsum += pDoc->InputImg[src_y][3 * (src_x) + 0];
						gsum += pDoc->InputImg[src_y][3 * (src_x) + 1];
						bsum += pDoc->InputImg[src_y][3 * (src_x) + 2];
					}
				pDoc->gResultImg[y / yscale][3 * (x / xscale) + 0] = rsum / (yscale * xscale);
				pDoc->gResultImg[y / yscale][3 * (x / xscale) + 1] = gsum / (yscale * xscale);
				pDoc->gResultImg[y / yscale][3 * (x / xscale) + 2] = bsum / (yscale * xscale);
			}
		}

	Invalidate();
}


#define PI 3.1416926521
#include "CAngleDialog.h"
void CImageProc20180781View::OnGeometryRotation()
{
	CImageProc20180781Doc* pDoc = GetDocument();
	CAngleDialog dlg;

	int x, y;
	int angle = 30;		//degree
	float radian;
	int Hy;
	int Cx, Cy;
	int xdiff, ydiff;
	int x_source, y_source;

	dlg.m_IAngle = angle;
	if (dlg.DoModal() == IDCANCEL)
		return;
	angle = dlg.m_IAngle;

	radian = PI / 180 * angle;
	//y의 마지막
	Hy = pDoc->ImageHeight - 1;
	//중심점 (영상의 가운데)
	Cx = pDoc->ImageWidth / 2;
	Cy = pDoc->ImageHeight / 2;

	if (pDoc->gResultImg != NULL) {
		for (int i = 0; i < pDoc->gImageHeight; i++) {
			free(pDoc->gResultImg[i]);
		}
		free(pDoc->gResultImg);
	}
										//90 - theta, 음수로 바뀌어 크기가 줄어듦 방지
	pDoc->gImageWidth = (pDoc->ImageHeight * fabs(cos(PI / 2 - radian))) + (pDoc->ImageHeight * fabs(cos(radian)));	 
	pDoc->gImageHeight = pDoc->ImageHeight * fabs(cos(radian)) + pDoc->ImageWidth * fabs(cos(PI / 2 - radian));

	// 메모리할당
	pDoc->gResultImg = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));
	for (int i = 0; i < pDoc->gImageHeight; i++) {
		pDoc->gResultImg[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);
	}

	xdiff = (pDoc->gImageWidth - pDoc->ImageWidth) / 2;
	ydiff = (pDoc->gImageHeight - pDoc->ImageHeight) / 2;
	
	for(y = -ydiff; y < pDoc->gImageHeight - ydiff; y++)
		for (x = -xdiff; x < pDoc->gImageWidth - xdiff; x++) {
			x_source = (Hy - y - Cx) * sin(radian) + (x - Cx) * cos(radian) + Cx;
			y_source = Hy - ((Hy - y - Cy) * cos(radian) - (x - Cx) * sin(radian) + Cy);

			if (pDoc->depth == 1) {
				//범위를 벗어났는지 확인
				if (x_source < 0 || x_source > pDoc->ImageWidth - 1 ||
					y_source < 0 || y_source > pDoc->ImageHeight - 1)
					pDoc->gResultImg[y + ydiff][x + xdiff] = 255;
				else
					pDoc->gResultImg[y + ydiff][x + xdiff] = pDoc->InputImg[y_source][x_source];
			}
			else {
				//범위를 벗어났는지 확인
				if (x_source < 0 || x_source > pDoc->ImageWidth - 1 ||
					y_source < 0 || y_source > pDoc->ImageHeight - 1) {
					pDoc->gResultImg[y + ydiff][3 * (x + xdiff) + 0] = 255;
					pDoc->gResultImg[y + ydiff][3 * (x + xdiff) + 1] = 255;
					pDoc->gResultImg[y + ydiff][3 * (x + xdiff) + 2] = 255;
				}
				else {
					pDoc->gResultImg[y + ydiff][3 * (x + xdiff) + 0] = pDoc->InputImg[y_source][3 * x_source + 0];
					pDoc->gResultImg[y + ydiff][3 * (x + xdiff) + 1] = pDoc->InputImg[y_source][3 * x_source + 1];
					pDoc->gResultImg[y + ydiff][3 * (x + xdiff) + 2] = pDoc->InputImg[y_source][3 * x_source + 2];
				}
			}
			
		}
	Invalidate();
}

//좌우대칭
void CImageProc20180781View::OnGeometryHorizontalFlip()
{
	CImageProc20180781Doc* pDoc = GetDocument();
	int x, y;

	for(y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++) {
			if(pDoc->depth == 1)
				pDoc->ResultImg[y][x] = pDoc->InputImg[y][pDoc->ImageWidth - 1 - x];	//대칭이동의 형태
			else {
				pDoc->ResultImg[y][3 * x + 0] = pDoc->InputImg[y][3 * (pDoc->ImageWidth - 1 - x) + 0];
				pDoc->ResultImg[y][3 * x + 1] = pDoc->InputImg[y][3 * (pDoc->ImageWidth - 1 - x) + 1];
				pDoc->ResultImg[y][3 * x + 2] = pDoc->InputImg[y][3 * (pDoc->ImageWidth - 1 - x) + 2];
			}
		}
	Invalidate();
}


void CImageProc20180781View::OnGeometryVerticalFlip()
{
	CImageProc20180781Doc* pDoc = GetDocument();
	int x, y;

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++) {
			if (pDoc->depth == 1)
				pDoc->ResultImg[y][x] = pDoc->InputImg[pDoc->ImageHeight - 1 - y][x];	//대칭이동의 형태
			else {
				pDoc->ResultImg[y][3 * x + 0] = pDoc->InputImg[pDoc->ImageHeight - 1 - y][3 * x + 0];
				pDoc->ResultImg[y][3 * x + 1] = pDoc->InputImg[pDoc->ImageHeight - 1 - y][3 * x + 1];
				pDoc->ResultImg[y][3 * x + 2] = pDoc->InputImg[pDoc->ImageHeight - 1 - y][3 * x + 2];
			}
		}
	Invalidate();
}

typedef struct
{
	int Px;
	int Py;
	int Qx;
	int Qy;
}control_line;

control_line mctrl_source = { 100,100,150,150 };
control_line mctrl_dest = { 100,100,200,200 };

void CImageProc20180781View::OnGeometryWarping()
{
	CImageProc20180781Doc* pDoc = GetDocument();

	control_line source_lines[5] = { {100,100,150,150},
		{0,0,pDoc->ImageWidth-1,0},{pDoc->ImageWidth - 1,0,pDoc->ImageWidth - 1,pDoc->ImageHeight - 1},
		{pDoc->ImageWidth - 1,pDoc->ImageHeight - 1,0,pDoc->ImageHeight - 1},{0,pDoc->ImageHeight - 1,0,0} };

	control_line dest_lines[5] = { {100,100,200,200},
		{0,0,pDoc->ImageWidth - 1,0},{pDoc->ImageWidth - 1,0,pDoc->ImageWidth - 1,pDoc->ImageHeight - 1},
		{pDoc->ImageWidth - 1,pDoc->ImageHeight - 1,0,pDoc->ImageHeight - 1},{0,pDoc->ImageHeight - 1,0,0} };

	source_lines[0] = mctrl_source;
	dest_lines[0] = mctrl_dest;

	int x, y;
	double u;		//수직 교차점의 위치를 지정하기위한 변수(선의 안쪽인지 바깥쪽인지 계산)
	double h;		//제어선으로부터 픽셀의 수직변위
	double d;		//제어선과 픽셀 사이의 거리
	double tx, ty;	//결과영상 픽셀에 대응되는 입력 영상 픽셀 사이의 변위의 합
	double xp, yp;	//각 제어선에 대해 계산된 입력 영상의 대응되는 픽셀 위치
	double weight;	//각 제어선의 가중치
	double totalWeight;		//가중치의 합
	double a = 0.001;
	double b = 2.0;
	double p = 0.75;

	int x1, y1, x2, y2;		//1번은 시작점, 2번은 도착점
	int src_x1, src_y1, src_x2, src_y2;		//이동하기 전의 좌표값, 이동후의 좌표값
	double src_line_length, dest_line_length;	//이동전의 제어선 길이, 이동후의 제어선 길이

	int num_lines = 5;		//제어선의 갯수
	int line;
	int	source_x, source_y;	//최종적으로 좌표값 저장할 변수
	int last_row, last_col;			//y좌표의 위치

	last_col = pDoc->ImageWidth - 1;
	last_row = pDoc->ImageHeight - 1;

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++) {
			tx = 0.0;
			ty = 0.0;
			totalWeight = 0.0;

			for (line = 0; line < num_lines; line++) {
				//이동 후의 좌표값
				x1 = dest_lines[line].Px;
				y1 = dest_lines[line].Py;
				x2 = dest_lines[line].Qx;
				y2 = dest_lines[line].Qy;

				dest_line_length = sqrt((double)((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));

				u = (double)((x - x1) * (x2 - x1) + (y - y1) * (y2 - y1)) /
					(double)((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));

				//+가 아니라 -
				h = (double)((y - y1) * (x2 - x1) - (x - x1) * (y2 - y1)) / dest_line_length;

				//점과 선사이의 거리, 수직교차점의 거리
				if (u < 0)		d = sqrt((double)((x - x1) * (x - x1) + (y - y1) * (y - y1)));
				else if (u > 1)	d = sqrt((double)((x - x2) * (x - x2) + (y - y2) * (y - y2)));
				else 			d = fabs(h);
				

				//이동전의 좌표값
				src_x1 = source_lines[line].Px;
				src_y1 = source_lines[line].Py;
				src_x2 = source_lines[line].Qx;
				src_y2 = source_lines[line].Qy;

				src_line_length = sqrt((double)((src_x2 - src_x1) * (src_x2 - src_x1) + (src_y2 - src_y1) * (src_y2 - src_y1)));

				//소스의 변화위치
				xp = src_x1 + u * (src_x2 - src_x1) - h * (src_y2 - src_y1) / src_line_length;
				yp = src_y1 + u * (src_y2 - src_y1) + h * (src_x2 - src_x1) / src_line_length;

				//가중치값 계산
				weight = pow((pow((double)(dest_line_length), p) / (a + d)), b);

				//가중치를 종합해서 변위값 계산
				tx += (xp - x) * weight;
				ty += (yp - y) * weight;
				totalWeight += weight;
			}
			//원래있던 x좌표에서 변위만큼 이동한것
			source_x = x + (tx / totalWeight);
			source_y = y + (ty / totalWeight);

			if (source_x < 0)			source_x = 0;
			if (source_x > last_col)	source_x = last_col;
			if (source_y < 0)			source_y = 0;
			if (source_y > last_row)	source_y = last_row;

			if(pDoc->depth == 1)			
			pDoc->ResultImg[y][x] = pDoc->InputImg[source_y][source_x];		//역방향사상 계산
			else {
				pDoc->ResultImg[y][3*x+0] = pDoc->InputImg[source_y][3*source_x+0];
				pDoc->ResultImg[y][3*x+1] = pDoc->InputImg[source_y][3*source_x+1];
				pDoc->ResultImg[y][3*x+2] = pDoc->InputImg[source_y][3*source_x+2];
			}
		}
	Invalidate();
}


CPoint mpos_st, mpos_end;

void CImageProc20180781View::OnLButtonDown(UINT nFlags, CPoint point)
{
	mpos_st = point;

	CScrollView::OnLButtonDown(nFlags, point);
}


void CImageProc20180781View::OnLButtonUp(UINT nFlags, CPoint point)
{
	mpos_end = point;

	CDC* pDC = GetDC();
	CPen rpen;
	rpen.CreatePen(PS_SOLID, 0, RGB(255, 0, 0));
	pDC->SelectObject(&rpen);
	
	pDC->MoveTo(mpos_st);
	pDC->LineTo(mpos_end);
	ReleaseDC(pDC);

	int Ax, Ay, Bx, By;
	Ax = mpos_st.x;
	Ay = mpos_st.y;
	Bx = mpos_end.x;
	By = mpos_end.y;

	if (Ax < Bx)	mctrl_source.Px = Ax - (Bx - Ax) / 2;
	else			mctrl_source.Px = Ax + (Bx - Ax) / 2;

	if (Ay < By)	mctrl_source.Py = Ay - (By - Ay) / 2;
	else			mctrl_source.Py = Ay + (By - Ay) / 2;

	mctrl_dest.Px = mctrl_source.Px;
	mctrl_dest.Py = mctrl_source.Py;

	mctrl_source.Qx = mpos_st.x;
	mctrl_source.Qy = mpos_st.y;
	mctrl_dest.Qx = mpos_end.x;
	mctrl_dest.Qy = mpos_end.y;


	CScrollView::OnLButtonUp(nFlags, point);
}


void CImageProc20180781View::OnAviView()
{	
	CFileDialog dlg(TRUE,"","",OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
		"AVI파일(*.avi)|*.avi|모든파일|*.*|");
		
	if (dlg.DoModal() == IDOK) {
		AviFileName = dlg.GetPathName();
		bAVIMode = true;
		Invalidate();
	}
}


void CImageProc20180781View::LoadAviFile(CDC* pDC)
{
	PAVIFILE pavi;				//파일을 처리하기위한 포인터
	AVIFILEINFO  fi;			//파일에 대한 정보
	int stm;					//몇번째 스트림을 재생할지 처리하기위한 변수
	PAVISTREAM pstm = NULL;	//스트림에 대한 정보를 쓸수있는 포인터
	AVISTREAMINFO si;			//스트림에 대한 정보
	PGETFRAME pfrm = NULL;		//프레임을 가져오기위한 포인터
	int frame;					//스트림을 처리하기위한 변수
	LPBITMAPINFOHEADER pbmpih;
	unsigned char *image;
	int x, y;

	AVIFileInit();
	AVIFileOpen(&pavi, AviFileName, OF_READ | OF_SHARE_DENY_NONE, NULL);	//선택한 파일의 이름으로 파일을 연다
	AVIFileInfo(pavi, &fi, sizeof(AVIFILEINFO));

	for (stm = 0; stm < fi.dwStreams; stm++) {
		AVIFileGetStream(pavi, &pstm, 0, stm);		//스트림 하나 가져오는것
		AVIStreamInfo(pstm, &si, sizeof(si));		//포인터의 정보를 읽어서 si에
		if (si.fccType == streamtypeVIDEO) {

			pfrm = AVIStreamGetFrameOpen(pstm, NULL);		//한 프레임을 잘라서 가져오는 함수
			for (frame = 0; frame < si.dwLength; frame++) {
				pbmpih = (LPBITMAPINFOHEADER)AVIStreamGetFrame(pfrm, frame);
				if (!pbmpih) continue;

				//첫 시작위치+biSize 실제데이터 시작위치 = 이미지 데이터 시작위치
				image = (unsigned char*)((LPSTR)pbmpih + (WORD)pbmpih->biSize);

				/*
				for(y = 0; y < fi.dwHeight; y++)
					for (x = 0; x < fi.dwWidth; x++) {
						pDC->SetPixel(x, fi.dwHeight-1-y,
							RGB(image[(y * fi.dwWidth + x) * 3 + 2],
								image[(y * fi.dwWidth + x) * 3 + 1],
								image[(y * fi.dwWidth + x) * 3 + 0]));
						
					}
				*/
				::SetDIBitsToDevice(pDC->GetSafeHdc(), 0, 0, fi.dwWidth, fi.dwHeight,
					0, 0, 0, fi.dwWidth, image, (BITMAPINFO*)pbmpih, DIB_RGB_COLORS);
				Sleep(33);
			}
		}
	}
	AVIStreamGetFrameClose(pfrm);
	AVIStreamRelease(pstm);
	AVIFileRelease(pavi);
	AVIFileExit();
}
