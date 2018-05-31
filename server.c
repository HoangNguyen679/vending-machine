#include "server.h"


int max_drink;
drink all_drink[20];


void checkForDelivery(client_info *clt){
  int i = clientName2id(clt->name);
  int j;
  
  while(1){   
      for (j = 0; j < max_drink; j++){
        int figure = equipInfoAccess(1, j, &client_set[i]);
	printf("sndvcoiashdvoihadsoigvjhaDSOIHFVAOISDNJHVCAOSIDJHFVOIADSHVOI %d\n", i);
        if (figure < 3){
	  printf("%d\n", figure);
	  deliveryMng();
	  equipInfoAccess(2, j, &client_set[i]);
        
      }
    }
    sleep(10);
  }
}

int
main(int argc, char *argv[])
{

  char* figures_str = (char *)malloc(BUFF_SIZE);
  printf("Vending machine list:\n1.VM1\n2.VM2\n3.VM3\n");
  
  int port = 0;
  va_ser(argc, argv, &port);

  int listen_sock, conn_sock; 
  char recv_data[BUFF_SIZE];
  int bytes_sent, bytes_received;

  struct sockaddr_in server; 
  struct sockaddr_in client; 

  int sin_size;
  pid_t pid;
  
  readDrinkInfo(all_drink, &max_drink);

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


  char client_name[100] = "";
  if (recv(conn_sock, client_name, 100, 0) < 0) {
      printf("Cannot recv machine's name!");
      return 0;
  }

  client_info* recv_client = findClient(client_name);

  printf("%d %d %d\n", equipInfoAccess(1, 0, recv_client), equipInfoAccess(1, 1, recv_client), equipInfoAccess(1, 2, recv_client));
  sprintf(figures_str,"%d %d %d", equipInfoAccess(1, 0, recv_client), equipInfoAccess(1, 1, recv_client), equipInfoAccess(1, 2, recv_client));
  send(conn_sock, figures_str, BUFF_SIZE, 0);
  if (fork() == 0)
      checkForDelivery(recv_client);
  
  printf("%s\n", recv_client->name);

	printf("You got a connection from %s\nVending machine's name: %s\n",
	       inet_ntoa(client.sin_addr), client_name);

	while(1)
	  salesMng(conn_sock, recv_client);
	exit(0);
      }		
    close(conn_sock);	
  }

  close(listen_sock);
  return 0;
}

client_info *findClient(char name[]) {
  printf("%shaha\n", name);
  int i;
  for (i = 0; i < 3; i++) {
    if (strcmp(client_set[i].name, name) == 0) {
      return &client_set[i];
    }
  }
  printf("Invalid client name\n");
  return NULL;
}

void
salesMng(int conn_sock, client_info *clt)
{
  
  /* handle information from client */
  char recv_data[BUFF_SIZE];
  int id_drink;
  int byte_receive = recv(conn_sock,
			  recv_data,
			  BUFF_SIZE-1, 0);
  recv_data[byte_receive] = '\0';
  if (strcmp(recv_data, "shut_down") == 0) exit(0);
  printf("\nReceive: %s\n", recv_data);
  sscanf(recv_data, "%d", &id_drink);
  equipInfoAccess(0, id_drink, clt);
}


int
equipInfoAccess(int action, int num, client_info *clt)
{
  /* 
     action = 0: write history for bought
     action = 1: read figures in database
     action = 2: write history and update inventory after delivery
   */
  time_t t;
  struct tm *info ;
  time(&t);
  info = localtime(&t);
  int client_id;
  client_id = clientName2id(clt -> name);
  
  int* figures = readInventoryInfo(all_drink, max_drink);
  //for(i = 0 ; i < max_drink; i++)
  //  printf("%d %s\n", all_drink[i].no, all_drink[i].brand);

  if (action == 0){
    FILE *f = fopen(salesHistory, "a");
    if(f == NULL)
    {
      printf("Cannot open file sales history\n");
      exit(-1);
    }
    //cache[num] += 1;
    fprintf(f, "%s: %s Bought: %s\n",
	    clt -> name,
	    asctime(info),
	    no2brand(all_drink,max_drink,num));    
    fclose(f);
    //updateInventoryInfo(figures, cache, max_drink);
    figures[client_id * max_drink + num] -= 1;
    printf("%d\n", figures[num]);
    writeInventoryInfo(all_drink, max_drink, figures);
    return -1;
  }

  else if (action == 1){
    //    printf("thu in cai so ra coi %d\n", client_id * MAX_CLIENTS +  num);
    return figures[client_id * MAX_CLIENTS +  num];
  }

  else if (action == 2){   
    //cache[num] -= 10;
    FILE *f = fopen(salesHistory, "a");
    if(f == NULL)
    {
      printf("Cannot open file saleshistory\n");
      exit(-1);
    }
    fprintf(f, "Machine name: %s\n", clt->name);
    fprintf(f, "%s: %s Deliveried: %s + 10 \n",
	    clt -> name,
	    asctime(info),
	    no2brand(all_drink, max_drink, num));    
    fclose(f);
    figures[client_id * MAX_CLIENTS + num] += 10;
    printf("inadsjkfhaodsihfloaid %d\n",client_id * MAX_CLIENTS + num); 
    writeInventoryInfo(all_drink, max_drink, figures);
    return -1;
  }
  else
    exit(-1);
}

void
deliveryMng()
{
  printf("dang giao hang\n");
}
