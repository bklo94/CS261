/* CS261- Assignment 1 - Q.5*/
/* Name:Brandon Lo
 * Date:1/22/17
 * Solution description: Program that takes a string then outputs it in StUdLy CaPs.
 */

#include <stdio.h>
#include <stdlib.h>

/*converts ch to upper case, assuming it is in lower case currently*/
char toUpperCase(char ch){
     return ch-'a'+'A';
}

/*converts ch to lower case, assuming it is in upper case currently*/
char toLowerCase(char ch){
     return ch-'A'+'a';
}

void sticky(char* word){
     /*Convert to sticky caps*/
    char currentCharater;

    for ( int index = 0; *word; index++){
        currentCharater = *word;
        if ((index % 2) == 0 && currentCharater >= 'a' && currentCharater <= 'z')
            *word = toUpperCase(currentCharater);
        else if((index % 2) != 0 && currentCharater >= 'A' && currentCharater <= 'Z')
            *word = toLowerCase(currentCharater);
        word++;
    }

}

int main(){
   char stringWord[1000];
    /*Read word from the keyboard using scanf*/
    printf("Reading a word from keyboard: ");
    scanf("%s", stringWord);
    /*Call sticky*/
    sticky(stringWord);
    /*Print the new word*/
    printf("%s\n", stringWord);
    return 0;
}
