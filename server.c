#include "lib.h"
#include "extra.h"
#include "drink.h"

void connectMng();
void salesMng(int conn_sock);
void equipInfoAccess(char s[BUFF_SIZE]);
void deliveryMng();


int
main(int argc, char *argv[])
{

  int port = 0;
  va_ser(argc, argv, &port);

  int listen_sock, conn_sock; 
  char recv_data[BUFF_SIZE];
  int bytes_sent, bytes_received;

  struct sockaddr_in server; 
  struct sockaddr_in client; 

  int sin_size;
  pid_t pid;
	
  // Construct a TCP socket to listen connection request
  if ((listen_sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {  
      perror("\nError: ");
      return 0;
    }
	
  // Bind address to socket
  bzero(&server, sizeof(server));
  server.sin_family = AF_INET;         
  server.sin_port = htons(port);  
  server.sin_addr.s_addr = htonl(INADDR_ANY);
  
  if(bind(listen_sock,
	  (struct sockaddr*)&server,
	  sizeof(server))==-1)
    { 
      perror("\nError: ");
      return 0;
    }     
  
  // Listen request from client
  if(listen(listen_sock, BACKLOG) == -1)
    { 
      perror("\nError: ");
      return 0;
    }
  
  // handing zombie state
  signal(SIGCHLD,sig_chld);
  
  // Communicate with client
  while(1){
    
    sin_size = sizeof(struct sockaddr_in);
    if ((conn_sock = accept(listen_sock,
			    ( struct sockaddr *)&client,
			    &sin_size)) == -1)
      {
	if (errno == EINTR)
	  continue;
	else
	  perror("\nError: ");
      }
		
    if ((pid = fork()) == 0)
      {
	close(listen_sock);
	printf("You got a connection from %s\n",
	       inet_ntoa(client.sin_addr) );
  
	salesMng(conn_sock);
	exit(0);
      }		
    close(conn_sock);	
  }

  close(listen_sock);
  return 0;
}

void
salesMng(int conn_sock)
{
  
  /* handle information from client */
  char recv_data[BUFF_SIZE];
  int byte_receive = recv(conn_sock,
			  recv_data,
			  BUFF_SIZE-1, 0);
  recv_data[byte_receive] = '\0';
  printf("\nReceive: %s\n", recv_data);

  equipInfoAccess(recv_data);
}


void
equipInfoAccess(char s[BUFF_SIZE])
{
  time_t t;
  struct tm *info ;

  time(&t);
  info = localtime(&t);
  
  FILE *f = fopen(salesHistory, "a");

  if(f == NULL)
    {
      printf("Cannot open file saleshistory\n");
      return;
    }

  drink all_drink[20];
  int max_drink;
  readDrinkInfo(all_drink, &max_drink);
  for(int i = 0 ; i < max_drink; i++)
    printf("%d %s\n", all_drink[i].no, all_drink[i].brand);

  int num;
  sscanf(s,"%d", &num);
  fprintf(f, "%s%s\n",
	  asctime(info),
	  no2brand(all_drink,max_drink,num));    
  fclose(f);

}

void
deliveryMng()
{

}
