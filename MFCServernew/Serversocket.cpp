#pragma once
#include "stdafx.h"
#include "MFCServernewDlg.h"
#include "ServerSocket.h"
#include"MFCServernew.h"


ServerSocket::ServerSocket(CMFCServernewDlg* dlg)
{
	m_dlg = dlg;
}

ServerSocket::~ServerSocket()
{
}



// 新的连接请求来了，该函数将被回调
void ServerSocket::OnAccept(int nErrorCode)//通知侦听套接字，它可以通过调用Accept，接受挂起连接请求
{
	ConnectSocket * client = new ConnectSocket(m_dlg);
	SOCKADDR_IN addr;
	memset(&addr, 0, sizeof(addr));
	int addrLen = sizeof(addr);

	// 获取通信套接字
	Accept(*client, (SOCKADDR*)&addr, &addrLen);
	char* ip = inet_ntoa(addr.sin_addr);
	client->SetClientAddr(CString(ip), addr.sin_port);
	m_clientList.push_back(client);

	// 界面添加连接消息
	CString msg;
	SYSTEMTIME t;//时间信息
	GetLocalTime(&t);
	msg.Format(_T("[%d:%d:%d] %s:%d: Connect Success!"), t.wHour, t.wMinute, t.wSecond, CString(ip), addr.sin_port);
	m_dlg->AddMsg(msg);//消息信息

	CSocket::OnAccept(nErrorCode); ILC_HIGHQUALITYSCALE;
}

void ServerSocket::CloseAllConn()// 关闭监听套接字
{
	// 先关闭 连接的套接字
	list<ConnectSocket*>::iterator it;//list链表
	for (it = m_clientList.begin(); it != m_clientList.end(); it++)
	{
		(*it)->Close();
		delete (*it);
		it = m_clientList.erase(it);
	}
}