#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<stdio.h>
#include <winsock2.h>// window 운영체계에서 소켓을 사용하기 위해
#pragma comment(lib, "ws2_32.lib") //bind, connect 등 과 같은 코드를 사용하기 위해

//변수 DEFINE
#define BUFSIZE 1024
// main 함수
int main() {
	//winsocket 정보 초기화
	WSADATA wsaData;//소캣 정보 초기화
	SOCKET sock; // 소켓 핸들 값 저장
	SOCKADDR_IN servAddr;// 소캣 ip, 포트 정보 저장

	WSAStartup(MAKEWORD(2, 2), &wsaData);// 윈도우 소켓 초기화  WSAStartup(사용 버전, 초기화 포인터);


	// socket open 함수
	sock = socket(AF_INET,SOCK_STREAM,0);// socket(통신영역, 소켓 서비스 타입, 소켓 프로토콜) , 소캣 생성

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

	char* cliip = inet_ntoa(servAddr.sin_addr);
	int cliport = ntohs(servAddr.sin_port);

	printf("connected clint IP is %s, Port is %05d\n", cliip, cliport);

	// connect 기능
	if (connect(sock, (SOCKADDR*)&servAddr, sizeof(servAddr)) < 0){ // 서버 연결 connect(소켓핸들, 소캔 정보, 소캣 정보 구조체 크기)
		printf("connect fail\n");
		printf("Connection failed. Error: %d\n", WSAGetLastError());
		closesocket(sock);
		WSACleanup();
	}
	else {
		printf("connect success!\n");
		
	}
	
	// read, write 기능
	char buf[BUFSIZE] = {0,}; // 서버로부터 받아와서 저장할 배열
	char name_buf[10] = {"kim"};

	send(sock, name_buf, strlen(name_buf), 0);

	int recv_result1 = recv(sock, buf, sizeof(buf), 0);
	if (recv_result1 > 0) {
		printf("KIM의 학번은 %s 입니다.", buf);
	}
	else {
		printf("서버로부터 데이터를 받아오지 못함");
	}
	
	// close 기능
	return 0;
}
