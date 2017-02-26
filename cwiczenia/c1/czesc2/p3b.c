#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

int main(int argc, char **argv)
{
    struct hostent *he;
    struct in_addr addr;
    char abcd[512];

    printf("Podaj adres (IP address) IP: ");
    scanf("%s", abcd);
    addr.s_addr = inet_addr(abcd);
    he = gethostbyaddr((char*) &addr, sizeof(struct in_addr), AF_INET);
    if (he == NULL) {
        printf("Brak danych o (no data about) %s\n", abcd);
        return 1;
    }
    printf("Nazwa (name): %s\n",
           he->h_name);

    return 0;
}
