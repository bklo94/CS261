/* CS261- Assignment 1 - Q. 0*/
/* Name:Brandon Lo
 * Date:1/22/17
 * Solution description: Prints out the address and value of the pointer. Also uses fooA to print out the address, value, and value that is pointing to it.
 */

#include <stdio.h>
#include <stdlib.h>

void fooA(int* iptr){
     /*Print the value pointed to by iptr*/
     printf("%i\n", *iptr);
     /*Print the address pointed to by iptr*/
     printf("%p\n", iptr);
     /*Print the address of iptr itself*/
     printf("%p\n", &iptr);
}

int main(){

    /*declare an integer x*/
    int x = 10;
    /*print the address of x*/
    printf("%p\n", &x);
    /*Call fooA() with the address of x*/
    fooA(&x);
    /*print the value of x*/
    printf("%i\n", x);

    return 0;
}
