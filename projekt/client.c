#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int cusConnect();
int cusReceive(int gniazdo);

int main(void) {
    // char ip[512];
    struct sockaddr_in adr;
    // unsigned int port;
    
    
    
    // adr.sin_family = AF_INET;
    // adr.sin_port = htons(port);
    // adr.sin_addr.s_addr = inet_addr(abcd);
    // if (connect(gniazdo, (struct sockaddr*) &adr,
    //             sizeof(adr)) < 0) 
    // {
    //     printf("Nawiazanie polaczenia nie powiodlo sie (connection failed).\n");
    //     return 1;
    // }

    cusConnect();

    // printf("Polaczenie nawiazane (connection successful).\nPodaj wiadomosc (message to send): ");
    // fflush(stdout); fgetc(stdin);
    // fgets(wiadomosc, 1024, stdin);
    // send(gniazdo, wiadomosc, strlen(wiadomosc), 0);
    // printf("Wiadomosc wyslana (message sent).\n");
    // close(gniazdo);
    return 0;
}

int cusConnect() {
    char nick[64], ip[512];
    struct sockaddr_in adr, nadawca;
    int gniazdo, gniazdo2, gniazdo3;
    unsigned int port;
    socklen_t dl = sizeof(struct sockaddr_in);
    char bufor[1024];

    printf("Podaj adres IP odbiorcy (IP address of the receiver): ");
    scanf("%s", ip);
    printf("Podaj numer portu odbiorcy (port number of the receiver): ");
    scanf("%u", &port);

    gniazdo  = socket(PF_INET, SOCK_STREAM, 0);
    gniazdo2 = socket(PF_INET, SOCK_STREAM, 0);

    adr.sin_family = AF_INET;
    adr.sin_port = htons(port);
    adr.sin_addr.s_addr = INADDR_ANY;

    if (connect(gniazdo, (struct sockaddr*) &adr,
                sizeof(adr)) < 0) 
    {
        printf("Nawiazanie polaczenia nie powiodlo sie (connection failed).\n");
        return 1;
    }

    printf("Podaj swój nick: ");
    scanf("%s", nick);
    send(gniazdo, nick, strlen(nick), 0);
    close(gniazdo);
 
    if (connect(gniazdo2, (struct sockaddr*) &adr, sizeof(adr)) < 0) {
        printf("Bind nie powiodl sie (bind failed).\n");
        return 1;
    }
    if (listen(gniazdo2,10) < 0) {
        printf("Coś się popsuło");
    }

    while((gniazdo3 = accept(gniazdo2, (struct sockaddr*) &nadawca, &dl)) > 0) {
        memset(bufor, 0, 1024);
        recv(gniazdo2, bufor, 1024, 0);
        printf("%s", inet_ntoa(nadawca.sin_addr),bufor);
        close(gniazdo2);
    }

}

int cusReceive(int gniazdo) {
    int gniazdo2;
    struct sockaddr_in adr, nadawca;
    socklen_t dl = sizeof(struct sockaddr_in);
    char bufor[1024];


    if (listen(gniazdo,10) < 0) {
        printf("Coś się popsuło");
    }

    while((gniazdo2 = accept(gniazdo, (struct sockaddr*) &nadawca, &dl)) > 0) {
        memset(bufor, 0, 1024);
        recv(gniazdo2, bufor, 1024, 0);
        printf("%s", inet_ntoa(nadawca.sin_addr),bufor);
        close(gniazdo2);
    }
}
