#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <io_utils.h>
#include <tinycthread.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define QUEUEBUFFER 16
#define RECVBUF 512
#define ECHO_SERVICE_PORT 1035
#define DEBUG 0

mtx_t mutex;

typedef int SockDes;
typedef struct {
    struct sockaddr_in cliaddr;
    SockDes _sock;

    void (*callback)(const char *, SockDes);
} ComCliaddr;

int Process_T(const ComCliaddr *cliaddrArg) {
    char buf[RECVBUF];
    char *cliaddr = inet_ntoa(cliaddrArg->cliaddr.sin_addr);
    while (1) {
        ssize_t _recvLen = read(cliaddrArg->_sock, buf, RECVBUF - 1);
        if (_recvLen > 0) {
            buf[_recvLen] = '\0';
            PRINTLNF("receive from client@[%s]: %s", cliaddr, buf);
            fflush(stdout);
            thrd_sleep(&(struct timespec) {.tv_sec=2,}, NULL);

            write(cliaddrArg->_sock, buf, strlen(buf));
        } else if (_recvLen == 0) {
            cliaddrArg->callback(cliaddr, cliaddrArg->_sock);
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
}

int main() {
    struct sockaddr_in servSockAddr = {
            .sin_family = AF_INET,
            .sin_port = htons(ECHO_SERVICE_PORT),
            .sin_addr = htonl(INADDR_LOOPBACK),
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

    PRINTLNF("Server@[%s] is waiting for connections...",
             inet_ntoa(servSockAddr.sin_addr));
    for (;;) {
        struct sockaddr_in cliaddr;
        ComCliaddr cliaddrArg;
        unsigned int cliaddr_len = sizeof(cliaddr);
        SockDes _sockClient = accept(_sock, (struct sockaddr *) &cliaddr,
                                     &cliaddr_len);
        if (_sockClient == -1) {
            PRINTLNF("the acceptation from [%s] is failed",
                     inet_ntoa(cliaddr.sin_addr));
            continue;
        }
        PRINTLNF("connection with client@[%s] established",
                 inet_ntoa(cliaddr.sin_addr));
        cliaddrArg.cliaddr = cliaddr;
        cliaddrArg._sock = _sockClient;
        cliaddrArg.callback = SockCloseCallback;
        thrd_t pro_t;
        thrd_create(&pro_t, (thrd_start_t) Process_T, &cliaddrArg);
        thrd_detach(pro_t);

#if DEBUG
        break;
#endif
    }
    close(_sock);
    return 0;
}