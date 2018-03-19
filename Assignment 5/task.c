/* CS261- Assignment 5 - task.c*/
/* Name:Brandon Lo
 * Date:3/5/17
 * Solution description: Implementing a compare function and creating a new task
 */

#include "task.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * Creates a new task with the given priority and name.
 * @param priority
 * @param name
 * @return  The new task.
 */
Task* taskNew(int priority, char* name)
{
   // FIXME: implement
   struct Task *newTask = malloc(sizeof(struct Task)); //allocate memory to newTask
   strcpy(newTask->name, name); //copy the given name to the new task
   newTask->priority = priority;  //give the given priority to the newTask

   return newTask;
}

/**
 * Frees a dynamically allocated task.
 * @param task
 */
void taskDelete(Task* task)
{
    free(task);
}

/**
 * Casts left and right to Task pointers and returns
 * -1 if left's priority < right's priority,
 *  1 if left's priority > right's priority,
 *  0 if left's priority == right's priority.
 * @param left  Task pointer.
 * @param right  Task pointer.
 * @return
 */
int taskCompare(void* left, void* right)
{
   // FIXME: implement
   struct Task* leftCompare = left;
   struct Task* rightCompare = right;

   if (leftCompare->priority < rightCompare->priority)
      return -1;
   else if (leftCompare->priority > rightCompare->priority)
      return  1;
   else
      return 0;
}

/**
 * Prints a task as a (priority, name) pair.
 * @param value  Task pointer.
 */
void taskPrint(void* value)
{
    Task* task = (Task*)value;
    printf("(%d, %s)", task->priority, task->name);
}
