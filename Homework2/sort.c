#include <stdio.h>
#include<string.h>
#define MAX_STUDENTS 10
int main()
{
  char studentNames[MAX_STUDENTS][10], temp[10]; // 2d array for students
  int count = 0;
  //printf("Enter the students. When done use ctrl-d.\n");
  int i=0;
  for(i; i< MAX_STUDENTS; i++){
    if(scanf("%s", &studentNames[i]) != EOF) // takes in stundet names
        count ++;
  }
  int k = 0;
  for (k; k < count; k++)  // sorts student names 
        {
            int j = k + 1;
            for (j; j < count; j++)
            {
                if (strcmp(studentNames[k], studentNames[j]) > 0)
                {
                    strcpy(temp, studentNames[k]);
                    strcpy(studentNames[k], studentNames[j]);
                    strcpy(studentNames[j], temp);
                }
            }
        }


  //printf("The students names in aphabetical order are: \n");
  int g = 0;
  for (g; g < count; g++) {
      printf("%s\n",studentNames[g]);
  }
}
