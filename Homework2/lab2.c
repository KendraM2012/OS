/*	Homework 2 Kendra Maggiore*/
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <fcntl.h>


main()

{

char *path, *argv[20], buf[80], n, *p;

int m, status, inword, continu;



while(1) {



inword = 0;

p = buf;

m = 0;

continu=0;



printf( "\nshhh> ");

while ( ( n = getchar() ) != '\n'  || continu ) {

	if ( n ==  ' ' ) {

	    if ( inword ) {

		inword = 0;

		*p++ = 0;

	    }

	}

	else if ( n == '\n' ) continu = 0;

	else if ( n == '\\' && !inword ) continu = 1;

	else {

	    if ( !inword ) {

		 inword = 1;

		 argv[m++] = p;

		 *p++ = n;

	     }

	     else

		 *p++ = n;

	}

}

*p++ = 0;

argv[m] = 0;



if ( strcmp(argv[0],"exit") == 0 ) exit (0);
//Setting all variables
int in = 0; // for input
int out = 0; // for output
int pid = 0;
int pCount = 0;
int pipes[20]; // pipes
int rPipe[2]; //right pipe
int lPipe[2]; // left pipe
int processes[20]; // holds the commands
int proCount = 0;
int i;
char inputFile[64]; // holds the input file
char outputFile[64]; // holds the output file

processes[proCount++] = 0; //pushes the first command into the proccess

//pre proccessing for | < >
for(i=0;argv[i]!='\0';i++)
{
	if(strcmp(argv[i],"|") ==0)
	{
		pipes[pCount++] = i;
		argv[i] =0;
		processes[proCount++]= i + 1;
	}
	else if(strcmp(argv[i],"<")==0)
	{
		argv[i] = NULL;
		strcpy(inputFile,argv[i+1]);
		in = 2;

	}
	else if(strcmp(argv[i],">")==0)
	{
		argv[i] = NULL;
		strcpy(outputFile,argv[i+1]);
		out = 2;
	}
}
//loop for proccesses
int k;
for(k = 0; k <= pCount; k++)
{
		if(k < pCount)
		{
			pipe(rPipe);
		}

	pid = fork();

	if(pid < 0) // checks if pid is empty
  {
    printf("pipe failed exiting program");
    exit(EXIT_FAILURE);
  }
	else if(pid == 0)
	{
		//in
		if(in)
		{
			int inFile = open(inputFile,O_RDONLY);
			if(inFile < 0)
			{
				printf("Input failed");
		    exit(EXIT_FAILURE);
			}
			close(0);
			dup(inFile);
			close(inFile);
			in = 0;
		}
		//output
		if(out)
		{
			int outFile = open(outputFile, O_CREAT | O_WRONLY, 0755);
			if(outFile < 0)
			{
				printf("Output failed");
		    exit(EXIT_FAILURE);
			}
			close(1);
			dup(outFile);
			close(outFile);
			out = 0;
		}
		//everything else
		if(pCount > 0)
		{
			if(k==0)
			{
				close(1);
        dup(rPipe[1]);
        close(rPipe[1]);
        close(rPipe[0]);
        close(lPipe[1]);
        close(lPipe[0]);
			}
			else if( k < pCount)
			{
				close(0);
        dup(lPipe[0]);
        close(lPipe[0]);
        close(lPipe[1]);
				close(1);
        dup(rPipe[1]);
        close(rPipe[1]);
      	close(rPipe[0]);
			}
			else
			{
				close(0);
        dup(lPipe[0]);
        close(lPipe[0]);
        close(lPipe[1]);
        close(rPipe[1]);
        close(rPipe[0]);
			}
		}
		execvp(argv[processes[k]], &argv[processes[k]]); // execute commands
	  printf(" The command can not execute \n ");
		}
		else
		{

				if (k > 0)
				{
						close(lPipe[1]);
						close(lPipe[0]);
				}

				lPipe[1] = rPipe[1];
				lPipe[0] = rPipe[0];


				wait(&status);
		}
	}
}
}
