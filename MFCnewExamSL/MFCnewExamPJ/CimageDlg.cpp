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

//(cenX,cenY) 좌표에 원 그리기
void CimageDlg::drawCircle(int cenX, int cenY)
{
	int nWidth = m_image.GetWidth(); //이미지 영역 너비
	int nHeight = m_image.GetHeight(); //이미지 영역 높이
	int nPitch = m_image.GetPitch(); //이미지 영역 한 줄 비트수

	unsigned char* fm = (unsigned char*)m_image.GetBits(); //이미지 영역 포인터
	memset(fm, WHITE_NUM, nWidth * nHeight);
	for (int j = cenY - m_nRadius; j < cenY + m_nRadius; j++) {
		for (int i = cenX - m_nRadius; i < cenX + m_nRadius; i++) {
			if (isInArea(i, j) && isInCircle(i, j, cenX, cenY)) //이미지 영역 내이고 원 안의 점이면
				fm[j * nPitch + i] = 0; //검은색으로 그리기
		}
	}
	updateDisplay(); //이미지 갱신
}

//(x,y)가 이미지 영역 내에 있는지 검사
bool CimageDlg::isInArea(int x, int y)
{
	int nWidth = m_image.GetWidth(); //이미지 영역 너비
	int nHeight = m_image.GetHeight(); //이미지 영역 높이

	CRect rect(0, 0, nWidth, nHeight); //이미지 영역
	return rect.PtInRect(CPoint(x, y)); //영역 내에 있는지 검사
}

//(x,y)가 원 안에 있는지 확인
bool CimageDlg::isInCircle(int x, int y, int cenX, int cenY)
{
	bool bRet = false;

	double dX = x - cenX; //x 좌표간 거리
	double dY = y - cenY; //y 좌표간 거리
	double dDist = dX * dX + dY * dY; //거리 벡터값의 제곱
	//거리 벡터값으로 원 안의 점인지 검사
	if (dDist <= m_nRadius * m_nRadius) bRet = true;
	return bRet;
}

//이미지 갱신
void CimageDlg::updateDisplay()
{
	//화면 업데이트
	CClientDC dc(this);
	m_image.Draw(dc, 0, 0);
	if (m_bExistData) drawData(&dc);
}

//이미지 파일 저장
void CimageDlg::saveCircleIMG()
{
	CString strFileName; //파일명 저장할 문자열
	strFileName.Format(_T("..//image/image%d.bmp"), ++m_nIMGNum);
	m_image.Save(strFileName); //솔루션 폴더 내 image 디렉토리에 저장
}

//이미지 파일 로드
void CimageDlg::loadCircleIMG(CString* filePath)
{
	if (m_image != NULL) m_image.Destroy(); //기존 이미지 제거
	m_image.Load(*filePath);
	focusCircle(); //원 중앙 x자 표시, 외곽선 그리기
}

//원 중심 좌표 찾기
void CimageDlg::focusCircle()
{
	//특정 패턴의 중앙 좌표 찾기 와 Elipse활용을 하기 위해 추가한 기능
	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();
	int nPitch = m_image.GetPitch();
	unsigned char* fm = (unsigned char*)m_image.GetBits();

	CRect rect(0, 0, nWidth, nHeight); //검사할 영역 생성
	int nSumX = 0;
	int nSumY = 0;
	int nCount = 0;
	for (int j = rect.top; j < rect.bottom; j++) {
		for (int i = rect.left; i < rect.right; i++) {
			if (fm[j * nPitch + i] == 0) {
				nSumX += i;
				nSumY += j;
				nCount++;
			}
		}
	}
	//중앙 좌표 저장
	m_nCenterX = (int)round((double)nSumX / nCount);
	m_nCenterY = (int)round((double)nSumY / nCount);
	std::cout << "로드된 원의 중앙 좌표: ( " << m_nCenterX << ", " << m_nCenterY << " )\n";

	m_bExistData = true; //원 중앙 십자 표시와 외곽선 그리게함
	updateDisplay();
	m_bExistData = false;
}

void CimageDlg::drawData(CDC* pDc)
{
	CPen pen;
	pen.CreatePen(PS_SOLID, 2, RGB(0xff,0xff,0)); //노란색으로 설정
	CPen* pOldPen = pDc->SelectObject(&pen); //기존 펜 저장
	//X자 그리기
	pDc->MoveTo(m_nCenterX - 5, m_nCenterY-5);
	pDc->LineTo(m_nCenterX + 5, m_nCenterY+5);
	pDc->MoveTo(m_nCenterX+5, m_nCenterY - 5);
	pDc->LineTo(m_nCenterX-5, m_nCenterY + 5);
	//원 그리기
	CBrush* pOldBrush = (CBrush*)pDc->SelectStockObject(NULL_BRUSH); //안에 색채우기 끄기
	CRect rect(CPoint(m_nCenterX - m_nRadius, m_nCenterY - m_nRadius), CPoint(m_nCenterX + m_nRadius, m_nCenterY + m_nRadius));
	pDc->Ellipse(rect);

	pDc->SelectObject(pOldBrush); //원래 브러쉬로 돌리기
	pDc->SelectObject(pOldPen); //원래 펜으로 돌리기

	m_image.Destroy(); //로드한 이미지 제거
	initImage(); //이미지 다시 초기화 -- 이 두 단계있어야 여러번 돌려도 안터짐!
}
