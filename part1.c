#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
char *strrev(char *str)
{
      char *p1, *p2;

      if (! str || ! *str)
            return str;
      for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
      {
            *p1 ^= *p2;
            *p2 ^= *p1;
            *p1 ^= *p2;
      }
      return str;
}
int main()
{
	int pipefd[2],pipefd1[2];
	
	int in = pipe(pipefd);
	
	if(in==-1)
	{
		perror("Error in Pipe creation.");
		return 0;
	}
	in = pipe(pipefd1);
	if(in==-1)
	{
		perror("Error in Pipe 1 creation.");
		return 0;
	}

	pid_t pid = fork();
	char str[100] = "INPUT";
	if(pid==0)
	{
		char buff[100];
		
			
		close(pipefd[1]);
		close(pipefd1[0]);
		// pipefd[0]. pipefd1[1]
		printf("\n\nChild Writing: %s",str);
		in = write(pipefd1[1],str,strlen(str)+1);
		if(in==-1)
		{
			perror("\nChild Error In Writing");
		}
		
		close(pipefd1[1]);
		//Read
		in = read(pipefd[0],buff,strlen(str)+1);
		if(in==-1)
		{
			perror("\nChild Error In Reading");
		}
		str[in]= ' ';
		close(pipefd[0]);
		printf("\n\nChild Read: %s\n", buff);
		exit(0);
	}	
	
	else
	{
		close(pipefd[0]);
		close(pipefd1[1]);
		//pipefd1[0],pipefd[1]
		char buff[100];
		
		in = read(pipefd1[0],buff,strlen(str)+1);
		close(pipefd1[0]);
		if(in==-1)
		{
			perror("\nParent Error In Reading");
		}
		buff[in]= ' ';
		printf("\n\nParent Recieved: %s",buff);
		char *revs = strrev(buff);
		printf("\n\nParent Writing: %s\n\n",buff);
		in = write(pipefd[1],buff,strlen(str)+1);
		close(pipefd[1]);
		if(in==-1)
		{
			perror("\nChild Error In Wriing");
		}
		wait(NULL);
		return 0;
	}
}
