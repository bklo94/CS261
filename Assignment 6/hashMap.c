/*
 * CS 261 Data Structures
 * Assignment 6
 * Name: Brandon Lo
 * Date:3/12/17
 */

#include "hashMap.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

int hashFunction1(const char* key)
{
    int r = 0;
    for (int i = 0; key[i] != '\0'; i++)
    {
        r += key[i];
    }
    return r;
}

int hashFunction2(const char* key)
{
    int r = 0;
    for (int i = 0; key[i] != '\0'; i++)
    {
        r += (i + 1) * key[i];
    }
    return r;
}

/**
 * Creates a new hash table link with a copy of the key string.
 * @param key Key string to copy in the link.
 * @param value Value to set in the link.
 * @param next Pointer to set as the link's next.
 * @return Hash table link allocated on the heap.
 */
HashLink* hashLinkNew(const char* key, int value, HashLink* next)
{
    HashLink* link = malloc(sizeof(HashLink));
    link->key = malloc(sizeof(char) * (strlen(key) + 1));
    strcpy(link->key, key);
    link->value = value;
    link->next = next;
    return link;
}

/**
 * Free the allocated memory for a hash table link created with hashLinkNew.
 * @param link
 */
static void hashLinkDelete(HashLink* link)
{
    free(link->key);
    free(link);
}

/**
 * Initializes a hash table map, allocating memory for a link pointer table with
 * the given number of buckets.
 * @param map
 * @param capacity The number of table buckets.
 */
void hashMapInit(HashMap* map, int capacity)
{
    map->capacity = capacity;
    map->size = 0;
    map->table = malloc(sizeof(HashLink*) * capacity);
    for (int i = 0; i < capacity; i++)
    {
        map->table[i] = NULL;
    }
}

/**
 * Removes all links in the map and frees all allocated memory. You can use
 * hashLinkDelete to free the links.
 * @param map
 */
void hashMapCleanUp(HashMap* map)
{
    // FIXME: implement
    assert(map != NULL);
    HashLink *next;
    HashLink *current;
    int i = 0;
    //removes all links
    while (i != map->capacity){
      current = map->table[i];
      //deletes all the free links
      while(current != NULL){
         next = current->next;
         hashLinkDelete(current);
         current = next;
      }
      i++;
   }
   //after links are free, map is freed
   free(map->table);
   map->size = 0;
}

/**
 * Creates a hash table map, allocating memory for a link pointer table with
 * the given number of buckets.
 * @param capacity The number of buckets.
 * @return The allocated map.
 */
HashMap* hashMapNew(int capacity)
{
    HashMap* map = malloc(sizeof(HashMap));
    hashMapInit(map, capacity);
    return map;
}

/**
 * Removes all links in the map and frees all allocated memory, including the
 * map itself.
 * @param map
 */
void hashMapDelete(HashMap* map)
{
    hashMapCleanUp(map);
    free(map);
}

/**
 * Returns a pointer to the value of the link with the given key. Returns NULL
 * if no link with that key is in the table.
 *
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket. Also make sure to search the entire list.
 *
 * @param map
 * @param key
 * @return Link value or NULL if no matching link.
 */
int* hashMapGet(HashMap* map, const char* key)
{
    // FIXME: implement
    assert(map != NULL);
    assert(key != NULL);
    int index = HASH_FUNCTION(key) % hashMapCapacity(map);
    HashLink* current = map->table[index];

    //searches for the key then returns it
    while(current != NULL){
      if(strcmp(current->key, key) == 0)
         return &(current->value);
      current = current->next;
   }
   //default is returning NULL if it is not found
    return NULL;
}

/**
 * Resizes the hash table to have a number of buckets equal to the given
 * capacity. After allocating the new table, all of the links need to be
 * rehashed into it because the capacity has changed.
 *
 * Remember to free the old table and any old links if you use hashMapPut to
 * rehash them.
 *
 * @param map
 * @param capacity The new number of buckets.
 */
void resizeTable(HashMap* map, int capacity)
{
    // FIXME: implement
    int currentCapacity = hashMapCapacity(map);
    HashMap* temp = hashMapNew(capacity);
    int i = 0;

    //rehashing all the links
    while(i != currentCapacity){
      HashLink *current = map->table[i];
      //puts the current map's values into the new table
      while(current != NULL){
         hashMapPut(temp,current->key,current->value);
         current = current->next;
      }
      i++;
   }
    //freeing old table links and reassigning the sizes
    hashMapCleanUp(map);
    map->size = temp->size;
    map->table = temp->table;
    map->capacity = temp->capacity;
    temp->table = NULL;

    free(temp);
}

/**
 * Updates the given key-value pair in the hash table. If a link with the given
 * key already exists, this will just update the value. Otherwise, it will
 * create a new link with the given key and value and add it to the table
 * bucket's linked list. You can use hashLinkNew to create the link.
 *
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket. Also make sure to search the entire list.
 *
 * @param map
 * @param key
 * @param value
 */
void hashMapPut(HashMap* map, const char* key, int value)
{
    // FIXME: implement
    int currentCapacity = hashMapCapacity(map);
    int index = HASH_FUNCTION(key) % hashMapCapacity(map);

    if(index < 0)
      index = index + currentCapacity;
   //update the value since it exists
   if(hashMapContainsKey(map,key)){
      int *newValue = hashMapGet(map,key);
      (*newValue) += value;
   }
   //create a new link with the given key and value using hashLinkNew
   else{
      HashLink* new = hashLinkNew(key, value, NULL);
      assert(new != NULL);
      //create a link if it is the last value
      if(map->table[index] == NULL)
         map->table[index] = new;
      //else it goes through until it finds the last last link
      else{
         HashLink *current = map->table[index];
         while(current->next != NULL)
            current = current->next;
         current->next = new;
      }
      map->size++;
   }

   //resize if the table is too large
   if(hashMapTableLoad(map) >= MAX_TABLE_LOAD)
      resizeTable(map,2*currentCapacity);
}

/**
 * Removes and frees the link with the given key from the table. If no such link
 * exists, this does nothing. Remember to search the entire linked list at the
 * bucket. You can use hashLinkDelete to free the link.
 * @param map
 * @param key
 */
void hashMapRemove(HashMap* map, const char* key)
{
    // FIXME: implement
    assert(map != NULL);
    assert(key != NULL);
    int index = HASH_FUNCTION(key) % hashMapCapacity(map);
    HashLink *currentLink = map->table[index];
    HashLink *previousLink;

    //if it is not the end of the map/empty
    if(currentLink != NULL){
      //if the key is found then
      if (strcmp(currentLink->key, key) == 0)
         map->table[index] = currentLink->next;
      else{
         //search the entire linked list at the bucket
         while(strcmp(currentLink->key, key) != 0){
            previousLink = currentLink;
            currentLink = currentLink->next;
         }
         //while the "search link" does not hit the end of the list
         if(previousLink != NULL)
            previousLink->next = currentLink->next;
      }
      //hashLinkDelete to free the link
      hashLinkDelete(currentLink);
      map->size--;
   }
}

/**
 * Returns 1 if a link with the given key is in the table and 0 otherwise.
 *
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket. Also make sure to search the entire list.
 *
 * @param map
 * @param key
 * @return 1 if the key is found, 0 otherwise.
 */
int hashMapContainsKey(HashMap* map, const char* key)
{
    // FIXME: implement
    assert(key != NULL);
    assert(map != NULL);
    int capacity = hashMapCapacity(map);
    int index = HASH_FUNCTION(key) % capacity;

    if (index < 0)
      index = index + capacity;
    HashLink* current = map->table[index];
    //while link is not the end, it searches and uses strcmp to find the link.
    while(current != NULL) {
      if (strcmp(current->key, key) == 0)
         return 1;
      current = current->next;
    }
    //default is that it is not found
    return 0;
}

/**
 * Returns the number of links in the table.
 * @param map
 * @return Number of links in the table.
 */
int hashMapSize(HashMap* map)
{
    // FIXME: implement
    assert(map != NULL);
    return map->size;
}

/**
 * Returns the number of buckets in the table.
 * @param map
 * @return Number of buckets in the table.
 */
int hashMapCapacity(HashMap* map)
{
    // FIXME: implement
    assert(map != NULL);
    return map->capacity;
}

/**
 * Returns the number of table buckets without any links.
 * @param map
 * @return Number of empty buckets.
 */
int hashMapEmptyBuckets(HashMap* map)
{
    // FIXME: implement
    int numBuckets = 0;
    int i = 0;
    //goes through the buckets and looks for the ones without any linkes
    while(i < hashMapCapacity(map)){
      if(map->table[i] == NULL)
         numBuckets++;
      i++;
   }

    return numBuckets;
}

/**
 * Returns the ratio of (number of links) / (number of buckets) in the table.
 * Remember that the buckets are linked lists, so this ratio tells you nothing
 * about the number of empty buckets. Remember also that the load is a floating
 * point number, so don't do integer division.
 * @param map
 * @return Table load.
 */
float hashMapTableLoad(HashMap* map)
{
    // FIXME: implement
    assert(map != NULL);
    float numLinks = (float) hashMapSize(map);
    float numBuckets = (float) hashMapCapacity(map);
    float ratio = numLinks/numBuckets;

    return ratio;
}

/**
 * Prints all the links in each of the buckets in the table.
 * @param map
 */
void hashMapPrint(HashMap* map)
{
    for (int i = 0; i < map->capacity; i++)
    {
        HashLink* link = map->table[i];
        if (link != NULL)
        {
            printf("\nBucket %i ->", i);
            while (link != NULL)
            {
                printf(" (%s, %d) ->", link->key, link->value);
                link = link->next;
            }
        }
    }
    printf("\n");
}
