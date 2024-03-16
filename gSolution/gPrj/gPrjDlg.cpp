
// gPrjDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "gPrj.h"
#include "gPrjDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma comment(linker,"/entry:wWinMainCRTStartup /subsystem:console")

#define MAX_POINT 100

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


// CgPrjDlg 대화 상자



CgPrjDlg::CgPrjDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GPRJ_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CgPrjDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CgPrjDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//ON_BN_CLICKED(IDC_BTN_DLG, &CgPrjDlg::OnBnClickedBtnDlg) 
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_TEST, &CgPrjDlg::OnBnClickedBtnTest)
	ON_BN_CLICKED(IDC_BTN_PROCESS, &CgPrjDlg::OnBnClickedBtnProcess)
	ON_BN_CLICKED(IDC_BTN_MAKE_PATTERN, &CgPrjDlg::OnBnClickedBtnMakePattern)
	ON_BN_CLICKED(IDC_BTN_GET_DATA, &CgPrjDlg::OnBnClickedBtnGetData)
	ON_BN_CLICKED(IDC_BTN_THREAD, &CgPrjDlg::OnBnClickedBtnThread)
END_MESSAGE_MAP()


// CgPrjDlg 메시지 처리기

BOOL CgPrjDlg::OnInitDialog()
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
	MoveWindow(0, 0, 1280, 800);
	m_pDlgImage = new CDlgImage; //new -> delete 있어야함!
	m_pDlgImage->Create(IDD_CDlgImage, this); //ID, 메인 창(부모 다이얼로그)
	m_pDlgImage->ShowWindow(SW_SHOW); //이렇게 모달리스트 대화창으로 하면 둘다 조작 가능!

	m_pDlgImgResult = new CDlgImage;
	m_pDlgImgResult->Create(IDD_CDlgImage, this);
	m_pDlgImgResult->ShowWindow(SW_SHOW);
	m_pDlgImgResult->MoveWindow(640, 0, 640, 480);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CgPrjDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CgPrjDlg::OnPaint()
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
HCURSOR CgPrjDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//void CgPrjDlg::OnBnClickedBtnDlg()
//{
	// gitTest
	//여러 다이얼로그 창 띄우기
	//CDlgImage dlg; //빨간 줄 뜨면 include 안한것
	//dlg.DoModal(); //창 띄우기 --이렇게만 하면 이 창이 닫힐때까지 원래 창으로 돌아가지 못함 => 그래서 모달리스트 다이얼로그 사용!
//	m_pDlgImage->ShowWindow(SW_SHOW);
//}


void CgPrjDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (m_pDlgImage) delete m_pDlgImage; //메모리 해제
	if (m_pDlgImgResult) delete m_pDlgImgResult;
}
#include <iostream>
//자식 창이 호출하게할 함수
void CgPrjDlg::callFunc(int n)
{
	int nData = n;
	std::cout << n << std::endl;
}


void CgPrjDlg::OnBnClickedBtnTest()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	unsigned char* fm = (unsigned char*)m_pDlgImage->m_Image.GetBits();

	//점 찍기를 해보자
	int nWidth = m_pDlgImage->m_Image.GetWidth();
	int nHeight = m_pDlgImage->m_Image.GetHeight();
	int nPitch = m_pDlgImage->m_Image.GetPitch();
	memset(fm, 0, nWidth * nHeight);

	for (int k = 0; k < MAX_POINT; k++)
	{
		int x = rand() % nWidth; //특정 좌표만 
		int y = rand() % nHeight;
		fm[y * nPitch + x] = rand()%0xff;
	}

	//찍은 점 개수 세어보기
	int nIndex = 0;
	m_pDlgImgResult->m_nDataCount = 0;
	for (int j = 0; j < nHeight; j++) { //전체 이미지 훑기
		for (int i = 0; i < nWidth; i++) { //이때 i랑 j가 좌표~!!
			if (fm[j * nPitch + i] >100 ) {
				m_pDlgImgResult->m_ptData[nIndex].x = i;
				m_pDlgImgResult->m_ptData[nIndex].y = j;
				m_pDlgImgResult->m_nDataCount = ++nIndex;
				//std::cout << nIndex << ";" << i << "," << j << std::endl;
			}
		}
	}
	//std::cout << nSum << std::endl;

	//memset(fm, 0, 640*480);

	m_pDlgImage->Invalidate(); //화면 업데이트
	m_pDlgImgResult->Invalidate();
}

#include "CProcess.h"
#include <chrono> //테스크 타임 관리

using namespace std::chrono;

void CgPrjDlg::OnBnClickedBtnProcess()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//이미지 프로세싱
	CProcess process;

	auto start = std::chrono::system_clock::now(); //현재 시간 저장
	int nRet = process.getStarInfo(&m_pDlgImage->m_Image); //nTh = 100(디폴트 매개변수)
	auto end = std::chrono::system_clock::now();
	auto millisec = std::chrono::duration_cast<std::chrono::milliseconds>(end - start); //경과 시간
	//end-start = 경과 시간!!
	std::cout << nRet<<"\t"<<millisec.count() << std::endl;
}


void CgPrjDlg::OnBnClickedBtnMakePattern()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//패턴 만들기
	unsigned char* fm = (unsigned char*)m_pDlgImage->m_Image.GetBits();
	int nWidth = m_pDlgImage->m_Image.GetWidth();
	int nHeight = m_pDlgImage->m_Image.GetHeight();
	int nPitch = m_pDlgImage->m_Image.GetPitch();
	memset(fm, 0, nWidth * nHeight);

	//일정 영역에 패턴 만들기
	CRect rect(100, 200, 150, 400); //영역 지정
	for (int j = rect.top; j < rect.bottom; j++) {
		for (int i = rect.left; i < rect.right; i++) {
			fm[j * nPitch + i] = rand()%256;
		}
	}
	m_pDlgImage->Invalidate();
}


void CgPrjDlg::OnBnClickedBtnGetData()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	unsigned char* fm = (unsigned char*)m_pDlgImage->m_Image.GetBits();
	int nWidth = m_pDlgImage->m_Image.GetWidth();
	int nHeight = m_pDlgImage->m_Image.GetHeight();
	int nPitch = m_pDlgImage->m_Image.GetPitch();

	//특정 영역의 중앙 좌표(무게 중심) 구하기
	int nTh = 0x80;
	CRect rect(0,0,nWidth,nHeight);
	int nSumX = 0;
	int nSumY = 0;
	int nCount = 0;
	for (int j = rect.top; j < rect.bottom; j++) {
		for (int i = rect.left; i < rect.right; i++) {
			if (fm[j * nPitch + i] > nTh) {
				nSumX += i;
				nSumY += j;
				nCount++;
			}
		}
	}

	double dCenterX = (double)nSumX / nCount;
	double dCenterY = (double)nSumY / nCount;

	std::cout << dCenterX << "\t" << dCenterY << std::endl;
}


void CgPrjDlg::OnBnClickedBtnThread()
{
	auto start = system_clock::now(); //시작 시간

	//스레드 코드
	int nImgSize = 4096 * 4;
	CRect rect(0, 0, nImgSize, nImgSize);//분할 영역
	CRect rt[4]; //4 영역으로 분할
	//rt[0].SetRect(0, 0, nImgSize, nImgSize);
	//rt[1].SetRect(nImgSize, 0, nImgSize*2, nImgSize);
	//rt[2].SetRect(0, nImgSize, nImgSize, nImgSize*2);
	//rt[3].SetRect(nImgSize, nImgSize, nImgSize*2, nImgSize);
	for (int k = 0; k < 4; k++)
	{
		rt[k] = rect; //처음 만든 영역 가져오기
		rt[k].OffsetRect(nImgSize * (k % 2), nImgSize * (k / 2)); //일정 영역만큼 움직이라 
	}


	auto end = system_clock::now(); //종료 시간
	auto millisec = duration_cast<milliseconds>(end - start);
	std::cout << millisec.count() << std::endl;
}
