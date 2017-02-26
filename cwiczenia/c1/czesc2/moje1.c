#include <stdio.h>

main() {
 int input;

 printf("Podaj input");
 scanf(&input);
 printf("Input: %d", input);
 printf("Input po funkcji: %l", htonl(input));
}
