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
END_MESSAGE_MAP()

// CImageProc20211431View 생성/소멸

CImageProc20211431View::CImageProc20211431View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

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
					pDC->SetPixel(2 * (pDoc->ImageWidth + 20) + x, y, RGB(pDoc->InputImage2[y][x], pDoc->InputImage2[y][x], pDoc->InputImage2[y][x]));
		}
		else
		{
			for (y = 0; y < pDoc->ImageHeight; y++)
				for (x = 0; x < pDoc->ImageWidth; x++)
					pDC->SetPixel(2 * (pDoc->ImageWidth + 20) + x, y, RGB(pDoc->InputImage2[y][3 * x + 0], pDoc->InputImage2[y][3 * x + 1], pDoc->InputImage2[y][3 * x + 2]));
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
					pDC->SetPixel(x, pDoc->ImageHeight + 20 + y, RGB(pDoc->gresultImage[y][3 * x + 0], pDoc->gresultImage[y][3 * x + 1], pDoc->gresultImage[y][3 * x + 2]));
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

	int x, y, value;

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth * pDoc->depth; x++)
		{
			value = pDoc->InputImage[y][x] + 50;
			if (value > 255)	value = 255;
			else if (value < 0)	value = 0;
			pDoc->resultImage[y][x] = value;

		}

	Invalidate();
}


void CImageProc20211431View::OnPixelSub()
{
	CImageProc20211431Doc* pDoc = GetDocument();
	int x, y;
	int value;

	for (y = 0; y < 256; y++)
		for (x = 0; x < 256; x++)
		{
			value = pDoc->InputImage[y][x] - 100;
			if (value > 255)   value = 255;
			else if (value < 0)   value = 0;
			pDoc->resultImage[y][x] = value;
		}
	Invalidate();
}


void CImageProc20211431View::OnPixelMul()
{
	CImageProc20211431Doc* pDoc = GetDocument();

	int x, y, value;

	for (y = 0; y < 256; y++)
		for (x = 0; x < 256; x++)
		{
			value = pDoc->InputImage[y][x] * 1.5;
			if (value > 255)	value = 255;
			else if (value < 0)	value = 0;
			pDoc->resultImage[y][x] = value;
		}

	Invalidate();
}


void CImageProc20211431View::OnPixelDiv()
{
	CImageProc20211431Doc* pDoc = GetDocument();
	int x, y;
	int value;

	for (y = 0; y < 256; y++)
		for (x = 0; x < 256; x++)
		{
			value = pDoc->InputImage[y][x] / 1.5;
			if (value > 255)   value = 255;
			else if (value < 0)   value = 0;
			pDoc->resultImage[y][x] = value;
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
	int x, y, value;
	int threshold = 100;

	for (y = 0; y < 256; y++)
		for (x = 0; x < 256; x++)
		{
			value = pDoc->InputImage[y][x];
			if (value >= threshold)	pDoc->resultImage[y][x] = 255;
			else					pDoc->resultImage[y][x] = 0;
		}

	Invalidate();
}


void CImageProc20211431View::OnPixelTwoImageAdd()
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
	//LoadTwoImage();

	int x, y, value;
	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			value = 0.3 * pDoc->InputImage[y][x] + 0.7 * pDoc->InputImage2[y][x];
			if (value > 255)	value = 255;
			else if (value < 0)	value = 0;
			pDoc->resultImage[y][x] = value;
		}

	Invalidate();
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

	CFileDialog dlg(TRUE);

	if (dlg.DoModal() == IDOK)
		return;

	CFile file;
	file.Open(dlg.GetPathName(), CFile::modeRead);
	CArchive ar(&file, CArchive::load);
	pDoc->LoadSecondImageFile(ar);
	file.Close();
	//LoadTwoImage();

	int x, y, value;
	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			value = 0.3 * pDoc->InputImage[y][x] + 0.7 * pDoc->InputImage2[y][x];
			if (value > 255)	value = 255;
			else if (value < 0)	value = 0;
			pDoc->resultImage[y][x] = value;
		}
	Invalidate();
}

void CImageProc20211431View::OnRegionSmooting() //흐리게 하기
{
	CImageProc20211431Doc* pDoc = GetDocument();

	float kernel[3][3] = { {1 / 9.0,1 / 9.0,1 / 9.0},
						   {1 / 9.0,1 / 9.0,1 / 9.0},
						   {1 / 9.0,1 / 9.0,1 / 9.0}, };
	Convolve(pDoc->InputImage, pDoc->resultImage, pDoc->ImageWidth, pDoc->ImageHeight, kernel, 0, pDoc->depth);

	Invalidate();
}


void CImageProc20211431View::Convolve(unsigned char** Inimg, unsigned char** Outimg, int cols, int rows, float mask[][3], int bias, int depth)
{
	int x, y, value, i, j;
	float sum, redsum, greensum, bluesum; //sum 흑백, 나머지 컬러

	for (y = 1; y < rows-1; y++)
		for (x = 1; x < cols - 1; x++)
		{
			if (depth == 1)
			{
				sum = 0;
				for (j = 0; j < 3; j++)
					for (i = 0; i < 3; i++)
					{
						sum += Inimg[y - 1 + j][x - 1 + i] * mask[j][i];
					}
				sum += bias;
				if (sum > 255)	  sum = 255;
				else if (sum < 0) sum = 0;
				Outimg[y][x] = sum;
			}
			else
			{
				redsum = 0; greensum = 0; bluesum = 0;
				for (j = 0; j < 3; j++)
					for (i = 0; i < 3; i++)
					{
						redsum += Inimg[y - 1 + j][3*(x - 1 + i)+0] * mask[j][i];
						greensum += Inimg[y - 1 + j][3 * (x - 1 + i) + 1] * mask[j][i];
						bluesum += Inimg[y - 1 + j][3 * (x - 1 + i) + 2] * mask[j][i];
					}
				redsum += bias;
				greensum += bias;
				bluesum += bias;

				if (redsum > 255)	 redsum = 255;
				else if (redsum < 0) redsum = 0;
				if (greensum > 255)	 greensum = 255;
				else if (greensum < 0) greensum = 0;
				if (bluesum > 255)	 bluesum = 255;
				else if (bluesum < 0) bluesum = 0;

				Outimg[y][3 * x + 0] = redsum;
				Outimg[y][3 * x + 1] = greensum;
				Outimg[y][3 * x + 2] = bluesum;
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

	float Hmask[3][3] = {  {-1,-1,-1},
						   {0, 0, 0},
						   {1, 1, 1} }; //수평 방향 마스크
	float Vmask[3][3] = {  {-1, 0, 1},
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
				if (value > 255) value = 255;
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

}


void CImageProc20211431View::OnRegionSobel()
{
	CImageProc20211431Doc* pDoc = GetDocument();

	float Hmask[3][3] = { {-1,-2,-1},
						   {0, 0, 0},
						   {1, 2, 1} };
	float Vmask[3][3] = { {-1, 0,1},
						   {-2, 0, 2},
						   {-1, 0, 1} };
}


void CImageProc20211431View::OnRegionAverageFiltering()
{
	CImageProc20211431Doc* pDoc = GetDocument();
	int x, y, i, j;
	int xcor, ycor;
	int sum, count;
	int rsum, gsum, bsum;

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			if (pDoc->depth == 1) {
				sum = 0;
				count = 0;
				for (j = -2; j <= 2; j++)
					for (i = -2; i <= 2; i++)
					{
						ycor = y + j;
						xcor = x + i;

						if (ycor >= 0 && ycor <= pDoc->ImageHeight - 1 && ycor >= 0 && ycor <= pDoc->ImageWidth - 1)
						{
							sum += pDoc->InputImage[ycor][xcor];
							count++;
						}
					}
				pDoc->resultImage[y][x] = sum / count;
			}
			else
			{
				rsum = gsum = bsum = 0;
				count = 0;
				for (j = -1; j <= 1; j++)
					for (i = -1; i <= 1; i++)
					{
						ycor = y + j;
						xcor = x + i;
						if (ycor >= 0 && ycor <= pDoc->ImageHeight - 1 && ycor >= 0 && ycor <= pDoc->ImageWidth - 1)
						{
							rsum += pDoc->InputImage[ycor][3 * xcor + 0];
							gsum += pDoc->InputImage[ycor][3 * xcor + 1];
							bsum += pDoc->InputImage[ycor][3 * xcor + 2];
							count++;
						}
					}
				pDoc->resultImage[y][3 * x + 0] = rsum / count;
				pDoc->resultImage[y][3 * x + 0] = gsum / count;
				pDoc->resultImage[y][3 * x + 0] = bsum / count;
			}
		}
	Invalidate();
}

void CImageProc20211431View::OnRegionMadianFiltering() //ppm, raw
{
	CImageProc20211431Doc* pDoc = GetDocument();
	int x, y, i, j;
	int n[9], temp;
		
		for (y = 1; y < pDoc->ImageHeight-1; y++)
			for (x = 1; x < pDoc->ImageWidth - 1; x++)
			{
				if (pDoc->depth == 1)
				{
					n[0] = pDoc->InputImage[y - 1][x - 1];
					n[1] = pDoc->InputImage[y - 1][x - 0];
					n[2] = pDoc->InputImage[y - 1][x + 1];
					n[3] = pDoc->InputImage[y - 0][x - 1];
					n[4] = pDoc->InputImage[y - 0][x - 0];
					n[5] = pDoc->InputImage[y - 0][x + 1];
					n[6] = pDoc->InputImage[y + 1][x - 1];
					n[7] = pDoc->InputImage[y + 1][x - 0];
					n[8] = pDoc->InputImage[y + 1][x + 1];

					//sorting 정렬
					for (i = 8; i > 0; i--)
						for (j = 0; j < i; j++)
							if (n[j] > n[j + 1])
							{
								temp = n[j + 1];
								n[j + 1] = n[j];
								n[j] = temp;
							}
					pDoc->resultImage[y][x] = n[4];
				}
				else
				{
					n[0] = pDoc->InputImage[y - 1][3 * (x - 1) + 0];
					n[1] = pDoc->InputImage[y - 1][3 * (x - 0) + 0];
					n[2] = pDoc->InputImage[y - 1][3 * (x + 1) + 0];
					n[3] = pDoc->InputImage[y - 0][3 * (x - 1) + 0];
					n[4] = pDoc->InputImage[y - 0][3 * (x - 0) + 0];
					n[5] = pDoc->InputImage[y - 0][3 * (x + 1) + 0];
					n[6] = pDoc->InputImage[y + 1][3 * (x - 1) + 0];
					n[7] = pDoc->InputImage[y + 1][3 * (x - 0) + 0];
					n[8] = pDoc->InputImage[y + 1][3 * (x + 1) + 0];

					for (i = 8; i > 0; i--)
						for (j = 0; j < i; j++)
							if (n[j] > n[j + 1])
							{
								temp = n[j + 1];
								n[j + 1] = n[j];
								n[j] = temp;
							}
					pDoc->resultImage[y][x] = n[4];

					n[0] = pDoc->InputImage[y - 1][3 * (x - 1) + 2];
					n[1] = pDoc->InputImage[y - 1][3 * (x - 0) + 2];
					n[2] = pDoc->InputImage[y - 1][3 * (x + 1) + 2];
					n[3] = pDoc->InputImage[y - 0][3 * (x - 1) + 2];
					n[4] = pDoc->InputImage[y - 0][3 * (x - 0) + 2];
					n[5] = pDoc->InputImage[y - 0][3 * (x + 1) + 2];
					n[6] = pDoc->InputImage[y + 1][3 * (x - 1) + 2];
					n[7] = pDoc->InputImage[y + 1][3 * (x - 0) + 2];
					n[8] = pDoc->InputImage[y + 1][3 * (x + 1) + 2];

					for (i = 8; i > 0; i--)
						for (j = 0; j < i; j++)
							if (n[j] > n[j + 1])
							{
								temp = n[j + 1];
								n[j + 1] = n[j];
								n[j] = temp;
							}
					pDoc->resultImage[y][x] = n[4];
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
	int thresh = 128;

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
				if ((pDoc->InputImage[y][3 * x + 0] + pDoc->InputImage[y][3 * x + 1] + pDoc->InputImage[y][3 * x + 2]) / 3
	> thresh)
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

	int x, y;

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

	int x, y;

	float xscale = 2.3;
	float yscale = 1.5;
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
void CImageProc20211431View::OnGeometryRotation()
{
	CImageProc20211431Doc* pDoc = GetDocument();
	CAngleDialog dlg;

	int angle = 30; // degree 단위
	float radian;
	int Hy; 	//y좌표의 마지막 위치
	int Cx, Cy; //영상의 가운데 좌표값
	int x, y, xdiff, ydiff;
	int x_source, y_source;

	dlg.m_iAngle = angle;
	if (dlg.DoModal() == IDCANCEL) return;
	angle = dlg.m_iAngle;

	
	radian = PI / 180 * angle;
	//y의 마지막
	Hy = pDoc->ImageHeight - 1;
	//중심점
	Cx = pDoc->ImageWidth / 2;
	Cy = pDoc->ImageHeight / 2;

	if (pDoc->gresultImage != NULL)
	{
		for (int i = 0; i < pDoc->gImageHeight; i++)
			free(pDoc->gresultImage[i]);
		free(pDoc->gresultImage);
	}


	pDoc->gImageWidth = pDoc->ImageHeight * fabs(cos(PI / 2 - radian)) + pDoc->ImageWidth * fabs(cos(radian));
	pDoc->gImageHeight = pDoc->ImageHeight * fabs(cos(radian)) + pDoc->ImageWidth * fabs(cos(PI / 2 - radian));
	// 메모리할당
	pDoc->gresultImage = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));
	for (int i = 0; i < pDoc->gImageHeight; i++)
	{
		pDoc->gresultImage[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);
	}
	xdiff = (pDoc->gImageWidth - pDoc->ImageWidth) / 2;
	ydiff = (pDoc->gImageHeight - pDoc->ImageHeight) / 2;

	for (y = -ydiff; y < pDoc->gImageHeight - ydiff; y++)
		for (x = -xdiff; x < pDoc->gImageWidth - xdiff; x++)
		{
			x_source = (Hy - y - Cx) * sin(radian) + (x - Cx) * cos(radian) + Cx;
			y_source = Hy - ((Hy - y - Cy) * cos(radian) - (x - Cx) * sin(radian) + Cy);

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
					pDoc->gresultImage[y + ydiff][3 * (x + xdiff) + 0] = pDoc->InputImage[y_source][3 * x_source + 0];
					pDoc->gresultImage[y + ydiff][3 * (x + xdiff) + 1] = pDoc->InputImage[y_source][3 * x_source + 1];
					pDoc->gresultImage[y + ydiff][3 * (x + xdiff) + 2] = pDoc->InputImage[y_source][3 * x_source + 2];
				}
			}
		}
	Invalidate();
}


void CImageProc20211431View::OnGeometryHolizationalFilp()
{
	CImageProc20211431Doc* pDoc = GetDocument();
	int x, y;

	for(y=0; y<pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			if(pDoc->depth==1)
				pDoc->resultImage[y][x] = pDoc->InputImage[y][pDoc->ImageWidth-1-x]; //그대로 복사-x
			else
			{
				pDoc->resultImage[y][3 * x + 0] = pDoc->InputImage[y][3 * (pDoc->ImageWidth - 1 - x) + 0];
				pDoc->resultImage[y][3 * x + 1] = pDoc->InputImage[y][3 * (pDoc->ImageWidth - 1 - x) + 1];
				pDoc->resultImage[y][3 * x + 2] = pDoc->InputImage[y][3 * (pDoc->ImageWidth - 1 - x) + 2];
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
