#pragma once
#include"INetMediator.h"

class INet;
class UDPmediator :public INetmediator {
public:
	UDPmediator();
	 ~UDPmediator();
	virtual bool OpenNet();
	virtual bool SendData(long lSendIP, char* buf, int nlen);
	virtual void CloseNet();
	virtual void DealData(char* buf, int nlen);

protected:
	INet* m_pNet;
};