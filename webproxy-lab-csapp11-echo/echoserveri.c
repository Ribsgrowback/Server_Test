#include "csapp.h"  /* 소켓, 에러 처리, 보조 타입을 위한 CS:APP 래퍼들. */

void echo(int connfd);   /* echo.c에 구현된 Echo 서비스 루틴. */

int main(int argc, char **argv)
{ /* 반복형(iterative) echo 서버의 진입점. */
    int listenfd, connfd;                                /* 리슨 소켓과 accept된 연결 소켓. */
    socklen_t clientlen;                                 /* 클라이언트 주소 구조체 길이. */
    struct sockaddr_storage clientaddr;                  /* 프로토콜 독립 클라이언트 주소 저장용 구조체. */
    char client_hostname[MAXLINE], client_port[MAXLINE]; /* 사람이 읽을 수 있는 클라이언트 호스트/포트 버퍼. */

    if (argc != 2) {                                     /* 인자는 정확히 1개(리슨 포트)여야 한다. */
        fprintf(stderr, "usage: %s <port>\n", argv[0]);  /* 인자가 잘못되면 올바른 사용법 출력. */
        exit(1);                                         /* 잘못된 실행이므로 실패 코드로 종료. */
    } /* 인자 검증 끝. */

    listenfd = Open_listenfd(argv[1]);                   /* 지정된 포트에 리슨 소켓 생성 및 바인드. */
    while (1) {                                          /* 반복형 서버 루프: 한 번에 한 클라이언트 처리. */
        clientlen = sizeof(struct sockaddr_storage);     /* 매 Accept 호출 전에 길이 값 초기화. */
        connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen); /* 새 클라이언트 연결이 올 때까지 대기. */
        Getnameinfo((SA *)&clientaddr, clientlen,        /* 바이너리 클라이언트 주소를 문자열로 변환. */
                    client_hostname, MAXLINE,            /* 클라이언트 호스트명/IP 문자열 출력 버퍼. */
                    client_port, MAXLINE, 0);            /* 클라이언트 포트 문자열 출력 버퍼. */
        printf("Connected to (%s, %s)\n", client_hostname, client_port); /* 접속한 클라이언트 주소 로그 출력. */
        echo(connfd);                                    /* 클라이언트가 닫을 때까지 echo 처리. */
        Close(connfd);                                   /* 연결 소켓 닫고 다음 클라이언트 대기. */
    } /* 정상 동작에서는 종료되지 않음. */
} /* 서버 프로그램 종료 지점. */
