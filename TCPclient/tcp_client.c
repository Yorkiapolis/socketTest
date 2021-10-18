#include <string.h>
#include <stdlib.h>
#include <io_utils.h>
#include <unistd.h>
#include <arpa/inet.h>

#define ECHO_SERVICE_PORT 1035
#define BUFSIZE 512

typedef int SockDes;

int main(int argc, char **argv) {
    const char *arg_ip = "127.0.0.1";
    SockDes _sock = socket(AF_INET, SOCK_STREAM,
                          IPPROTO_IP);
    if(_sock < 0){
        perror("sock");
        PRINTLNF("creating server-side socket failed");
        exit(-1);
    }

    struct sockaddr_in servCLient = {
            .sin_family = AF_INET,
            .sin_port = htons(atoi(argv[1])),
            .sin_addr = htonl(INADDR_ANY),
    };
    PRINTLNF("client port [%hu]", ntohs(servCLient.sin_port));
    PRINT_INT(atoi(argv[1]));
    memset(&servCLient.sin_zero, 0,
           sizeof(servCLient.sin_zero));
    int bindRes = bind(_sock, (struct sockaddr *) &servCLient,
                       sizeof(servCLient));
    if (bindRes != 0) {
        perror("bind");
        PRINTLNF("\rbind failed, error[%d] occurs", bindRes);
        exit(-1);
    }

    struct sockaddr_in servAddr = {
            .sin_family = AF_INET,
            .sin_port = htons(ECHO_SERVICE_PORT),
            .sin_addr = inet_addr(arg_ip),
    };
    memset(&servAddr.sin_zero, 0,
           sizeof(servAddr.sin_zero));
    int connectRes = connect(_sock, (struct sockaddr *)&servAddr,
            sizeof(servAddr));
    if(connectRes < 0){
        perror("connect");
        exit(-1);
    }

    while(1){
        char buf[BUFSIZE];
        char *next = fgets(buf, BUFSIZE, stdin);
        if(!next){
            if(ferror(stdin)){
                perror("client input error");
                break;
            }else if(feof(stdin)){
                continue;
            } else{
                perror("unknown error");
                break;
            }
        }
        if(strcmp(next, "end\n") == 0){
            close(_sock);
            break;
        }
        ssize_t wrtRes = write(_sock, buf, strlen(buf)-1); // -1 means striping the character '\n'
        if(wrtRes < 0){
            perror("client send");
            exit(-1);
        }
        memset(buf, 0, sizeof(buf));
        ssize_t readRes = read(_sock, buf, BUFSIZE);
        if(readRes < 0){
            perror("receive");
            exit(-1);
        }
        PRINTLNF("[ECHO] from server@[%s]: %s", arg_ip, buf);
    }

    return 0;
}
