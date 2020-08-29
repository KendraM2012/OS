/* Kendra Maggiore Spring 2020 */

#include <stdio.h>
#include <stdlib.h>
#define MAX_STUDENTS 10
int main()
{
  char studentNames[MAX_STUDENTS][10]; // 2d array for students
  double studentGPA[10]; // double for gpa's
  int count = 0;
  int i =0;
  //printf("Enter the students names and GPA. When done use ctrl-d.\n");

  while (scanf("%s %lf\n",&studentNames[count],&studentGPA[count]) !=EOF) {  //takes names and gpa in until crl-D
    count++;
    if(count == 10)
      break;
  }

  //printf("-------------------------------\n");
  //printf("students with GPA 3.0 or better\n");

  for (i; i< count; i++) {
      if(studentGPA[i] >= 3.0) // looks to see if student gpa is above or equal to 3.0
      {
        printf("%s \n", studentNames[i]);
      }
  }

}
