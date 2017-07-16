#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MSG_BUF_SIZE 1024

int main(int argc, char *argv[])
{
	struct sockaddr_in addr;
	int fd;
	char message[MSG_BUF_SIZE] = {0};
	int port = atoi(argv[2]);
	int n;

	/* create what looks like an ordinary UDP socket */
	if ((fd=socket(AF_INET,SOCK_DGRAM,0)) < 0)
	{
		perror("socket");
		exit(1);
	}

	/* set up destination address */
	memset(&addr,0,sizeof(addr));
	addr.sin_family=AF_INET;
	addr.sin_addr.s_addr=inet_addr(argv[1]);
	addr.sin_port=htons(port);

	printf("Writer \n--------------\n");

	/* now just sendto() our destination! */
	while (1) {
		n = sprintf(message, "%s%s", argv[3], ": ");
		fgets(message + n, MSG_BUF_SIZE - n, stdin);
		message[strcspn(message, "\n")] = 0;

		if (sendto(fd,message,sizeof(message),0,(struct sockaddr *) &addr, sizeof(addr)) < 0)
		{
			perror("sendto");
			return 1;
		}
	}
	return 0;
}
