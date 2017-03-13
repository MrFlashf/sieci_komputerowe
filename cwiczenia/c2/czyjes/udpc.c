/*
    Simple udp client
*/
#include<stdio.h> //printf
#include<string.h> //memset
#include<stdlib.h> //exit(0);
#include<arpa/inet.h>
#include <unistd.h>
#include<sys/socket.h>
#include <netdb.h>
#include <sys/time.h>

#define SERVER "127.0.0.1"
#define BUFLEN 10000 //Max length of buffer

 
void die(char *s)
{
    perror(s);
    exit(1);
}
 
    char buf[BUFLEN];
    char message[BUFLEN];

int main(int argc, char **argv)
{
    struct sockaddr_in si_other;
    int s, i, slen=sizeof(si_other);
    struct timeval time_b, time_e;
	struct hostent *he;

	if (argc<3) {
		    printf("podaj nazwe hosta i numer portu jako parametry (provide hostname and port number in command line)\n");
		    return 1;
		}

 	he = gethostbyname(argv[1]);
    if (he == NULL) {
        printf("Nieznany host (unknown kost): %s\n",argv[1]);
        return 0;
    }
	gettimeofday(&time_b, NULL);
    if ( (s=socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        die("socket");
    }
 
    memset((char *) &si_other, 0, sizeof(si_other));
    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(atoi(argv[2]));
     


    for(i=0; i<100; i++)
    {
        //printf("Enter message : ");
        //scanf("%s",message);
         
        //send the message
        if (sendto(s, message, strlen(message) , 0 , (struct sockaddr *) &si_other, slen)==-1)
        {
            die("sendto()");
        }
         
        //receive a reply and print it
        //clear the buffer by filling null, it might have previously received data
        memset(buf,'\0', BUFLEN);
        //try to receive some data, this is a blocking call
        if (recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen) == -1)
        {
            die("recvfrom()");
        }
        //puts(buf);
    }
	close(s);
	gettimeofday(&time_e, NULL);
 

    
	printf("czas: %.6f s\n",
        (((double) (time_e.tv_sec - time_b.tv_sec) * 1000000) +
        ((double) (time_e.tv_usec - time_b.tv_usec)))
        / (1000000.0 * 100));

    return 0;
}
