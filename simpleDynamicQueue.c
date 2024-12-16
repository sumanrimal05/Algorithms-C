#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct Node {
  int data;
  struct Node *next;
};

struct Queue{
  struct Node *head;
  struct Node *tail;
  int size;
};

void enqueue(struct Queue *queue, struct Node **previousNode, int data);
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
  struct Queue *queue = malloc(sizeof(struct Queue));
  struct Node *previousNode = NULL;
  enqueue(queue, &previousNode, 10);
  enqueue(queue, &previousNode, 20);
  enqueue(queue, &previousNode, 30);
  enqueue(queue, &previousNode, 40);
  enqueue(queue, &previousNode, 50);
  printQueue(queue);
  dequeue(queue);
  printQueue(queue);
  front(queue);
  rear(queue);
  size(queue);
  freeQueue(queue);


  return 0;
}


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


void enqueue(struct Queue *queue, struct Node **previousNode, int data){
  struct Node *newNode = createNode(data);

  if(queue->head == NULL){
    queue->head = newNode;
    *previousNode = newNode;
    queue->size++;
    return;
  }
  
  (*previousNode)->next = newNode;
  *previousNode = newNode;
  queue->tail = newNode;
  queue->size++;
}


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


struct Node* front(struct Queue *queue){
  if(isEmpty(queue)){
    printf("Queue is empty.\n");
    return NULL;
  }
  return queue->head;
}


struct Node* rear(struct Queue *queue){
  if(isEmpty(queue)){
    printf("Queue is empty.\n");
    return NULL;
  }
  return queue->tail;
}


bool isEmpty(struct Queue *queue){
  if(queue->head == NULL){
    printf("Queue is empty.\n");
    return true;
  }
  return false;
}


int size(struct Queue *queue){
  if(isEmpty(queue)){
    printf("Queue is Empty.\n");
    return 0;
  }
  printf("Size: %d\n", queue->size);
  return queue->size;
}


void dequeue(struct Queue *queue){
  if(isEmpty(queue)){
    printf("Queue is empty.\n");
    exit(1);
  }
  struct Node *previousNode;
  previousNode = queue->head;
  queue->head = queue->head->next;
  free(previousNode);
  queue->size--;

}


void freeQueue(struct Queue *queue){
  while(queue->head != NULL){
    dequeue(queue);
  }
  printf("Queue is empty\n");
}