#include <stdio.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <unistd.h>
#include <netinet/in.h>

char *endpoint = "./p2.fifo";

int main(int argc, char **argv)
{
    int fdFifo;
    long lNetworkFormat, lHostFormat;

    mkfifo(endpoint, 0666);
    fdFifo = open(endpoint, O_RDONLY);
    read(fdFifo, &lNetworkFormat, sizeof(long));
    lHostFormat = ntohl(lNetworkFormat);
    printf("odczytano (read): %ld\n", lHostFormat);
    close(fdFifo);
    return 0;
}
