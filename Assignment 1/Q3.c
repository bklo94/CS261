/* CS261- Assignment 1 - Q.3*/
/* Name:Brandon Lo
 * Date:1/22/17
 * Solution description: Program that sorts an integer array
 */

#include <stdio.h>
#include<stdlib.h>
#include<math.h>

/*insertion sort*/
void sort(int* number, int n){
   /*Sort the given array number , of length n*/
   for (int i = 1; i < n; i++){
      int currentPosition = i,
      temp = 0;

      /*Inserstion sort*/
      while (currentPosition > 0 && *(number+currentPosition) < *(number+currentPosition-1)){
         temp = *(number+currentPosition);
         *(number+currentPosition)=*(number+currentPosition-1);
         *(number+currentPosition-1) = temp;

         currentPosition--;
      }
   }
}

int main(){
   /*Declare an integer n and assign it a value of 20.*/
   int n = 20;

   /*Allocate memory for an array of n integers using malloc.*/
   int *arr = (int *)malloc(sizeof(int) * n);

   /*Fill this array with random numbers, using rand().*/
   for (int i = 0; i < n; i++){
      *(arr+i) = rand() % 100;
   }

   /*Print the contents of the array.*/
   printf("UNSORTED ARRAY\n");
   for (int i = 0; i < n; i++){
      printf("%i, ", *(arr+i));
   }

   /*Pass this array along with n to the sort() function of part a.*/
   sort(arr, n);

   /*Print the contents of the array.*/
   printf("SORTED ARRAY\n");
   for (int i = 0; i < n; i++){
      printf("%i, ", *(arr+i));
   }

   return 0;
}
