// CAngleDialog.cpp: 구현 파일
//

#include "pch.h"
#include "ImageProc_20211431.h"
#include "afxdialogex.h"
#include "CAngleDialog.h"


// CAngleDialog 대화 상자

IMPLEMENT_DYNAMIC(CAngleDialog, CDialogEx)

CAngleDialog::CAngleDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_ANGLEINPUT, pParent)
	, m_iAngle(0)
{

}

CAngleDialog::~CAngleDialog()
{
}

void CAngleDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ANGLE, m_iAngle);
}


BEGIN_MESSAGE_MAP(CAngleDialog, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT_ANGLE, &CAngleDialog::OnEnChangeEditAngle)
END_MESSAGE_MAP()


// CAngleDialog 메시지 처리기


void CAngleDialog::OnEnChangeEditAngle()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
