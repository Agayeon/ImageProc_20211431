// ImageProc_20211431View.cpp: CImageProc20211431View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ImageProc_20211431.h"
#endif

#include "ImageProc_20211431Doc.h"
#include "ImageProc_20211431View.h"

#include <math.h>
#include <vfw.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImageProc20211431View

IMPLEMENT_DYNCREATE(CImageProc20211431View, CScrollView)

BEGIN_MESSAGE_MAP(CImageProc20211431View, CScrollView)
	ON_COMMAND(ID_PIXEL_ADD, &CImageProc20211431View::OnPixelAdd)
	ON_COMMAND(ID_PIXEL_SUB, &CImageProc20211431View::OnPixelSub)
	ON_COMMAND(ID_PIXEL_MUL, &CImageProc20211431View::OnPixelMul)
	ON_COMMAND(ID_PIXEL_DIV, &CImageProc20211431View::OnPixelDiv)
	ON_COMMAND(ID_PIXEL_HIST_EQ, &CImageProc20211431View::OnPixelHistEq)
	ON_COMMAND(ID_PIXEL_CONTRAST_STRACHTING, &CImageProc20211431View::OnPixelContrastStrachting)
	ON_COMMAND(ID_PIXEL_BINARIZATION, &CImageProc20211431View::OnPixelBinarization)
	ON_COMMAND(ID_PIXEL_TWO_IMAGE_ADD, &CImageProc20211431View::OnPixelTwoImageAdd)
	ON_COMMAND(ID_PIXEL_TWO_IMAGE_SUB, &CImageProc20211431View::OnPixelTwoImageSub)
	ON_COMMAND(ID_REGION_SMOOTING, &CImageProc20211431View::OnRegionSmooting)
	ON_COMMAND(ID_REGION_SHARPING, &CImageProc20211431View::OnRegionSharping)
	ON_COMMAND(ID_REGION_EMBOSSING, &CImageProc20211431View::OnRegionEmbossing)
	ON_COMMAND(ID_REGION_PREWITT, &CImageProc20211431View::OnRegionPrewitt)
	ON_COMMAND(ID_REGION_ROBERTS, &CImageProc20211431View::OnRegionRoberts)
	ON_COMMAND(ID_REGION_SOBEL, &CImageProc20211431View::OnRegionSobel)
	ON_COMMAND(ID_REGION_AVERAGE_FILTERING, &CImageProc20211431View::OnRegionAverageFiltering)
	ON_COMMAND(ID_REGION_MADIAN_FILTERING, &CImageProc20211431View::OnRegionMadianFiltering)
	ON_COMMAND(ID_MOPOLOGY_COLOR_GRAY, &CImageProc20211431View::OnMopologyColorGray)
	ON_COMMAND(ID_MOPOLOGY_BINARIZATION, &CImageProc20211431View::OnMopologyBinarization)
	ON_COMMAND(ID_MOPOLOGY_EROSION, &CImageProc20211431View::OnMopologyErosion)
	ON_COMMAND(ID_MOPOLOGY_OPENING, &CImageProc20211431View::OnMopologyOpening)
	ON_COMMAND(ID_MOPOLOPY_DILATION, &CImageProc20211431View::OnMopolopyDilation)
	ON_COMMAND(ID_MOPOLOGY_CLOSING, &CImageProc20211431View::OnMopologyClosing)
	ON_COMMAND(ID_GEOMETRY_ZOOMIN_PIXEL_COPY, &CImageProc20211431View::OnGeometryZoominPixelCopy)
	ON_COMMAND(ID_GEOMETRY_ZOOMIN_BILNEAR_INTERPOLATION, &CImageProc20211431View::OnGeometryZoominBilnearInterpolation)
	ON_COMMAND(ID_GEOMETRY_ZOONOUT_SUBSAMPLING, &CImageProc20211431View::OnGeometryZoonoutSubsampling)
	ON_COMMAND(ID_GEOMETRY_ZOOMOUT_MEAN_SUB, &CImageProc20211431View::OnGeometryZoomoutMeanSub)
	ON_COMMAND(ID_GEOMETRY_AVG_FILTERING, &CImageProc20211431View::OnGeometryAvgFiltering)
	ON_COMMAND(ID_GEOMETRY_ROTATION, &CImageProc20211431View::OnGeometryRotation)
	ON_COMMAND(ID_GEOMETRY_HOLIZATIONAL_FILP, &CImageProc20211431View::OnGeometryHolizationalFilp)
	ON_COMMAND(ID_GEOMETRY_VETICAL_FILP, &CImageProc20211431View::OnGeometryVeticalFilp)
	ON_COMMAND(ID_GEOMETRYWARPING, &CImageProc20211431View::OnGeometrywarping)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()

	ON_COMMAND(ID_OPENCV, &CImageProc20211431View::OnOpencv)
END_MESSAGE_MAP()

// CImageProc20211431View 생성/소멸
CImageProc20211431View::CImageProc20211431View() noexcept
{
	bAviMdode = false;
}


CImageProc20211431View::~CImageProc20211431View()
{
}

BOOL CImageProc20211431View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CScrollView::PreCreateWindow(cs);
}

// CImageProc20211431View 그리기

void CImageProc20211431View::OnDraw(CDC* pDC)
{
	CImageProc20211431Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (bAviMdode)
	{
		//재생
		LoadAviFile(pDC);
		bAviMdode = false;
		return;
	}
	int x, y;

	if (pDoc->InputImage != NULL)
	{
		if (pDoc->depth == 1)
		{
			for (y = 0; y < pDoc->ImageHeight; y++)
				for (x = 0; x < pDoc->ImageWidth; x++)
					pDC->SetPixel(x, y, RGB(pDoc->InputImage[y][x], pDoc->InputImage[y][x], pDoc->InputImage[y][x]));
		}
		else
		{
			for (y = 0; y < pDoc->ImageHeight; y++)
				for (x = 0; x < pDoc->ImageWidth; x++)
					pDC->SetPixel(x, y, RGB(pDoc->InputImage[y][3 * x + 0], pDoc->InputImage[y][3 * x + 1], pDoc->InputImage[y][3 * x + 2]));
		}
	}

	if (pDoc->resultImage != NULL)
	{
		if (pDoc->depth == 1)
		{
			for (y = 0; y < pDoc->ImageHeight; y++)
				for (x = 0; x < pDoc->ImageWidth; x++)
					pDC->SetPixel(pDoc->ImageWidth + 20 + x, y, RGB(pDoc->resultImage[y][x], pDoc->resultImage[y][x], pDoc->resultImage[y][x]));
		}
		else
		{
			for (y = 0; y < pDoc->ImageHeight; y++)
				for (x = 0; x < pDoc->ImageWidth; x++)
					pDC->SetPixel(pDoc->ImageWidth + 20 + x, y, RGB(pDoc->resultImage[y][3 * x + 0], pDoc->resultImage[y][3 * x + 1], pDoc->resultImage[y][3 * x + 2]));
		}
	}

	if (pDoc->InputImage2 != NULL)
	{
		if (pDoc->depth == 1)
		{
			for (y = 0; y < pDoc->ImageHeight; y++)
				for (x = 0; x < pDoc->ImageWidth; x++)
					pDC->SetPixel((pDoc->ImageWidth + 20)*2 + x, y, RGB(pDoc->InputImage2[y][3 * x + 0], pDoc->InputImage2[y][3 * x + 1], pDoc->InputImage2[y][3 * x + 2]));
		}
		else
		{
			for (y = 0; y < pDoc->ImageHeight; y++)
				for (x = 0; x < pDoc->ImageWidth; x++)
					pDC->SetPixel((pDoc->ImageWidth + 20)*2 + x, y, RGB(pDoc->InputImage2[y][3 * x + 0], pDoc->InputImage2[y][3 * x + 1], pDoc->InputImage2[y][3 * x + 2]));
		}

	}
	if (pDoc->gresultImage != NULL)
	{
		if (pDoc->depth == 1) //흑백일때
		{
			for (y = 0; y < pDoc->gImageHeight; y++)
				for (x = 0; x < pDoc->gImageWidth; x++)
					pDC->SetPixel( x, pDoc->ImageHeight+20+y, RGB(pDoc->gresultImage[y][x], pDoc->gresultImage[y][x], pDoc->gresultImage[y][x]));
		}
		else //칼라일때
		{
			for (y = 0; y < pDoc->gImageHeight; y++)
				for (x = 0; x < pDoc->gImageWidth; x++)
					pDC->SetPixel(x, pDoc->ImageHeight+ 20 + y, RGB(pDoc->gresultImage[y][3 * x + 0], pDoc->gresultImage[y][3 * x + 1], pDoc->gresultImage[y][3 * x + 2]));

		}
	}
}

void CImageProc20211431View::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 이 뷰의 전체 크기를 계산합니다.
	sizeTotal.cx = sizeTotal.cy = 2048;
	
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CImageProc20211431View 진단

#ifdef _DEBUG
void CImageProc20211431View::AssertValid() const
{
	CScrollView::AssertValid();
}

void CImageProc20211431View::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CImageProc20211431Doc* CImageProc20211431View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageProc20211431Doc)));
	return (CImageProc20211431Doc*)m_pDocument;
}
#endif //_DEBUG


// CImageProc20211431View 메시지 처리기


void CImageProc20211431View::OnPixelAdd()
{
	CImageProc20211431Doc* pDoc = GetDocument();

	if (pDoc->InputImage == NULL)	return;

	int x, y;
	int value;

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			if (pDoc->depth == 1)
			{
				value = pDoc->InputImage[y][x] + 100;
				if (value > 255)	value = 255;
				else if (value < 0)	value = 0;
				pDoc->resultImage[y][x] = value;
			}
			else
			{
				value = pDoc->InputImage[y][3 * x + 0] + 100;
				if (value > 255)	value = 255;
				else if (value < 0)	value = 0;
				pDoc->resultImage[y][3 * x + 0] = value;

				value = pDoc->InputImage[y][3 * x + 1] + 100;
				if (value > 255)	value = 255;
				else if (value < 0)	value = 0;
				pDoc->resultImage[y][3 * x + 1] = value;

				value = pDoc->InputImage[y][3 * x + 2] + 100;
				if (value > 255)	value = 255;
				else if (value < 0)	value = 0;
				pDoc->resultImage[y][3 * x + 2] = value;
			}

		}

	Invalidate();
}


void CImageProc20211431View::OnPixelSub()
{
	CImageProc20211431Doc* pDoc = GetDocument();

	if (pDoc->InputImage == NULL)	return;

	int x, y;
	int value;

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			if (pDoc->depth == 1)
			{
				value = pDoc->InputImage[y][x] - 100;
				if (value > 255)	value = 255;
				else if (value < 0)	value = 0;
				pDoc->resultImage[y][x] = value;
			}
			else
			{
				value = pDoc->InputImage[y][3 * x + 0] - 100;
				if (value > 255)	value = 255;
				else if (value < 0)	value = 0;
				pDoc->resultImage[y][3 * x + 0] = value;

				value = pDoc->InputImage[y][3 * x + 1] - 100;
				if (value > 255)	value = 255;
				else if (value < 0)	value = 0;
				pDoc->resultImage[y][3 * x + 1] = value;

				value = pDoc->InputImage[y][3 * x + 2] - 100;
				if (value > 255)	value = 255;
				else if (value < 0)	value = 0;
				pDoc->resultImage[y][3 * x + 2] = value;
			}
		}

	Invalidate();
}

void CImageProc20211431View::OnPixelMul()
{
	CImageProc20211431Doc* pDoc = GetDocument();

	if (pDoc->InputImage == NULL) return;

	int x, y;
	int value;

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth * pDoc->depth; x++)
		{
			value = static_cast<int>(pDoc->InputImage[y][x] * 1.5);
			if (value > 255)    value = 255;
			else if (value < 0)    value = 0;
			pDoc->resultImage[y][x] = static_cast<unsigned char>(value);
		}

	Invalidate();
}


void CImageProc20211431View::OnPixelDiv()
{
	CImageProc20211431Doc* pDoc = GetDocument();

	if (pDoc->InputImage == NULL) return;

	int x, y;
	int value;

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth * pDoc->depth; x++)
		{
			value = static_cast<int>(pDoc->InputImage[y][x] / 1.5);
			if (value > 255)   value = 255;
			else if (value < 0)   value = 0;
			pDoc->resultImage[y][x] = static_cast<unsigned char>(value);
		}

	Invalidate();
}



void CImageProc20211431View::OnPixelHistEq()
{
	CImageProc20211431Doc* pDoc = GetDocument();

	int x, y, i, k;
	int acc_hist;
	float N = 256 * 256;
	int hist[256], sum[256];

	for (i = 0; i < 256; i++)	hist[i] = 0;
	//히스토그램 구하기
	for (y = 0; y < 256; y++)
		for (x = 0; x < 256; x++)
		{
			k = pDoc->InputImage[y][x];
			hist[k]++;
		}

	//누적분포 구하기
	acc_hist = 0;
	for (i = 0; i < 256; i++)
	{
		acc_hist += hist[i];
		sum[i] = acc_hist;
	}

	//평활화 화소값저장
	for (y = 0; y < 256; y++)
		for (x = 0; x < 256; x++)
		{
			k = pDoc->InputImage[y][x];
			pDoc->resultImage[y][x] = (float)sum[k] / N * 255;
		}

	Invalidate();
}


void CImageProc20211431View::OnPixelContrastStrachting()
{
	CImageProc20211431Doc* pDoc = GetDocument();

	int x, y;
	int minPixelValue = 255;
	int maxPixelValue = 0;

	// 최소 및 최대 픽셀 값을 찾습니다.
	for (y = 0; y < 256; y++) {
		for (x = 0; x < 256; x++) {
			int pixelValue = pDoc->InputImage[y][x];
			if (pixelValue < minPixelValue) {
				minPixelValue = pixelValue;
			}
			if (pixelValue > maxPixelValue) {
				maxPixelValue = pixelValue;
			}
		}
	}

	// 명암 대비 스트레칭 수행
	for (y = 0; y < 256; y++) {
		for (x = 0; x < 256; x++) {
			int pixelValue = pDoc->InputImage[y][x];
			int stretchedValue = (int)((float)(pixelValue - minPixelValue) / (maxPixelValue - minPixelValue) * 255);

			// 결과 이미지에 저장
			pDoc->resultImage[y][x] = stretchedValue;
		}
	}

	Invalidate();
}


void CImageProc20211431View::OnPixelBinarization()
{
	CImageProc20211431Doc* pDoc = GetDocument();

	int thresh = 150; //중간값 기준 이거보다 크면 흰색 이거보다 작으면 검은색 //흰색이 많이 타면 thresh값을 올려서 검은색이 더 많이 나오게 하면 된다.
	int x, y;

	for (y = 0; y < 256; y++)
		for (x = 0; x < 256; x++) //이중 for 문으로 순환시키기

		{
			if (pDoc->InputImage[y][x] > thresh)
				pDoc->resultImage[y][x] = 255;
			else                        //2가지 비교 그래서 Result에는 흰색 아니면 검은색이 들어가게됨 
				pDoc->resultImage[y][x] = 0;
		}

	Invalidate();

}


void CImageProc20211431View::OnPixelTwoImageAdd()
{
	CImageProc20211431Doc* pDoc = GetDocument();

	CFileDialog dlg(true);
	CFile file;

	if (dlg.DoModal() == IDOK)
	{
		file.Open(dlg.GetPathName(), CFile::modeRead);
		CArchive ar(&file, CArchive::load);
		pDoc->LoadSecondImageFile(ar);
		file.Close();

		int x, y;

		for (y = 0; y < pDoc->ImageHeight; y++)
			for (x = 0; x < pDoc->ImageWidth; x++)
			{
				if (pDoc->depth == 1)
				{
					pDoc->resultImage[y][x] = 0.5 * pDoc->InputImage[y][x] + 0.5 * pDoc->InputImage2[y][x];
				}
				else
				{
					pDoc->resultImage[y][3 * x + 0] = 0.5 * pDoc->InputImage[y][3 * x + 0] + 0.5 * pDoc->InputImage2[y][3 * x + 0];
					pDoc->resultImage[y][3 * x + 1] = 0.5 * pDoc->InputImage[y][3 * x + 1] + 0.5 * pDoc->InputImage2[y][3 * x + 1];
					pDoc->resultImage[y][3 * x + 2] = 0.5 * pDoc->InputImage[y][3 * x + 2] + 0.5 * pDoc->InputImage[y][3 * x + 2];
				}
			}

		Invalidate();
	}
}


void CImageProc20211431View::LoadTwoImage()
{
	CImageProc20211431Doc* pDoc = GetDocument();
	CFileDialog dlg(TRUE);

	if (dlg.DoModal() == IDOK)
		return;

	CFile file;
	file.Open(dlg.GetPathName(), CFile::modeRead);
	CArchive ar(&file, CArchive::load);
	pDoc->LoadSecondImageFile(ar);
	file.Close();
	// LoadTwoImage();

	int x, y, value;
	for (y = 0; y < pDoc->ImageHeight; y++) {
		for (x = 0; x < pDoc->ImageWidth; x++) {
			value = pDoc->InputImage[y][x] + pDoc->InputImage2[y][x];
			if (value > 255) value = 255;
			pDoc->resultImage[y][x] = value;
		}
	}

	Invalidate();
}


void CImageProc20211431View::OnPixelTwoImageSub()
{
	CImageProc20211431Doc* pDoc = GetDocument();

	CFileDialog dlg(true);
	CFile file;

	if (dlg.DoModal() == IDOK)
	{
		file.Open(dlg.GetPathName(), CFile::modeRead);
		CArchive ar(&file, CArchive::load);
		pDoc->LoadSecondImageFile(ar);
		file.Close();

		int x, y;

		for (y = 0; y < pDoc->ImageHeight; y++)
			for (x = 0; x < pDoc->gImageWidth; x++)
			{
				if (pDoc->depth == 1)
				{
					pDoc->resultImage[y][x] = abs(pDoc->InputImage[y][x] - pDoc->InputImage2[y][x]);
				}
				else
				{
					pDoc->resultImage[y][3 * x + 0] = abs(pDoc->InputImage[y][3 * x + 0] - pDoc->InputImage2[y][3 * x + 0]);
					pDoc->resultImage[y][3 * x + 1] = abs(pDoc->InputImage[y][3 * x + 1] - pDoc->InputImage2[y][3 * x + 1]);
					pDoc->resultImage[y][3 * x + 2] = abs(pDoc->InputImage[y][3 * x + 2] - pDoc->InputImage2[y][3 * x + 2]);
				}
			}

		Invalidate();
	}
}


void CImageProc20211431View::OnRegionSmooting() //흐리게 하기
{
	CImageProc20211431Doc* pDoc = GetDocument();

	float kernel[3][3] = { {1.0 / 9.0,1.0 / 9.0,1.0 / 9.0},
							{1.0 / 9.0,1.0 / 9.0,1.0 / 9.0},
							{1.0 / 9.0,1.0 / 9.0,1.0 / 9.0} };

	Convolve(pDoc->InputImage, pDoc->resultImage, pDoc->ImageWidth, pDoc->ImageHeight, kernel, 0, pDoc->depth);

	Invalidate();
}


void CImageProc20211431View::Convolve(unsigned char** Inimg, unsigned char** Outimg, int cols, int rows, float mask[][3], int bias, int depth)
{
	int x, y;
	int i, j;
	int sum, rsum, gsum, bsum;

	for (y = 1; y < rows - 1; y++)
		for (x = 1; x < cols - 1; x++)
		{
			if (depth == 1)
			{
				sum = 0;
				for (j = 0; j < 3; j++)
					for (i = 0; i < 3; i++)
					{
						sum += (Inimg[y + j - 1][x + i - 1] * mask[j][i]);
					}
				sum += bias;
				if (sum > 255)	sum = 255;
				else if (sum < 0)	sum = 0;
				Outimg[y][x] = sum;
			}
			else
			{
				rsum = 0; gsum = 0; bsum = 0;
				for (j = 0; j < 3; j++)
					for (i = 0; i < 3; i++)
					{
						rsum += (Inimg[y + j - 1][3 * (x + i - 1) + 0] * mask[j][i]);
						gsum += (Inimg[y + j - 1][3 * (x + i - 1) + 1] * mask[j][i]);
							bsum += (Inimg[y + j - 1][3 * (x + i - 1) + 2] * mask[j][i]);
					}
				rsum += bias;	gsum += bias;	bsum += bias;
				if (rsum > 255)	rsum = 255;
				else if (rsum < 0)	rsum = 0;
				if (gsum > 255)	gsum = 255;
				else if (gsum < 0)	gsum = 0;
					if (bsum > 255)	bsum = 255;
					else if (bsum < 0)	bsum = 0;

				Outimg[y][3 * x + 0] = rsum;
				Outimg[y][3 * x + 1] = gsum;
				Outimg[y][3 * x + 2] = bsum;
			}
		}
}



void CImageProc20211431View::OnRegionSharping() //선명하게 하기
{
	CImageProc20211431Doc* pDoc = GetDocument();

	float kernel[3][3] = { {0, 1, -1},
					     {-1, 5, -1}, 
						 {0, -1, 0} };

	Convolve(pDoc->InputImage, pDoc->resultImage, pDoc->ImageWidth, pDoc->ImageHeight, kernel, 0, pDoc->depth);

	Invalidate();
}


void CImageProc20211431View::OnRegionEmbossing() //엠보싱 효과
{
	CImageProc20211431Doc* pDoc = GetDocument();

	float kernel[3][3] = { {-1, 0, 0},
						 {0, 0, 0},
						 {0, 0, 1} };

	Convolve(pDoc->InputImage, pDoc->resultImage, pDoc->ImageWidth, pDoc->ImageHeight, kernel, 128, pDoc->depth);

	Invalidate();
}


void CImageProc20211431View::OnRegionPrewitt()
{
	CImageProc20211431Doc* pDoc = GetDocument();

	float Hmask[3][3] = { {-1,-1,-1},
				 {0, 0, 0},
				 {1, 1, 1} }; //수평 방향 마스크
	float Vmask[3][3] = { {-1, 0, 1},
				  {-1, 0, 1},
				  {-1, 0, 1} }; //수직 방향 마스크

	unsigned char** Er, ** Ec;
	int x, y, value;

	//메모리 할당
	Er = (unsigned char**)malloc(pDoc->ImageHeight * sizeof(unsigned char*));
	Ec = (unsigned char**)malloc(pDoc->ImageHeight * sizeof(unsigned char*));
	for (int i = 0; i < pDoc->ImageHeight; i++)
	{
		Er[i] = (unsigned char*)malloc(pDoc->ImageWidth * pDoc->depth);
		Ec[i] = (unsigned char*)malloc(pDoc->ImageWidth * pDoc->depth);
	}

	Convolve(pDoc->InputImage, Er, pDoc->ImageWidth, pDoc->ImageHeight, Hmask, 0, pDoc->depth); //수평 방향
	Convolve(pDoc->InputImage, Ec, pDoc->ImageWidth, pDoc->ImageHeight, Vmask, 0, pDoc->depth); //수직 방향

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			if (pDoc->depth == 1)
			{
				value = sqrt(Er[y][x] * Er[y][x] + Ec[y][x] * Ec[y][x]);
				if (value > 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->resultImage[y][x] = value;
			}
			else {
				value = sqrt(Er[y][3 * x + 0] * Er[y][3 * x + 0] + Ec[y][3 * x + 0] * Ec[y][3 * x + 0]);
				if (value > 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->resultImage[y][3 * x + 0] = value;

				value = sqrt(Er[y][3 * x + 1] * Er[y][3 * x + 1] + Ec[y][3 * x + 1] * Ec[y][3 * x + 1]);
				if (value > 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->resultImage[y][3 * x + 1] = value;

				value = sqrt(Er[y][3 * x + 2] * Er[y][3 * x + 2] + Ec[y][3 * x + 2] * Ec[y][3 * x + 2]);
				if (value > 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->resultImage[y][3 * x + 2] = value;

				value = sqrt(pDoc->resultImage[y][3 * x + 0] * pDoc->resultImage[y][3 * x + 0] +
					pDoc->resultImage[y][3 * x + 1] * pDoc->resultImage[y][3 * x + 1] +
					pDoc->resultImage[y][3 * x + 2] * pDoc->resultImage[y][3 * x + 2]);
				if (value < 0) value = 0;
				else if (value < 0) value = 0;

				pDoc->resultImage[y][3 * x + 0] = value;
				pDoc->resultImage[y][3 * x + 1] = value;
				pDoc->resultImage[y][3 * x + 2] = value;

			}
		}

	//메모리 해제
	for (int i = 0; i < pDoc->ImageHeight; i++)
	{
		free(Er[i]);
		free(Ec[i]);
	}
	free(Er);
	free(Ec);

	Invalidate();
}


void CImageProc20211431View::OnRegionRoberts()
{
	CImageProc20211431Doc* pDoc = GetDocument();

	float Hmask[3][3] = { {1, 0, 0},
				 {0, -1, 0},
				 {0, 0, 0} }; // 수평 방향 마스크
	float Vmask[3][3] = { {0, 0, 0},
					 {0, -1, 0},
					 {0, 1, 0} }; // 수직 방향 마스크

	unsigned char** Er, ** Ec;
	int x, y, value;

	// 메모리 할당
	Er = (unsigned char**)malloc(pDoc->ImageHeight * sizeof(unsigned char*));
	Ec = (unsigned char**)malloc(pDoc->ImageHeight * sizeof(unsigned char*));
	for (int i = 0; i < pDoc->ImageHeight; i++)
	{
		Er[i] = (unsigned char*)malloc(pDoc->ImageWidth * pDoc->depth);
		Ec[i] = (unsigned char*)malloc(pDoc->ImageWidth * pDoc->depth);
	}

	Convolve(pDoc->InputImage, Er, pDoc->ImageWidth, pDoc->ImageHeight, Hmask, 0, pDoc->depth); // 수평 방향
	Convolve(pDoc->InputImage, Ec, pDoc->ImageWidth, pDoc->ImageHeight, Vmask, 0, pDoc->depth); // 수직 방향

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			if (pDoc->depth == 1)
			{
				value = sqrt(Er[y][x] * Er[y][x] + Ec[y][x] * Ec[y][x]);
				if (value > 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->resultImage[y][x] = value;
			}
			else {
				value = sqrt(Er[y][3 * x + 0] * Er[y][3 * x + 0] + Ec[y][3 * x + 0] * Ec[y][3 * x + 0]);
				if (value > 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->resultImage[y][3 * x + 0] = value;

				value = sqrt(Er[y][3 * x + 1] * Er[y][3 * x + 1] + Ec[y][3 * x + 1] * Ec[y][3 * x + 1]);
				if (value > 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->resultImage[y][3 * x + 1] = value;

				value = sqrt(Er[y][3 * x + 2] * Er[y][3 * x + 2] + Ec[y][3 * x + 2] * Ec[y][3 * x + 2]);
				if (value > 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->resultImage[y][3 * x + 2] = value;

				value = sqrt(pDoc->resultImage[y][3 * x + 0] * pDoc->resultImage[y][3 * x + 0] +
					pDoc->resultImage[y][3 * x + 1] * pDoc->resultImage[y][3 * x + 1] +
					pDoc->resultImage[y][3 * x + 2] * pDoc->resultImage[y][3 * x + 2]);
				if (value < 0) value = 0;
				else if (value < 0) value = 0;

				pDoc->resultImage[y][3 * x + 0] = value;
				pDoc->resultImage[y][3 * x + 1] = value;
				pDoc->resultImage[y][3 * x + 2] = value;

			}
		}

	// 메모리 해제
	for (int i = 0; i < pDoc->ImageHeight; i++)
	{
		free(Er[i]);
		free(Ec[i]);
	}
	free(Er);
	free(Ec);

	Invalidate();
}


void CImageProc20211431View::OnRegionSobel()
{
	CImageProc20211431Doc* pDoc = GetDocument();

	float Hmask[3][3] = { {-1,-1,-1},
						   {0, 0, 0},
						   {1, 1, 1} }; //수평 방향 마스크
	float Vmask[3][3] = { {-1, 0, 1},
						   {-1, 0, 1},
						   {-1, 0, 1} }; //수직 방향 마스크

	unsigned char** Er, ** Ec;
	int i, x, y;
	int sum, rsum, gsum, bsum;

	//메모리할당
	Er = (unsigned char**)malloc(pDoc->ImageHeight * sizeof(unsigned char*));
	Ec = (unsigned char**)malloc(pDoc->ImageHeight * sizeof(unsigned char*));
	for (i = 0; i < pDoc->ImageHeight; i++)
	{
		Er[i] = (unsigned char*)malloc(pDoc->ImageWidth * pDoc->depth);
		Ec[i] = (unsigned char*)malloc(pDoc->ImageWidth * pDoc->depth);
	}

	Convolve(pDoc->InputImage, Er, pDoc->ImageWidth, pDoc->ImageHeight, Hmask, 128, pDoc->depth);  //수평 방향
	Convolve(pDoc->InputImage, Ec, pDoc->ImageWidth, pDoc->ImageHeight, Vmask, 128, pDoc->depth); //수직 방향

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			if (pDoc->depth == 1)
			{
				sum = sqrt((Er[y][x] - 128) * (Er[y][x] - 128) + (Ec[y][x] - 128) * (Ec[y][x] - 128));
				if (sum > 255)	sum = 255;
				else if (sum < 0)	sum = 0;
				pDoc->resultImage[y][x] = sum;
			}
			else
			{
				rsum = sqrt((Er[y][3 * x + 0] - 128) * (Er[y][3 * x + 0] - 128) + (Ec[y][3 * x + 0] - 128) * (Ec[y][3 * x + 0] - 128));
				if (rsum > 255)		rsum = 255;
				else if (rsum < 0)	rsum = 0;

				gsum = sqrt((Er[y][3 * x + 1] - 128) * (Er[y][3 * x + 1] - 128) + (Ec[y][3 * x + 1] - 128) * (Ec[y][3 * x + 1] - 128));
				if (gsum > 255)		gsum = 255;
				else if (rsum < 0)	gsum = 0;

				bsum = sqrt((Er[y][3 * x + 2] - 128) * (Er[y][3 * x + 2] - 128) + (Ec[y][3 * x + 2] - 128) * (Ec[y][3 * x + 2] - 128));
				if (bsum > 255)		bsum = 255;
				else if (rsum < 0)	bsum = 0;

				sum = sqrt(rsum * rsum + gsum * gsum + bsum * bsum);
				if (sum > 255)			sum = 255;
				else if (sum < 0)		sum = 0;

				pDoc->resultImage[y][3 * x + 0] = sum;
				pDoc->resultImage[y][3 * x + 1] = sum;
				pDoc->resultImage[y][3 * x + 2] = sum;
			}
		}
	//메모리 해제
	for (int i = 0; i < pDoc->ImageHeight; i++)
	{
		free(Er[i]);
		free(Ec[i]);
	}
	free(Er);
	free(Ec);

	Invalidate();
}


void CImageProc20211431View::OnRegionAverageFiltering()
{
	CImageProc20211431Doc* pDoc = GetDocument();
	int x, y, i, j;
	int xcor, ycor;
	int sum, count;
	int rsum, gsum, bsum;

	//5*5 영역의 평균값
	for (y = 2; y < pDoc->ImageHeight - 2; y++)
		for (x = 2; x < pDoc->ImageWidth - 2; x++)
		{
			if (pDoc->depth == 1)
			{
				sum = 0;
				for (j = 0; j < 5; j++)
					for (i = 0; i < 5; i++)
					{
						sum += pDoc->InputImage[y + j - 2][x + i - 2];
					}
				sum /= 25;

				if (sum > 255)      sum = 255;
				else if (sum < 0)      sum = 0;

				pDoc->resultImage[y][x] = sum;
			}
			else
			{
				rsum = 0;   gsum = 0;   bsum = 0;
				for (j = 0; j < 5; j++)
					for (i = 0; i < 5; i++)
					{
						rsum += pDoc->InputImage[y + j - 2][3 * (x + i - 2) + 0];
						gsum += pDoc->InputImage[y + j - 2][3 * (x + i - 2) + 1];
						bsum += pDoc->InputImage[y + j - 2][3 * (x + i - 2) + 2];
					}
				rsum /= 25;      gsum /= 25;      bsum /= 25;

				if (rsum > 255)         rsum = 255;
				else if (rsum < 0)      rsum = 0;
				if (gsum > 255)         gsum = 255;
				else if (gsum < 0)      gsum = 0;
				if (bsum > 255)         bsum = 255;
				else if (bsum < 0)      bsum = 0;

				pDoc->resultImage[y][3 * x + 0] = rsum;
				pDoc->resultImage[y][3 * x + 1] = gsum;
				pDoc->resultImage[y][3 * x + 2] = bsum;
			}
		}

	Invalidate();
}

void CImageProc20211431View::OnRegionMadianFiltering() //ppm, raw
{
	CImageProc20211431Doc* pDoc = GetDocument();
	int x, y, i, j;
	int n[9], temp;

	for (y = 1; y < pDoc->ImageHeight - 1; y++)
		for (x = 1; x < pDoc->ImageWidth - 1; x++)
		{
			if (pDoc->depth == 1)
			{
				n[0] = pDoc->InputImage[y - 1][x - 1];
				n[1] = pDoc->InputImage[y - 1][x + 0];
				n[2] = pDoc->InputImage[y - 1][x + 1];
				n[3] = pDoc->InputImage[y - 0][x - 1];
				n[4] = pDoc->InputImage[y - 0][x + 0];
				n[5] = pDoc->InputImage[y - 0][x + 1];
				n[6] = pDoc->InputImage[y + 1][x - 1];
				n[7] = pDoc->InputImage[y + 1][x + 0];
				n[8] = pDoc->InputImage[y + 1][x + 1];

				//sorting=오름차순
				for (i = 8; i > 0; i--)
					for (j = 0; j < i; j++)
					{
						if (n[j] > n[j + 1])
						{
							temp = n[j + 1];
							n[j + 1] = n[j];
							n[j] = temp;
						}
					}

				pDoc->resultImage[y][x] = n[4];
			}
			else
			{
				n[0] = pDoc->InputImage[y - 1][3 * (x - 1) + 0];
				n[1] = pDoc->InputImage[y - 1][3 * (x + 0) + 0];
				n[2] = pDoc->InputImage[y - 1][3 * (x + 1) + 0];
				n[3] = pDoc->InputImage[y - 0][3 * (x - 1) + 0];
				n[4] = pDoc->InputImage[y - 0][3 * (x + 0) + 0];
				n[5] = pDoc->InputImage[y - 0][3 * (x + 1) + 0];
				n[6] = pDoc->InputImage[y + 1][3 * (x - 1) + 0];
				n[7] = pDoc->InputImage[y + 1][3 * (x + 0) + 0];
				n[8] = pDoc->InputImage[y + 1][3 * (x + 1) + 0];

				//sorting=오름차순
				for (i = 8; i > 0; i--)
					for (j = 0; j < i; j++)
					{
						if (n[j] > n[j + 1])
						{
							temp = n[j + 1];
							n[j + 1] = n[j];
							n[j] = temp;
						}
					}

				pDoc->resultImage[y][3 * x + 0] = n[4];

				n[0] = pDoc->InputImage[y - 1][3 * (x - 1) + 1];
				n[1] = pDoc->InputImage[y - 1][3 * (x + 0) + 1];
				n[2] = pDoc->InputImage[y - 1][3 * (x + 1) + 1];
				n[3] = pDoc->InputImage[y - 0][3 * (x - 1) + 1];
				n[4] = pDoc->InputImage[y - 0][3 * (x + 0) + 1];
				n[5] = pDoc->InputImage[y - 0][3 * (x + 1) + 1];
				n[6] = pDoc->InputImage[y + 1][3 * (x - 1) + 1];
				n[7] = pDoc->InputImage[y + 1][3 * (x + 0) + 1];
				n[8] = pDoc->InputImage[y + 1][3 * (x + 1) + 1];

				//sorting=오름차순
				for (i = 8; i > 0; i--)
					for (j = 0; j < i; j++)
					{
						if (n[j] > n[j + 1])
						{
							temp = n[j + 1];
							n[j + 1] = n[j];
							n[j] = temp;
						}
					}

				pDoc->resultImage[y][3 * x + 1] = n[4];

				n[0] = pDoc->InputImage[y - 1][3 * (x - 1) + 2];
				n[1] = pDoc->InputImage[y - 1][3 * (x + 0) + 2];
				n[2] = pDoc->InputImage[y - 1][3 * (x + 1) + 2];
				n[3] = pDoc->InputImage[y - 0][3 * (x - 1) + 2];
				n[4] = pDoc->InputImage[y - 0][3 * (x + 0) + 2];
				n[5] = pDoc->InputImage[y - 0][3 * (x + 1) + 2];
				n[6] = pDoc->InputImage[y + 1][3 * (x - 1) + 2];
				n[7] = pDoc->InputImage[y + 1][3 * (x + 0) + 2];
				n[8] = pDoc->InputImage[y + 1][3 * (x + 1) + 2];

				//sorting=오름차순
				for (i = 8; i > 0; i--)
					for (j = 0; j < i; j++)
					{
						if (n[j] > n[j + 1])
						{
							temp = n[j + 1];
							n[j + 1] = n[j];
							n[j] = temp;
						}
					}

				pDoc->resultImage[y][3 * x + 2] = n[4];
			}
		}

	Invalidate();
}


void CImageProc20211431View::OnMopologyColorGray()
{
	CImageProc20211431Doc* pDoc = GetDocument();
	if (pDoc->depth == 1) return;

	int x, y;
	int gray;

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			gray = (pDoc->InputImage[y][3 * x + 0] + pDoc->InputImage[y][3 * x + 1] + pDoc->InputImage[y][3 * x + 2]) / 3;
			pDoc->InputImage[y][3 * x + 0] = gray;
			pDoc->InputImage[y][3 * x + 1] = gray;
			pDoc->InputImage[y][3 * x + 2] = gray;
		}
	Invalidate();
}

void CImageProc20211431View::OnMopologyBinarization()
{
	CImageProc20211431Doc* pDoc = GetDocument();

	int x, y;
	int thresh = 100;

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			if (pDoc->depth == 1)
			{
				if (pDoc->InputImage[y][x] > thresh)
					pDoc->InputImage[y][x] = 255;
				else
					pDoc->InputImage[y][x] = 0;
			}
			else
			{
				if (pDoc->InputImage[y][3 * x + 0] > thresh)
				{
					pDoc->InputImage[y][3 * x + 0] = 255;
					pDoc->InputImage[y][3 * x + 1] = 255;
					pDoc->InputImage[y][3 * x + 2] = 255;
				}
				else
				{
					pDoc->InputImage[y][3 * x + 0] = 0;
					pDoc->InputImage[y][3 * x + 1] = 0;
					pDoc->InputImage[y][3 * x + 2] = 0;
				}

			}
		}
	Invalidate();
}


void CImageProc20211431View::OnMopologyErosion()
{
	CImageProc20211431Doc* pDoc = GetDocument();

	int x, y, i, j;
	int min, rmin, gmin, bmin = 255;

	for (y = 1; y < pDoc->ImageHeight-1; y++)
		for (x = 1; x < pDoc->ImageWidth-1; x++)
		{
			if (pDoc->depth == 1)
			{
				min = 255;
				for (j = -1; j <= 1; j++)
					for (i = -1; i <= 1; i++)
					{
						if (pDoc->InputImage[y + j][x + i] < min)
							min = pDoc->InputImage[y + j][x + i];

					}
				pDoc->resultImage[y][x] = min;
			}
			else
			{
				rmin = 255; gmin = 255; bmin = 255;
				for (j = -1; j <= 1; j++)
					for (i = -1; i <= 1; i++)
					{
						if (pDoc->InputImage[y + j][3 * (x + i) + 0] < rmin)
							rmin = pDoc->InputImage[y + j][3 * (x + i) + 0];
						if (pDoc->InputImage[y + j][3 * (x + i) + 1] < gmin)
							gmin = pDoc->InputImage[y + j][3 * (x + i) + 1];
						if (pDoc->InputImage[y + j][3 * (x + i) + 2] < bmin)
							bmin = pDoc->InputImage[y + j][3 * (x + i) +2];

					}
				pDoc->resultImage[y][3 * x + 0] = rmin;
				pDoc->resultImage[y][3 * x + 1] = gmin;
				pDoc->resultImage[y][3 * x + 2] = bmin;
			}

		}
	Invalidate();
}

void CImageProc20211431View::OnMopolopyDilation() //팽창 연산
{
	CImageProc20211431Doc* pDoc = GetDocument();

	int x, y, i, j;
	int max, rmax, gmax, bmax = 0;

	for (y = 1; y < pDoc->ImageHeight - 1; y++)
		for (x = 1; x < pDoc->ImageWidth - 1; x++)
		{
			if (pDoc->depth == 1)
			{
				max = 0;
				for (j = -1; j <= 1; j++)
					for (i = -1; i <= 1; i++)
					{
						if (pDoc->InputImage[y + j][x + i] > max)
							max = pDoc->InputImage[y + j][x + i];

					}
				pDoc->resultImage[y][x] = max;
			}
			else
			{
				rmax = 0; gmax = 0; bmax = 0;
				for (j = -1; j <= 1; j++)
					for (i = -1; i <= 1; i++)
					{
						if (pDoc->InputImage[y + j][3 * (x + i) + 0] > rmax)
							rmax = pDoc->InputImage[y + j][3 * (x + i) + 0];
						if (pDoc->InputImage[y + j][3 * (x + i) + 1] > gmax)
							gmax = pDoc->InputImage[y + j][3 * (x + i) + 1];
						if (pDoc->InputImage[y + j][3 * (x + i) + 2] > bmax)
							bmax = pDoc->InputImage[y + j][3 * (x + i) + 2];

					}
				pDoc->resultImage[y][3 * x + 0] = rmax;
				pDoc->resultImage[y][3 * x + 1] = gmax;
				pDoc->resultImage[y][3 * x + 2] = bmax;
			}

		}
	Invalidate();
}

void CImageProc20211431View::OnMopologyOpening()
{
	OnMopologyErosion();
	CopyResultToInput();
	OnMopologyErosion();
	CopyResultToInput();
	OnMopologyErosion();

	CopyResultToInput();
	OnMopolopyDilation();
	CopyResultToInput();
	OnMopolopyDilation();
	CopyResultToInput();
	OnMopolopyDilation();

}


void CImageProc20211431View::CopyResultToInput()
{
	CImageProc20211431Doc* pDoc = GetDocument();

	int x, y;

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth*pDoc->depth; x++)
		{
			pDoc->InputImage[y][x] = pDoc->resultImage[y][x]; //흑백

		}

}


void CImageProc20211431View::OnMopologyClosing()
{
	OnMopolopyDilation();
	CopyResultToInput();
	OnMopolopyDilation();
	CopyResultToInput();
	OnMopolopyDilation();
	
	CopyResultToInput();
	OnMopologyErosion();
	CopyResultToInput();
	OnMopologyErosion();
	CopyResultToInput();
	OnMopologyErosion();

	
}


void CImageProc20211431View::OnGeometryZoominPixelCopy()
{
	CImageProc20211431Doc* pDoc = GetDocument();

	int x, y, i, j;

	int xscale = 3;
	int yscale = 2;

	if (pDoc->gresultImage != NULL)
	{
		for (int i = 0; i < pDoc->gImageHeight; i++)
			free(pDoc->gresultImage[i]);
		free(pDoc->gresultImage);
	} //NULL이 아니면 확대나 축소를 하고 있어야 함 = 메모리 없애는 부분

	pDoc->gImageWidth = pDoc->ImageWidth * xscale;
	pDoc->gImageHeight = pDoc->ImageHeight* yscale;
	// 메모리 할당
	pDoc->gresultImage = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));
	for (int i = 0; i < pDoc->gImageHeight; i++)
	{
		pDoc->gresultImage[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);
	}
	//역방향사상
	for (y = 0; y<pDoc->gImageHeight; y++)
		for (x = 0; x < pDoc->gImageWidth; x++)
		{
			if(pDoc->depth==1)
				pDoc->gresultImage[y][x] = pDoc->InputImage[y/yscale][x/xscale];
			else
			{
				pDoc->gresultImage[y][3 * x + 0] = pDoc->InputImage[y / yscale][3 * (x / xscale) + 0];
				pDoc->gresultImage[y][3 * x + 1] = pDoc->InputImage[y / yscale][3 * (x / xscale) + 1];
				pDoc->gresultImage[y][3 * x + 2] = pDoc->InputImage[y / yscale][3 * (x / xscale) + 2];

			}
		}

/*	//전방향사상
	for (y = 0; y < pDoc->gImageHeight; y++)
		for (x = 0; x < pDoc->gImageWidth; x++)
		{
			pDoc->gresultImage[y*yscale][x*xscale] = pDoc->InputImage[y][x];
		}

		*/
	Invalidate();
}

void CImageProc20211431View::OnGeometryZoominBilnearInterpolation()
{
	CImageProc20211431Doc* pDoc = GetDocument();

	int x, y, i, j;

	float xscale = 2.6;
	float yscale = 1.3;
	float src_x, src_y;
	float alpha, beta;
	int Ax, Ay, Bx, By, Cx, Cy, Dx, Dy;
	int E, F;

	if (pDoc->gresultImage != NULL)
	{
		for (int i = 0; i < pDoc->gImageHeight; i++)
			free(pDoc->gresultImage[i]);
		free(pDoc->gresultImage);
	}

	pDoc->gImageWidth = pDoc->ImageWidth * xscale + 0.5;
	pDoc->gImageHeight = pDoc->ImageHeight * yscale + 0.5;

	// 메모리 할당
	pDoc->gresultImage = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));
	for (int i = 0; i < pDoc->gImageHeight; i++)
	{
		pDoc->gresultImage[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);
	}

	//역방향사상
	for (y = 0; y < pDoc->gImageHeight; y++)
		for (x = 0; x < pDoc->gImageWidth; x++)
		{
			src_x = x / xscale;
			src_y = y / xscale;
			alpha = src_x - (int)src_x;
			beta = src_y - (int)src_y;

			Ax = (int)src_x;
			Ay = (int)src_y;
			Bx = Ax + 1;
			By = Ay;
			Cx = Ax;
			Cy = Ay + 1;
			Dx = Ax + 1;
			Dy = Ay + 1;

			if (Bx > pDoc->ImageWidth - 1) Bx = pDoc->ImageWidth - 1;
			if (Cy > pDoc->ImageHeight- 1) Cy = pDoc->ImageHeight - 1;
			if (Dx > pDoc->ImageWidth - 1) Dx = pDoc->ImageWidth - 1;
			if (Dy > pDoc->ImageHeight - 1) Dy = pDoc->ImageHeight - 1;

			if (pDoc->depth == 1)
			{
				E = (1 - alpha) * pDoc->InputImage[Ay][Ax] + alpha * pDoc->InputImage[By][Bx];
				F = (1 - alpha) * pDoc->InputImage[Cy][Cx] + alpha * pDoc->InputImage[Dy][Dx];

				pDoc->gresultImage[y][x] = (1 - beta) * E + beta * F;
			}
			else
			{
				E = (1 - alpha) * pDoc->InputImage[Ay][3 * Ax + 0] + alpha * pDoc->InputImage[By][3 * Bx + 0];
				F = (1 - alpha) * pDoc->InputImage[Cy][3 * Cx + 0] + alpha * pDoc->InputImage[Dy][3 * Dx + 0];
				pDoc->gresultImage[y][3 * x + 0] = (1 - beta) * E + beta * F;

				E = (1 - alpha) * pDoc->InputImage[Ay][3 * Ax + 1] + alpha * pDoc->InputImage[By][3 * Bx + 1];
				F = (1 - alpha) * pDoc->InputImage[Cy][3 * Cx + 1] + alpha * pDoc->InputImage[Dy][3 * Dx + 1];
				pDoc->gresultImage[y][3 * x + 1] = (1 - beta) * E + beta * F;

				E = (1 - alpha) * pDoc->InputImage[Ay][3 * Ax + 2] + alpha * pDoc->InputImage[By][3 * Bx + 2];
				F = (1 - alpha) * pDoc->InputImage[Cy][3 * Cx + 2] + alpha * pDoc->InputImage[Dy][3 * Dx + 2];
				pDoc->gresultImage[y][3 * x + 2] = (1 - beta) * E + beta * F;


			}
		}

	Invalidate();
}


void CImageProc20211431View::OnGeometryZoonoutSubsampling()
{
	CImageProc20211431Doc* pDoc = GetDocument();

	int xscale = 3; //1/3
	int yscale = 2; //1/2
	int x, y;

	if (pDoc->gresultImage != NULL)
	{
		for (int i = 0; i < pDoc->gImageHeight; i++)
			free(pDoc->gresultImage[i]);
		free(pDoc->gresultImage);
	}
	pDoc->gImageWidth = pDoc->ImageWidth / xscale;
	pDoc->gImageHeight = pDoc->ImageHeight / yscale;

	// 메모리 할당
	pDoc->gresultImage = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));
	for (int i = 0; i < pDoc->gImageHeight; i++)
	{
		pDoc->gresultImage[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);
	}
	//역방향사상
	for (y = 0; y < pDoc->gImageHeight; y++)
		for (x = 0; x < pDoc->gImageWidth; x++)
		{
			if(pDoc->depth==1)
				pDoc->gresultImage[y][x] = pDoc->InputImage[y * yscale][x * xscale]; //흑백일때
			else
			{
				pDoc->gresultImage[y][3 * x + 0] = pDoc->InputImage[y * yscale][3 * (x * xscale) + 0];
				pDoc->gresultImage[y][3 * x + 1] = pDoc->InputImage[y * yscale][3 * (x * xscale) + 1];
				pDoc->gresultImage[y][3 * x + 2] = pDoc->InputImage[y * yscale][3 * (x * xscale) + 2];
			}
		}

	Invalidate();
}


void CImageProc20211431View::OnGeometryZoomoutMeanSub()
{
	OnRegionSmooting();
	CopyResultToInput();
	OnGeometryZoonoutSubsampling();
}




void CImageProc20211431View::OnGeometryAvgFiltering()
{
	CImageProc20211431Doc* pDoc = GetDocument();

	int xscale = 3; //1/3
	int yscale = 2; //1/2
	int x, y, i, j;
	int sum, rsum, gsum, bsum;
	int src_x, src_y;

	if (pDoc->gresultImage != NULL)
	{
		for (int i = 0; i < pDoc->gImageHeight; i++)
			free(pDoc->gresultImage[i]);
		free(pDoc->gresultImage);
	}
	pDoc->gImageWidth = pDoc->ImageWidth / xscale;
	pDoc->gImageHeight = pDoc->ImageHeight / yscale;

	// 메모리 할당
	pDoc->gresultImage = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));
	for (int i = 0; i < pDoc->gImageHeight; i++)
	{
		pDoc->gresultImage[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);
	}
	//전방향사상
	for (y = 0; y < pDoc->ImageHeight; y+= yscale)
		for (x = 0; x < pDoc->ImageWidth; x+= xscale )
		{
			if (pDoc->depth == 1)
			{
				sum = 0;
				for (j = 0; j < yscale; j++)
					for (i = 0; i < xscale; i++)
					{
						src_x = x + i;
						src_y = y + j;

						sum += pDoc->InputImage[src_y][src_x];
					}
				pDoc->gresultImage[y / yscale][x / xscale] = sum / (yscale * xscale);
			}
			else
			{
				rsum = 0;	gsum = 0;	bsum = 0;
				for (j = 0; j < yscale; j++)
					for (i = 0; i < xscale; i++)
					{
						src_x = x + i;
						src_y = y + j;

						rsum += pDoc->InputImage[src_y][3 * src_x + 0];
						gsum += pDoc->InputImage[src_y][3 * src_x + 1];
						bsum += pDoc->InputImage[src_y][3 * src_x + 2];
					}
				pDoc->gresultImage[y / yscale][3 * (x / xscale) + 0] = rsum / (yscale * xscale);
				pDoc->gresultImage[y / yscale][3 * (x / xscale) + 1] = gsum / (yscale * xscale);
				pDoc->gresultImage[y / yscale][3 * (x / xscale) + 2] = bsum / (yscale * xscale);
			}
		}
	Invalidate();
}
#define PI 3.1415926521
#include "CAngleDialog.h"
#include <math.h>

void CImageProc20211431View::OnGeometryRotation()
{
	CImageProc20211431Doc* pDoc = GetDocument();
	CAngleDialog dlg;

	int angle = 30; // degree 단위
	float radian;
	int Hy; 	//y좌표의 마지막 위치
	int Cx, Cy; //영상의 가운데 좌표값
	int x, y, i, xdiff, ydiff;
	int x_source, y_source;

	dlg.m_iAngle = angle;
	if (dlg.DoModal() == IDCANCEL) return;
	angle = dlg.m_iAngle;

	
	radian = PI / 180 * angle;

	if (pDoc->gresultImage != NULL)
	{
		for (i = 0; i < pDoc->gImageHeight; i++)
			free(pDoc->gresultImage[i]);
		free(pDoc->gresultImage);
	}

	pDoc->gImageWidth = pDoc->ImageHeight * fabs(cos(PI / 2 - radian)) +
		pDoc->ImageWidth * fabs(cos(radian));
	pDoc->gImageHeight = pDoc->ImageHeight * fabs(cos(radian)) +
		pDoc->ImageWidth * fabs(cos(PI / 2 - radian));
	// 메모리 할당
	pDoc->gresultImage = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));
	for (i = 0; i < pDoc->gImageHeight; i++)
	{
		pDoc->gresultImage[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);
	}

	//중심점
	Cx = pDoc->ImageWidth / 2;
	Cy = pDoc->ImageHeight / 2;
	//y의 마지막좌표
	Hy = pDoc->ImageHeight - 1;

	xdiff = (pDoc->gImageWidth - pDoc->ImageWidth) / 2;
	ydiff = (pDoc->gImageHeight - pDoc->ImageHeight) / 2;

	for (y = -ydiff; y < pDoc->gImageHeight - ydiff; y++)
		for (x = -xdiff; x < pDoc->gImageWidth - xdiff; x++)
		{
			x_source = ((Hy - y) - Cy) * sin(radian) + (x - Cx) * cos(radian) + Cx;
			y_source = Hy - (((Hy - y) - Cy) * cos(radian) - (x - Cx) * sin(radian) + Cy);

			if (pDoc->depth == 1)
			{
				if (x_source<0 || x_source>pDoc->ImageWidth - 1 ||
					y_source<0 || y_source>pDoc->ImageHeight - 1)
					pDoc->gresultImage[y + ydiff][x + xdiff] = 255;
				else
					pDoc->gresultImage[y + ydiff][x + xdiff] = pDoc->InputImage[y_source][x_source];
			}
			else
			{
				if (x_source<0 || x_source>pDoc->ImageWidth - 1 ||
					y_source<0 || y_source>pDoc->ImageHeight - 1)
				{
					pDoc->gresultImage[y + ydiff][3 * (x + xdiff) + 0] = 255;
					pDoc->gresultImage[y + ydiff][3 * (x + xdiff) + 1] = 255;
					pDoc->gresultImage[y + ydiff][3 * (x + xdiff) + 2] = 255;
				}
				else
				{
					pDoc->gresultImage[y + ydiff][3 * (x + xdiff) + 0] = pDoc->InputImage[y_source][3 * (x_source)+0];
					pDoc->gresultImage[y + ydiff][3 * (x + xdiff) + 1] = pDoc->InputImage[y_source][3 * (x_source)+1];
					pDoc->gresultImage[y + ydiff][3 * (x + xdiff) + 2] = pDoc->InputImage[y_source][3 * (x_source)+2];

				}
			}
		}
	Invalidate();
}


void CImageProc20211431View::OnGeometryHolizationalFilp()
{
	CImageProc20211431Doc* pDoc = GetDocument();
	int x, y;

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			if (pDoc->depth == 1)
			{
				pDoc->resultImage[y][pDoc->ImageWidth - 1 - x] = pDoc->InputImage[y][x];
			}
			else
			{
				pDoc->resultImage[y][3 * (pDoc->ImageWidth - 1 - x) + 0] = pDoc->InputImage[y][3 * x + 0];
				pDoc->resultImage[y][3 * (pDoc->ImageWidth - 1 - x) + 1] = pDoc->InputImage[y][3 * x + 1];
				pDoc->resultImage[y][3 * (pDoc->ImageWidth - 1 - x) + 2] = pDoc->InputImage[y][3 * x + 2];
			}
		}
	Invalidate();
}


void CImageProc20211431View::OnGeometryVeticalFilp()
{
	CImageProc20211431Doc* pDoc = GetDocument();
	int x, y;

	for (y = 0; y < pDoc->ImageHeight; y++) {
		for (x = 0; x < pDoc->ImageWidth; x++) {
			if (pDoc->depth == 1) {
				pDoc->resultImage[y][x] = pDoc->InputImage[pDoc->ImageHeight - 1 - y][x];
			}
			else {
				pDoc->resultImage[y][3 * x + 0] = pDoc->InputImage[pDoc->ImageHeight - 1 - y][3 * x + 0];
				pDoc->resultImage[y][3 * x + 1] = pDoc->InputImage[pDoc->ImageHeight - 1 - y][3 * x + 1];
				pDoc->resultImage[y][3 * x + 2] = pDoc->InputImage[pDoc->ImageHeight - 1 - y][3 * x + 2];
			}
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


void CImageProc20211431View::OnGeometrywarping()
{
	CImageProc20211431Doc* pDoc = GetDocument();

	control_line source_lines[5] = { {100,100,150,150},
		{0,0,pDoc->ImageWidth - 1,0},
		{pDoc->ImageWidth - 1,0,pDoc->ImageWidth - 1,pDoc->ImageHeight - 1},
		{pDoc->ImageWidth - 1,pDoc->ImageHeight - 1,0,pDoc->ImageHeight - 1},
		{0,pDoc->ImageHeight - 1,0,0} };
	control_line dest_lines[5] = { {100,100,200,200},
		{0,0,pDoc->ImageWidth - 1,0},
		{pDoc->ImageWidth - 1,0,pDoc->ImageWidth - 1,pDoc->ImageHeight - 1},
		{pDoc->ImageWidth - 1,pDoc->ImageHeight - 1,0,pDoc->ImageHeight - 1},
		{0,pDoc->ImageHeight - 1,0,0} };

	source_lines[0] = mctrl_source;
	dest_lines[0] = mctrl_dest;

	int x, y;

	double u;	// 수직 교차점의 위치
	double h;	// 제어선으로부터 픽셀의 수직변위
	double d;	// 제어선과 픽셀 사이의 거리 
	double tx, ty;		// 결과영상 픽셀에 대응되는 입력 영상 픽셀 사이의 변위의 합
	double xp, yp;	// 각 제어선에 대해 계산된 입력 영상의 대응되는 픽셀 위치   
	double weight;	// 각 제어선의 가중치 
	double totalweight;		// 가중치의 합   
	double a = 0.001;
	double b = 2.0;
	double p = 0.75;

	int x1, y1, x2, y2;
	int src_x1, src_y1, src_x2, src_y2;
	double src_line_length, dest_line_length;

	int num_lines = 5;	// 제어선의수
	int line;
	int source_x, source_y;

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			tx = 0.0;
			ty = 0.0;
			totalweight = 0.0;
			for (line = 0; line < num_lines; line++)
			{
				x1 = dest_lines[line].Px;
				y1 = dest_lines[line].Py;
				x2 = dest_lines[line].Qx;
				y2 = dest_lines[line].Qy;

				dest_line_length = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));

				u = (double)((x - x1) * (x2 - x1) + (y - y1) * (y2 - y1)) /
					(double)((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));

				h = ((y - y1) * (x2 - x1) - (x - x1) * (y2 - y1)) / dest_line_length;

				if (u < 0)		d = sqrt((x - x1) * (x - x1) + (y - y1) * (y - y1));
				else if (u > 1)	d = sqrt((x - x2) * (x - x2) + (y - y2) * (y - y2));
				else				d = fabs(h);

				src_x1 = source_lines[line].Px;
				src_y1 = source_lines[line].Py;
				src_x2 = source_lines[line].Qx;
				src_y2 = source_lines[line].Qy;

				src_line_length = sqrt((src_x2 - src_x1) * (src_x2 - src_x1) + (src_y2 - src_y1) * (src_y2 - src_y1));

				xp = src_x1 + u * (src_x2 - src_x1) - h * (src_y2 - src_y1) / src_line_length;
				yp = src_y1 + u * (src_y2 - src_y1) + h * (src_x2 - src_x1) / src_line_length;

				weight = pow(pow(dest_line_length, p) / (a + d), b);

				tx += (xp - x) * weight;
				ty += (yp - y) * weight;
				totalweight += weight;
			}

			source_x = x + tx / totalweight;
			source_y = y + ty / totalweight;

			if (source_x < 0)			source_x = 0;
			else if (source_x > pDoc->ImageWidth - 1)		source_x = pDoc->ImageWidth - 1;
			if (source_y < 0)			source_y = 0;
			else if (source_y > pDoc->ImageHeight - 1)		source_y = pDoc->ImageHeight - 1;

			if (pDoc->depth == 1)
			{
				pDoc->resultImage[y][x] = pDoc->InputImage[source_y][source_x];
			}
			else
			{
				pDoc->resultImage[y][3 * x + 0] = pDoc->InputImage[source_y][3 * source_x + 0];
				pDoc->resultImage[y][3 * x + 1] = pDoc->InputImage[source_y][3 * source_x + 1];
				pDoc->resultImage[y][3 * x + 2] = pDoc->InputImage[source_y][3 * source_x + 2];
			}
		}

	Invalidate();
}

CPoint mpos_st, mpos_end;

void CImageProc20211431View::OnLButtonDown(UINT nFlags, CPoint point)
{
	mpos_st = point;

	CScrollView::OnLButtonDown(nFlags, point);
}


void CImageProc20211431View::OnLButtonUp(UINT nFlags, CPoint point)
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

	if (Ax < Bx) mctrl_source.Px = Ax - (Bx - Ax) / 2;
	else		 mctrl_source.Px = Ax + (Bx - Ax) / 2;

	if (Ay < By) mctrl_source.Py = Ay - (Bx - Ay) / 2;
	else		 mctrl_source.Py = Ay + (Bx - Ay) / 2;

	mctrl_dest.Px = mctrl_source.Px;
	mctrl_dest.Px = mctrl_source.Px;

	mctrl_source.Qx = mpos_st.x;
	mctrl_source.Qy = mpos_st.y;
	mctrl_dest.Qx = mpos_end.x;
	mctrl_dest.Qy = mpos_end.y;

	CScrollView::OnLButtonUp(nFlags, point);
}


void CImageProc20211431View::LoadAviFile(CDC* pDC)
{
	PAVIFILE pavi;
	AVIFILEINFO fi;
	int stm;
	PAVISTREAM pstm = NULL;
	AVISTREAMINFO si;
	PGETFRAME pfrm = NULL;
	int frame;
	LPBITMAPINFOHEADER pbmpih;
	unsigned char* image;
	int x, y;

	AVIFileInit();
	AVIFileOpen(&pavi, AviFIleName, OF_READ | OF_SHARE_DENY_NONE, NULL);
	AVIFileInfo(pavi, &fi, sizeof(AVIFILEINFO));

	for (stm = 0; stm < fi.dwStreams; stm++)
	{
		AVIFileGetStream(pavi, &pstm, 0, stm);
		AVIStreamInfo(pstm, &si, sizeof(si));
		if (si.fccType == streamtypeVIDEO)
		{
			pfrm = AVIStreamGetFrameOpen(pstm, NULL);
			for (frame = 0; frame < si.dwLength; frame++) //fi.dwWidth
			{
				pbmpih = (LPBITMAPINFOHEADER)AVIStreamGetFrame(pfrm, frame);
				if (!pbmpih) continue;

				image = (unsigned char*)((LPSTR)pbmpih + (WORD)pbmpih->biSize);

				/* for (y = 0; y<fi.dwHeight; y++)
					for (x = 0; x < fi.dwWidth; x++)
					{
						pDC->SetPixel(x, fi.dwHeight - 1 - y,
							RGB(image[(y * fi.dwWidth + x) * 3 + 2],
								image[(y * fi.dwWidth + x) * 3 + 1],
								image[(y * fi.dwWidth + x) * 3 + 0]));
					}
					*/
				::SetDIBitsToDevice(pDC->GetSafeHdc(), 0, 0, fi.dwWidth, fi.dwHeight,
					0, 0, 0, fi.dwWidth, image, (BITMAPINFO*)pbmpih, DIB_RGB_COLORS);
				Sleep(1);
			}
		}
	}
	AVIStreamGetFrameClose(pfrm);
	AVIStreamRelease(pstm);
	AVIFileRelease(pavi);
	AVIFileExit();
}

#include"COpenCVDlg.h"

void CImageProc20211431View::OnOpencv()
{
	COpenCVDlg dlg;

	if (dlg.DoModal() == IDOK)
	{

	}
}
