#pragma once
#include "afxdialogex.h"


// CimageDlg 대화 상자

class CimageDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CimageDlg)

private:
	bool m_bExistData = false; //데이터 유무 체크
	//데이터들(원 중앙 좌표, 반지름)
	int m_nCenterX;
	int m_nCenterY;

public:
	CImage m_image; //이미지를 그리기 위한 객체 생성
	int m_nRadius; //그려지는 원의 반지름
	int m_nIMGNum; //생성된 이미지 수

	//이미지 갱신
	void updateDisplay();
	//이미지 파일 저장
	void saveCircleIMG();
	//이미지 파일 로드
	void loadCircleIMG(CString*);
	//(cenX,cenY) 좌표에 원 그리기
	void drawCircle(int cenX, int cenY);
	//(x,y)가 이미지 영역 내에 있는지 검사
	bool isInArea(int x, int y);
	//(x,y)가 원 안에 있는지 확인
	bool isInCircle(int x, int y, int cenX, int cenY);

	//원 중심 좌표 찾기
	void focusCircle();
	//원 중심 그리기
	void drawData(CDC* pDc);

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
