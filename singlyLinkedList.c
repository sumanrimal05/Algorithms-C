#include<stdio.h>
#include<stdlib.h>

struct Node{
  int data;
  struct Node *next;

};

// Insert in linked list
void insertAtHead(struct Node **head, int data);
// void insertAtTail();
// void insertAtIndex();

// Delete Operation
void deleteAtHead(struct Node **head);
void deleteFromList(struct Node **head, int item);
// void deleteAtTail();
// void deleteAtIndex();

void traverseList(struct Node *head);   // Traverse the list
void searchInList(struct Node *head, int item);  // Search through the whole list
// void reverseList();   // Reverse the list
int getLength(struct Node *head);   // Return the number of nodes in linked list
// void removeDuplicates();  // Remove duplicates from the list

// void sortList();    // Sort the list
// void mergeSorted(); //Merge two sorted list

int main(){
  struct Node *head = NULL;
  insertAtHead(&head, 10);
  insertAtHead(&head, 20);
  insertAtHead(&head, 30);
  insertAtHead(&head, 40);
  insertAtHead(&head, 50);
  insertAtHead(&head, 60);

  searchInList(head, 80);

  int count = getLength(head);
  printf(" Count is %d\n", count);


  return 0;
}

void insertAtHead(struct Node **head, int data){
  struct Node *newNode = malloc(sizeof(struct Node));

  if(newNode ==NULL){
    printf("Memory allocation failed.\n");
    return;
  }

  newNode->data = data;
  newNode->next = *head;
  *head = newNode;

}

void traverseList(struct Node *head){
  // we need head to traverse
  // continue the loop until you find the null

  // head->[30, address]->[20, address]->[10, address]
  printf("head -> ");
  while(head != NULL){
    printf("[%d, %p] -> ", head->data, head->next);
    head = head->next;
  }
  printf("\n");
  printf("List traversal complete\n");

}

void deleteAtHead(struct Node **head){
  if(*head == NULL){
    printf("The linked list is empty.\n");
    return;
  }
  // Before deleting Copy the second node (head->next) to temp
  // Free the memory of the current head node
  // Update the head to point to the second node (the new head)
  struct Node *temp = (*head)->next;
  free(*head);
  *head = temp;
}

void deleteFromList(struct Node **head, int item){
  struct Node *currentNode,*previousNode;

  //Search until you find the item or you are in the end of the list
  for(currentNode = *head, previousNode = NULL; currentNode != NULL && currentNode->data != item; previousNode = currentNode, currentNode = currentNode->next);

  if(currentNode == NULL){
    printf("Item not found\n");
    return;
  }

  if(previousNode == NULL){
    // item is in the first node
    *head = (*head)->next;
  }
  else{
    // item in between
    previousNode->next = currentNode->next;
  }

  //Free the memory of the deleted node
  free(currentNode);
  
}

void searchInList(struct Node *head, int item){
  // Traverse through the link list until you find the item or it is the end of the list
  struct Node *currentNode;

// The oder of evaluation matters.When the currentNode pointer reaches the end of linked list where
// the currentNode next points to null, with this code seg fault occurs. Because, when the currentNode is NULL the first condition
// that is being evaluated is not whether the curentNode is NULL or not but we are trying to access currentNode->data. 
//So, segfault occurs
  // for(currentNode = head; currentNode->data != item && currentNode != NULL; currentNode = currentNode->next);

  for(currentNode = head; currentNode != NULL && currentNode->data != item; currentNode = currentNode->next);
  if(currentNode == NULL){
    printf("Item not found\n");
    return;
  }

  printf("Item found\n");
}

int getLength(struct Node *head){
  int count; // Number of nodes
  for(count = 0; head != NULL; head = head->next, count++);
  return count;
}