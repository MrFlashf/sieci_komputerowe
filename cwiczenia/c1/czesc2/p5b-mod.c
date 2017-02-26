#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>

int main(void) {
    char abcd[512];
    char wiadomosc[1024];
    struct sockaddr_in adr;
    unsigned int port;
    int gniazdo;
    struct hostent *he;
    struct in_addr adres;    

    printf("Podaj nazwe domenowa: ");
    scanf("%s", abcd);
    he = gethostbyname((const char*) abcd);
    printf("Podaj numer portu odbiorcy (port number of the receiver): ");
    scanf("%u", &port);
    adres.s_addr = *((unsigned long*) he->h_addr_list[0]);
    gniazdo = socket(PF_INET, SOCK_STREAM, 0);
    adr.sin_family = AF_INET;
    adr.sin_port = htons(port);
    adr.sin_addr.s_addr = inet_addr(inet_ntoa(adres));
    if (connect(gniazdo, (struct sockaddr*) &adr,
                sizeof(adr)) < 0) 
    {
        printf("Nawiazanie polaczenia nie powiodlo sie (connection failed).\n");
        return 1;
    }
    printf("Polaczenie nawiazane (connection successful).\nPodaj wiadomosc (message to send): ");
    fflush(stdout); fgetc(stdin);
    fgets(wiadomosc, 1024, stdin);
    send(gniazdo, wiadomosc, strlen(wiadomosc), 0);
    printf("Wiadomosc wyslana (message sent).\n");
    close(gniazdo);
    return 0;
}
