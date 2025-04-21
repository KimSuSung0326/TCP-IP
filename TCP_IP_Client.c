#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<stdio.h>
#include <winsock2.h>// window �ü�迡�� ������ ����ϱ� ����
#pragma comment(lib, "ws2_32.lib") //bind, connect �� �� ���� �ڵ带 ����ϱ� ����

//���� DEFINE
#define BUFSIZE 1024
// main �Լ�
int main() {
	//winsocket ���� �ʱ�ȭ
	WSADATA wsaData;//��Ĺ ���� �ʱ�ȭ
	SOCKET sock; // ���� �ڵ� �� ����
	SOCKADDR_IN servAddr;// ��Ĺ ip, ��Ʈ ���� ����

	WSAStartup(MAKEWORD(2, 2), &wsaData);// ������ ���� �ʱ�ȭ  WSAStartup(��� ����, �ʱ�ȭ ������);


	// socket open �Լ�
	sock = socket(AF_INET,SOCK_STREAM,0);// socket(��ſ���, ���� ���� Ÿ��, ���� ��������) , ��Ĺ ����

	if (sock < 0) {
		printf("sock open error\n");
		WSACleanup();
		return 1;
	}
	else {
		printf("sock open\n");
	}

	servAddr.sin_family = AF_INET; //  ���� �ּ� ����ü���� ���Ǵ� �ּ� ü��
	servAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // ���� IP ����
	servAddr.sin_port = htons(12345);                  // ���� ��Ʈ ����

	char* cliip = inet_ntoa(servAddr.sin_addr);
	int cliport = ntohs(servAddr.sin_port);

	printf("connected clint IP is %s, Port is %05d\n", cliip, cliport);

	// connect ���
	if (connect(sock, (SOCKADDR*)&servAddr, sizeof(servAddr)) < 0){ // ���� ���� connect(�����ڵ�, ��ĵ ����, ��Ĺ ���� ����ü ũ��)
		printf("connect fail\n");
		printf("Connection failed. Error: %d\n", WSAGetLastError());
		closesocket(sock);
		WSACleanup();
	}
	else {
		printf("connect success!\n");
		
	}
	
	// read, write ���
	char buf[BUFSIZE] = {0,}; // �����κ��� �޾ƿͼ� ������ �迭
	char name_buf[10] = {"kim"};

	send(sock, name_buf, strlen(name_buf), 0);

	int recv_result1 = recv(sock, buf, sizeof(buf), 0);
	if (recv_result1 > 0) {
		printf("KIM�� �й��� %s �Դϴ�.", buf);
	}
	else {
		printf("�����κ��� �����͸� �޾ƿ��� ����");
	}
	
	// close ���
	return 0;
}
