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

void str_cli(FILE *fp, int sockfd)
{
	char sendline[1024];
	char recvline[1024];

	while(fgets(sendline, 1024, fp) != NULL)
	{
		write(sockfd, sendline, strlen(sendline));
		if(readline(sockfd, recvline, 1024) == 0)
			printf("str_cli: server terminated prematurely\n");

		fputs(recvline, stdout);
	}
}

int main()
{
	struct sockaddr_in saddr;
	saddr.sin_port = htons(8888);
	saddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	saddr.sin_family = AF_INET;
	int socketfd = socket(AF_INET, SOCK_STREAM, 0);
	assert(socketfd != -1);
	int connfd = connect(socketfd, (struct sockaddr *)&saddr, sizeof(saddr));
	assert(connfd != -1);
	str_cli(stdin, socketfd);

	return 0;
}
