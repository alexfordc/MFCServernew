#pragma once
//#define _WINSOCK_DEPRECATED_NO_WARNINGS 1
//#include  "ConnSocket.h"
#include "afxsock.h"
#include <list>
#include"ConnectSocket.h"
#include"MFCServernewDlg.h"
using namespace std;
// CServerSocket 命令目标
class CMFCServernewDlg;
class ServerSocket : public CSocket
{
public:
	ServerSocket(CMFCServernewDlg* dlg = NULL);
	virtual ~ServerSocket();
	// 接受到客户端连接的 回调函数
	virtual void OnAccept(int nErrorCode);
	// 关闭所有连接套接字
	void CloseAllConn();
private:
	CMFCServernewDlg* m_dlg;
	list<ConnectSocket*> m_clientList;
};