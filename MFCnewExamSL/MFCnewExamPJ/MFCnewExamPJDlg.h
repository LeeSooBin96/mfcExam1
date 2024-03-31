﻿
// MFCnewExamPJDlg.h: 헤더 파일
//

#pragma once

#include "CimageDlg.h"
// CMFCnewExamPJDlg 대화 상자
class CMFCnewExamPJDlg : public CDialogEx
{
	CimageDlg* m_pImgDlg; //동적으로 생성하기 위한 대화창 포인터

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
};
