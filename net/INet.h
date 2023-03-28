#pragma once
#include<WinSock2.h>
#include<iostream>
using namespace std;

#pragma comment(lib,"Ws2_32.lib")

class INetmediator;//������һ��INetmediator���࣬����Ҫ����ͷ�ļ�
class INet {
public:
	INet() {};
	virtual ~INet() {};//ʹ��ʱ������ָ��ָ�����������Ҫʹ��������
	//��ʼ������
	virtual bool InitNet() = 0;
	//�ر�����
	virtual void UninitNet() = 0;
	//��������
	virtual bool SendData(long lSendIP, char* buf,int nlen) = 0;
protected:
	//��������
	virtual bool RecvData() = 0;
	INetmediator* m_pMediator;
};
