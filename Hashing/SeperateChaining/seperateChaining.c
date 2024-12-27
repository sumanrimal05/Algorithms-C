#include <stdio.h>
#include <stdlib.h>

#define LOAD_FACTOR_THRESHOLD_EXPAND 0.75 // Defines the threshold for expanding the hash table
#define LOAD_FACTOR_THRESHOLD_SHRINK 0.2  // Defines the threshold for shrinking the hash table

// Node for storing the key that results in collison as a chain using linked list
struct Node
{
  int key;           // key to be stored in hashTable
  struct Node *next; // Pointer to the next element in the chain. Used to handle collsions.
};

struct HashTable
{
  // Base address of the hash table, double pointer because
  // we can only store same type of key inside an array.
  // And some elements in case of collision will be stored in linked list
  // And we cannot store index in one index and pointer in another index.
  // So, we will make the array of pointers.
  // Also, we need the hashTable as array because we want the access time complixity of the array to be 0(1) or near constant time.
  struct Node **hashTableBaseAddress;
  int capacity;     // size of the hashtable
  int size;         // Element number in the hashTable
  float loadFactor; // Defines how filled the array is.
};

// Function Prototype
struct HashTable *hashMap_create_hashTable_withoutCapacity();
struct HashTable *hashMap_create_hashTable_withCapacity(int initialCapacity);
void hashMap_insert(struct HashTable *hashTable, int item);
void hashMap_delete(struct HashTable *hashTable, int item);
int hashMap_search(struct HashTable *hashTable, int item);
void hashMap_printMap(struct HashTable *hashTable);

// Helper Function
int hashMap_generate_hashIndex(int key);
void hashMap_expand(struct HashTable *hashTable, int expandSize);
void hashMap_shrink(struct HashTable *hashTable, int shrinkSize);
void hashMap_free(struct HashTable *hashTable);

// I beautified this comment with chatgpt. Tehee!!
// The primary goal of a hash function is to minimize collisions by distributing keys uniformly across the table.
// Choosing a prime number as the table size is beneficial because:
// - When using the modulo operation with a prime number, the hash keys exhibit a non-repeating pattern.
// - This non-repeating pattern ensures keys are distributed more evenly across the table, reducing the likelihood of clustering.
// For example, if the table size is not prime, certain patterns may emerge (e.g., results like 1, 3, 4, 3, 1, 4...),
// leading to repeated collisions or longer probing sequences before finding an empty slot.

// In the solution below we will be using the table size of power of 2.
// Because power of 2 eg(dec:2 , bin:00000010  dec:4 , bin:00000100   dec:8 , bin:00001000   dec:16 , bin:00010000)
// can be a consistent representation like one bit is high and rest of the bit are low in all 2 power cases.
// Using power of 2 is important as be can use bit wise operator on calculating hash function.
// Also if we have used prime numbers, while doubling the hashTable size we need to find the nearest prime number
// to the double which is computationally a little heavy.
int tableSize = 16; // Power of 2
int main()
{
  struct HashTable *hashTable = hashMap_create_hashTable_withoutCapacity();
  // int result = hashMap_generate_hashIndex(3);
  // printf("Hash Index: %d\n", result);

  // result = hashMap_generate_hashIndex(13);
  // printf("Hash Index: %d\n", result);
  hashMap_insert(hashTable, 20);
  hashMap_insert(hashTable, 1678555666);
  hashMap_printMap(hashTable);
  hashMap_free(hashTable);
  return 0;
}
void hashMap_insert(struct HashTable *hashTable, int key)
{
  // TODO: while resizing the hashTable you needd to copy all the value of previous hashTable into the new hashTable
  // If you don't make a new hashtable and just resize the previous hashTable
  //  The hash function will give inconsistent hashIndex as the table size is changed
  // Generate hashIndex for the key
  int hashIndex = hashMap_generate_hashIndex(key);
  // Check if the hashTable loadFactor is above the threshold expand
  // IF above double the size of hashTable and recalculate the loadFactor
  if (hashTable->loadFactor >= LOAD_FACTOR_THRESHOLD_EXPAND)
  {
    hashTable->capacity *= 2; // We are doubling the table capacity because 2 is 2^0. So, it will make the new table size in power of 2.
  }

  // Check if the hashIndex in HashTable is empty
  // If empty create a node and keep the key, key pair in the node and keep the memory address of the node in the index.

  struct Node *hashTableIndexHeadPointer = hashTable->hashTableBaseAddress[hashIndex];
  struct Node *newNode = malloc(sizeof(struct Node));
  if ((hashTableIndexHeadPointer) == NULL)
  {
    newNode->key = key;
    newNode->next = NULL;
    hashTable->hashTableBaseAddress[hashIndex] = newNode;
  }
  // If the hashIndex not empty. traverse to the end of linked list and put the node there.
  if (!hashTableIndexHeadPointer)
  {

    newNode->key = key;
    newNode->next = hashTableIndexHeadPointer;

    hashTable->hashTableBaseAddress[hashIndex] = newNode;
  }
}

struct HashTable *hashMap_create_hashTable_withoutCapacity()
{
  struct HashTable *hashTable = malloc(sizeof(struct HashTable));
  // Initializing the strucuture variables
  hashTable->capacity = tableSize;
  hashTable->size = 0;
  hashTable->loadFactor = 0;
  // Create a hash table with initial table size
  hashTable->hashTableBaseAddress = calloc(hashTable->capacity, sizeof(struct Node *));

  if (!(hashTable->hashTableBaseAddress))
  {
    printf("Create Error: Cannot create Hash Table.\n");
    exit(1);
  }
  return hashTable;
}

struct HashTable *hashMap_create_hashTable_withCapacity(int initialCapacity)
{
  struct HashTable *hashTable = malloc(sizeof(struct HashTable));
  // Initializing the strucuture variables
  tableSize = initialCapacity;
  hashTable->capacity = tableSize;
  hashTable->size = 0;
  hashTable->loadFactor = 0;
  // Create a hash table with initial table size
  // We are using calloc because in case of pointers calloc initializes the memory address with NULL value
  hashTable->hashTableBaseAddress = calloc(hashTable->capacity, sizeof(struct Node *));

  if (!(hashTable->hashTableBaseAddress))
  {
    printf("Create Error: Cannot create Hash Table.\n");
    exit(1);
  }
  return hashTable;
}

int hashMap_generate_hashIndex(int key)
{
  // We will be using bit wise operator on hash function because
  // 1.Bit wise operator are fast comparison to modulo operator.
  // 2. We can perform various logic gates (AND, OR, XOR, NOT) operation on the hash key
  // which will help create unique number for similar keys output.
  // Like for key = 3 and 13. If we use modulo (key % 10). we will get same output = 3 and the collision will occur.

  int hashCode;
  int index;
  // We are first shifting the key by 4 to XOR with the original key
  // to generate variation in the hashcode
  // we are shifting to 4 to mix the higher order and lower oder bits. and xoring the key
  // XOR combines the bits of two numbers in a way that preserves differences.
  // It ensures that small changes in the input (e.g., flipping a single bit) result in significant changes to the output hash, which improves uniformity.
  hashCode = (key ^ (key >> 4));

  // The operation key & (table_size - 1) is a technique used in hash tables where the table size is a power of 2.
  // It serves the same purpose as the modulo operation (key % table_size), but it’s faster because it uses a bitwise AND operation instead of division.
  // Also key % table_size brings the index to the table size even if the key size is larger than the table size.
  index = hashCode & (tableSize - 1);
  return index;
}

void hashMap_printMap(struct HashTable *hashTable)
{
  // Access the base address of HashTable
  // Loop through the whole hashTable
  for (int hashTableIndex = 0; hashTableIndex < (hashTable->capacity); hashTableIndex++)
  {
    printf("%p\n", hashTable->hashTableBaseAddress[hashTableIndex]);
  }
  // Print the baseAddress[hashIndex] and chain in one line
  // Print other hashIndex value in another line
}

void hashMap_free(struct HashTable *hashTable)
{
  // Free Nodes associated with the HashTable
  for (int hashTableIndex = 0; hashTableIndex < (hashTable->capacity); hashTableIndex++)
  { // Outer Loop for passing all the Hash Table Indices
    struct Node *hashTableIndexHeadPointer = hashTable->hashTableBaseAddress[hashTableIndex];
    if (hashTableIndexHeadPointer == NULL)
    { // If the hashIndex points to null just skipp the block
      continue;
    }
    struct Node *hashTableIndexPreviousPointer = NULL;
    while (hashTableIndexHeadPointer != NULL)
    {
      hashTableIndexPreviousPointer = hashTableIndexHeadPointer;
      hashTableIndexHeadPointer = hashTableIndexHeadPointer->next;
      free(hashTableIndexPreviousPointer);
    }
  }
  // Free the Hash Table
  free(hashTable->hashTableBaseAddress);
  // Free the Hash Table structure
  free(hashTable);
}