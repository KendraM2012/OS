#include <stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
  pid_t pid; //sets the pid
  int process[2]; //sets how many process

  pipe(process); // puts the procces into a pipe
  pid = fork(); // sets pid to fork

  if(pid < 0) // checks if pid is empty
  {
    printf("pipe failed exiting program");
    exit(EXIT_FAILURE);
  }
  if(pid == 0) // child
  {
    close(1);
    dup(process[1]);
    close(process[1]);
    close(process[0]);
    execlp("./pre","pre",  (char*) NULL);
  }
  else  // parent
  {
    close(0);
    dup(process[0]);
    close(process[1]);
    close(process[0]);
    execlp("./sort","sort",(char*) NULL);
  }
  return 0;
}
