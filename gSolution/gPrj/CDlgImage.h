#pragma once
#include "afxdialogex.h"


// CDlgImage 대화 상자

class CDlgImage : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgImage)

public:
	CDlgImage(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDlgImage(); 

	CImage m_Image; //이미지 변수
	CWnd* m_pParent; //윈도위 형태의 포인터! 부모 창 가리키기 위함
	int m_nDataCount = 0; //몇개를 그릴건지
	CPoint m_ptData[100]; //좌표 정보

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CDlgImage };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnUpParent();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
private:
	void InitImage();
	void drawData(CDC* pDC);
};
