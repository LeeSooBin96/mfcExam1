// CProcess.cpp: 구현 파일
//

#include "pch.h"
#include "gPrj.h"
#include "CProcess.h"


// CProcess

CProcess::CProcess()
{
}

CProcess::~CProcess()
{
}


// CProcess 멤버 함수
int CProcess::getStarInfo(CImage* pimage,int nTh)
{
	unsigned char* fm = (unsigned char*)pimage->GetBits();
	int nWidth = pimage->GetWidth();
	int nHeight = pimage->GetHeight();
	int nPitch = pimage->GetPitch();

	int nSum = 0;
	for (int k = 0; k < nWidth * nHeight; k++) //이미지 전체 검사
	{
		if (fm[k] > nTh)
			nSum++;
	}
	return nSum;
}