#include "StdAfx.h"


CCommTools::CCommTools(void)
{
}


CCommTools::~CCommTools(void)
{
}

/**
* Brief    : 获得当前时间
* Param    : 
* Return   : CString 时：分
*   Date     : 
*   Author   :  
*   Memo     : new
*/
CString CCommTools::GetLocTime(int iMode)
{
	CString csTime;
	SYSTEMTIME stLoctime; 
	GetLocalTime(&stLoctime); 
	switch ( iMode )
	{
	case 0:
		csTime.Format(_T("%02d:%02d"),stLoctime.wHour,stLoctime.wMinute, stLoctime.wSecond);
		break;

	case 1:
		csTime.Format(_T("%02d:%02d:%02d"),stLoctime.wHour,stLoctime.wMinute, stLoctime.wSecond);
		break;

	case 2:
		break;

	default:
		break;
	}

	return csTime;
}

void  CCommTools::MajorMap(CImage *pImage)
{
	/** 优化png显示。 */
	if (pImage->GetBPP() == 32 ) //确认该图像包含Alpha通道
	{
		int i = 0;
		int j = 0;
		for ( i=0; i < pImage->GetWidth(); i++ )
		{
			for ( j=0; j < pImage->GetHeight(); j++ )
			{
				byte *pByte = (byte *)pImage->GetPixelAddress(i, j);
				pByte[0] = pByte[0] * pByte[3] / 255;
				pByte[1] = pByte[1] * pByte[3] / 255;
				pByte[2] = pByte[2] * pByte[3] / 255;
			}
		}
	}
}

/**
* Brief    : TOOL 换字体
* Param    : 
* Return   : UNCHAR *
*   Date     : 
*   Author   :  
*   Memo     : new
*/
void CCommTools::SetFont(CFont *pfont, long lHeight, CString csFaceName)
{
	LOGFONT logfont;
	logfont.lfHeight = lHeight;
	logfont.lfWeight = 10;
	logfont.lfUnderline = 0;
	logfont.lfStrikeOut = 0;
	logfont.lfWidth= 0;
	logfont.lfEscapement=0;
	logfont.lfOrientation= 0;
	logfont.lfItalic= 0;
	logfont.lfCharSet =134; 
	logfont.lfOutPrecision =3;
	logfont.lfClipPrecision =2; 
	logfont.lfQuality= 1;
	logfont.lfPitchAndFamily =2; 

#ifdef UNICODE
	wcscpy(logfont.lfFaceName, csFaceName); 
#else
	strcpy(logfont.lfFaceName, csFaceName); 
#endif
	

	pfont->Detach();
	pfont->CreateFontIndirect(&logfont);
}

char* CCommTools::EncodeToUTF8(const char* mbcsStr) 
{ 
	wchar_t*  wideStr; 
	char*   utf8Str; 
	int   charLen; 

	charLen = MultiByteToWideChar(CP_UTF8, 0, mbcsStr, -1, NULL, 0); 
	wideStr = (wchar_t*) malloc(sizeof(wchar_t)*charLen); 
	MultiByteToWideChar(CP_ACP, 0, mbcsStr, -1, wideStr, charLen); 

	charLen = WideCharToMultiByte(CP_UTF8, 0, wideStr, -1, NULL, 0, NULL, NULL); 

	utf8Str = (char*) malloc(charLen);

	WideCharToMultiByte(CP_UTF8, 0, wideStr, -1, utf8Str, charLen, NULL, NULL);


	free(wideStr); 
	return utf8Str;
} 

char* CCommTools::WTUTF8(CString csBuffer) 
{ 
	char*   utf8Str; 
	int   charLen; 

	charLen = WideCharToMultiByte(CP_UTF8, 0, csBuffer, -1, NULL, 0, NULL, NULL); 
	utf8Str = (char*) malloc(charLen);
	WideCharToMultiByte(CP_UTF8, 0, csBuffer, -1, utf8Str, charLen, NULL, NULL);

	return utf8Str;
} 

char* CCommTools::WTA(CString csBuffer) 
{ 
	int size=WideCharToMultiByte(CP_ACP,0,csBuffer,-1,NULL,0,NULL,NULL); 
	char *ch=new char[size+1]; 
	WideCharToMultiByte(CP_ACP,0,csBuffer,-1,ch,size,NULL,NULL);

	return ch;
} 

//char* CCommTools::EncodeToUTF8(const char* mbcsStr) 
//{ 
//	wchar_t*  wideStr; 
//	char*   utf8Str; 
//	int   charLen; 
//
//	charLen = MultiByteToWideChar(CP_UTF8, 0, mbcsStr, -1, NULL, 0); 
//	wideStr = (wchar_t*) malloc(sizeof(wchar_t)*charLen); 
//	MultiByteToWideChar(CP_ACP, 0, mbcsStr, -1, wideStr, charLen); 
//
//	charLen = WideCharToMultiByte(CP_UTF8, 0, wideStr, -1, NULL, 0, NULL, NULL); 
//
//	utf8Str = (char*) malloc(charLen);
//
//	WideCharToMultiByte(CP_UTF8, 0, wideStr, -1, utf8Str, charLen, NULL, NULL);
//
//
//	free(wideStr); 
//	return utf8Str;
//} 