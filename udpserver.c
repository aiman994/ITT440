#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main(){

	int udpsocket , nbytes , status, para;
	char buffer[1024];
	struct sockaddr_in serveraddr;
	struct sockaddr_storage serverstorage;
	socklen_t addr_size = sizeof serveraddr;
	udpsocket = socket(AF_INET, SOCK_DGRAM , 0);

	serveraddr.sin_family= AF_INET;
	serveraddr.sin_port= htons(1055); //pitfall 3
	serveraddr.sin_addr.s_addr = INADDR_ANY;
	memset(serveraddr.sin_zero,'\0', sizeof serveraddr.sin_zero);

	bind(udpsocket,(struct sockaddr *)&serveraddr,sizeof(serveraddr));

	addr_size = sizeof serverstorage;
	printf("server running , waiting for connection");

	while(1){
		nbytes = recvfrom(udpsocket,buffer,1024,0,(struct sockaddr *)&serveraddr,&addr_size);
		printf( " dapat ", buffer , " : " , nbytes);
		sendto(udpsocket,buffer,nbytes,0,(struct sockaddr *)&serveraddr,addr_size);
		status = getsockopt(udpsocket,SOL_SOCKET , SO_REUSEADDR, &para ,&addr_size);
		if ( status >0 ) // PITFALL 1
			printf ("already set ");
		else if (status == 0)
			setsockopt(udpsocket,SOL_SOCKET, SO_REUSEADDR,&para,sizeof 1); //PITFALL 2
		else
			printf(" ERROR : ", strerror (48) ); // PITFALL 4


	}
	return 0;

}
