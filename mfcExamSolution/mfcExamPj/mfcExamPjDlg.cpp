
// mfcExamPjDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "mfcExamPj.h"
#include "mfcExamPjDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma comment(linker,"/entry:wWinMainCRTStartup /subsystem:console")

#include <iostream>

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CmfcExamPjDlg 대화 상자



CmfcExamPjDlg::CmfcExamPjDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCEXAMPJ_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CmfcExamPjDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_EDIT_X1, m_nX1);
}

BEGIN_MESSAGE_MAP(CmfcExamPjDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_EXCUTE, &CmfcExamPjDlg::OnBnClickedBtnExcute)
END_MESSAGE_MAP()


// CmfcExamPjDlg 메시지 처리기

BOOL CmfcExamPjDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	MoveWindow(50, 50, 1280, 960); //창 크기 조절
	m_pImgDlg = new CimageDlg; //new 연산자 사용시 delete 잊지 말기
	m_pImgDlg->Create(IDD_CimageDlg, this); //ID와 부모 다이얼로그 등록
	m_pImgDlg->ShowWindow(SW_SHOW); //모달리스트 대화창 생성
	m_pImgDlg->MoveWindow(40, 40, 1200, 800); //창 이동 및 크기조절

	//컨트롤 글자 크기 설정
	CFont font; //아무설정 안해도
	GetDlgItem(IDC_BTN_EXCUTE)->SetFont(&font); //버튼 크기에 맞춰 커진다!

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CmfcExamPjDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CmfcExamPjDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CmfcExamPjDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CmfcExamPjDlg::OnDestroy() //창 닫을때
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (m_pImgDlg != NULL) delete m_pImgDlg; //메모리 해제
}

void CmfcExamPjDlg::OnBnClickedBtnExcute() //실행 버튼 클릭 시
{
	int nX1 = GetDlgItemInt(IDC_EDIT_X1); //컨트롤 변수 없이 값가져오기!
	int nY1 = GetDlgItemInt(IDC_EDIT_Y1);
	int nX2 = GetDlgItemInt(IDC_EDIT_X2);
	int nY2 = GetDlgItemInt(IDC_EDIT_Y2);
	if (!isValidX(nX1) || !isValidX(nX2) || !isValidY(nY1) || !isValidY(nY2)) return; //잘못된값 입력
	int nRadius = GetDlgItemInt(IDC_EDIT_RADIUS);
	if (nRadius < 5) nRadius = 5; //반지름 디폴트 길이 5
	int nTerm = 10; //이동 간격

	movingCircle(nTerm, nX1, nY1, nX2, nY2, nRadius); //움직이는 원그리기
}
//움직이는 원 그리기
void CmfcExamPjDlg::movingCircle(int nTerm, int nX1, int nY1, int nX2, int nY2, int nRadius)
{
	if (nX1 > nX2) nTerm = -nTerm;
	for (int i = nX1, j = nY1;;) {
		if (isInArea(i, j, nRadius)) //원 안잘리게 하기 위한 조건 검사
			m_pImgDlg->drawCircle(i, j, nRadius); //해당 좌표에 원그리기
		if (i == nX2 && j == nY2) break; //목적지 좌표면 반복문 탈출
		
		if (isInScope(i,nX2,nTerm)) i += nTerm;
		else i = nX2; //범위 넘어가면 목적지 좌표
		if (isInScope(j,nY2,nTerm)) j += nTerm;
		else j = nY2; //범위 넘어가면 목적지 좌표
	}

	LoadRandomIMG(nX1, nY1, nX2, nY2, nRadius, nTerm);
}
//원의 중심이 유효 영역 안에 있는지 검사
bool CmfcExamPjDlg::isInArea(int nX, int nY, int nRadius)
{
	int nWidth = m_pImgDlg->m_image.GetWidth();
	int nHeight = m_pImgDlg->m_image.GetHeight();

	CRect rect(nRadius, nRadius, nWidth - nRadius, nHeight - nRadius); //원의 중심 좌표가 있어야할 영역의 범위
	return rect.PtInRect(CPoint(nX, nY));
}
//범위 안인지 검사
bool CmfcExamPjDlg::isInScope(int i, int nX, int nTerm)
{
	return (nTerm > 0) ? (i < nX - nTerm) : (i > nX - nTerm);
}
//랜덤하게 이미지 로드
void CmfcExamPjDlg::LoadRandomIMG(int nX1, int nY1, int nX2, int nY2,int nRadius, int nTerm)
{
	int nInterval, nRNum, nCenterX, nCenterY; //변수 선언
	//랜덤 이미지 로드 - 랜덤 좌표 값의 이미지 로드
	do {
		srand((unsigned int)time(NULL)); //랜덤 시드값 초기화
		nInterval = abs(nX2 - nX1) < abs(nY2 - nY1) ? abs(nX2 - nX1) : abs(nY2 - nY1); //각 좌표 차이중 적은 것 기준으로
		if (nInterval == 0) { nCenterX = nX1; nCenterY = nY1; break; }
		nRNum = (rand() % nInterval / abs(nTerm)) * abs(nTerm); //랜덤 난수 생성(nTerm단위로)
		if (nX1 > nX2)  nRNum = -nRNum;
		nCenterX = nX1 + nRNum;
		if (!isInScope(nCenterX, nX2, nTerm)) nCenterX = nX1; //범위 밖이면 시작 좌표
		nCenterY = nY1 + nRNum;
		if (!isInScope(nCenterY, nY2, nTerm)) nCenterY = nY1; //범위 밖이면 시작 좌표
	} while (!isInArea(nCenterX, nCenterY, nRadius)); //좌표값이 영역 안이 아니면 다시 값 설정
	std::cout << "원의 중앙 좌표 : " << nCenterX << ", " << nCenterY << std::endl;
	m_pImgDlg->loadImage(nCenterX, nCenterY);
}
bool CmfcExamPjDlg::isValidX(int x)
{
	int nWidth = m_pImgDlg->m_image.GetWidth();
	return x <= nWidth;
}
bool CmfcExamPjDlg::isValidY(int y)
{
	int nHeight = m_pImgDlg->m_image.GetHeight();
	return y <= nHeight;
}