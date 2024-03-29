#pragma once

class INet;
class INetmediator {
public:
	INetmediator() {};
	virtual ~INetmediator() {};
	//打开网络
	virtual bool OpenNet() = 0;
	//发送数据
	virtual bool SendData(long lSendIP, char* buf, int nlen) = 0;
	//关闭网络
	virtual void CloseNet() = 0;
	//处理数据
	virtual void DealData(char* buf, int nlen) = 0;

protected:
	INet* m_pNet;
};