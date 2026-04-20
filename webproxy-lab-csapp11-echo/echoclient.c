#include "csapp.h"  /* 클라이언트 소켓 및 robust I/O용 CS:APP 래퍼. */

int main(int argc, char **argv)
{ /* 대화형 echo 클라이언트의 진입점. */
    int clientfd;                    /* echo 서버에 연결된 소켓 디스크립터. */
    char *host, *port, buf[MAXLINE]; /* 서버 호스트/포트 인자와 I/O 버퍼. */
    rio_t rio;                       /* 서버 읽기를 위한 robust 버퍼 I/O 상태. */

    if (argc != 3) {                                  /* 서버 호스트와 포트 인자가 필요하다. */
        fprintf(stderr, "usage: %s <host> <port>\n", argv[0]); /* 올바른 사용법 출력. */
        exit(1);                                      /* 실행 인자가 잘못되면 종료. */
    } /* 인자 검증 끝. */

    host = argv[1];                                   /* argv에서 대상 호스트명/IP 읽기. */
    port = argv[2];                                   /* argv에서 대상 TCP 포트 읽기. */

    clientfd = Open_clientfd(host, port);             /* echo 서버로 TCP 연결 열기. */
    Rio_readinitb(&rio, clientfd);                    /* 연결 소켓 기반 버퍼 리더 준비. */

    while (Fgets(buf, MAXLINE, stdin) != NULL) {      /* 터미널 입력에서 한 줄씩 반복해서 읽기. */
        Rio_writen(clientfd, buf, strlen(buf));       /* 입력한 줄을 서버로 전송. */
        if (Rio_readlineb(&rio, buf, MAXLINE) == 0) { /* echo 응답 한 줄 읽기; 0이면 서버가 종료. */
            break;                                     /* 연결 종료/EOF 시 루프 탈출. */
        } /* 서버 종료 체크 끝. */
        Fputs(buf, stdout);                            /* echo로 돌아온 응답을 터미널에 출력. */
    } /* 대화형 요청/응답 루프 종료. */

    Close(clientfd);                                   /* 프로세스 종료 전에 소켓 닫기. */
    return 0;                                          /* 성공 상태 코드 반환. */
} /* 클라이언트 프로그램 끝. */
