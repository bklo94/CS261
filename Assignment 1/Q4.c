/* CS261- Assignment 1 - Q.4*/
/* Name:Brandon Lo
 * Date:1/22/17
 * Solution description: Generates a array of students and then sorts that list using insertion sort
 */

#include <stdio.h>
#include<stdlib.h>
#include<math.h>

struct student{
	int id;
	int score;
};


void sort(struct student* students, int n){
     /*Sort the n students based on their score lowest to highest*/
     for (int i = 1; i < n; i++){
        int currentPosition = i;
        struct student temp;

		  /*Inserstion sort*/
        while (currentPosition > 0 && students[currentPosition].score < students[currentPosition-1].score){
           temp = students[currentPosition];
           students[currentPosition] = students[currentPosition-1];
           students[currentPosition-1] = temp;

           currentPosition--;
        }
     }
}


/*Generate function taken from assignment 1 to create an array of students*/
void generate(struct student* students, int n){
      /*Generate random and unique ID and scores for ten students, ID being between n students, scores between 0 and 100*/
     int swap = 0;
	  struct student temp;

     for (int i = 0; i < n; i++){
        students[i].id = (i+1);
        students[i].score = (rand() % 101);
     }

	  /*order of student id's are randomized here*/
     for (int i = 0; i < 10; i++){
	 	 swap = rand() % (i+1);

	 	 temp = students[i];
	 	 students[i] = students[swap];

	 	 students[swap] = temp;
	  }
}

int main(){
    /*Declare an integer n and assign it a value.*/
    int n = 25;
    /*Allocate memory for n students using malloc.*/
    struct student *students = malloc(n * sizeof(struct student));
    /*Generate random and unique IDs and random scores for the n students, using rand().*/
    generate(students, n);
    /*Print the contents of the array of n students.*/
    printf("UNSORTED ARRAY\n");
    for (int i = 0; i < n; i++)
      printf("ID:%i \t SCORE:%i\n", students[i].id, students[i].score);
    /*Pass this array along with n to the sort() function*/
    sort(students, n);
    /*Print the contents of the array of n students.*/
    printf("SORTED ARRAY\n");
    for (int i = 0; i < n; i++)
      printf("ID:%i \t SCORE:%i\n", students[i].id, students[i].score);
    return 0;
}
