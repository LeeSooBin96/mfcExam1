// CimageDlg.cpp: 구현 파일
//

#include "pch.h"
#include "MFCnewExamPJ.h"
#include "afxdialogex.h"
#include "CimageDlg.h"

#define WHITE_NUM 0xff

// CimageDlg 대화 상자

IMPLEMENT_DYNAMIC(CimageDlg, CDialogEx)

CimageDlg::CimageDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CimageDlg, pParent)
{

}

CimageDlg::~CimageDlg()
{
}

void CimageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CimageDlg, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CimageDlg 메시지 처리기


BOOL CimageDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	initImage();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CimageDlg::initImage()
{
	//이미지 초기화
	int nWidth = 640; //이미지 너비
	int nHeight = 480; //이미지 높이
	int nBpp = 8; //픽셀당 비트 수 - 그레이 레벨(0~255)

	m_image.Create(nWidth, -nHeight, nBpp); //이미지 생성
	if (nBpp == 8) {
		//흑백으로 하기 위한 설정
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++) {
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		}
		m_image.SetColorTable(0, 256, rgb);
	}

	//이미지 포인터 가져오기(바이트 배열의 첫요소의 주소를 받아온다)
	unsigned char* fm = (unsigned char*)m_image.GetBits();
	memset(fm, WHITE_NUM, nWidth * nHeight); //White 이미지 생성
}

/* 창 최소화, 크기변경 때마다 갱신(호출)된다 */
void CimageDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (m_image) {
		m_image.Draw(dc, 0, 0);
	}
	// 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
}
