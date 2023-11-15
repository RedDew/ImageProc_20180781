﻿
// ImageProc_20180781View.h: CImageProc20180781View 클래스의 인터페이스
//

#pragma once


class CImageProc20180781View : public CScrollView
{
protected: // serialization에서만 만들어집니다.
	CImageProc20180781View() noexcept;
	DECLARE_DYNCREATE(CImageProc20180781View)

// 특성입니다.
public:
	CImageProc20180781Doc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.

// 구현입니다.
public:
	virtual ~CImageProc20180781View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPixelAdd();
	afx_msg void OnPixelSub();
	afx_msg void OnPixelMul();
	afx_msg void OnPixelDiv();
	afx_msg void OnPixelHistoEq();
	afx_msg void OnPixelContrastStretching();
	afx_msg void OnPixelBinarization();
	afx_msg void OnPixelTwoImageAdd();
	void LoadTwoImage();
	afx_msg void OnPixelTwoImageSub();
	afx_msg void OnRegionSmoothing();
	void Convolve(unsigned char** InImg, unsigned char** OutImg, int cols, int rows, float mask[][3], int bias, int depth);
	afx_msg void OnRegionSharpening();
	afx_msg void OnRegionEmbossing();
	afx_msg void OnRegionPrewitt();
	afx_msg void OnRegionSobel();
	afx_msg void OnRegionRoberts();
	afx_msg void OnRegionAveragefiltering();
	afx_msg void OnRegionMedianfiltering();
	afx_msg void OnMopologyColorGray();
	afx_msg void OnMopologyBinaryzation();
	afx_msg void OnMopologyErosion();
	afx_msg void OnMopologyDilation();
	afx_msg void OnMopologyOpening();
	void CopyResultToInput();
	afx_msg void OnMopologyClosing();
	afx_msg void OnGeometryZoominPixelCopy();
	afx_msg void OnGeometryZoominBilinearinterpolation();
	afx_msg void OnGeometryTryzoomoutSubsampling();
	afx_msg void OnGeometryZoomoutMeansub();
	afx_msg void OnGeometryAvgFiltering();
	afx_msg void OnGeometryRotation();
};

#ifndef _DEBUG  // ImageProc_20180781View.cpp의 디버그 버전
inline CImageProc20180781Doc* CImageProc20180781View::GetDocument() const
   { return reinterpret_cast<CImageProc20180781Doc*>(m_pDocument); }
#endif

