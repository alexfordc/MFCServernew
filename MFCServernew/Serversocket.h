#pragma once
//#define _WINSOCK_DEPRECATED_NO_WARNINGS 1
//#include  "ConnSocket.h"
#include "afxsock.h"
#include <list>
#include"ConnectSocket.h"
#include"MFCServernewDlg.h"
using namespace std;
// CServerSocket ����Ŀ��
class CMFCServernewDlg;
class ServerSocket : public CSocket
{
public:
	ServerSocket(CMFCServernewDlg* dlg = NULL);
	virtual ~ServerSocket();
	// ���ܵ��ͻ������ӵ� �ص�����
	virtual void OnAccept(int nErrorCode);
	// �ر����������׽���
	void CloseAllConn();
private:
	CMFCServernewDlg* m_dlg;
	list<ConnectSocket*> m_clientList;
};