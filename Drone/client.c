#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include "checksums.h"
#define SERVER_IP "192.168.2.1"
#define SERVER_PORT 2022
#define MAX_LINE 1024


int main(int argc, char *argv[])
{
    printf("init starting\n");
    //initialise all the variables required for the connection to the server
    FILE *fp;
    struct hostent *hp;
    struct sockaddr_in sin;
    char *host = SERVER_IP;
    unsigned char buf[MAX_LINE];
    volatile unsigned int *buf2[MAX_LINE];
    int s;
    int len;

    /* translate host name into peer's IP address */

    hp = gethostbyname(host);
    if (!hp)
    {

        fprintf(stderr, "simplex-talk: unknown host: %s\n", host);
        exit(1);
    }

    printf("data struct setup\n");
    /* build address data structure */
    bzero((char *)&sin, sizeof(sin));
    sin.sin_family = AF_INET;
    bcopy(hp->h_addr, (char *)&sin.sin_addr, hp->h_length);
    sin.sin_port = htons(SERVER_PORT);

    printf("openning socket\n");
    /* active open */
    if ((s = socket(PF_INET, SOCK_STREAM, 0)) < 0) // creates new socket, and if it fails prints simplex-talk: socket. 
    {
        perror("simplex-talk: socket");
        exit(1);
    }
    if (connect(s, (struct sockaddr *)&sin, sizeof(sin)) < 0) // connects socket to the address, and listens on that socket. else print simplex-talk: connect and closes connection. 
    {
        perror("simplex-talk: connect");
        close(s);
        exit(1);
    }
    printf("connected to service\n");

    bool continued = true;
    
    
    /* main loop: get and send lines of text */
    while (continued)
    {
        int bytes = recv(s, buf, sizeof(buf), 0);
        buf[MAX_LINE - 1] = '\0';
        len = strlen(buf) + 1;
        //sscanf(buf,1024,"%o");
    
        //
        // printf("%s", buf);
        if(bytes > 0){
            


            for(int i = 0; i < bytes; i++){
                printf("%#02x/", buf[i]);
            }
            printf("\n");
            
        }
        //printf("%#02x\n",CRC8_Table_Get(buf,0,len));
        //printf("%#02x\n",*buf);
        // send(s, buf, len, 0);
    }
}
