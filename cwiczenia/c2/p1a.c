#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h> 


char buf[512];

int main(int argc, char **argv)
{
    struct sockaddr_in myaddr, endpoint;
    int sdsocket, r;
    socklen_t addrlen;
    unsigned int port;
    
    printf("Na ktorym porcie mam sluchac (on which port should I listen)? : ");
    scanf("%u", &port);

    if ((sdsocket = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        printf("socket() nie powiodl sie (failed)\n");
        return 1;
    }
        
    myaddr.sin_family = AF_INET;
    myaddr.sin_port = htons(port);
    myaddr.sin_addr.s_addr = INADDR_ANY;

    if (
        bind(sdsocket,
             (struct sockaddr*) &myaddr,
             sizeof(struct sockaddr_in)) < 0) {
        printf("bind() nie powiodl sie (failed)\n");
        return 1;
    }

    addrlen = sizeof(struct sockaddr_in);
    while (1) { /* nieskonczona petla (infinite loop)*/
        memset(buf, 0, 512);
        r = recvfrom(sdsocket,
                     buf,
                     512,
                     0,
                     (struct sockaddr*) &endpoint,
                     &addrlen);
        printf("Wiadomosc od (message from) %s: %s\n",
               inet_ntoa(endpoint.sin_addr),
               buf);
    }    
    return 0;
}
