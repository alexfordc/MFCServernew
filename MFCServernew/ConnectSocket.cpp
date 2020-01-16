#pragma once
#include "stdafx.h"
#include "MFCServernewDlg.h"
#include "ServerSocket.h"
#include"ConnectSocket.h"

ConnectSocket::ConnectSocket(CMFCServernewDlg* dlg)
{
	m_dlg = dlg;
}

ConnectSocket::~ConnectSocket()
{
}


// ���������Ϳͻ��˳ɹ����������ӣ����������Զ����ô˺���
void ConnectSocket::OnSend(int nErrorCode)
{
	// �������ɿ�ܵ��ã�֪ͨ�׽������ڿ��Ե���Send��Ա�������������ˡ�
	char buf[] = "your connect success";
	Send(buf, strlen(buf)); //���ͻ��˷�����Ϣ
	CSocket::OnSend(nErrorCode);
}

// ���Է�������Ϣ���Զ����ô˺���
// �����ں������������մ���
// ֪ͨ�׽��ֻ����������ݣ����Ե���Receive��Ա����ȡ��
void ConnectSocket::OnReceive(int nErrorCode)
{
	char recvBuf[512] = { 0 };
	int recvLen = this->Receive(recvBuf, sizeof(recvBuf));//ȡ������
	CString msg;
	SYSTEMTIME t;
	GetLocalTime(&t);
	msg.Format(_T("[%d:%d:%d] %s:%d: %s"), t.wHour, t.wMinute, t.wSecond, m_ip, m_port, CString(recvBuf));
	m_dlg->AddMsg(msg);
	// ������Ϣ
	CharUpperA(recvBuf);
	this->Send(recvBuf, strlen(recvBuf));
}

// �Է������Ͽ����ӣ��Զ����ô˺�����֪ͨ�׽��֣��رն������׽�������
void ConnectSocket::OnClose(int nErrorCode)
{
	CString msg;
	SYSTEMTIME t;
	GetLocalTime(&t);
	msg.Format(_T("[%d:%d:%d] %s:%d: already close!"), t.wHour, t.wMinute, t.wSecond, m_ip, m_port);
	m_dlg->AddMsg(msg);
	CSocket::OnClose(nErrorCode);
}

void ConnectSocket::SetClientAddr(CString ip, USHORT port)
{
	m_ip = ip;
	m_port = port;
}
