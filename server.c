#include "server.h"

int *cache;
int max_drink;
drink all_drink[20];

void checkForDelivery(){
  int i;
  while(1){    
    for (i = 0; i < max_drink; i++){
      int* figures = readInventoryInfo(all_drink, max_drink);
      if (figures[i] < 3){
	deliveryMng();
	figures[i] += 10;
      }
      writeInventoryInfo(all_drink, max_drink, figures);
    }
    
    sleep(10);
  }
}

int
main(int argc, char *argv[])
{
  
  int port = 0,i;
  va_ser(argc, argv, &port);

  int listen_sock, conn_sock; 
  char recv_data[BUFF_SIZE];
  int bytes_sent, bytes_received;

  struct sockaddr_in server; 
  struct sockaddr_in client; 

  int sin_size;
  pid_t pid;
  
  readDrinkInfo(all_drink, &max_drink);
  cache = (int *)malloc(max_drink * sizeof(int));
  if (cache == NULL) throwMallocException();
  pthread_t delivery_thread;
  pthread_create(&delivery_thread, NULL, checkForDelivery, NULL);
 
  
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
  int i;
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
  for(i = 0 ; i < max_drink; i++)
    printf("%d %s\n", all_drink[i].no, all_drink[i].brand);

  int num;
  sscanf(s,"%d", &num);
  cache[num] += 1;
  printf("sau khi cap nhat: %d:%d\n", num, cache[1]);
  fprintf(f, "%s%s\n",
	  asctime(info),
	  no2brand(all_drink,max_drink,num));    
  fclose(f);

  int* figures = readInventoryInfo(all_drink, max_drink);
  updateInventoryInfo(figures, cache, max_drink);
  writeInventoryInfo(all_drink, max_drink, figures);
}

void
deliveryMng()
{
  printf("dang giao hang\n");
}
