#include <stdlib.h>  
#include <stdio.h>  
#include <stddef.h>  
#include <sys/socket.h>  
#include <sys/un.h>  
#include <errno.h>  
#include <string.h>  
#include <unistd.h>  
 
#define MAXLINE 80  
 
// char *client_path = "/var/run/my/client.sock";  
char *server_path = "/var/run/my/server.sock";  
 
int main() {  
    struct  sockaddr_un cliun, serun;  
    int len;  
    char buf[100];  
    int sockfd, n;  
 
    if ((sockfd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0){  
        perror("client socket error");  
        exit(1);  
    }
 
    memset(&serun, 0, sizeof(serun));  
    serun.sun_family = AF_UNIX;  
    strcpy(serun.sun_path, server_path);  
    len = offsetof(struct sockaddr_un, sun_path) + strlen(serun.sun_path);  
    if (connect(sockfd, (struct sockaddr *)&serun, len) < 0){  
        perror("connect error");  
        exit(1);  
    }  
 
    while(fgets(buf, MAXLINE, stdin) != NULL) {    
         write(sockfd, buf, strlen(buf));  
    }   
    close(sockfd);  
    return 0;  
}  