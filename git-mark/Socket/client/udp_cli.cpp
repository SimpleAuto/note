#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <assert.h>
#include <errno.h>
#include <string.h>

ssize_t readline(int fd, void *vptr, size_t maxlen)
{
	ssize_t n, rc;
	char c,*ptr;
	ptr = (char*)vptr;
	for(n = 1; n < maxlen; ++n)
	{
again:
		if( (rc = read(fd, &c, 1)) == 1)
		{
			*ptr++ = c;
			if(c == '\n')
				break;
		}
		else if (rc == 0)
		{
			*ptr = 0;
			return (n-1);
		}
		else
		{
			if(errno = EINTR)
				goto again;
			return (-1);
		}
	}

	*ptr = 0;
	return (n);
}

void str_cli(FILE *fp, int sockfd, struct sockaddr_in &saddr)
{
	char sendline[1024];
	char recvline[1024];

	//int connfd = connect(sockfd , (struct sockaddr *)&saddr, sizeof(saddr));
	//assert(connfd != -1);
	while(fgets(sendline, 1024, fp) != NULL)
	{
		socklen_t len = sizeof(saddr);
		//write(sockfd, sendline, strlen(sendline));
		//int n = read(sockfd, recvline, 1024);

		sendto(sockfd, sendline, strlen(sendline), 0, (struct sockaddr *)&saddr, sizeof(saddr));
		int n = recvfrom(sockfd, recvline, 1024, 0, (struct sockaddr *)&saddr, &len);
	
		// if connect 
		//write(sockfd, sendline, strlen(sendline));
		//int n = read(sockfd, recvline, 1024);
		//sendto(sockfd, sendline, strlen(sendline), 0, NULL, 0);
		//int n = recvfrom(sockfd, recvline, 1024, 0, NULL, 0);

		recvline[n] = 0;
		printf("recv msg length %d, msg: %s\n", n, recvline);

		fputs(recvline, stdout);
	}
}

int main()
{
	struct sockaddr_in saddr;
	saddr.sin_port = htons(8888);
	saddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	saddr.sin_family = AF_INET;
	int socketfd = socket(AF_INET, SOCK_DGRAM, 0);
	assert(socketfd != -1);
	str_cli(stdin, socketfd, saddr);

	return 0;
}
