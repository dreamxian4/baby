#include"UDPmediator.h"
#include"UDPnet.h"

UDPmediator::UDPmediator() {
	m_pNet = new UDPnet(this);
}
UDPmediator::~UDPmediator() {
	if (m_pNet) {
		delete m_pNet;
		m_pNet = nullptr;
	}
}
//������
bool UDPmediator::OpenNet() {
	if (!m_pNet->InitNet()) {
		return false;
	}
	return true;
}
//��������
bool UDPmediator::SendData(long lSendIP, char* buf, int nlen) {
	if (!m_pNet->SendData(lSendIP, buf, nlen)) {
		return false;
	}
	return true;
}
//�ر�����
void UDPmediator::CloseNet() {
	m_pNet->UninitNet();
}
//��������
void UDPmediator::DealData(char* buf, int nlen) {
	//TODO:�����ݷ������Ĵ�����
	cout << buf << endl;
}