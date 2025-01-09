#include <stdio.h>
#include <stdlib.h>
struct Tree
{
  int height;
  int size;
  struct Node *root;
};

struct Node
{
  int value;
  struct Node *left;
  struct Node *right;
};

// Function Prototype
struct Tree *bst_create();
struct Node *bst_node_create(int value);
void bst_insert(struct Node **root, int value);
void bst_insert_iteratively(struct Tree *tree, int value);
void bst_delete(struct Tree *tree, int value);
void bst_search(struct Tree *tree, int value);
void bst_traverse_inOrder(struct Tree *tree);   // Left, Root, Right
void bst_traverse_preOrder(struct Tree *tree);  // Root, Left, Right
void bst_traverse_postOrder(struct Tree *tree); // Left, Right, Root
void bst_print(void (*callback)(struct Tree *tree));
void bst_free(struct Tree *tree);

// Helper Function

int main()
{
  // int input[] = {15, 10, 20, 8, 12, 17, 25};
  struct Tree *tree = bst_create();
  struct Node *root = tree->root = NULL;
  bst_insert(&root, 10);
  bst_insert(&root, 15);
  bst_insert(&root, 20);
  bst_insert(&root, 8);
  bst_insert(&root, 12);
  bst_insert(&root, 17);
  bst_insert(&root, 25);
  return 0;
}

struct Tree *bst_create()
{
  // Calloc allocates memory and assigns int to zero and pointer to NULL.
  struct Tree *newTree = malloc(sizeof(struct Tree));
  if (!newTree)
  {
    printf("Tree Create Fail: Memory allocation error.\n");
    exit(1);
  }
  return newTree;
}

struct Node *bst_node_create(int value)
{
  struct Node *newNode = malloc(sizeof(struct Node));

  if (!newNode)
  {
    printf("Node Create Error: Can't create node.\n");
    exit(1);
  }

  newNode->left = NULL;
  newNode->right = NULL;
  newNode->value = value;

  return newNode;
}

// Use recursion to insert into BST
void bst_insert(struct Node **root, int value)
{

  // if root is null
  if (*root == NULL)
  {
    *root = bst_node_create(value);
    return;
  }

  // Insert to left
  else if (value <= (*root)->value)
  {
    bst_insert(&((*root)->left), value);
  }
  // insert to right
  else
  {
    bst_insert(&((*root)->right), value);
  }
}

// Insert into BST iteratively and doesnot allow duplicate
void bst_insert_iteratively(struct Tree *tree, int value)
{
  struct Node *newNode = calloc(1, sizeof(struct Node));

  if (!newNode)
  {
    printf("Node Create Fail: Memory allocation error.\n");
    exit(1);
  }
  newNode->value = value;
  // Check if tree is empty
  if (!tree->root)
  {
    tree->root = newNode;
    return;
  }
  // Check the value size to insert it in left or right of the parent
  struct Node *temp = tree->root;
  while (temp)
  {

    // Left Insertion
    if (value < temp->value)
    {
      if (!(temp->left))
      {
        temp->left = newNode;
        return;
      }
      temp = temp->left;
    }

    // Right Insertion
    else if (value > temp->value)
    {
      if (!(temp->right))
      {
        temp->right = newNode;
        return;
      }
      temp = temp->right;
    }
    else
    {
      // Duplicate value
      printf("Insert Error: Duplicate Value %d.\n", value);
      return;
    }
  }
  tree->size++;
}

// Traverse the tree, order: Left, Root, Right Tree
// void bst_traverse_inOrder(struct Tree *tree)
// {
// }