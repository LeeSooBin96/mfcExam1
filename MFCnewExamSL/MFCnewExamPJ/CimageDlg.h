#pragma once
#include "afxdialogex.h"


// CimageDlg 대화 상자

class CimageDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CimageDlg)

public:
	CImage m_image; //이미지를 그리기 위한 객체 생성

public:
	CimageDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CimageDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CimageDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void initImage();
	afx_msg void OnPaint();
};
