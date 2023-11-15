﻿
// ImageProc_20180781Doc.cpp: CImageProc20180781Doc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ImageProc_20180781.h"
#endif

#include "ImageProc_20180781Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CImageProc20180781Doc

IMPLEMENT_DYNCREATE(CImageProc20180781Doc, CDocument)

BEGIN_MESSAGE_MAP(CImageProc20180781Doc, CDocument)
END_MESSAGE_MAP()


// CImageProc20180781Doc 생성/소멸

CImageProc20180781Doc::CImageProc20180781Doc() noexcept
{
	InputImg = NULL;
	InputImg2 = NULL;
	ResultImg = NULL;
	gResultImg = NULL;
}

CImageProc20180781Doc::~CImageProc20180781Doc()
{
	if (InputImg != NULL) {
		for (int i = 0; i < ImageHeight; i++) {
			free(InputImg[i]);
		}
		free(InputImg);
	}

	if (InputImg2 != NULL) {
		for (int i = 0; i < ImageHeight; i++) {
			free(InputImg2[i]);
		}
		free(InputImg2);
	}

	if (ResultImg != NULL) {
		for (int i = 0; i < ImageHeight; i++) {
			free(ResultImg[i]);
		}
		free(ResultImg);
	}

	if (gResultImg != NULL) {
		for (int i = 0; i < gImageHeight; i++) {
			free(gResultImg[i]);
		}
		free(gResultImg);
	}
}

BOOL CImageProc20180781Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CImageProc20180781Doc serialization

void CImageProc20180781Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		LoadImageFile(ar);
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CImageProc20180781Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CImageProc20180781Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CImageProc20180781Doc::SetSearchContent(const CString& value)
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

// CImageProc20180781Doc 진단

#ifdef _DEBUG
void CImageProc20180781Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CImageProc20180781Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CImageProc20180781Doc 명령


void CImageProc20180781Doc::LoadImageFile(CArchive& ar)
{
	int maxValue;
	char type[16], buf[256];
	CFile* fp = ar.GetFile();
	CString fname = fp->GetFilePath();		//경로명, 확장자까지 다 들어있음
	bool isbmp = false;
	
	if (strcmp(strchr(fname, '.'), ".ppm") == 0 || strcmp(strchr(fname, '.'), ".PPM") == 0 || 
		strcmp(strchr(fname, '.'), ".pgm") == 0 || strcmp(strchr(fname, '.'), ".PGM") == 0) 
	{
		ar.ReadString(type, 15);			//헤더부분은 아스키코드라 readString

		do {
			ar.ReadString(buf, 256);
		} while (buf[0] == '#');
		sscanf_s(buf, "%d %d", &ImageWidth, &ImageHeight);

		do {
			ar.ReadString(buf, 256);
		} while (buf[0] == '#');
		sscanf_s(buf, "%d", &maxValue);

		if (strcmp(type, "P5") == 0) {
			depth = 1;
		}
		else {
			depth = 3;
		}

	}
	else if (strcmp(strchr(fname, '.'), ".bmp") == 0 || strcmp(strchr(fname, '.'), ".BMP") == 0) {
		//bitmap file header 읽기
		BITMAPFILEHEADER bmfh;
		ar.Read((LPSTR)&bmfh, sizeof(bmfh));
		if(bmfh.bfType != (WORD)('B'| ('M' << 8)))	return;		//WORD단위로 16비트

		//bitmap info header 이미지에 대한 크기 읽기
		BITMAPINFOHEADER bih;
		ar.Read((LPSTR)&bih, sizeof(bih));
		ImageWidth = bih.biWidth;
		ImageHeight = bih.biHeight;
		depth = bih.biBitCount / 8;

		if (depth == 1) {
			//palette 존재
			BYTE palette[256 * 4];
			ar.Read(palette, 256 * 4);
		}

		isbmp = true;
	}
	else if(strcmp(strchr(fname, '.'), ".raw") == 0 || strcmp(strchr(fname, '.'), ".RAW") == 0)
	{
		if (fp->GetLength() != 256 * 256) {
			AfxMessageBox("256 * 256 크기의 raw 파일만 사용가능합니다.");
			return;
		}

		ImageWidth = 256;
		ImageHeight = 256;
		depth = 1;
	}

	//메모리할당
	InputImg = (unsigned char**)malloc(ImageHeight * sizeof(unsigned char*));		
	ResultImg = (unsigned char**)malloc(ImageHeight * sizeof(unsigned char*));
	for (int i = 0; i < ImageHeight; i++) {
		InputImg[i] = (unsigned char*)malloc(ImageWidth * depth);		
		ResultImg[i] = (unsigned char*)malloc(ImageWidth * depth);
	}

	//영상데이터 읽기
	if (!isbmp) {
		for (int i = 0; i < ImageHeight; i++) {
			ar.Read(InputImg[i], ImageWidth * depth);		//그냥 Read는 Binary 코드
		}
	}
	else {
		//파일에서 읽어서 저장
		BYTE nu[4 * 3];					//char의 unsigned 형식	, nu[4]
		int widthfile;
		widthfile = (ImageWidth * 8 + 32) / 32 * 4;		//32보다 작은값이 32로 나눠짐 4의배수가 아닌것을 4의배수로 만듦

		for (int j = 0; j < ImageHeight; j++) {
			if (depth == 1) {
				ar.Read(InputImg[ImageHeight - 1 - j], ImageWidth * depth);		//거꾸로 출력되므로 제일 마지막부터 input
			}
			else {
				for (int i = 0; i < ImageWidth; i++) {
					BYTE r, g, b;
					ar.Read(&b, 1); ar.Read(&g, 1); ar.Read(&r, 1);

					InputImg[ImageHeight - 1 - j][3 * i + 0] = r;
					InputImg[ImageHeight - 1 - j][3 * i + 1] = g;
					InputImg[ImageHeight - 1 - j][3 * i + 2] = b;
				}
			}
			if ((widthfile - ImageWidth) != 0) {
				ar.Read(nu, (widthfile - ImageWidth) * depth);
			}
		}
	}
}


void CImageProc20180781Doc::LoadSecondImageFile(CArchive& ar)
{
	int maxValue;
	char type[16], buf[256];
	CFile* fp = ar.GetFile();
	CString fname = fp->GetFilePath();		//경로명, 확장자까지 다 들어있음
	bool isbmp = false;

	int imgw, imgh, imgd;

	if (strcmp(strchr(fname, '.'), ".ppm") == 0 || strcmp(strchr(fname, '.'), ".PPM") == 0 ||
		strcmp(strchr(fname, '.'), ".pgm") == 0 || strcmp(strchr(fname, '.'), ".PGM") == 0)
	{
		ar.ReadString(type, 15);			//헤더부분은 아스키코드라 readString

		do {
			ar.ReadString(buf, 256);
		} while (buf[0] == '#');
		sscanf_s(buf, "%d %d", &imgw, &imgh);	//기존의 메모리가 변할수도 있어서 임시변수에

		do {
			ar.ReadString(buf, 256);
		} while (buf[0] == '#');
		sscanf_s(buf, "%d", &maxValue);

		if (strcmp(type, "P5") == 0) {
			imgd = 1;
		}
		else {
			imgd = 3;
		}

	}
	else if (strcmp(strchr(fname, '.'), ".bmp") == 0 || strcmp(strchr(fname, '.'), ".BMP") == 0) {
		//bitmap file header 읽기
		BITMAPFILEHEADER bmfh;
		ar.Read((LPSTR)&bmfh, sizeof(bmfh));
		if (bmfh.bfType != (WORD)('B' | ('M' << 8)))	return;		//WORD단위로 16비트

		//bitmap info header 이미지에 대한 크기 읽기
		BITMAPINFOHEADER bih;
		ar.Read((LPSTR)&bih, sizeof(bih));
		imgw = bih.biWidth;
		imgh = bih.biHeight;
		imgd = bih.biBitCount / 8;

		if (imgd == 1) {
			//palette 존재
			BYTE palette[256 * 4];
			ar.Read(palette, 256 * 4);
		}

		isbmp = true;
	}
	else if (strcmp(strchr(fname, '.'), ".raw") == 0 || strcmp(strchr(fname, '.'), ".RAW") == 0)
	{
		if (fp->GetLength() != 256 * 256) {
			AfxMessageBox("256 * 256 크기의 raw 파일만 사용가능합니다.");
			return;
		}

		imgw = 256;
		imgh = 256;
		imgd = 1;
	}

	if (imgw != ImageWidth || imgh != ImageHeight || imgd != depth) {
		AfxMessageBox("동일한 크기의 파일만 읽어들일 수 있습니다.");
		return;
	}

	//메모리할당	
	InputImg2 = (unsigned char**)malloc(ImageHeight * sizeof(unsigned char*));			
	for (int i = 0; i < ImageHeight; i++) {		
		InputImg2[i] = (unsigned char*)malloc(ImageWidth * depth);
	}

	//영상데이터 읽기
	if (!isbmp) {
		for (int i = 0; i < ImageHeight; i++) {
			ar.Read(InputImg2[i], ImageWidth * depth);		//그냥 Read는 Binary 코드
		}
	}
	else {
		//파일에서 읽어서 저장
		BYTE nu[4 * 3];					//char의 unsigned 형식	, nu[4]
		int widthfile;
		widthfile = (ImageWidth * 8 + 32) / 32 * 4;		//32보다 작은값이 32로 나눠짐 4의배수가 아닌것을 4의배수로 만듦

		for (int j = 0; j < ImageHeight; j++) {
			if (depth == 1) {
				ar.Read(InputImg2[ImageHeight - 1 - j], ImageWidth * depth);		//거꾸로 출력되므로 제일 마지막부터 input
			}
			else {
				for (int i = 0; i < ImageWidth; i++) {
					BYTE r, g, b;
					ar.Read(&b, 1); ar.Read(&g, 1); ar.Read(&r, 1);

					InputImg2[ImageHeight - 1 - j][3 * i + 0] = r;
					InputImg2[ImageHeight - 1 - j][3 * i + 1] = g;
					InputImg2[ImageHeight - 1 - j][3 * i + 2] = b;
				}
			}
			if ((widthfile - ImageWidth) != 0) {
				ar.Read(nu, (widthfile - ImageWidth) * depth);
			}
		}
	}
}
