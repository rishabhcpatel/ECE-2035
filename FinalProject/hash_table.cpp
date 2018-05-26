/*
 Student Name: Rishabh C. Patel
 Date: 3/25/18

=======================
ECE 2035 Project 2-1:
=======================
This file provides definition for the structs and functions declared in the
header file. It also contains helper functions that are not accessible from
outside of the file.

FOR FULL CREDIT, BE SURE TO TRY MULTIPLE TEST CASES and DOCUMENT YOUR CODE.

===================================
Naming conventions in this file:
===================================
1. All struct names use camel case where the first letter is capitalized.
  e.g. "HashTable", or "HashTableEntry"

2. Variable names with a preceding underscore "_" will not be called directly.
  e.g. "_HashTable", "_HashTableEntry"

  Recall that in C, we have to type "struct" together with the name of the struct
  in order to initialize a new variable. To avoid this, in hash_table.h
  we use typedef to provide new "nicknames" for "struct _HashTable" and
  "struct _HashTableEntry". As a result, we can create new struct variables
  by just using:
    - "HashTable myNewTable;"
     or
    - "HashTableEntry myNewHashTableEntry;"

  The preceding underscore "_" simply provides a distinction between the names
  of the actual struct defition and the "nicknames" that we use to initialize
  new structs.
  [See Hidden Definitions section for more information.]

3. Functions, their local variables and arguments are named with camel case, where
  the first letter is lower-case.
  e.g. "createHashTable" is a function. One of its arguments is "numBuckets".
       It also has a local variable called "newTable".

4. The name of a struct member is divided by using underscores "_". This serves
  as a distinction between function local variables and struct members.
  e.g. "num_buckets" is a member of "HashTable".

*/

/****************************************************************************
* Include the Public Interface
*
* By including the public interface at the top of the file, the compiler can
* enforce that the function declarations in the the header are not in
* conflict with the definitions in the file. This is not a guarantee of
* correctness, but it is better than nothing!
***************************************************************************/
#include "hash_table.h"


/****************************************************************************
* Include other private dependencies
*
* These other modules are used in the implementation of the hash table module,
* but are not required by users of the hash table.
***************************************************************************/
#include <stdlib.h>   // For malloc and free
#include <stdio.h>    // For printf


/****************************************************************************
* Hidden Definitions
*
* These definitions are not available outside of this file. However, because
* the are forward declared in hash_table.h, the type names are
* available everywhere and user code can hold pointers to these structs.
***************************************************************************/
/**
 * This structure represents an a hash table.
 * Use "HashTable" instead when you are creating a new variable. [See top comments]
 */
struct _HashTable {
  /** The array of pointers to the head of a singly linked list, whose nodes
      are HashTableEntry objects */
  HashTableEntry** buckets;

  /** The hash function pointer */
  HashFunction hash;

  /** The number of buckets in the hash table */
  unsigned int num_buckets;
};

/**
 * This structure represents a hash table entry.
 * Use "HashTableEntry" instead when you are creating a new variable. [See top comments]
 */
struct _HashTableEntry {
  /** The key for the hash table entry */
  unsigned int key;

  /** The value associated with this hash table entry */
  void* value;

  /**
  * A pointer pointing to the next hash table entry
  * NULL means there is no next entry (i.e. this is the tail)
  */
  HashTableEntry* next;
};


/****************************************************************************
* Private Functions
*
* These functions are not available outside of this file, since they are not
* declared in hash_table.h.
***************************************************************************/
/**
* createHashTableEntry
*
* Helper function that creates a hash table entry by allocating memory for it on
* the heap. It initializes the entry with key and value, initialize pointer to
* the next entry as NULL, and return the pointer to this hash table entry.
*
* @param key The key corresponds to the hash table entry
* @param value The value stored in the hash table entry
* @return The pointer to the hash table entry
*/
static HashTableEntry* createHashTableEntry(unsigned int key, void* value) {
    //First, malloc the space for the date in the struct HashTableEntry
    HashTableEntry* newPtr = (HashTableEntry*)malloc(sizeof(HashTableEntry));
    if(!newPtr) return newPtr;
    //Once space is allocated, point the pointer to key,value,next
    newPtr->key = key;
    newPtr->value = value; 
    newPtr->next = NULL;
    return newPtr;      
}

/**
* findItem
*
* Helper function that checks whether there exists the hash table entry that
* contains a specific key.
*
* @param hashTable The pointer to the hash table.
* @param key The key corresponds to the hash table entry
* @return The pointer to the hash table entry, or NULL if key does not exist
*/
static HashTableEntry* findItem(HashTable* hashTable, unsigned int key) {   
    //To get to the item, get the bucket index by using the hash fuction in hashtable
    HashTableEntry* newPtr;
    unsigned int bucketLocation = hashTable->hash(key); 
    newPtr = hashTable->buckets[bucketLocation];        
    //Once the index is obtained, walk the list until the key has been found.
    while(newPtr)
    {
        if(newPtr->key==key) return newPtr;
        newPtr = newPtr->next;
    }
    return NULL;


}

/****************************************************************************
* Public Interface Functions
*
* These functions implement the public interface as specified in the header
* file, and make use of the private functions and hidden definitions in the
* above sections.
****************************************************************************/
// The createHashTable is provided for you as a starting point.
HashTable* createHashTable(HashFunction hashFunction, unsigned int numBuckets) {
  // The hash table has to contain at least one bucket. Exit gracefully if
  // this condition is not met.
  if (numBuckets==0) {
    printf("Hash table has to contain at least 1 bucket...\n");
    exit(1);
  }

  // Allocate memory for the new HashTable struct on heap.
  HashTable* newTable = (HashTable*)malloc(sizeof(HashTable));

  // Initialize the components of the new HashTable struct.
  newTable->hash = hashFunction;
  newTable->num_buckets = numBuckets;
  newTable->buckets = (HashTableEntry**)malloc(numBuckets*sizeof(HashTableEntry*));

  // As the new buckets are empty, init each bucket as NULL.
  unsigned int i;
  for (i=0; i<numBuckets; ++i) {
    newTable->buckets[i] = NULL;
  }

  // Return the new HashTable struct.
  return newTable;
}

void destroyHashTable(HashTable* hashTable) {
    //Create temp pointers to hold the value and next pointer in current hashtableentry.
    if(hashTable){
    HashTableEntry* temp;
    HashTableEntry* temp2;
    unsigned int numBuckets = hashTable->num_buckets;
    //Loop thought the number of buckets present in the hashtable and walk the list
    //at each bucket index to free value and next pointer stored in temp pointers
    for(int i = 0; i < numBuckets; i++)
    {
        //newPtr = hashTable->buckets[i];
        while(hashTable->buckets[i])
        {
            temp = (HashTableEntry*)hashTable->buckets[i]->value;
            temp2 = (HashTableEntry*)hashTable->buckets[i];
            hashTable->buckets[i] = temp2->next;
            free(temp);
            free(temp2);         
        }  
    }
    //Once the list is walked, free the all the buckets in the hashtable, and free
    //the hashtable itself
    free(hashTable->buckets);
    free(hashTable);
    }
}

void* insertItem(HashTable* hashTable, unsigned int key, void* value) { 
    //Inorder to insert the item, get the bucket index using hash function and walk the list 
    // to see if the key exists.
    HashTableEntry* newPtr;
    unsigned int bucketLocation = hashTable->hash(key);
    newPtr = findItem(hashTable, key);
    //if the key is found while walking the hashtableentry, return the old value and overwrite 
    //the present value in the current hashtable entry 
    if(newPtr)
    {
        void* currentVal = newPtr->value;
        newPtr->value = value;
        return currentVal;  
        
    }
    //If the key isnt found, create a new entry using createhashtableentry and point the
    //appropriate pointers inorder to insert the entry 
    newPtr = createHashTableEntry(key, value);  
    //if(!newPtr) return newPtr;
    newPtr->next = hashTable->buckets[bucketLocation];
    hashTable->buckets[bucketLocation] = newPtr;
    //newPtr->value = value;
    return NULL;    
}

void* getItem(HashTable* hashTable, unsigned int key) {
    //call findItem() to get the pointer to the hashtableentry.
    HashTableEntry* newPtr;
    newPtr = findItem(hashTable,key);
    if(newPtr == NULL) return NULL;
    //return value corresponding to the key
    //once at the hashtableentry, return the pointer to the value
    return newPtr->value;
}

void* removeItem(HashTable* hashTable, unsigned int key) {
    //use the hash() function to get the bucket index in the hashtable;
    //create temp pointers to store hashtable entry data. 
    HashTableEntry* newPtr;
    HashTableEntry* temp;
    HashTableEntry* temp2;
    unsigned int bucketLocation = hashTable->hash(key); 
    if(!(hashTable->buckets[bucketLocation])) return NULL;
    //if the key is present in the first hashtableentry of the appropriate bucket index 
    if(hashTable->buckets[bucketLocation]->key==key)
    {
        temp = (HashTableEntry*)hashTable->buckets[bucketLocation]->value;
        temp2 = (HashTableEntry*)hashTable->buckets[bucketLocation];
        //update the hashtable pointer to the next location
        hashTable->buckets[bucketLocation] = hashTable->buckets[bucketLocation]->next;
        //once the pointer is updated, free the pointer to the value.
        free(temp2);
        return temp;
    }
    newPtr = hashTable->buckets[bucketLocation];
    //if the key isn't present in the first hashtableentry of the appropriate bucket index
    //walk the list until the key is found and use temp to store data and free the temp pointer to
    //the value once the pointer to the next is updated
    while(newPtr->next)
    {
        if(newPtr->next->key==key)
        {
            temp = (HashTableEntry*)newPtr->next->value;
            temp2 = newPtr->next;
            newPtr->next = (HashTableEntry*)newPtr->next->next;
            free(temp2);        
            return temp;            
        }
        //update the next pointer
        newPtr = newPtr->next;   
    }
    return NULL;
}

void deleteItem(HashTable* hashTable, unsigned int key) {
    //use remove item to delete the hashtable entry
    HashTableEntry* newPtr;
    newPtr = (HashTableEntry*)removeItem(hashTable,key);
    //free the pointer to the value since thats what removeitem returns
    free(newPtr);
}
