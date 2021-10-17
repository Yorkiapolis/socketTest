#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <io_utils.h>
#include <tinycthread.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define QUEUEBUFFER 16
#define RECVBUF 512

typedef int SockDes;
typedef struct {
    struct sockaddr_in cliaddr;
    SockDes _sock;
    void (*callback)(const char *);
} ComCliaddr;


int Process_T(const ComCliaddr *cliaddrArg){
    char buf[RECVBUF];
    char *cliaddr = inet_ntoa(cliaddrArg->cliaddr.sin_addr);
    while (1){
        ssize_t _recvLen = read(cliaddrArg->_sock, buf,RECVBUF-1);
        if(_recvLen > 0){
            buf[_recvLen] = '\0';
            PRINTLNF("receive from client@[%s]: %s", cliaddr, buf);
            thrd_sleep(&(struct timespec){.tv_sec=2,}, NULL);
            write(cliaddrArg->_sock, buf, strlen(buf));
        }else if(_recvLen == EOF){
            cliaddrArg->callback(cliaddr);
            break;
        } else{
            PRINTLNF("\rread error[%ld]", _recvLen);
            break;
        }
    }
    return 0;
}

void SockCloseCallback(const char *cliaddr){
    PRINTLNF("\rCLient@[%s] is closed", cliaddr);
}

int main() {
    struct sockaddr_in servSockAddr = {
            .sin_family = AF_INET,
            .sin_port = htons(1033),
            .sin_addr = htonl(INADDR_ANY),
    };
    memset(&servSockAddr.sin_zero, 0,
           sizeof(servSockAddr.sin_zero));

    SockDes _sock = socket(AF_INET,
                          SOCK_STREAM, IPPROTO_IP);
    int bindRes = bind(_sock, (struct sockaddr *)&servSockAddr,
            sizeof(servSockAddr));
    if (bindRes != 0){
        perror("");
        PRINTLNF("\rbind failed, error[%d] occurs", bindRes);
        exit(-1);
    }

    listen(_sock, QUEUEBUFFER);  // what if exceed the queue buffer size??

    for(;;){
        struct sockaddr_in cliaddr;
        ComCliaddr cliaddrArg;
        unsigned int cliaddr_len = sizeof(cliaddr);
        PRINTLNF("Server@[%s] is waiting for connections...",
                 inet_ntoa(servSockAddr.sin_addr));
        SockDes _sockCLient = accept(_sock, (struct sockaddr *)&cliaddr,
                &cliaddr_len);
        if(_sockCLient == -1){
            PRINTLNF("the acception from [%s] is failed",
                     inet_ntoa(cliaddr.sin_addr));
            continue;
        }
        cliaddrArg.cliaddr = cliaddr;
        cliaddrArg._sock = _sockCLient;
        cliaddrArg.callback = SockCloseCallback;
        thrd_t pro_t;
        thrd_create(&pro_t, (thrd_start_t) Process_T, &cliaddrArg);
        thrd_detach(pro_t);
    }
    return 0;
}
