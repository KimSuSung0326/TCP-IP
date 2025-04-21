#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<stdio.h>
#include <winsock2.h>// window 운영체계에서 소켓을 사용하기 위해
#pragma comment(lib, "ws2_32.lib") //bind, connect 등 과 같은 코드를 사용하기 위해

int main() {
	// socket 설정 및 오픈
	WSADATA wsaData;//소캣 정보 초기화
	SOCKET sock, clisock; // 소켓 핸들 값 저장 clisock 은 클라이언트 쪽 저장 하기 위한 소켓
	SOCKADDR_IN servAddr, cliAddr;// 소캣 ip, 포트 정보 저장

	WSAStartup(MAKEWORD(2, 2), &wsaData);// 윈도우 소켓 초기화  WSAStartup(사용 버전, 초기화 포인터);

	sock = socket(AF_INET, SOCK_STREAM, 0);// socket(통신영역, 소켓 서비스 타입, 소켓 프로토콜) , 소캣 생성

	if (sock < 0) {
		printf("sock open error\n");
		WSACleanup();
		return 1;
	}
	else {
		printf("sock open\n");
	}
	servAddr.sin_family = AF_INET; //  서버 주소 구조체에서 사용되는 주소 체계
	servAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // 서버 IP 설정
	servAddr.sin_port = htons(12345);                  // 서버 포트 설정

	// bind  // bind() 함수로 내가 운영하려는 서비스의 IP 주소와 포트를 소켓에 할당해 주어 클라이언트가 접속할 수 있도록 프로세스를 특정 포트로 고정
	if (bind(sock, (SOCKADDR*)&servAddr, sizeof(servAddr)) < 0) {
		printf("fail to client bind\n");
	}
	else {
		printf("success bind\n");
	}
	// listen //  서버를 대기 상태로 만들어 주어 누가 접속을 시도하려고 할 때 곧바로 응답할 수 있도록 설정
	listen(sock, 1); // 서버 대기 상태로 만들기 1개만 연결

	//accept // 클라이언트로부터 connect()가 발생했을 때 클라이언트의 요청을 승인하여 연결을 맺는 과정
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