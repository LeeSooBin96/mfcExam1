#pragma once
#include "afxdialogex.h"


// CimageDlg 대화 상자

class CimageDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CimageDlg)
public:
	CImage m_image; //이미지를 그리기 위한 객체 생성
	int m_nIMGNum = 0; //이미지 번호
	int m_nRadius; //반지름은 한번만 저장하면 되니까 밖에서 값 대입하게

private:
	bool m_bExistData = false; //데이터 유무 체크
	//데이터들(원 중앙 좌표, 반지름)
	int m_nCenterX; 
	int m_nCenterY; 

public:
	CimageDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CimageDlg();

	//필요한 함수(메서드)
	void drawCircle(int nX1,int nY1); //원 그리기
	void loadImage(); //이미지 파일 로드

private:
	void initImage(); //이미지 초기화 메소드
	void updateDisplay(); //이미지창 갱신
	void SaveImage(); //이미지 파일 저장
	void focusCircle(); //원 포커스 잡기
	void drawData(CDC* pDc); //데이터 그리기
	bool isInArea(int i, int j); //영역 안인지 검사
	bool isInCircle(int i, int j, int nCenterX, int nCenterY, int nRadius); //원 안에 있는지 조건 검사

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CimageDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
};
