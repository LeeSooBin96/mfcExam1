
// MFCnewExamPJDlg.h: 헤더 파일
//

#pragma once

#include "CimageDlg.h"
// CMFCnewExamPJDlg 대화 상자
class CMFCnewExamPJDlg : public CDialogEx
{
	CimageDlg* m_pImgDlg; //동적으로 생성하기 위한 대화창 포인터
	bool m_bDraw = false; //draw 버튼 클릭 여부 확인
	
	//유효한 x좌표 값인지 검사
	bool isValidX(int x);
	//유효한 y좌표 값인지 검사
	bool isValidY(int y);
	//원의 중심이 이미지 영역 내에 있는지 검사
	bool isCenterInArea(int x, int y, int radius);

// 생성입니다.
public:
	CMFCnewExamPJDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCNEWEXAMPJ_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedBtnDraw();
	afx_msg void OnBnClickedBtnAction();
	afx_msg void OnBnClickedBtnOpen();
};
