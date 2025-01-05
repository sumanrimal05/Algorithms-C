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
void bst_insert(struct Tree *tree, int value);
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
  bst_insert(tree, 15);
  bst_insert(tree, 10);
  bst_insert(tree, 20);
  bst_insert(tree, 8);
  bst_insert(tree, 12);
  bst_insert(tree, 17);
  bst_insert(tree, 25);
  return 0;
}

struct Tree *bst_create()
{
  // Calloc allocates memory and assigns int to zero and pointer to NULL.
  struct Tree *newTree = calloc(1, sizeof(struct Tree));
  return newTree;
}

void bst_insert(struct Tree *tree, int value)
{
  struct Node *newNode = calloc(1, sizeof(struct Node));
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
      printf("%d\n", temp->value);
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