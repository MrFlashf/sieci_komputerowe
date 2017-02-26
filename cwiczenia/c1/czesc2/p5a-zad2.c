#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(void) {
    unsigned int port;
    char bufor[1024];
    int gniazdo, gniazdo2; //socket
    int i;
    struct sockaddr_in adr, nadawca; //sender
    socklen_t dl = sizeof(struct sockaddr_in);
    
    printf("Na ktorym porcie mam sluchac (on which port should I listen)? : ");
    scanf("%u", &port);
    gniazdo = socket(PF_INET, SOCK_STREAM, 0);
    adr.sin_family = AF_INET;
    adr.sin_port = htons(port);
    adr.sin_addr.s_addr = INADDR_ANY;
    if (bind(gniazdo, (struct sockaddr*) &adr, 
             sizeof(adr)) < 0) {
        printf("Bind nie powiodl sie (bind failed).\n");
        return 1;
    }
    if (listen(gniazdo, 10) < 0) {
        printf("Listen nie powiodl sie (listen failed).\n");
        return 1;        
    }
    printf("Czekam na polaczenie (I am waiting for connection)...\n");
    while ((gniazdo2 = accept(gniazdo,(struct sockaddr*) &nadawca,&dl)) > 0) {
     memset(bufor, 0, 1024);
     while (recv(gniazdo2, bufor, 1024, 0)>0) {
       printf("Wiadomosc od (message from) %s: %s\n",
        inet_ntoa(nadawca.sin_addr),
        bufor);
     }     
    close(gniazdo2);
     
   }
   close(gniazdo);
   return 0;
}
