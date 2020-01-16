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



// �µ������������ˣ��ú��������ص�
void ServerSocket::OnAccept(int nErrorCode)//֪ͨ�����׽��֣�������ͨ������Accept�����ܹ�����������
{
	ConnectSocket * client = new ConnectSocket(m_dlg);
	SOCKADDR_IN addr;
	memset(&addr, 0, sizeof(addr));
	int addrLen = sizeof(addr);

	// ��ȡͨ���׽���
	Accept(*client, (SOCKADDR*)&addr, &addrLen);
	char* ip = inet_ntoa(addr.sin_addr);
	client->SetClientAddr(CString(ip), addr.sin_port);
	m_clientList.push_back(client);

	// �������������Ϣ
	CString msg;
	SYSTEMTIME t;//ʱ����Ϣ
	GetLocalTime(&t);
	msg.Format(_T("[%d:%d:%d] %s:%d: Connect Success!"), t.wHour, t.wMinute, t.wSecond, CString(ip), addr.sin_port);
	m_dlg->AddMsg(msg);//��Ϣ��Ϣ

	CSocket::OnAccept(nErrorCode); ILC_HIGHQUALITYSCALE;
}

void ServerSocket::CloseAllConn()// �رռ����׽���
{
	// �ȹر� ���ӵ��׽���
	list<ConnectSocket*>::iterator it;//list����
	for (it = m_clientList.begin(); it != m_clientList.end(); it++)
	{
		(*it)->Close();
		delete (*it);
		it = m_clientList.erase(it);
	}
}