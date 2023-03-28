#pragma once 

#define _DEF_UDP_PORT (12345)
#define _DEF_BUFFER_SIZE (4096)
#define _DEF_NAME_SIZE (60)
#define _DEF_CONTENT_SIZE (1024)

//Э��ͷ
#define _DEF_PROTOCAL_BASE (1000)
//UDPЭ��ͷ
//����
#define _DEF_PROTOCAL_ONLINE_RQ (_DEF_PROTOCAL_BASE+1)
#define _DEF_PROTOCAL_ONLINE_RS (_DEF_PROTOCAL_BASE+2)
//����
#define _DEF_PROTOCAL_OFFLINE_RQ (_DEF_PROTOCAL_BASE+3)
//����
#define _DEF_PROTOCAL_CHAT_RQ (_DEF_PROTOCAL_BASE+4)
//���ļ�
#define _DEF_PROTOCAL_FILEINFO_RQ (_DEF_PROTOCAL_BASE+5)

//UDPЭ��
//����ṹ��
//����֪ͨ���Լ���IP �ҵ�������
//���߻ظ����Լ���IP �ҵ�������
struct STRU_ONLINE {
	STRU_ONLINE():nType(_DEF_PROTOCAL_ONLINE_RQ){
		memset(szName, 0, _DEF_NAME_SIZE);
	}
	int nType;
	//long ip;
	char szName[_DEF_NAME_SIZE];
};

//����֪ͨ���Լ���IP
struct STRU_OFFLINE_RQ {
	STRU_OFFLINE_RQ() :nType(_DEF_PROTOCAL_OFFLINE_RQ) {

	}
	int nType;
};

//���������������ݡ��Լ���IP
struct STRU_CHAT_RQ {
	STRU_CHAT_RQ():nType(_DEF_PROTOCAL_CHAT_RQ){
		memset(szContent, 0, _DEF_CONTENT_SIZE);
	}
	int nType;
	char szContent[_DEF_CONTENT_SIZE];
};