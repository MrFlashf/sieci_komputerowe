#include <stdio.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <netinet/in.h>
#include <unistd.h>

char *endpoint = "./p2.fifo";

int main(int argc, char **argv)
{
    int fdFifo;
    long lNetworkFormat, lHostFormat;

    lHostFormat = 999999;
    lNetworkFormat = htonl(lHostFormat);
    fdFifo = open(endpoint, O_WRONLY);
    write(fdFifo, &lNetworkFormat, sizeof(long));
    printf("zapisano (written): %ld\n", lHostFormat);
    close(fdFifo);
    return 0;
}
