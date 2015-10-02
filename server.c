#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>

int main ()
{
	/* variables */
	int sock;
	struct sockaddr_in server;
	int mysock ; /*hold connection*/
	char buff[1024];
	int retval;

	/*create sock*/
	sock= socket(AF_INET,SOCK_STREAM, 0);
	if (sock<0){
		perror("fail create error");
	        exit(1);
	}
	server.sin_family =AF_INET;
	server.sin_addr.s_addr= INADDR_ANY;
	server.sin_port = htons(1055);

	/*bind*/
	if(bind(sock,(struct sockaddr*)&server, sizeof(server))){
	 	perror("bind fail");
		exit (1);
	}
	
	/*listen*/
	listen(sock,1);


	/*accept*/
	do{
		mysock = accept(sock,(struct sockaddr *) 0,0);
		if ( mysock== -1)
		{	perror("accept fail");
			exit(1);
		}
		else {
			memset(buff,0,sizeof(buff));
				if( retval = recv(mysock,buff, sizeof(buff),0) <0)
			       {	perror("reading stream message error");
					exit(1);
			        }
				else if (retval == 0){
			           printf("Haluuuu\n");
					exit(1);
				}
				else
					printf("MSG %s\n" , buff);




				printf("got the message (retval   - %d)\n" ,retval);
				close(mysock);
					}
				}while (1);


	return 0;
}
