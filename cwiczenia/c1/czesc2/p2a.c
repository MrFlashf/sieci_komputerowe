#include <netinet/in.h>
#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>

int main(void) {
    char abcd[512];
    in_addr_t adrsiec; //networkaddress
    unsigned char *jako_bajty =  //as bytes
        (unsigned char*) &adrsiec;
    
    printf("Podaj adres IP w formacie (IP address in format) a.b.c.d: ");
    scanf("%s",abcd);
    adrsiec = inet_addr(abcd);
    if (adrsiec == 0xffffffff) {
        printf("To nie jest prawidlowy adres IP (invalid IP address)!\n");
        return 1;
    }
    printf("Adres w formacie sieci to (network format) %u, hex=%X\n",
        adrsiec, adrsiec);
    printf("Adres bajt po bajcie (bytes) (hex): %X %X %X %X\n",
        jako_bajty[0], jako_bajty[1],
        jako_bajty[2], jako_bajty[3]);
    printf("Adres bajt po bajcie (bytes) (dec): %u %u %u %u\n",
        jako_bajty[0], jako_bajty[1],
        jako_bajty[2], jako_bajty[3]);
    return 0;
}
