#include <stdio.h>
#include <stdlib.h>

#define LOAD_FACTOR_THRESHOLD_EXPAND 0.75 // Defines the threshold for expanding the hash table
#define LOAD_FACTOR_THRESHOLD_SHRINK 0.2  // Defines the threshold for shrinking the hash table

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
#define INITIAL_CAPACITY 4 // Default hash table capacity or table size, power of 2

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
struct HashTable *hashTable_default();
struct HashTable *hashTable_create(int initialCapacity);
void hashTable_insert(struct HashTable **hashTable, int key);
void hashTable_delete(struct HashTable *hashTable, int key);
int hashTable_search(struct HashTable *hashTable, int key);
void hashTable_print(struct HashTable *hashTable);
struct HashTable *hashTable_copy(struct HashTable *oldHashTable, struct HashTable *newHashTable);

// Helper Function
void calculate_loadFactor(struct HashTable *hashTable);
int generate_hashIndex(struct HashTable *hashTable, int key);
void hashTable_expand(struct HashTable **hashTable);
void hashTable_shrink(struct HashTable **hashTable);
void hashTable_free(struct HashTable *hashTable);
unsigned int convert_input_to_powerOfTwo(int number);

int main()
{
  struct HashTable *hashTable = hashTable_default();

  hashTable_insert(&hashTable, 20);
  hashTable_insert(&hashTable, 21);
  hashTable_insert(&hashTable, 1678555666);
  hashTable_insert(&hashTable, 3);
  hashTable_insert(&hashTable, 13);
  hashTable_insert(&hashTable, 14);
  hashTable_insert(&hashTable, 3);
  hashTable_print(hashTable);
  hashTable_delete(hashTable, 1678555666);
  hashTable_print(hashTable);
  hashTable_free(hashTable);
  return 0;
}

struct HashTable *hashTable_default()
{
  struct HashTable *hashTable = malloc(sizeof(struct HashTable));
  // Initializing the strucuture variables
  hashTable->capacity = INITIAL_CAPACITY;
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

struct HashTable *hashTable_create(int initialCapacity)
{
  struct HashTable *hashTable = malloc(sizeof(struct HashTable));
  // Initializing the strucuture variables
  hashTable->size = 0;
  hashTable->loadFactor = 0;
  // Converting the hashTable into power of 2.
  int tableSize = convert_input_to_powerOfTwo(initialCapacity);
  hashTable->capacity = tableSize;
  // We are using calloc because in case of pointers calloc initializes the memory address with NULL value
  hashTable->hashTableBaseAddress = calloc(hashTable->capacity, sizeof(struct Node *));

  if (!(hashTable->hashTableBaseAddress))
  {
    printf("Create Error: Cannot create Hash Table.\n");
    exit(1);
  }
  return hashTable;
}

int generate_hashIndex(struct HashTable *hashTable, int key)
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
  index = hashCode & ((hashTable->capacity) - 1);
  return index;
}

void hashTable_insert(struct HashTable **hashTable, int key)
{
  // Check for duplicate Key
  int checkDuplicate = hashTable_search(*hashTable, key);
  if (checkDuplicate != -1)
  {
    printf("Insert Error: Duplicate Key exists.\n");
    return;
  }
  // Check if the hashTable loadFactor is above or below the threshold
  calculate_loadFactor(*hashTable);
  // IF above double the size of hashTable and recalculate the table capacity
  if ((*hashTable)->loadFactor >= LOAD_FACTOR_THRESHOLD_EXPAND)
  {
    hashTable_expand(hashTable);
  }

  if (((*hashTable)->loadFactor <= LOAD_FACTOR_THRESHOLD_SHRINK) && ((*hashTable)->loadFactor >= INITIAL_CAPACITY))
  {
    hashTable_shrink(hashTable);
  }
  // Check if the hashIndex in HashTable is empty
  // If empty create a node and keep the key, key pair in the node and keep the memory address of the node in the index.

  // Generate hashIndex for the key
  int hashIndex = generate_hashIndex(*hashTable, key);
  struct Node *hashTableIndexHeadPointer = (*hashTable)->hashTableBaseAddress[hashIndex];
  struct Node *newNode = malloc(sizeof(struct Node));
  // Collison not detected case
  if ((hashTableIndexHeadPointer) == NULL)
  {
    newNode->key = key;
    newNode->next = NULL;
    (*hashTable)->hashTableBaseAddress[hashIndex] = newNode;
  }
  // If the hashIndex not empty. traverse to the end of linked list and put the node there.
  else // Collison detected case
  {
    newNode->key = key;
    newNode->next = hashTableIndexHeadPointer;

    (*hashTable)->hashTableBaseAddress[hashIndex] = newNode;
  }
  (*hashTable)->size++;
}

struct HashTable *hashTable_copy(struct HashTable *oldHashTable, struct HashTable *newHashTable)
{
  // Check if newHashTable size is small then oldHashTable Size
  // If newHashTable size is small then cannot copy as the new hash table cannot fit all the elements
  if (newHashTable->capacity < oldHashTable->capacity)
  {
    printf("Copy Error: Can't copy a larger hash table into small hashtable.\n");
    exit(1);
  }

  // Traverse the old hashTable nodes and while traversing calculate new hashIndex for the key and put it in the new hashTable
  for (int index = 0; index < (oldHashTable->capacity); index++)
  {
    // While resizing the hashTable you needd to copy all the value of previous hashTable into the new hashTable
    // If you don't make a new hashtable and just resize the previous hashTable
    //  The hash function will give inconsistent hashIndex as the table size is changed
    struct Node *oldHashTableIndexHeadPointer = oldHashTable->hashTableBaseAddress[index];

    // If the old hash table index pointer is NULL.
    // Just skip it as there is no key and trying to access the key will give error
    if (oldHashTableIndexHeadPointer == NULL)
    {
      continue;
    }

    while (oldHashTableIndexHeadPointer != NULL)
    {
      // 1. Find the key at head
      // 2. Generate new hashIndex for new hashTable with that key.
      // 3. Insert the key in the new hashIndex to the new Hash Table.
      // 4. Move the pointer to the next node
      // 5. Continue step 1 to 4 until you reach the end of the loop

      int key = oldHashTableIndexHeadPointer->key;
      int newHashIndex = generate_hashIndex(newHashTable, key);
      // Create a node to store the key
      struct Node *newNode = malloc(sizeof(struct Node));
      struct Node *newHashTableIndexHeadPointer = newHashTable->hashTableBaseAddress[newHashIndex];

      // No collison
      if (newHashTableIndexHeadPointer == NULL)
      {
        newNode->key = key;
        newNode->next = NULL;
        newHashTable->hashTableBaseAddress[newHashIndex] = newNode;
      }

      // Collison occurs
      newNode->key = key;
      newNode->next = newHashTableIndexHeadPointer;
      newHashTable->hashTableBaseAddress[newHashIndex] = newNode;

      // Go to next bucket
      oldHashTableIndexHeadPointer = oldHashTableIndexHeadPointer->next;
    }
  }
  return newHashTable;
}

int hashTable_search(struct HashTable *hashTable, int key)
{
  int hashIndex = generate_hashIndex(hashTable, key);
  struct Node *hashTableIndexHeadPointer = hashTable->hashTableBaseAddress[hashIndex];

  while (hashTableIndexHeadPointer != NULL)
  {
    if (hashTableIndexHeadPointer->key == key)
    {
      printf("Key found at index %d.\n", hashIndex);
      return hashIndex;
    }
    hashTableIndexHeadPointer = hashTableIndexHeadPointer->next;
  }

  return -1; // No key found
}

void hashTable_delete(struct HashTable *hashTable, int key)
{
  int keyIndex = hashTable_search(hashTable, key);
  if (keyIndex == -1)
  {
    printf("Delete Error: Key not found\n");
    return; // Exit if key is not found
  }

  // Address of the pointer to the head node of the list at this index
  struct Node **hashTableIndexHeadPointerAddress = &(hashTable->hashTableBaseAddress[keyIndex]);
  struct Node *previousNode = NULL, *currentNode = *hashTableIndexHeadPointerAddress;

  // Traverse the linked list to find the key
  while (currentNode != NULL && currentNode->key != key)
  {
    previousNode = currentNode;
    currentNode = currentNode->next;
  }

  // Key found: handle deletion
  if (currentNode != NULL)
  {
    if (previousNode == NULL)
    {
      // Key is in the head node
      *hashTableIndexHeadPointerAddress = currentNode->next;
    }
    else
    {
      // Key is in a non-head node
      previousNode->next = currentNode->next;
    }

    // Free the memory of the deleted node
    free(currentNode);

    // Update size and load factor
    hashTable->size--;
    calculate_loadFactor(hashTable);
  }
}

void hashTable_print(struct HashTable *hashTable)
{
  // Access the base address of HashTable  // Print the baseAddress[hashIndex] and chain in one line
  // Print other hashIndex value in another line
  // Loop through the whole hashTable

  for (int index = 0; index < (hashTable->capacity); index++)
  {
    printf("%d: ", index);
    struct Node *hashTableIndexHeadPointer = hashTable->hashTableBaseAddress[index];

    while (hashTableIndexHeadPointer != NULL)
    {
      printf("[%d, %p]->", hashTableIndexHeadPointer->key, hashTableIndexHeadPointer->next);
      hashTableIndexHeadPointer = hashTableIndexHeadPointer->next;
    }
    if (hashTableIndexHeadPointer == NULL)
    {
      printf("NULL\n");
    }
  }
  printf("\n");
}

void hashTable_expand(struct HashTable **hashTable)
{
  // While resizing the hashTable you needd to copy all the value of previous hashTable into the new hashTable
  // If you don't make a new hashtable and just resize the previous hashTable
  //  The hash function will give inconsistent hashIndex as the table size is changed
  int newCapacity = (*hashTable)->capacity * 2; // We are doubling the table capacity because 2 is 2^0. So, it will make the new table size in power of 2.
                                                // Create a new hashTable with double the size.
  struct HashTable *newHashTableWithSize = hashTable_create(newCapacity);
  struct HashTable *oldHashTable = *hashTable;
  *hashTable = hashTable_copy(oldHashTable, newHashTableWithSize);
  // Once the traversal is complete and you copied everything free the old hashTable
  free(oldHashTable);
}

void hashTable_shrink(struct HashTable **hashTable)
{
  int newCapacity = (*hashTable)->capacity / 2; // Reducing the size of hashTable by half
  struct HashTable *newHashTableWithSize = hashTable_create(newCapacity);
  struct HashTable *oldHashTable = *hashTable;
  *hashTable = hashTable_copy(oldHashTable, newHashTableWithSize);
  // Once the traversal is complete and you copied everything free the old hashTable
  free(oldHashTable);
}

void calculate_loadFactor(struct HashTable *hashTable)
{
  // Check if the capacity is zero to avoid division by zero
  if (hashTable->capacity <= 0)
  {
    hashTable->loadFactor = 0.0f;
  }
  hashTable->loadFactor = (float)hashTable->size / (float)hashTable->capacity;
}

void hashTable_free(struct HashTable *hashTable)
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

// Convert the user entered initial table capacity to nearest power of 2
unsigned int convert_input_to_powerOfTwo(int number)
{
  // Check if the number is less than power of 2^31 - 1. Because while converting unsigned value over this number can cause integer overflow
  // or undefined behavior.
  // IF the number exceeds this. The shift operation will result in negative number.
  if (number > 2147483647)
  {
    unsigned int result = 2147483647; // If the user tries to add more keys than the load factor logic which will double the size of hashmap will handle rest.
    return result;
  }
  // Check if the value is negative or positive
  // The size of the table cannot be negative. So, we will be using unsigned int
  // So, taking the absolute value
  // Also we are using unsigned integer. So, we don't have to worry about negative values.
  unsigned int absValue = (number < 0) ? -number : number;
  unsigned int shift = 0;

  // The power of two has the MSB 1 and other 0.
  // We will convert all the bits 0 except MSB to get its nearest power to 2.
  // To do this we need to calculate how many bits the MSB is far from the LSB. So, we will use shift to know this
  // absValue >> 1 shifts the bit to right by 1
  // If the number = 44. In first iteration , binary of 44 = 101100, it shift to 010110(22), then to 001011(11). and loop stops until it it 000001 or 1.
  while (absValue > 1)
  {
    absValue = absValue >> 1;
    shift++;
  }
  // Shifting the number 1 by the toatal numbers of bits or shifts to get it's nearest power of 2.
  unsigned int result = 1 << shift;
  return result;
}