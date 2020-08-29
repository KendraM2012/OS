#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include <unistd.h>

//Student struct
struct Student{
  int scholorshipTotal; // total money
  int id[3]; // student id's
};

void get_total(int studentID);
void award( int studentID);

struct Student student; // seting struct

int main(){
    student.scholorshipTotal = 4000;
    //sets each student ammount to 0
    student.id[0] = 0;
    student.id[1] = 0;
    student.id[2] = 0;

    pthread_t t1,t2,t3;

    pthread_setconcurrency(3); // setting concurrency
    //creating pthreads
    pthread_create(&t1, NULL, (void *(*)(void *))award,(void *)0);
    pthread_create(&t2, NULL, (void *(*)(void *))award,(void *)1);
    pthread_create(&t3, NULL, (void *(*)(void *))award,(void *)2);

    //joining pthrads
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_join(t3,NULL);
    //total students were awarded
    int studentTotal = student.id[0] + student.id[1] + student.id[2];
    //print total
    printf("Student Total $%d\n", studentTotal);
    //exits the pthreads
    pthread_exit(0);

    return 0;

}

// calulates the award amount
void get_total(int studentID)
{
    sleep(1); //sleeps the program for 1 sec
    int tempMoney = ceil(student.scholorshipTotal *0.25);
    student.scholorshipTotal -= tempMoney;
    student.id[studentID] = student.id[studentID] + tempMoney; //puts the money into each student id
    printf("%c = $%d \n", 'A'+ studentID, tempMoney); //prints money given to students
}
void award(int studentID)
{ // keeps running the program while the amount is not 0
  while (student.scholorshipTotal > 0)
  {
    get_total(studentID); //calls the get_award function
  }
}
