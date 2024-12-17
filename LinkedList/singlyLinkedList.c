#include<stdio.h>
#include<stdlib.h>

struct Node{
  int data;
  struct Node *next;

};

// Insert in linked list
void insertAtHead(struct Node **head, int data);
void insertAtTail(struct Node **head, int data);
// void insertAtIndex();

// Delete Operation
void deleteAtHead(struct Node **head);
void deleteFromList(struct Node **head, int item);
// void deleteAtTail();
// void deleteAtIndex();
void deleteList(struct Node **head);

struct Node* traverseList(struct Node *head);   // Traverse the list
void printList(struct Node *head);   // Print the entire linked list
void searchInList(struct Node *head, int item);  // Search through the whole list
void reverseList(struct Node **head);  // Reverse the list
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

  printf("Before reversing List\n");
  printList(head);

  reverseList(&head);
  printf("After reversing List\n");
  printList(head);

  // Free Linked list
  deleteList(&head);
  printList(head);


  return 0;
}

struct Node* createNode(int data){
  struct Node *newNode = malloc(sizeof(struct Node));

  if (newNode == NULL){
    printf("Memory allocation failed.\n");
     // Using exit(1) instead of return because exit(1)terminates the whole program
    // using return in main also terminates the whole program
    // but returning from the function only terminates the function.
    exit(1);
  }

  newNode->data = data;
  newNode->next = NULL;

  return newNode;
}

void insertAtHead(struct Node **head, int data){
  struct Node *newNode = createNode(data);
  newNode->next = *head;
  *head = newNode;

}


// Traverse the linked list and return the pointer to the end of linked list
struct Node* traverseList(struct Node *head){
  // we need head to traverse
  // continue the loop until you find the null

  // head->[30, address]->[20, address]->[10, address]
  while(head->next != NULL){
    head = head->next;
  }

  return head;
}

void printList(struct Node *head){
  if(head == NULL){
    printf("The list is empty\n");
    return;
  }

  printf("head[%p] -> ", head);
  while(head -> next != NULL){
    printf("[%d, %p] -> ", head->data, head->next);
    head = head->next;
  }
  if(head->next == NULL){
    printf("[%d, %p]", head->data, head->next);
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

// Free linked list
void deleteList(struct Node **head){
  struct Node *previousNode;
  
  while((*head) != NULL){
    previousNode = *head;
    *head = (*head) -> next;
    free(previousNode);
  }
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

void reverseList(struct Node **head){
  // Change the current pointer to point to previous Node
  // To do this first save the head pointer to currentNode
  // And make the head pointer point to another node
  //then change the 'currentNode' next to point to previousNode.
  struct Node *previousNode;
  struct Node *currentNode;

  for(previousNode = NULL ; (*head) != NULL; previousNode = currentNode){
    currentNode = (*head);
    *head = (*head)->next;
    currentNode->next = previousNode;
  }
  if((*head) == NULL){
    (*head) = previousNode;
  }
  
}

