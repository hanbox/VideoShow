#pragma once
class CCommTools
{
public:
	CCommTools(void);
	~CCommTools(void);

public:
	CString GetLocTime(int iMode = 0);
	void  MajorMap(CImage *pImage);
	void SetFont(CFont *pfont, long lHeight, CString csFaceName);
	char* EncodeToUTF8(const char* mbcsStr);
	char* WTUTF8(CString csBuffer);
	char* WTA(CString csBuffer);
};

