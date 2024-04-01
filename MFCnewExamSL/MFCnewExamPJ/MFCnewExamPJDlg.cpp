
// MFCnewExamPJDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCnewExamPJ.h"
#include "MFCnewExamPJDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#pragma comment(linker,"/entry:wWinMainCRTStartup /subsystem:console")
#endif


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


// CMFCnewExamPJDlg 대화 상자



CMFCnewExamPJDlg::CMFCnewExamPJDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCNEWEXAMPJ_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCnewExamPJDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCnewExamPJDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_DRAW, &CMFCnewExamPJDlg::OnBnClickedBtnDraw)
	ON_BN_CLICKED(IDC_BTN_ACTION, &CMFCnewExamPJDlg::OnBnClickedBtnAction)
	ON_BN_CLICKED(IDC_BTN_OPEN, &CMFCnewExamPJDlg::OnBnClickedBtnOpen)
END_MESSAGE_MAP()


// CMFCnewExamPJDlg 메시지 처리기

BOOL CMFCnewExamPJDlg::OnInitDialog()
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
	MoveWindow(50, 50, 800, 560);
	m_pImgDlg = new CimageDlg; //new 연산자 사용시 delete 잊지 말기
	m_pImgDlg->Create(IDD_CimageDlg, this); //ID와 부모 다이얼로그 등록
	m_pImgDlg->ShowWindow(SW_SHOW); //모달리스트 대화창 생성
	m_pImgDlg->MoveWindow(20, 20, 650, 490); //창 이동 및 크기조절
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCnewExamPJDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCnewExamPJDlg::OnPaint()
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
HCURSOR CMFCnewExamPJDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCnewExamPJDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (m_pImgDlg != NULL) delete m_pImgDlg;
}

void CMFCnewExamPJDlg::OnBnClickedBtnDraw()
{
	//draw 버튼 클릭 시
	srand(time(NULL)); //랜덤 시드값 초기화

	int nX1 = GetDlgItemInt(IDC_EDIT_X1);
	int nY1 = GetDlgItemInt(IDC_EDIT_Y1);
	if (!isValidX(nX1) || !isValidY(nY1)) {
		AfxMessageBox(_T("좌표 값이 범위를 벗어났습니다. \n 0<X1<640 ,0<Y1<480"));
		return;
	}
	int nRadius = rand()%50+1; //원의 반지름 랜덤 지정 (1~ 50)
	//원이 영역 안에 있을 수 있는 반지름  찾기
	while(!isCenterInArea(nX1,nY1,nRadius)) nRadius = rand() % 50 + 1;
	m_pImgDlg->m_nRadius = nRadius; //생성된 반지름 저장
	m_pImgDlg->m_nIMGNum = 0; //생성된 이미지 수 초기화
	
	m_pImgDlg->drawCircle(nX1, nY1);
	m_bDraw = true;
}

void CMFCnewExamPJDlg::OnBnClickedBtnAction()
{
	if (!m_bDraw) {
		AfxMessageBox(_T("draw 버튼을 먼저 눌러주세요."));
		return;
	}
	//action 버튼 클릭시
	int nX1 = GetDlgItemInt(IDC_EDIT_X1);
	int nY1 = GetDlgItemInt(IDC_EDIT_Y1);
	int nX2 = GetDlgItemInt(IDC_EDIT_X2);
	int nY2 = GetDlgItemInt(IDC_EDIT_Y2);
	if (!isValidX(nX1) || !isValidY(nY1) || !isValidX(nX2) || !isValidY(nY2)) {
		AfxMessageBox(_T("좌표 값이 범위를 벗어났습니다. \n 0<X<640 ,0<Y<480"));
		return;
	}
	//이동 간격
	int nTermX = (nX1 < nX2) ? 10 : -10;
	int nTermY = (nY1 < nY2) ? 10 : -10;
	//원 이동
	for (int i = nX1, j = nY1;;) {
		i += nTermX; j += nTermY; //이동
		if ((nTermX > 0) ? i > nX2:i < nX2) i = nX2; //범위 검사
		if ((nTermY > 0) ? j > nY2:j < nY2) j = nY2;
		if (isCenterInArea(i, j, m_pImgDlg->m_nRadius))
			m_pImgDlg->drawCircle(i, j); //원 그리기
		if (i == nX2 && j == nY2) break; //목적지에 도착하면 중지
		m_pImgDlg->saveCircleIMG(); //파일 이미지 저장
		Sleep(10);
	}

	m_bDraw = false; 
}

//원의 중심이 이미지 영역 내에 있는지 검사
bool CMFCnewExamPJDlg::isCenterInArea(int x, int y, int radius)
{
	int nWidth = m_pImgDlg->m_image.GetWidth();
	int nHeight = m_pImgDlg->m_image.GetHeight();
	
	//검사 영역
	CRect rect(radius-1, radius-1, nWidth - radius+1, nHeight - radius+1);
	return rect.PtInRect(CPoint(x, y)); //영역 내만 TRUE 경계도 FALSE
}

//유효한 x좌표 값인지 검사
bool CMFCnewExamPJDlg::isValidX(int x)
{
	return x >0  && x < m_pImgDlg->m_image.GetWidth();
}

//유효한 y좌표 값인지 검사
bool CMFCnewExamPJDlg::isValidY(int y)
{
	return y > 0 && y < m_pImgDlg->m_image.GetHeight();
}



void CMFCnewExamPJDlg::OnBnClickedBtnOpen()
{
	//open 버튼 클릭시
	CString strFileDir;

	CFileDialog fileDlg(TRUE, _T(".bmp"),NULL,0,L"파일선택(*.bmp)|*.bmp;");

	if (fileDlg.DoModal() == IDOK)
	{
		strFileDir = fileDlg.GetPathName(); //경로 받기
		m_pImgDlg->loadCircleIMG(&strFileDir);
	}
}
