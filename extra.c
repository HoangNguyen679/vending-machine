#include "extra.h"

void va_cli(int argc, char *argv[], char *server_ip, int *server_port, char *name)
{
  if(argc == 4)
    {
      struct sockaddr_in tmp_addr;
      if(inet_pton(AF_INET, argv[1], &(tmp_addr.sin_addr)) == 0)
	{
	  printf("IP Address is invalid\n");
	  exit(0);
	}
      else
	{
	  strcpy(server_ip, argv[1]);
	}

      int i;
      char *port_str = argv[2];
      for(i = 0; port_str[i] != '\0'; i++)
	{
	  if(!isdigit(port_str[i]))
	    {
	      printf("Port is invalid\n!");
	      exit(0);
	    }
	}
      
      if (port_str[i] == '\0')
	{
	  *server_port = atoi(port_str);
	}
    strcpy(name, argv[3]);
    }
  else
    {
      printf("ERROR!!! Syntax like: ./client ip port machine_name\n");
      exit(0);
    }
}

/*
 * check argument valid in server 
 */

void
va_ser(int argc,
       char *argv[],
       int *port)
{
  if (argc == 2)
    {
      int i;
      char *port_str = argv[1];
      for (i = 0; port_str[i] != '\0'; i++)
	{
	  if (!isdigit(port_str[i]))
	    {
	      printf("Port is invalid\n");
	      exit(0);
	    }
	}

      if (port_str[i] == '\0')
	{
	  *port = atoi(port_str);
	}
    }
  else
    {
      printf("ERROR!!! Syntax like: ./server port\n");
      exit(0);
    }
}

/*
 * handle sigchild
 */

void
sig_chld(int signo)
{
  pid_t pid;
  int stat;
  while ((pid = waitpid(-1, &stat, WNOHANG)) > 0)
    {
      printf("child %d terminated\n", pid);
    }  
}

void throwMallocException(){ // hope it will work
  fprintf(stderr, "failed to locate !\n");
  exit(-1);
}
