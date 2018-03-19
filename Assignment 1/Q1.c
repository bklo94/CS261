/* CS261- Assignment 1 - Q.1*/
/* Name:Brandon Lo
 * Date:1/22/17
 * Solution description: Generates and prints out 10 unique and random ID's with associated score.
 */

#include <stdio.h>
#include<stdlib.h>
#include<math.h>

struct student{
	int id;
	int score;
};

struct student* allocate(){
     /*Allocate memory for ten students*/
     struct student *students = malloc(10 * sizeof(struct student));
     /*return the pointer*/
     return students;
}

void generate(struct student* students){
      /*Generate random and unique ID and scores for ten students, ID being between 1 and 10, scores between 0 and 100*/
      int swap = 0;
		struct student temp;

     for (int i = 0; i < 10; i++){
        students[i].id = (i+1);
        students[i].score = (rand() % 101);
     }

	  /*Order of student id's is randomized here.*/
	  for (int i = 0; i < 10; i++){
	 	 swap = rand() % (i+1);

	 	 temp = students[i];
	 	 students[i] = students[swap];

	 	 students[swap] = temp;
	  }
}

void output(struct student* students){
   /*Output information about the ten students in the format:
              ID1 Score1
              ID2 score2
              ID3 score3
              ...
              ID10 score10*/
   for (int i = 0; i < 10; i++){
     printf("ID: %i \t SCORE: %i\n",students[i].id,students[i].score);
   }
}

void summary(struct student* students){
     /*Compute and print the minimum, maximum and average scores of the ten students*/
     int sum = 0,
     max = 0,
     min = 100;
     double avg = 0;

     for (int i = 0; i < 10; i++){
       if (students[i].score < min){
          min = students[i].score;
       }
       else if (students[i].score > max){
          max = students[i].score;
       }
       sum = sum + students[i].score;
     }

     avg = sum/10.0;

     printf("MIN: %i\n", min);
     printf("MAX: %i\n", max);
     printf("AVG: %lf\n", avg);
}

void deallocate(struct student* stud){
     /*Deallocate memory from stud*/
     if(stud != NULL){
        free(stud);
     }
}

int main(){
    struct student* stud = NULL;

    /*call allocate*/
   stud = allocate(stud);
    /*call generate*/
    generate(stud);
    /*call output*/
    output(stud);
    /*call summary*/
    summary(stud);
    /*call deallocate*/
    deallocate(stud);

    return 0;
}
