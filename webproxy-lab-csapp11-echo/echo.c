#include "csapp.h"  /* CS:APP 래퍼 API와 상수(MAXLINE, rio_t 등). */

/*
 * echo - 클라이언트가 연결을 닫을 때까지 텍스트 라인을 읽고 그대로 되돌려 보낸다.
 */
void echo(int connfd)
{ /* 하나의 연결된 클라이언트 소켓에 대한 echo 핸들러 시작. */
    size_t n;            /* 한 줄을 읽을 때 클라이언트에서 읽은 바이트 수. */
    char buf[MAXLINE];   /* 수신 및 에코 전송에 사용할 라인 버퍼. */
    rio_t rio;           /* connfd에 바인딩된 robust I/O 버퍼 상태. */

    Rio_readinitb(&rio, connfd);                 /* connfd용 robust 버퍼 리더 초기화. */
    while ((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0) { /* EOF(0)까지 텍스트 한 줄씩 읽기. */
        printf("server received %zu bytes\n", n);          /* 클라이언트에서 받은 바이트 수 로그 출력. */
        Rio_writen(connfd, buf, n);                        /* 받은 바이트를 그대로 다시 전송(echo). */
    } /* 클라이언트가 연결을 닫거나 EOF에 도달하면 루프 종료. */
} /* echo 핸들러 종료; connfd는 호출자가 닫는다. */
