/* CS261- Assignment 3 - circularList.c*/
/* Name:Brandon Lo
 * Date:2/5/17
 * Solution description: Implementation of the a circular list which is singularly linked
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "circularList.h"

// Double link
struct Link
{
	TYPE value;
	struct Link * next;
	struct Link * prev;
};

struct CircularList
{
	int size;
	struct Link* sentinel;
};

/**
 * Allocates the list's sentinel and sets the size to 0.
 * The sentinel's next and prev should point to the sentinel itself.
 */
static void init(struct CircularList* list)
{
	list->sentinel = (struct Link *)malloc(sizeof(struct Link));
	assert(list->sentinel != 0);

	list->sentinel->next = list->sentinel;
	list->sentinel->prev = list->sentinel;
	list->sentinel->value = 0;
	list->size = 0;

}

/**
 * Creates a link with the given value and NULL next and prev pointers.
 */
static struct Link* createLink(TYPE value)
{
	struct Link *newLink = (struct Link *)malloc(sizeof(struct Link));

	//next and prev pointers are set to give value and null set to the pointers
	newLink->next = 0;
	newLink->prev = 0;
	newLink->value = value;
	return newLink;
}

/**
 * Adds a new link with the given value after the given link and
 * increments the list's size.
 */
static void addLinkAfter(struct CircularList* list, struct Link* link, TYPE value)
{
	struct Link *newLink = createLink(value);

	//new link is added and the pointers are set.
	newLink->next = link->next;
	newLink->prev = link;
	newLink->next->prev = newLink;
	newLink->prev->next = newLink;
	list->size++; //original list size is also increased
}

/**
 * Removes the given link from the list and
 * decrements the list's size.
 */
static void removeLink(struct CircularList* list, struct Link* link)
{
	link->prev->next = link->next;
	link->next->prev = link->prev;
	//links have the points set to null to avoid hanging pointers
	link->prev = NULL;
	link->next = NULL;
	free(link);
	link = NULL;
	list->size--; //original list size is also decreased
}

/**
 * Allocates and initializes a list.
 */
struct CircularList* circularListCreate()
{
	struct CircularList* list = malloc(sizeof(struct CircularList));
	init(list);
	return list;
}

/**
 * Deallocates every link in the list and frees the list pointer.
 */
void circularListDestroy(struct CircularList* list)
{
	while (!circularListIsEmpty(list)){ //runs while the list is not empty. Stops running when it returns a 1.
		struct Link *current = list->sentinel->next;
		removeLink(list,current);
	}
	
	free(list->sentinel);
	free(list);
}

/**
 * Adds a new link with the given value to the front of the deque.
 */
void circularListAddFront(struct CircularList* list, TYPE value)
{
	addLinkAfter(list,list->sentinel,value);
}

/**
 * Adds a new link with the given value to the back of the deque.
 */
void circularListAddBack(struct CircularList* list, TYPE value)
{
	addLinkAfter(list,list->sentinel->prev,value);
}

/**
 * Returns the value of the link at the front of the deque.
 */
TYPE circularListFront(struct CircularList* list)
{
	//assert to check there is something to return
	assert(list != NULL);

	return list->sentinel->next->value;
}

/**
 * Returns the value of the link at the back of the deque.
 */
TYPE circularListBack(struct CircularList* list)
{
	//assert to check there is something to return
	assert(list != NULL);

	return list->sentinel->prev->value;
}

/**
 * Removes the link at the front of the deque.
 */
void circularListRemoveFront(struct CircularList* list)
{
	//makes sure list is not empty before removing the front
	assert(list != NULL);

	removeLink(list,(list->sentinel)->next);
}

/**
 * Removes the link at the back of the deque.
 */
void circularListRemoveBack(struct CircularList* list)
{
	//makes sure list is not empty before removing the back
	assert(list != NULL);

	removeLink(list,(list->sentinel)->prev);
}

/**
 * Returns 1 if the deque is empty and 0 otherwise.
 */
int circularListIsEmpty(struct CircularList* list)
{
	//simeple function that just checks the size of the list which should show 0 if its empty.
	if(list->size == 0)
		return 1;
	else
		return 0;
}

/**
 * Prints the values of the links in the deque from front to back.
 */
void circularListPrint(struct CircularList* list)
{
	//make sure to check if list isn't empty before you start the do while loop
	assert(list != NULL);

	int size = list->size;
	struct Link *current = list->sentinel->next;

	while (size){ //runs while size is not null or 0
		printf("%g\n", current->value);
		current = current->next;
		size--;
	}
	printf("\n");
}

/**
 * Reverses the deque.
 */
void circularListReverse(struct CircularList* list)
{
	//assert to check that there is something to reverse
	assert(list != NULL);

	struct Link *current = list->sentinel;
	struct Link * temp;
	// a temporary struct is made in order to hold the swapping links
	for (int i = 0; i < list->size + 1; i++) {
		temp = current->next;
		current->next = current->prev;
		current->prev = temp;
		current = current->next;
	}
}
