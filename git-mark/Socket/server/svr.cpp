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

void str_echo(int connfd)
{
	size_t n = 0;
	char buf[1024];
again:
	while(n = read(connfd, buf, sizeof(buf)))
	{
		write(connfd, buf, n);
	}
	if(n < 0 && errno == EINTR )
		goto again;
	else if(n < 0)
		printf("str_echo: read error\n");
}

int main()
{
	struct sockaddr_in saddr;
	saddr.sin_port = htons(8888);
	saddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	saddr.sin_family = AF_INET;
	int socketfd = socket(AF_INET, SOCK_STREAM, 0);
	assert(socketfd != -1);
	int ret = bind(socketfd, (struct sockaddr *)&saddr, sizeof(saddr));
	assert(ret != -1);
	int listenfd = listen(socketfd, 5);
	assert(listenfd != -1);
	pid_t pid;
	while(1)
	{
		struct sockaddr_in caddr;
		socklen_t length = sizeof(caddr);
		int connfd = accept(socketfd, (struct sockaddr *)&caddr, &length);
		assert(connfd != -1);
		if((pid = fork()) == 0)
		{
			close(socketfd);
			str_echo(connfd);
			exit(0);
		}

		close(connfd);
	}

	return 0;
}
