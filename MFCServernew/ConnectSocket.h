#pragma once
#include "afxsock.h"
#include <list>
#include"ConnectSocket.h"
#include"MFCServernewDlg.h"
using namespace std;
class CMFCServernewDlg;
class ConnectSocket : public CSocket
{
public:
	ConnectSocket(CMFCServernewDlg* dlg = NULL);
	virtual ~ConnectSocket();
	virtual void OnSend(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	// 设置连接的客户端的IP和端口
	void SetClientAddr(CString ip, USHORT port);
private:
	CString m_ip;
	UINT m_port;
	CMFCServernewDlg* m_dlg;
};