#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct Node {
  int data;
  struct Node* next;
};

void push(struct Node **head, int data);
void pop(struct Node **head);
int top(struct Node *head);
bool isEmpty(struct Node *head);
int size(struct Node *head);

void printStack(struct Node *head);
void freeStack(struct Node **head);

int main(){
  //Initialize head pointer to NULL
  struct Node *head = NULL;
  push(&head, 10);
  push(&head, 20);
  push(&head, 30);
  printStack(head);
  pop(&head);
  printStack(head);

  freeStack(&head);

  return 0;
}

void push(struct Node **head, int data){
  struct Node *newNode = malloc(sizeof(struct Node));

  if(newNode == NULL){
    printf("Memory allocation failed\n");
    exit(1);
  }
  newNode->data = data;
  newNode->next = *head;
  *head = newNode;

}

void pop(struct Node **head){
  if(*head == NULL){
    printf("Cannot pop from empty stack\n");
    return;
  }
  struct Node *currentNode;
  currentNode = *head;
  *head = (*head)->next;

  free(currentNode);

}

int top(struct Node *head){
  if(head == NULL){
    printf("Stack is empty");
    exit(1);
  }
  return head->data;
}

bool isEmpty(struct Node *head){
  if(head == NULL){
    return true;
  }
  return false;
}

int size(struct Node *head){
  int count; // Number of nodes
  for(count = 0; head != NULL; head = head->next, count++);
  return count;
}

void printStack(struct Node *head){
  if(head == NULL){
    printf("The stack is empty\n");
     return;
  }

  printf("head->");
  while(head != NULL){
    printf("[%d, %p]->",head->data, head->next);
    head = head->next;
  }
  printf("NULL\n");
}

void freeStack(struct Node **head){
  while(*head != NULL){
    pop(head);
  }
}