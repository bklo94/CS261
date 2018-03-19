/* CS261- Assignment 3 - linkedlist.c*/
/* Name:Brandon Lo
 * Date:2/5/17
 * Solution description: Implementation of the a doubly linked list that can remove links
 from the front and the back of the list. Will also print out everything in the list using the
 sentinels.
 */

#include "linkedList.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

// Double link
struct Link
{
	TYPE value;
	struct Link* next;
	struct Link* prev;
};

// Double linked list with front and back sentinels
struct LinkedList
{
	int size;
	struct Link* frontSentinel;
	struct Link* backSentinel;
};

/**
 * Allocates the list's sentinel and sets the size to 0.
 * The sentinels' next and prev should point to eachother or NULL
 * as appropriate.
 */
static void init(struct LinkedList* list) {
	struct Link * frontLink = (struct Link*)malloc(sizeof(struct Link));
	struct Link * backLink = (struct Link*)malloc(sizeof(struct Link));

	frontLink->prev = backLink;
	frontLink->next = NULL;
	backLink->prev = NULL;
	backLink->next = frontLink;
	list->frontSentinel = frontLink;
	list->backSentinel = backLink;
	list->size = 0;
}

/**
 * Adds a new link with the given value before the given link and
 * increments the list's size.
 */
static void addLinkBefore(struct LinkedList* list, struct Link* link, TYPE value)
{
	assert(list != NULL&& link != NULL);
	struct Link *current = (struct Link *)malloc(sizeof(struct Link));

	/*link value is saved and new temp link is made and has the pointers assigned to it*/
	current->value = value;
	link->prev = current;
	//struct temp is used to hold the link and then is used later to set the current link and the current link's prev
	struct Link *temp = link->prev;
	current->next = link;
	temp->next = current;
	current->prev = temp;
	list->size++;
}

/**
 * Removes the given link from the list and
 * decrements the list's size.
 */
static void removeLink(struct LinkedList* list, struct Link* link)
{
	assert(list->size != 0);

	struct Link *current = link;
	struct Link *prevLink = link->prev;
	struct Link *nextLink = link->next;

	/*links in front and behind are moved and then the memory is freed and size decreased*/
	prevLink->next = nextLink;
	nextLink->prev = prevLink;
	current->next = NULL;
	current->prev = NULL;
	free(current);
	list->size--;
}

/**
 * Allocates and initializes a list.
 */
struct LinkedList* linkedListCreate()
{
	struct LinkedList* newDeque = malloc(sizeof(struct LinkedList));
	init(newDeque);
	return newDeque;
}

/**
 * Deallocates every link in the list including the sentinels,
 * and frees the list itself.
 */
void linkedListDestroy(struct LinkedList* list)
{
	while (!linkedListIsEmpty(list))
	{
		linkedListRemoveFront(list);
	}
	free(list->frontSentinel);
	free(list->backSentinel);
	free(list);
}

/**
 * Adds a new link with the given value to the front of the deque.
 */
void linkedListAddFront(struct LinkedList* list, TYPE value)
{
	struct Link * newLink = (struct Link *)malloc(sizeof(struct Link));
	struct Link * prevLink;
	/*previous link is assigned as the prev link of front senteinel and the prev link is assigned the new link*/
	prevLink = (list->frontSentinel)->prev;
	prevLink->next = newLink;
	(list->frontSentinel)->prev = newLink;
	/*The front and back is assigned to newLink*/
	newLink->next = list->frontSentinel;
	newLink->prev = prevLink;
	newLink->value = value;
	list->size++;
}

/**
 * Adds a new link with the given value to the back of the deque.
 */
void linkedListAddBack(struct LinkedList* list, TYPE value)
{
	struct Link * newLink = (struct Link *)malloc(sizeof(struct Link));
	struct Link * prevLink;
	/*previous link is assigned as the prev link of back senteinel and the prev link is assigned the new link*/
	prevLink = (list->backSentinel)->next;
	prevLink->prev = newLink;
	(list->backSentinel)->next = newLink;
	/*The front and back is assigned to newLink*/
	newLink->prev = list->backSentinel;
	newLink->next = prevLink;
	newLink->value = value;
	list->size++;
}

/**
 * Returns the value of the link at the front of the deque.
 */
TYPE linkedListFront(struct LinkedList* list)
{
	//make sure to check if list is not empty before returning a value
	assert(list->size != 0);

	return list->frontSentinel->prev->value;
}

/**
 * Returns the value of the link at the back of the deque.
 */
TYPE linkedListBack(struct LinkedList* list)
{
	//make sure to check if list is not empty before returning a value
	assert(list->size != 0);

	return list->backSentinel->next->value;
}

/**
 * Removes the link at the front of the deque.
 */
void linkedListRemoveFront(struct LinkedList* list)
{
	assert(list->size != 0);
	/*Current link is deleted and a new link is assigned at the front*/
	struct Link * current;
	current = list->frontSentinel->prev;
	struct Link * newLink;
	//sets a new link the end of the list and then the pointers are assienged to the frontSentinel
	newLink = list->frontSentinel->prev->prev;
	newLink->next = list->frontSentinel;
	list->frontSentinel->prev = newLink;
	/*links are set to null to avoid hanging pointers and then the memory is freed*/
	current->prev = NULL;
	current->next = NULL;
	free(current);
	current = NULL;
	list->size--;
}

/**
 * Removes the link at the back of the deque.
 */
void linkedListRemoveBack(struct LinkedList* list)
{
	assert(list->size != 0);
	/*Current link is deleted and a new link is assigned at the back
	similar code to the removeFront except the backSentinel is use and
	the pointers are reversed since the operations are for the back of the linkedList
	instead of the front*/
	struct Link * current;
	current = list->backSentinel->next;
	struct Link * newLink;
	//sets a new link the end of the list and then the pointers are assienged to the backSentinel
	newLink = list->backSentinel->next->next;
	newLink->prev = list->backSentinel;
	list->backSentinel->next = newLink;
	/*links are set to null to avoid hanging pointers and then the memory is freed*/
	current->prev = NULL;
	current->next = NULL;
	free(current);
	current = NULL;
	list->size--;
}

/**
 * Returns 1 if the deque is empty and 0 otherwise.
 */
int linkedListIsEmpty(struct LinkedList* list)
{
	if(list->size == 0)
		return 1;
	else
		return 0;
}

/**
 * Prints the values of the links in the deque from front to back.
 */
void linkedListPrint(struct LinkedList* list)
{
	//make sure to check if list isn't empty before you start the do while loop
	assert(list->size != 0);

	struct Link * current = list->frontSentinel->prev;
	do{
		printf("%d\n", current->value);
		current = current->prev;
	}while (current->prev != 0);
	printf("\n");
}

/**
 * Adds a link with the given value to the bag.
 */
void linkedListAdd(struct LinkedList* list, TYPE value)
{
	assert(list != NULL);
	//adds value to the back, but front would work the same. Order doesn't matter since it is in a bag
	linkedListAddBack(list,value);
}


/**
* Returns 1 if a link with the value is in the bag and 0 otherwise.
*/
int linkedListContains(struct LinkedList* list, TYPE value)
{
	assert(list->size != 0);

	struct Link * current = list->frontSentinel->prev;
	do {
		if (current->value == value)
			return 1;
		else
			current = current->prev;
	} while (current->prev != 0);
	return 0;
}

/**
* Removes the first occurrence of a link with the given value.
*/
void linkedListRemove(struct LinkedList* list, TYPE value)
{
	//makes sure the list not empty and also contains the value before running the remove operation
	assert(list->size != 0);
	assert(linkedListContains(list, value));

	struct Link * current = list->frontSentinel->prev;
	do {
		if (current->value == value) {
			current->next->prev = current->prev;
			current->prev->next = current->next;
			//links are set to null to avoid hanging pointers and the memory is freed
			current->next = NULL;
			current->prev = NULL;
			free(current);
			list->size--;
			return; //ends the loop if the if runs
		}
		else
			current = current->prev;
	}while (current != 0);
}
