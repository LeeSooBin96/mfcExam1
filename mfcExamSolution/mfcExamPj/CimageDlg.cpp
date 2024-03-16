// CimageDlg.cpp: 구현 파일
//

#include "pch.h"
#include "mfcExamPj.h"
#include "afxdialogex.h"
#include "CimageDlg.h"


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

void CimageDlg::initImage() //이미지 초기화 메소드
{
	int nWidth = 1200; //이미지 폭
	int nHeight = 800; //이미지 높이
	int nBpp = 8; //그레이 레벨 픽셀 사용(0~255)

	m_image.Create(nWidth, -nHeight, nBpp); //이미지 생성
	if (nBpp == 8)
	{
		//흑백으로 하기 위한 설정
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++)
		{
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		}
		m_image.SetColorTable(0, 256, rgb);
	}

	//이미지 포인터 가져오기(바이트 배열의 첫요소의 주소를 받아온다)
	unsigned char* fm = (unsigned char*)m_image.GetBits();
	memset(fm, 0xff, nWidth * nHeight); //White로 설정
}



void CimageDlg::OnPaint() //화면이 갱신될 필요가 있을때 자동 호출
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (m_image) {
		m_image.Draw(dc, 0, 0);
	}
	// 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
}

void CimageDlg::drawCircle(int nCenX1, int nCenY1, int nRadius)
{
	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();
	int nPitch = m_image.GetPitch();

	unsigned char* fm = (unsigned char*)m_image.GetBits(); //이미지 포인터 가져오기
	memset(fm, 0xff, nWidth * nHeight);
	for (int j = nCenY1-nRadius;j < nCenY1 + nRadius;j++) {
		for (int i = nCenX1-nRadius;i < nCenX1 + nRadius;i++) {
			if(isInCircle(i,j,nCenX1,nCenY1,nRadius)) //원 조건에 맞으면
				fm[j * nPitch + i] = 0; //검은색으로 그리자
		}
	}

	//이미지 저장해야한다. (파일명: nCenX1bynCenY1.bmp)
	CString strFileName;
	strFileName.Format(_T("..//Image/%dby%d.bmp"), nCenX1, nCenY1);
	m_image.Save(strFileName); //프로젝트 파일의 Image폴더 안에 저장

	updateDisplay();
}

bool CimageDlg::isInCircle(int i, int j, int nCenterX, int nCenterY, int nRadius)
{
	bool bRet = false;

	double dX = i - nCenterX;
	double dY = j - nCenterY;
	double dDist = dX * dX + dY * dY;
	//거리벡터값이 반지름보다 작거나 같으면
	if (dDist <= nRadius * nRadius) bRet = true; 

	return bRet;
}

void CimageDlg::loadImage(int nCenterX, int nCenterY)
{
	if (m_image != NULL) m_image.Destroy();
	CString strFileName;
	strFileName.Format(_T("..//Image/%dby%d.bmp"), nCenterX, nCenterY);
	m_image.Load(strFileName);

	updateDisplay();
}

void CimageDlg::updateDisplay()
{
	//화면 업데이트
	CClientDC dc(this);
	m_image.Draw(dc, 0, 0);
}