﻿// ImageProc_20211431Doc.cpp: CImageProc20211431Doc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ImageProc_20211431.h"
#endif

#include "ImageProc_20211431Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CImageProc20211431Doc

IMPLEMENT_DYNCREATE(CImageProc20211431Doc, CDocument)

BEGIN_MESSAGE_MAP(CImageProc20211431Doc, CDocument)
END_MESSAGE_MAP()


// CImageProc20211431Doc 생성/소멸

CImageProc20211431Doc::CImageProc20211431Doc() noexcept
{
	InputImage = NULL;
	InputImage2 = NULL;
	resultImage = NULL;
	gresultImage = NULL;
}

CImageProc20211431Doc::~CImageProc20211431Doc()
{
	if (InputImage != NULL)
	{
		for (int i = 0; i < ImageHeight; i++)
			free(InputImage[i]);
		free(InputImage);
	}
	if (InputImage2 != NULL)
	{
		for (int i = 0; i < ImageHeight; i++)
			free(InputImage2[i]);
		free(InputImage2);
	}
	if (resultImage != NULL)
	{
		for (int i = 0; i < ImageHeight; i++)
			free(resultImage[i]);
		free(resultImage);
	}
	if (gresultImage != NULL)
	{
		for (int i = 0; i < gImageHeight; i++)
			free(gresultImage[i]);
		free(gresultImage);
	} //확대 축소와 관련된 부분
}

BOOL CImageProc20211431Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}

// CImageProc20211431Doc serialization

void CImageProc20211431Doc::Serialize(CArchive& ar)
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
void CImageProc20211431Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CImageProc20211431Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CImageProc20211431Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl* pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CImageProc20211431Doc 진단

#ifdef _DEBUG
void CImageProc20211431Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CImageProc20211431Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

// CImageProc20211431Doc 명령

void CImageProc20211431Doc::LoadImageFile(CArchive& ar)
{
	int maxValue, i;
	char type[16], buf[256];
	CFile* fp = ar.GetFile();
	CString fname = fp->GetFilePath();
	bool isbmp = false;

	if (strcmp(strchr(fname, '.'), ".ppm") == 0 || strcmp(strchr(fname, '.'), ".PPM") == 0 ||
		strcmp(strchr(fname, '.'), ".pgm") == 0 || strcmp(strchr(fname, '.'), ".PGM") == 0)
	{
		ar.ReadString(type, 15);
		do {
			ar.ReadString(buf, 255);
		} while (buf[0] == '#');
		sscanf(buf, "%d %d", &ImageWidth, &ImageHeight);

		do {
			ar.ReadString(buf, 255);
		} while (buf[0] == '#');
		sscanf(buf, "%d", &maxValue);

		if (strcmp(type, "P5") == 0)	depth = 1;
		else                            depth = 3;
	}
	else if (strcmp(strchr(fname, '.'), ".raw") == 0 || strcmp(strchr(fname, '.'), ".RAW") == 0)
	{
		ImageWidth = 256;
		ImageHeight = 256;
		depth = 1;
	}
	else if (strcmp(strchr(fname, '.'), ".bmp") == 0 || strcmp(strchr(fname, '.'), ".BMP") == 0)
	{
		// bitmap file 읽기
		BITMAPFILEHEADER	bmfh;
		ar.Read(&bmfh, sizeof(bmfh));

		// BMP화일임을 나타내는 "BM" 마커가 있는지 확인
		if (bmfh.bfType != (WORD)(('M' << 8) | 'B'))		return;

		//bitmap info 읽기
		BITMAPINFOHEADER	bih;
		ar.Read(&bih, sizeof(bih));

		ImageWidth = bih.biWidth;
		ImageHeight = bih.biHeight;
		depth = bih.biBitCount / 8;

		if (depth == 1)
		{	// palette 존재
			BYTE palette[256 * 4];
			ar.Read(palette, 256 * 4);
		}
		isbmp = true;

	}

	// 메모리 할당
	InputImage = (unsigned char**)malloc(ImageHeight * sizeof(unsigned char*));
	resultImage = (unsigned char**)malloc(ImageHeight * sizeof(unsigned char*));
	for (i = 0; i < ImageHeight; i++)
	{
		InputImage[i] = (unsigned char*)malloc(ImageWidth * depth);
		resultImage[i] = (unsigned char*)malloc(ImageWidth * depth);
	}

	// 파일에서 읽어서 저장
	if (!isbmp)
	{
		for (i = 0; i < ImageHeight; i++)
			ar.Read(InputImage[i], ImageWidth * depth);
	}
	else
	{
		BYTE nu[4];
		int widthbyte;

		widthbyte = (ImageWidth * 3 * 8 + 31) / 32 * 4;

		for (i = 0; i < ImageHeight; i++)
		{
			if (depth == 1)
				ar.Read(InputImage[ImageHeight - 1 - i], ImageWidth * depth);
			else
			{
				for (int j = 0; j < ImageWidth; j++)
				{
					BYTE r, g, b;
					ar.Read(&b, 1);	ar.Read(&g, 1);	ar.Read(&r, 1);
					InputImage[ImageHeight - 1 - i][3 * j + 0] = r;
					InputImage[ImageHeight - 1 - i][3 * j + 1] = g;
					InputImage[ImageHeight - 1 - i][3 * j + 2] = b;
				}
			}

			if ((widthbyte - ImageWidth * depth) != 0)
				ar.Read(nu, (widthbyte - ImageWidth * depth));
		}

	}

	return;
}


void CImageProc20211431Doc::LoadSecondImageFile(CArchive& ar)
{
	int maxValue;
	char type[16], buf[256];
	CFile* fp = ar.GetFile();
	CString fname = fp->GetFilePath();
	bool isbmp = false;

	int imgw, imgh, imgd;

	if (strcmp(strchr(fname, '.'), ".ppm") == 0 || strcmp(strchr(fname, '.'), ".PPM") == 0 ||
		strcmp(strchr(fname, '.'), ".pgm") == 0 || strcmp(strchr(fname, '.'), ".PGM") == 0)
	{
		ar.ReadString(type, 15);

		do {
			ar.ReadString(buf, 256);
		} while (buf[0] == '#');
		sscanf_s(buf, "%d %d", &imgw, &imgh);

		do {
			ar.ReadString(buf, 256);
		} while (buf[0] == '#');
		sscanf_s(buf, "%d", &maxValue);

		if (strcmp(type, "P5") == 0)	imgd = 1;
		else							imgd = 3;
	}
	else if (strcmp(strchr(fname, '.'), ".bmp") == 0 || strcmp(strchr(fname, '.'), ".BMP") == 0)
	{
		//bitmap file header읽기
		BITMAPFILEHEADER bmfh;
		ar.Read((LPSTR)&bmfh, sizeof(bmfh));
		if (bmfh.bfType != (WORD)('B' | ('M' << 8)))	return;

		//bitmap info header 읽기
		BITMAPINFOHEADER bih;
		ar.Read((LPSTR)&bih, sizeof(bih));
		imgw = bih.biWidth;
		imgh = bih.biHeight;
		imgd = bih.biBitCount / 8;

		if (imgd == 1)
		{	// palette 존재
			BYTE palette[256 * 4];
			ar.Read(palette, 256 * 4);
		}

		isbmp = true;
	}
	else if (strcmp(strchr(fname, '.'), ".raw") == 0 || strcmp(strchr(fname, '.'), ".RAW") == 0)
	{
		if (fp->GetLength() != 256 * 256)
		{
			AfxMessageBox("256*256 크기의 raw 파일만 사용가능합니다.");
			return;
		}

		imgw = 256;
		imgh = 256;
		imgd = 1;
	}

	if (imgw != ImageWidth || imgh != ImageHeight || imgd != depth)
	{
		AfxMessageBox("동일한 크기의 화일만 읽어들일 수 있습니다.");
		return;
	}

	//메모리 할당
	InputImage2 = (unsigned char**)malloc(ImageHeight * sizeof(unsigned char*));
	for (int i = 0; i < ImageHeight; i++)
	{
		InputImage2[i] = (unsigned char*)malloc(ImageWidth * depth);
	}

	//영상데이터 읽기
	if (!isbmp)
	{
		for (int i = 0; i < ImageHeight; i++)
			ar.Read(InputImage2[i], ImageWidth * depth);
	}
	else
	{
		// 파일에서 읽어서 저장
		BYTE nu[4 * 3];
		int widthfile;
		widthfile = (ImageWidth * 8 + 32) / 32 * 4;
		for (int j = 0; j < ImageHeight; j++)
		{
			if (depth == 1)
				ar.Read(InputImage2[ImageHeight - 1 - j], ImageWidth * depth);
			else
			{
				for (int i = 0; i < ImageWidth; i++)
				{
					BYTE r, g, b;
					ar.Read(&b, 1);	ar.Read(&g, 1);	ar.Read(&r, 1);

					InputImage2[ImageHeight - 1 - j][3 * i + 0] = r;
					InputImage2[ImageHeight - 1 - j][3 * i + 1] = g;
					InputImage2[ImageHeight - 1 - j][3 * i + 2] = b;
				}
			}

			if ((widthfile - ImageWidth) != 0)
			{
				ar.Read(nu, (widthfile - ImageWidth) * depth);
			}
		}

	}
}