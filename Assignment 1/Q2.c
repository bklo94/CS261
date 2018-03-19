/* CS261- Assignment 1 - Q.2*/
/* Name:Brandon Lo
 * Date:1/22/17
 * Solution description: More pointer practice where it tests the concept of pass by value versus pass by reference
 */

#include <stdio.h>
#include <stdlib.h>

int foo(int* a, int* b, int c){
    /*Set a to double its original value*/
    *a = *a * 2;
    /*Set b to half its original value*/
    *b = *b / 2;
    /*Assign a+b to c*/
    c = *a + *b;
    /*Return c*/
    return c;
}

int main(){
    /*Declare three integers x,y and z and initialize them to 5, 6, 7 respectively*/
    int x =5,
    y = 6,
    z = 7;
    /*Print the values of x, y and z*/
    printf("X: %i\n", x);
    printf("Y: %i\n", y);
    printf("Z: %i\n", z);
    /*Call foo() appropriately, passing x,y,z as parameters*/
    int answer = foo(&x,&y,z);
    /*Print the value returned by foo*/
    printf("foo: %i\n", answer);
    /*Print the values of x, y and z again*/
    printf("X: %i\n", x);
    printf("Y: %i\n", y);
    printf("Z: %i\n", z);
    /*Is the return value different than the value of z?  Why?*/
    return 0;
}

/*Even though the foo return value returns C, it is not changed because it was passed by value, so the c value inside the function(local).
Since x and y were passed by reference, they were changed globally. Therefore that is why z was not changed.*/
