
// MFCServernewDlg.h: 头文件
//

#pragma once
#include "afxsock.h"
#include "ConnectSocket.h"
#include "Serversocket.h"

// CMFCServernewDlg 对话框
class CMFCServernewDlg : public CDialogEx
{
// 构造
public:
	CMFCServernewDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCSERVERNEW_DIALOG };
#endif

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
public:
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonStop();
	int m_port;
	CButton m_start;
	CButton m_stop;
	ServerSocket m_socket;
	void AddMsg(CString msg);
	afx_msg void OnBnClickedButtonClean();
	CListCtrl m_listCtrl;
};