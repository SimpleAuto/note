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

void str_echo(int socketfd, struct sockaddr_in &saddr)
{
	int n;
	socklen_t len;	
	char mesg[1024];
	while(1)
	{
		len = sizeof(saddr);
		n = recvfrom(socketfd, mesg, 1024, 0, (struct sockaddr *)&saddr, &len);
		sendto(socketfd, mesg, n, 0, (struct sockaddr *)&saddr, len);

		//n = read(socketfd, mesg, 1024);
		//printf("read OK msg:%s \n", mesg);
		//write(socketfd, mesg, n);
		//printf("write OK msg:%s \n", mesg);
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
	int ret = bind(socketfd, (struct sockaddr *)&saddr, sizeof(saddr));
	assert(ret != -1);

	str_echo(socketfd, saddr);

	return 0;
}
