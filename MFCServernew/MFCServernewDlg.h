
// MFCServernewDlg.h: 头文件
//

#pragma once
#include "afxsock.h"

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
	CServerSocket m_socket;
};

class CServerSocket : public CSocket
{
public:
	CServerSocket(CMFCServernewDlg* dlg = NULL);
	virtual ~CServerSocket();
	// 接受到客户端连接的 回调函数
	virtual void OnAccept(int nErrorCode);
	// 关闭所有连接套接字
	void CloseAllConn();
private:
	CMFCServernewDlg* m_dlg;
	//list<CConnSocket*> m_clientList;

};
