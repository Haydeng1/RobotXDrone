#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#define SERVER_PORT 2022
#define MAX_LINE 256

int main(int argc, char *argv[])
{
    //initialise all the variables required for the connection to the server
    FILE *fp;
    struct hostent *hp;
    struct sockaddr_in sin;
    char *host;
    char buf[MAX_LINE];
    int s;
    int len;

    host = "192.168.2.1"; // the host will be the IP given in the second argument.

    /* translate host name into peer's IP address */
    hp = gethostbyname(host);
    if (!hp)
    {
        fprintf(stderr, "simplex-talk: unknown host: %s\n", host);
        exit(1);
    }
    /* build address data structure */
    bzero((char *)&sin, sizeof(sin));
    sin.sin_family = AF_INET;
    bcopy(hp->h_addr, (char *)&sin.sin_addr, hp->h_length);
    sin.sin_port = htons(SERVER_PORT);
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

    int buf_len;

    while (1)
    {
        while (buf_len = recv(s, buf, sizeof(buf), 0))
        {
            fputs(buf, stdout);
        }
        close(s);
        quit(1);
    }

    /* main loop: get and send lines of text */
    // while (fgets(buf, sizeof(buf), stdin))
    // {
    //     buf[MAX_LINE - 1] = '\0';
    //     len = strlen(buf) + 1;
    //     send(s, buf, len, 0);
    // }
}
