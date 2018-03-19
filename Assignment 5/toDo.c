/* CS261- Assignment 5 - toDo.c*/
/* Name:Brandon Lo
 * Date:3/5/17
 * Solution description: Implementing a switch for the commands to load/read/write and implement the toDo list
 */

#include "dynamicArray.h"
#include "task.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * Loads into heap a list from a file with lines formatted like
 * "priority, name".
 * @param heap
 * @param file
 */
void listLoad(DynamicArray* heap, FILE* file)
{
    const int FORMAT_LENGTH = 256;
    char format[FORMAT_LENGTH];
    snprintf(format, FORMAT_LENGTH, "%%d, %%%d[^\n]", TASK_NAME_SIZE);

    Task temp;
    while (fscanf(file, format, &temp.priority, &temp.name) == 2)
    {
        dyHeapAdd(heap, taskNew(temp.priority, temp.name), taskCompare);
    }
}

/**
 * Writes to a file all tasks in heap with lines formatted like
 * "priority, name".
 * @param heap
 * @param file
 */
void listSave(DynamicArray* heap, FILE* file)
{
    for (int i = 0; i < dySize(heap); i++)
    {
        Task* task = dyGet(heap, i);
        fprintf(file, "%d, %s\n", task->priority, task->name);
    }
}

/**
 * Prints every task in heap.
 * @param heap
 */
void listPrint(DynamicArray* heap)
{
    DynamicArray* temp = dyNew(1);
    dyCopy(heap, temp);
     while (dySize(temp) > 0)
    {
        Task* task = dyHeapGetMin(temp);
        printf("\n");
        taskPrint(task);
        printf("\n");
        dyHeapRemoveMin(temp, taskCompare);
    }
    dyDelete(temp);
}

/**
 * Handles the given command.
 * @param list
 * @param command
 */
void handleCommand(DynamicArray* list, char command)
{
    // FIXME: Implement
	char *fileName = malloc(sizeof(char) * 256);
	char *newTask =  malloc(sizeof(char) * 256);
   int priority;

	switch (command) {
	case 'l': //loading the list
		printf("Please enter the filename:");
		fgets(fileName, 256, stdin); //get the filename, with 255 character limit

      //Followed this instruction for helping the newline creation(formatting) https://piazza.com/class/ixgkmi3ldvo4by?cid=571
		if (fileName[strlen(fileName) - 1] == '\n') //when the newline character is entered
			fileName[strlen(fileName) - 1] = '\0'; //sets the last character to 0, which indicates an end to the string (null terminating character)
		FILE *fileLoad = fopen(fileName, "r"); //sets to read the file
		listLoad(list, fileLoad);
		printf("The list has been loaded from file successfully.");
      printf("\n\n");
		fclose(fileLoad);
		break;

	case 's': //saving to a text file
		printf("Please enter the filename: ");
		fgets(fileName, 256, stdin);

      //Followed this instruction for helping the newline creation(formatting) https://piazza.com/class/ixgkmi3ldvo4by?cid=571
		if (fileName[strlen(fileName) - 1] == '\n') //when the newline character is entered
			fileName[strlen(fileName) - 1] = '\0'; //sets the last character to 0, which indicates an end to the string (null terminating character)
		FILE *fileSave = fopen(fileName, "w"); //sets it to write the file
		listSave(list, fileSave);
		printf("List has been saved into the file successfully.");
      printf("\n\n");
		fclose(fileSave);
		break;

	case 'a': //adding a task and a priority
		printf("Please enter the task description: ");
		fgets(newTask, 256, stdin);

      //Followed this instruction for helping the newline creation(formatting) https://piazza.com/class/ixgkmi3ldvo4by?cid=571
		if (newTask[strlen(newTask) - 1] == '\n') //when the newline character is entered
			newTask[strlen(newTask) - 1] = '\0'; //sets the last character to 0, which indicates an end to the string (null terminating character)
		printf("Please enter the task priority (0-999): ");
		scanf("%i", &priority);
		Task *insertTask = taskNew(priority, newTask); //use taskNew from task.c to create  a new task
      while (getchar() != '\n'); //eats newlines
		dyHeapAdd(list, insertTask, taskCompare);
		printf("The task '%s' has been added to your to-do list", newTask);
      printf("\n\n");
		break;

	case 'g': //display first task
		if (dySize(list) != 0) { //if list is not empty, then get the first task
         struct Task *firstTask = dyHeapGetMin(list);
			printf("Your first task is:%s", firstTask->name);
         printf("\n\n");
		}
		else{ //else list is empty
			printf("Your to-do list is empty!");
         printf("\n\n");
      }
		break;

	case 'r': //remove first task
		if (dySize(list) == 0){//edge case testing if list is empty
			printf("Your to-do list is empty!");
         printf("\n\n");
      }
		else{
			struct Task *removeTask = (struct Task*) dyHeapGetMin(list); //gets the first item in the list/heap
			printf("Your first task '%s' has been removed from the list.", removeTask->name);
         printf("\n\n");
			dyHeapRemoveMin(list, taskCompare); //removes the first item in the list
			taskDelete(removeTask); //memory is freed
		}
		break;

	case 'p': //print out all the tasks
		if (dySize(list) == 0){ //edge case testing if list is empty
			printf("Your to-do list is empty!");
         printf("\n");
      }
		else
			listPrint(list);
		break;

	case 'e': //exit command
		printf("Bye!");
      printf("\n\n");
		break;
	}
}

int main()
{
    // Implement
    printf("\n\n** TO-DO LIST APPLICATION **\n\n");
    DynamicArray* list = dyNew(8);
    char command = ' ';
    do
    {
        printf("Press:\n"
               "'l' to load to-do list from a file\n"
               "'s' to save to-do list to a file\n"
               "'a' to add a new task\n"
               "'g' to get the first task\n"
               "'r' to remove the first task\n"
               "'p' to print the list\n"
               "'e' to exit the program\n"
        );
        command = getchar();
        // Eat newlines
        while (getchar() != '\n');
        handleCommand(list, command);
    }
    while (command != 'e');
 /* free dynamically allocated List pointers in array to avoid memory leaks */
         /* Fix it */
   int i = 0;
	while (i < dySize(list)) { //delete all the tasks in the list
		Task *deletedTask = dyGet(list, i);
		taskDelete(deletedTask);
      i++;
	}

    dyDelete(list); //after all the tasks are deleted, free the list
    return 0;
}
