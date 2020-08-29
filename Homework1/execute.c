#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main(int argc, char const *argv[]) {
  int pid;
  pid = fork(); //sets pid to fork

  if(pid < 0) // checks if pipe is empty
  {
    printf("pipe failed exiting program");
    exit(EXIT_FAILURE);
  }
  else if(pid ==0) //child
  {
    printf("The child pid is: %d, and the parent pid is: %d\n",getpid(),getpid());
    execvp(argv[1], argv +1);
  }
  else // parent
  {
    //printf("The child pid is: %d, and the parent pid is: %d\n",getpid(),getpid());
    wait(NULL);
  }
  return 0;
}
