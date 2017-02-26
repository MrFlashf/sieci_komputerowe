#include <stdio.h>
#include <netinet/in.h>

int main(void) {
    in_addr_t h, n;
    unsigned char *jako_bajty; //as bytes
    printf("Podaj liczbe calkowita (integer): ");
    scanf("%d",&h);
    printf("Liczba w formacie lokalnym jako hex (number in local format): %X\n",h);
    jako_bajty = (unsigned char *) &h;
    printf("Liczba w formacie lokalnym jako bajty hex (number in local format): %X %X %X %X\n",
        jako_bajty[0],
        jako_bajty[1],
        jako_bajty[2],
        jako_bajty[3]);
    n = htonl(h);
    jako_bajty = (unsigned char *) &n;
    printf("Liczba w formacie sieciowym jako bajty (number in network format): %X %X %X %X\n",
        jako_bajty[0],
        jako_bajty[1],
        jako_bajty[2],
        jako_bajty[3]);
    printf("Liczba w formacie sieciowym jako hex (number in network format): %X\n", n);
    printf("co daje dziesietnie (decimal) %u\n", n);
    return 0;
}
