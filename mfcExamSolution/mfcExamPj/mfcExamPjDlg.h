
// mfcExamPjDlg.h: 헤더 파일
//

#pragma once

#include "CimageDlg.h"
// CmfcExamPjDlg 대화 상자
class CmfcExamPjDlg : public CDialogEx
{
private:
	CimageDlg* m_pImgDlg; //동적으로 생성하기 위한 대화창 포인터

	void movingCircle(int nX1,int nY1,int nX2,int nY2,int nRadius,int nTermX,int nTermY); //움직이는 원그리기
	bool isInArea(int nX, int nY, int nRadius); //원 중앙좌표값이 영역안인지 확인
	bool isInScope(int i, int nX, int nTerm); //범위 안인지 검사
	bool isValidX(int x,int nRadius); //유효한 x좌표인지 검사
	bool isValidY(int y,int nRadius); //유효한 y좌표인지 검사

// 생성입니다.
public:
	CmfcExamPjDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCEXAMPJ_DIALOG };
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
	afx_msg void OnBnClickedBtnExcute();
};
