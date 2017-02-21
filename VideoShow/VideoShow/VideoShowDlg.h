
// VideoShowDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CVideoShowDlg 对话框
class CVideoShowDlg : public CDialogEx
{
// 构造
public:
	CVideoShowDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_VIDEOSHOW_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	CNiceSliderCtrl m_Slider;

	CRect m_dlgRect;
	libvlc_time_t m_TotalTime;
	UINT_PTR m_playerTimer;
	CCommTools m_tools;
	CVlcPlay   m_cPlayer;       
	BOOL           m_bFullScreen;     // 全屏标志  
	CRect           m_FullScreenRect;  // 整个屏幕尺寸  
	WINDOWPLACEMENT m_OldWndPlacement; // 全屏时对话框的位置属性  
	WINDOWPLACEMENT m_NewWndPlacement; // 全屏后对话框的位置属性 
	CRect			m_Audiorect;

public:
	afx_msg void OnBnClickedBtnVideoOpenfile();
protected:
	COwnerListBox m_List;
	CFont m_font;
	CNiceSliderCtrl m_SliderVoice;
public:
	afx_msg void OnBnClickedBtnVideoPlay();
	afx_msg void OnBnClickedBtnVideoSpeenLeft();
	afx_msg void OnBnClickedBtnVideoSpeenRight();
	afx_msg void OnBnClickedBtnVideoAllsceen();
	afx_msg void OnBnClickedBtnVideoList();
	void ShowPlaylist( BOOL bShow);
	void DealCtrlShow(int iMode);
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	virtual void OnCancel();
	virtual void OnOK();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void NormalShow(void);
	afx_msg void OnLbnDblclkListPlay();
//	afx_msg void OnStnDblclickStaPlay();
	afx_msg void OnStnClickedStaPlay();
	afx_msg void OnBnClickedBtnOpenurlOpen();

	void ShowURL(BOOL bShow);
protected:
	CStatic m_staURL;
public:
	afx_msg void OnBnClickedBtnOpenurl();

	void LoadPlaylist();
	void SavePlaylist();
	void DealRMenu(CListBox *pList);
	void  CVideoShowDlg::AddMessage(CString csMessage);

	CString m_csMessage;
	int m_iBGChange;
	afx_msg void OnMenuRListOpen();
	afx_msg void OnMenuRListDelete();
	afx_msg void OnMenuRListCopy();
	afx_msg void OnMenuRListClear();
	afx_msg void OnBnClickedBtnSnapshot();
	afx_msg void OnBnClickedBtnMute();
};
