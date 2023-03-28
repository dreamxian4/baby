#pragma once
#include"INet.h"

class UDPnet : public INet {
public:
	UDPnet();
	UDPnet(INetmediator* p);
	~UDPnet();//ʹ��ʱ������ָ��ָ�����������Ҫʹ��������
   //��ʼ������
	bool InitNet();
	//�ر�����
	void UninitNet();
	//��������
	bool SendData(long lSendIP, char* buf, int nlen);
protected:
	static unsigned int _stdcall recvthread(LPVOID p);
	//��������
	bool RecvData();
	SOCKET m_sock;
	HANDLE handle;
	bool m_isstop;
};
