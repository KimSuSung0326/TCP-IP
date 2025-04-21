#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<stdio.h>
#include <winsock2.h>// window �ü�迡�� ������ ����ϱ� ����
#pragma comment(lib, "ws2_32.lib") //bind, connect �� �� ���� �ڵ带 ����ϱ� ����

int main() {
	// socket ���� �� ����
	WSADATA wsaData;//��Ĺ ���� �ʱ�ȭ
	SOCKET sock, clisock; // ���� �ڵ� �� ���� clisock �� Ŭ���̾�Ʈ �� ���� �ϱ� ���� ����
	SOCKADDR_IN servAddr, cliAddr;// ��Ĺ ip, ��Ʈ ���� ����

	WSAStartup(MAKEWORD(2, 2), &wsaData);// ������ ���� �ʱ�ȭ  WSAStartup(��� ����, �ʱ�ȭ ������);

	sock = socket(AF_INET, SOCK_STREAM, 0);// socket(��ſ���, ���� ���� Ÿ��, ���� ��������) , ��Ĺ ����

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

	// bind  // bind() �Լ��� ���� ��Ϸ��� ������ IP �ּҿ� ��Ʈ�� ���Ͽ� �Ҵ��� �־� Ŭ���̾�Ʈ�� ������ �� �ֵ��� ���μ����� Ư�� ��Ʈ�� ����
	if (bind(sock, (SOCKADDR*)&servAddr, sizeof(servAddr)) < 0) {
		printf("fail to client bind\n");
	}
	else {
		printf("success bind\n");
	}
	// listen //  ������ ��� ���·� ����� �־� ���� ������ �õ��Ϸ��� �� �� ��ٷ� ������ �� �ֵ��� ����
	listen(sock, 1); // ���� ��� ���·� ����� 1���� ����

	//accept // Ŭ���̾�Ʈ�κ��� connect()�� �߻����� �� Ŭ���̾�Ʈ�� ��û�� �����Ͽ� ������ �δ� ����
	int addrsize = sizeof(cliAddr);
	clisock = accept(sock, (SOCKADDR*)&cliAddr, &addrsize);
	if (clisock < 0) {
		printf("accept fail\n");
	}
	else {
		printf("accept success\n");
		char* cliip = inet_ntoa(cliAddr.sin_addr);
		int cliport = ntohs(cliAddr.sin_port);

		printf("connected clint IP is %s, Port is %05d\n", cliip, cliport);

		char buf[10] = { 0, };
		int recv_result = recv(clisock, buf, sizeof(buf), 0);
		if (recv_result > 0) {
			printf("Received: %s\n", buf);
			if (strcmp(buf, "kim") ==0) {
				printf("received success");
				char buf[10] = "1758003";
				send(clisock, buf, strlen(buf), 0);
			}
		}
		else {
			printf("recv failed or no data received\n");
		}
	}
	// read or write
	char buf[10] = {0, };
	recv(clisock, buf, sizeof(buf), 0);
	printf("%s",buf);
	//close
	return 0;
}