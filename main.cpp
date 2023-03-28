#include<iostream>
#include"INetMediator.h"
#include"UDPmediator.h"
#include<WinSock2.h>
using namespace std;

int main() {
	//¿ªÆôÍøÂç
	/*INetmediator *pUdp = new UDPmediator;
	pUdp->OpenNet();
	pUdp->SendData(inet_addr("255.255.255.255"), "hello world", strlen("hello world")+1);
	pUdp->CloseNet();*/
	cout << htonl(192168251);
	system("pause");
	return 0;
}