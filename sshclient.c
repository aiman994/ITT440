#include <libssh/libssh.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

int main()
{
	int sock;
	struct sockaddr_in server;
	int mysock;
	char buff[1024];
	int retval;
	int optval;
	int optlen;
	int optvalue;

	/* create sock */

	sock=socket(AF_INET,SOCK_STREAM, 0);
	if(sock<0){
		perror("fail create error");
		exit(1);
	}

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port= htons(1055);

	/* BIND */
	if(bind(sock,(struct sockaddr*)&server, sizeof(server))){
		perror("bind fail");
		exit(1);
	}

	/*listen*/
	listen(sock,1);

	do {
		mysock = accept(sock,(struct sockaddr *) 0,0);
		if (mysock == -1)
		{	perror("accept fail");
			exit(1);
		}
		else{
			memset(buff,0, sizeof(buff));
				if(retval = recv(mysock,buff, sizeof(buff),0) <0)
				{	perror("reading stream message error");
					exit(1);
				}
				else if (retval == 0)
				{
					printf("ASSALAMUALAIKUM");
					printf("%d",sshsession());

				close(sock);
				exit(1);
				}
				else
					printf("MSG %s \n" , buff);



				printf("got the message (retval - %d)\n" , retval);
				close(mysock);
					}
				}while(1);

return 0;

}

int sshsession()
{
  ssh_session my_ssh_session;
  int verbosity = SSH_LOG_PROTOCOL;
  int port = 22;
  int rc;


  my_ssh_session = ssh_new();
  if(my_ssh_session ==NULL)
	exit(-1);
  else
	printf("ADA SESSION NIII \n ");
  ssh_options_set(my_ssh_session, SSH_OPTIONS_HOST, "192.168.211.129");
  ssh_options_set(my_ssh_session, SSH_OPTIONS_LOG_VERBOSITY, &verbosity);
  ssh_options_set(my_ssh_session, SSH_OPTIONS_PORT, &port);


  rc= ssh_connect(my_ssh_session);


  if(rc != SSH_OK)
  {
    exit(-1);
  }
  else
  {

    printf("SSH OK\n");
    authenticate_password(my_ssh_session);
  }

  ssh_free(my_ssh_session);

}


int  authenticate_password(ssh_session session)
{
  char *password, *banner;
  int rc;

  password = getpass("Enter Your Password : ");
  rc= ssh_userauth_password(session, NULL, password);
  if(rc == SSH_AUTH_ERROR)
  {
    return SSH_AUTH_ERROR;
  }
  else if(rc == SSH_AUTH_SUCCESS){
    printf("Success \n");
    banner = ssh_get_issue_banner(session);
	if(banner==NULL){
	 printf("NO BANNER PROVIDED \n " , banner);
	 free(banner);
	}
	else
	{printf(banner);}
  }
  return  rc;
}
