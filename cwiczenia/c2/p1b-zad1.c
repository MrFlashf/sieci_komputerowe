#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>


char buf[512];

int main(int argc, char **argv)
{
    struct sockaddr_in adr;
    int gniazdo, r,i;
    unsigned int port;
    char abcd[512];
    struct hostent *he;
    struct in_addr adres;

    printf("Podaj nazwe domenowa: ");
    scanf("%s", abcd);
    he = gethostbyname((const char*) abcd);
    printf("Podaj numer portu odbiorcy: ");
    scanf("%u", &port);
    adres.s_addr = *((unsigned long*) he->h_addr_list[0]);
    gniazdo = socket(AF_INET, SOCK_DGRAM, 0);
    adr.sin_family = AF_INET;
    adr.sin_port = htons(port);
    adr.sin_addr.s_addr = inet_addr(inet_ntoa(adres));
    i=1;
    while (i==1) {
     printf("Podaj wiadomosc: ");
     fflush(stdout); fgetc(stdin);
     fgets(buf, 512, stdin);
     r = sendto(gniazdo,
               buf,
               512,
               0,
               (struct sockaddr*) &adr,
               sizeof(adr));
     if (r != 512) printf("sendto() nie powiodl sie\n");
     else printf("Wiadomosc wyslana.\n");
    }
    close(gniazdo);
    return 0;
}
