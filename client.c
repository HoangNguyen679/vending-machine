#include "lib.h"
#include "extra.h"

int
main(int argc, char *argv[])
{
  int server_port = 0;
  char server_ip[16] = "";
  va_cli(argc, argv,&server_ip, &server_port);

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

  int byte_send = send(client_sock,
		       "I'm big_finger",
		       strlen(buff),
		       0);
  
  close(client_sock);
  return 0;
}


