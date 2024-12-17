#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

// Defination of a Node in the queue
struct Node {
  int data;             // Data stored in the node
  struct Node *next;    // Pointer to the next node in the queue
};

// Defination of a Queue
struct Queue{
  struct Node *head;   // Pointer to the first node(front) of the queue
  struct Node *tail;   // Pointer to the last node(rear) of the queue
  int size;            // Current size of the queue
};

// Function prototypes
void enqueue(struct Queue *queue, int data);
void dequeue(struct Queue *queue);
struct Node* front(struct Queue *queue);
struct Node* rear(struct Queue *queue);
// bool isFull(struct Queue *queue);
bool isEmpty(struct Queue *queue);
int size(struct Queue *queue);

struct Node* createNode(int data);
void printQueue(struct Queue *queue);
void freeQueue(struct Queue *queue);

int main(){
  // Allocate memory for the queue and initialize it.
  struct Queue *queue = malloc(sizeof(struct Queue));
  if(!queue){
    printf("Memory allocation failed for Queue.\n");
    return 1;
  }
  // Initialization to avoid garbage values
  queue->head = queue->tail = NULL;
  queue->size = 0;

  // Testing the queue operation
  enqueue(queue, 10);
  enqueue(queue, 20);
  enqueue(queue, 30);
  enqueue(queue, 40);
  enqueue(queue, 50);
  printQueue(queue);
 
  dequeue(queue);
  printQueue(queue);
  
  front(queue);
  rear(queue);
  size(queue);

  freeQueue(queue);

  return 0;
}

// Creates a new node with the given data
struct Node* createNode(int data){
  struct Node *newNode = malloc(sizeof(struct Node));

  if (newNode == NULL){
    printf("Create Error: Cannot create a node\n");
    exit(1);
  }

  newNode->data = data;
  newNode->next = NULL;
  return newNode;
}

//Adds a new element to the end of the queue
void enqueue(struct Queue *queue, int data){
  struct Node *newNode = createNode(data);

  // If the queue is empty, set both head and tail to the new node
  if(queue->head == NULL){
    queue->head = newNode;
    queue->tail = newNode;
  } else{
    queue->tail->next = newNode;  // Link the new node to the current tail
    queue->tail = newNode;        // Update the tail to the new node
  }
  
  queue->size++;    //Increment the size of the queue
}

// Removes an element from the front of the queue
void dequeue(struct Queue *queue){
  if(isEmpty(queue)){
    printf("Queue is empty. Cannot dequeue.\n");
    return;
  }
  struct Node *temp;                
  temp = queue->head;               // Temporarily store the current head
  queue->head = queue->head->next;  // Move the head to the next node

// If the element we removed is the last element.
// We need to make sure to point the tail to NULL.
  if(queue->head == NULL){
    queue->tail = NULL;
  }

  free(temp);     // Free the memory of the removed node
  queue->size--;  // Decrease the size of the queue

}


// Free all memory associated with the queue
void freeQueue(struct Queue *queue){
  while(queue->head != NULL){
    dequeue(queue);           // Remove all the element one by one
  }
  free(queue);               // Free the memory allocated for the queue structure
  printf("Queue is freed.\n");
}


// Print all the elements in the queue
void printQueue(struct Queue *queue){
  if(queue->head == NULL){
    printf("Queue is empty.\n");
    return;
  }

  struct Node *currentNode = queue->head;
  printf("head->");
  while(currentNode != NULL){
    printf("[%d, %p]->",currentNode->data, currentNode->next);
    currentNode = currentNode->next;
  }

  printf("NULL.\n");
}


// Returns the front element of the queue
struct Node* front(struct Queue *queue){
  if(isEmpty(queue)){
    printf("Queue is empty.\n");
    return NULL;
  }
  return queue->head;
}

// Returns the rear(last) element of the queue
struct Node* rear(struct Queue *queue){
  if(isEmpty(queue)){
    printf("Queue is empty.\n");
    return NULL;
  }
  return queue->tail;
}


// Checks if the queue is empty
bool isEmpty(struct Queue *queue){
  return queue->head == NULL;   // Returns true if head is NULL, otherwise false
}


// Returns the size fo the queue
int size(struct Queue *queue){
  if(isEmpty(queue)){
    printf("Queue is Empty.\n");
    return 0;
  }
  printf("Size: %d\n", queue->size);
  return queue->size;
}


