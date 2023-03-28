#pragma once

class INet;
class INetmediator {
public:
	INetmediator() {};
	virtual ~INetmediator() {};
	//������
	virtual bool OpenNet() = 0;
	//��������
	virtual bool SendData(long lSendIP, char* buf, int nlen) = 0;
	//�ر�����
	virtual void CloseNet() = 0;
	//��������
	virtual void DealData(char* buf, int nlen) = 0;

protected:
	INet* m_pNet;
};