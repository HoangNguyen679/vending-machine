#include "lib.h"
#include "extra.h"

int pipe_p2c[2];
int pipe_c2p[2];


void equipMain(int client_sock);
void commoditySales(int client_sock);

int
main(int argc, char *argv[])
{
  int server_port = 0;
  char server_ip[16] = "";
  va_cli(argc, argv, server_ip, &server_port);

  int client_sock;
  
  struct sockaddr_in server_addr;
  
  // Construct socket
  client_sock = socket(AF_INET,SOCK_STREAM,0);
  
  // Specify server address
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(server_port);
  server_addr.sin_addr.s_addr = inet_addr(server_ip);

  // Request to connect server
  if(connect(client_sock,
	     (struct sockaddr*)&server_addr,
	     sizeof(struct sockaddr)) < 0)
    {
      printf("\nError!Can not connect to sever! \
                Client exit imediately!\n");
      return 0;
    }

  equipMain(client_sock);
  
  close(client_sock);
  return 0;
}

void
equipMain(int client_sock)
{
  while(1)
    {
      menu_home();
      int c;
      scanf("%d", &c);
      switch(c)
	{
	case 4:
	  menu_bye();
	  exit(0);
	} // end switch menu home

      char buff[BUFF_SIZE];
      sprintf(buff,"%d",c);
      
     
      pipe(pipe_p2c);
      pipe(pipe_c2p);

      pid_t pid = 0;
      
      switch(pid = fork())
	{
	case -1:
	  perror("processGenerate fork");
	  exit(1);
	case 0:
	  //printf("childProcess start\n");
	  commoditySales(client_sock);
	  exit(0);
	default:
	  //printf("parentProcess start\n");

	  close(pipe_p2c[0]);
	  write(pipe_p2c[1], buff, strlen(buff) + 1);
	  close(pipe_p2c[1]);

	  wait(NULL);
	  
	  char tmp[BUFF_SIZE];
	  
	  close(pipe_c2p[1]);
	  read(pipe_c2p[0], tmp, BUFF_SIZE);
	  close(pipe_c2p[0]);

	  printf("\n\n%s\n\n",tmp);

		
	} // end switch fork()
    } // end while
  
}

void
commoditySales(int client_sock)
{
  char recv_str[BUFF_SIZE];

  close(pipe_p2c[1]);
  read(pipe_p2c[0], recv_str, BUFF_SIZE);
  close(pipe_p2c[0]);

  char send_str[BUFF_SIZE] = "Thank you for chosing us\n";

  close(pipe_c2p[0]);
  write(pipe_c2p[1], send_str, strlen(send_str) + 1);
  close(pipe_c2p[1]);

  send(client_sock, recv_str, strlen(recv_str) + 1, 0);
  
}
  
