
// ImageProc_20211431View.h: CImageProc20211431View 클래스의 인터페이스
//

#pragma once


class CImageProc20211431View : public CScrollView
{
protected: // serialization에서만 만들어집니다.
	CImageProc20211431View() noexcept;
	DECLARE_DYNCREATE(CImageProc20211431View)

// 특성입니다.
public:
	CImageProc20211431Doc* GetDocument() const;

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
	virtual ~CImageProc20211431View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void On32771();
//	afx_msg void On32773();
	afx_msg void OnPixelHistEq();
	afx_msg void OnPixelContrastStrachting();
	afx_msg void OnPixelBinarization();
	afx_msg void OnPixelAdd();
	afx_msg void OnPixelSub();
	afx_msg void OnPixelMul();
	afx_msg void OnPixelDiv();
	afx_msg void OnPixelTwoImageAdd();
	void LoadTwoImage();
	afx_msg void OnPixelTwoImageSub();
	afx_msg void OnRegionSmooting();
	void Convolve(unsigned char** Inimg, unsigned char** Outimg, int cols, int rows, float mask[][3], int bias, int depth);
	void OnRegionSharpening();
	afx_msg void OnRegionSharping();
	afx_msg void OnRegionEmbossing();
	afx_msg void OnRegionPrewitt();
	afx_msg void OnRegionRoberts();
	afx_msg void OnRegionSobel();
	afx_msg void OnRegionAverageFiltering();
	afx_msg void OnRegionMadianFiltering();
	afx_msg void OnMopologyColorGray();
	afx_msg void OnMopologyBinarization();
	afx_msg void OnMopologyErosion();
	afx_msg void OnMopologyOpening();
	afx_msg void OnMopolopyDilation();
	void CopyResultToInput();
	afx_msg void OnMopologyClosing();
	afx_msg void OnGeometryZoominPixelCopy();
	afx_msg void OnGeometryZoominBilnearInterpolation();
	afx_msg void OnGeometryZoonoutSubsampling();
	afx_msg void OnGeometryZoomoutMeanSub();
	afx_msg void OnGeometryAvgFiltering();
	afx_msg void OnGeometryRotation();
	afx_msg void OnGeometryHolizationalFilp();
	afx_msg void OnGeometryVeticalFilp();
	afx_msg void OnGeometrywarping();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);


	void LoadAviFile(CDC* pDC);
	afx_msg void OnOpencv();
	CString AviFIleName;
	bool bAviMdode;
};

#ifndef _DEBUG  // ImageProc_20211431View.cpp의 디버그 버전
inline CImageProc20211431Doc* CImageProc20211431View::GetDocument() const
   { return reinterpret_cast<CImageProc20211431Doc*>(m_pDocument); }
#endif

	