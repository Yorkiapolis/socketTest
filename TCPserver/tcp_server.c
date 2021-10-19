//
// Created by york on 2021/10/19.
//
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <io_utils.h>
#include <tinycthread.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdatomic.h>

#define QUEUEBUFFER 16
#define RECVBUF 512
#define ECHO_SERVICE_PORT (unsigned short)1035
#define DEBUG 0

typedef __int32_t SockDes;

typedef struct ComCliaddr{
    struct sockaddr_in cliaddr;
    SockDes _sock;

    void (*callback)(const char *, SockDes);
} ComCliaddr;

static atomic_int clientNum = 0;

int Process_T(ComCliaddr *cliaddrArg) {
    char buf[RECVBUF];
    char *cliaddr = inet_ntoa(cliaddrArg->cliaddr.sin_addr);
    while (1) {
        ssize_t _recvLen = read(cliaddrArg->_sock, buf, RECVBUF - 1);
        if (_recvLen > 0) {
            buf[_recvLen] = '\0';
            PRINTLNF("receive from client@[%s:%hu]: %s", cliaddr,
                     ntohs(cliaddrArg->cliaddr.sin_port),buf);
            fflush(stdout);
            thrd_sleep(&(struct timespec) {.tv_sec=2,}, NULL);

            write(cliaddrArg->_sock, buf, strlen(buf));
        } else if (_recvLen == 0) {
            clientNum--;
            cliaddrArg->callback(cliaddr, cliaddrArg->_sock);
            free(cliaddrArg);
            break;
        } else {
            PRINTLNF("\rread error[%ld]", _recvLen);
            break;
        }
    }
    return 0;
}

void SockCloseCallback(const char *cliaddr, SockDes _sktCLosed) {
    close(_sktCLosed);
    PRINTLNF("\rCLient@[%s] is closed", cliaddr);
    printf("************************************\n");
    PRINTLNF("Current connected user quantity: %d", clientNum);
    printf("************************************\n");
}

int main(int argc, char **argv) {
    if(argc != 2){
        fputs("Argument Error\n"
              "Please refer to the Usage --> <Server IP>", stderr);
        exit(-1);
    }

    struct sockaddr_in servSockAddr = {
            .sin_family = AF_INET,
            .sin_port = htons(ECHO_SERVICE_PORT),
            .sin_addr = inet_addr(argv[1]),
    };
    memset(&servSockAddr.sin_zero, 0,
           sizeof(servSockAddr.sin_zero));

    SockDes _sock = socket(AF_INET,
                           SOCK_STREAM, IPPROTO_IP);
    if (_sock < 0) {
        perror("sock");
        PRINTLNF("creating server-side socket failed");
        exit(-1);
    }

    int bindRes = bind(_sock, (struct sockaddr *) &servSockAddr,
                       sizeof(servSockAddr));
    if (bindRes != 0) {
        perror("bind");
        PRINTLNF("\rbind failed, error[%d] occurs", bindRes);
        exit(-1);
    }

    int listenRes = listen(_sock, QUEUEBUFFER);  // what if exceed the queue buffer size??
    if (listenRes < 0) {
        perror("listen");
        PRINTLNF("\rlisten failed, error[%d] occurs", listenRes);
        exit(-1);
    }

    PRINTLNF("Server@[%s:%hu] is waiting for connections...",
             inet_ntoa(servSockAddr.sin_addr), ECHO_SERVICE_PORT);

    for (;;) {
        struct sockaddr_in cliaddr;

        unsigned int cliaddr_len = sizeof(cliaddr);
        SockDes _sockClient = accept(_sock, (struct sockaddr *) &cliaddr,
                                     &cliaddr_len);
        if (_sockClient == -1) {
            PRINTLNF("the acceptation from [%s] is failed",
                     inet_ntoa(cliaddr.sin_addr));
            continue;
        }
        ComCliaddr *cliaddrArg = malloc(sizeof(ComCliaddr));
        clientNum++;
        PRINTLNF("connection with client@[%s:%hu] established",
                 inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));
        printf("************************************\n");
        PRINTLNF("Current connected user quantity: %d", clientNum);
        printf("************************************\n");

        cliaddrArg->cliaddr = cliaddr;
        cliaddrArg->_sock = _sockClient;
        cliaddrArg->callback = SockCloseCallback;

        thrd_t pro_t;
        thrd_create(&pro_t, (thrd_start_t) Process_T, cliaddrArg);
        thrd_detach(pro_t);
#if DEBUG
        break;
#endif
    }
    close(_sock);
    return 0;
}