
// ImageProc_20211431Doc.h: CImageProc20211431Doc 클래스의 인터페이스
//


#pragma once


class CImageProc20211431Doc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CImageProc20211431Doc() noexcept;
	DECLARE_DYNCREATE(CImageProc20211431Doc)

// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CImageProc20211431Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	unsigned char **InputImage;
	unsigned char **InputImage2; 
	unsigned char **resultImage;
	int ImageWidth; //영상의 가로 크기
	int ImageHeight; //영상의 세로 크기
	int depth; //흑백=1, 칼라=3

	int gImageWidth;
	int gImageHeight; 

	unsigned char** gresultImage;

	void LoadImageFile(CArchive& ar);
	void LoadSecondImageFile(CArchive& ar);
};
