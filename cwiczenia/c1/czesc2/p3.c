#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

int main(void) {
    char nazwa[512];
    struct hostent *he;
    struct in_addr adr;
    int i;
    
    printf("Podaj nazwe hosta (provide hostname): ");
    scanf("%s", nazwa);
    he = gethostbyname((const char*) nazwa);
    if (he == NULL) {
        printf("Nie ma hosta o takiej nazwie (no such host)\n");
        printf("lub blad serwera DNS (or DNS error).\n");
        return 1;
    }
    i = 0;
    while (he->h_addr_list[i]) {
        adr.s_addr =
        *((unsigned long*) he->h_addr_list[i]);
        printf("Adres hosta (host address): %s\n",
            inet_ntoa(adr));
        printf("W formacie sieci (in network format)(hex): %X, (dec): %u\n",
            adr.s_addr, adr.s_addr);
        i++;
    }
    return 0;
}
