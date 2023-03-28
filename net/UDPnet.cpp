#include "UDPnet.h"
#include"PackDef.h"
#include"UDPmediator.h"
#include<process.h>


UDPnet::UDPnet() {}
UDPnet::~UDPnet() {}

UDPnet::UDPnet(INetmediator* p):m_sock(INVALID_SOCKET), handle(0),m_isstop(false){
	m_pMediator = p;
}

//��ʼ������
bool UDPnet::InitNet()
{
	//1.ѡ��Ŀ--���ؿ�
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD(2, 2);//2.2�汾��
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {//err����0��˵�����سɹ�
		printf("WSAStartup failed with error:%d\n", err);
		system("pause");
		return false;
	}

	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {//�жϰ汾���Ƿ�Ϊ2.2
		printf("Could not find a usable version of Winsock.dll\n");
		UninitNet();
		system("pause");
		return false;
	}

	//2.����--�����׽���
	m_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);//���������ֱ����ipv4��ַ ʹ��udpЭ�� UDPЭ��
	if (m_sock == INVALID_SOCKET) {//��������Ȼ�Ƿ�
		printf("socket function failed with error=%d\n", WSAGetLastError());//��ӡ�����루����->�������->��������룩
		UninitNet();
		system("pause");
		return false;
	}

	//���޹㲥Ȩ��
	BOOL bval = TRUE;
	setsockopt(m_sock, SOL_SOCKET, SO_BROADCAST, (char*)&bval, sizeof(bval));

	//��IP
	sockaddr_in service;
	service.sin_family = AF_INET;
	service.sin_addr.s_addr = INADDR_ANY;//����������
	//inet_addr �ַ���ת����u_long����
	service.sin_port = htons(_DEF_UDP_PORT);//�˿ں�
	err = bind(m_sock, (SOCKADDR*)&service, sizeof(service));
	if (err == SOCKET_ERROR) {
		printf("bind failed with error %d\n", WSAGetLastError());
		UninitNet();
		system("pause");
		return false;
	}

	//TODO:�������� ���������������߳�
	//createThread ����������c++����ʱ�� �������ٿռ䣬���˳��߳�ʱ������տռ�
	//createThread��ExitThreadʱͬʱʹ�õģ�ExitThread������ϵͳ�Զ����õ�
	//_beginthreadex��_endthreadexһ��ʹ�ã�_endthreadex������ϵͳ�Զ����õ�
	//_endthreadex�������Ȼ���c++����ʱ�⺯�����ٵĿռ䣬Ȼ���ٵ���ExitThread�˳��߳�
	handle = (HANDLE)_beginthreadex(NULL, 0,&recvthread ,this , 0, NULL);
	return true;
}

unsigned int _stdcall UDPnet::recvthread(LPVOID p) {
	UDPnet* pthis = (UDPnet*)p;
	pthis->RecvData();
	return 0;
}

//�ر�����
void UDPnet::UninitNet()
{
	//�˳��߳�
	m_isstop = true;
	if (handle) {
		if (WaitForSingleObject(handle, 100) == WAIT_TIMEOUT) {
			TerminateThread(handle,-1);
		}
		CloseHandle(handle);
		handle = NULL;
	}
	//�ر��׽���
	if (m_sock && m_sock != INVALID_SOCKET) {
		closesocket(m_sock);
	}
	WSACleanup();//ж�ؿ�

}
//��������
bool UDPnet::RecvData()
{
	char recvbuf[_DEF_BUFFER_SIZE]="";
	SOCKADDR_IN addrClient;
	int nsize = sizeof(addrClient);
	int nrecvNum;
	m_isstop = false;
	while (!m_isstop) {
		nrecvNum = recvfrom(m_sock, recvbuf, _DEF_BUFFER_SIZE, 0, (sockaddr*)&addrClient, &nsize);
		if (nrecvNum > 0) {
			char* pack = new char[nrecvNum];
			if (pack) {
				memcpy(pack, recvbuf, nrecvNum);
				m_pMediator->DealData(pack, nrecvNum);
			}
		}
		else {
			printf("recvfrom error:%d\n", WSAGetLastError());
		}
	}
	return true;
}
//��������
bool UDPnet::SendData(long lSendIP,char* buf, int nlen)
{
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(_DEF_UDP_PORT);
	addr.sin_addr.S_un.S_addr = lSendIP;
	if (sendto(m_sock, buf, nlen, 0, (sockaddr*)&addr, sizeof(addr))<=0) {
		printf("sendto error��%d\n", WSAGetLastError());
		return false;
	}
	return true;
}


