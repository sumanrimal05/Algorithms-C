#include <stdio.h>
#include <stdlib.h>

struct Node
{
  int value;
  struct Node *left;
  struct Node *right;
};

// Function Prototype
struct Node *bst_node_create(int value);
void bst_insert(struct Node **root, int value);
struct Node *bst_insert_recursive_singlePointer(struct Node *root, int value);
void bst_insert_iteratively(struct Node *root, int value);
void bst_delete(struct Node *root, int value);
void bst_search(struct Node *root, int value);
void bst_traverse_inOrder(struct Node *root);   // Left, Root, Right
void bst_traverse_preOrder(struct Node *root);  // Root, Left, Right
void bst_traverse_postOrder(struct Node *root); // Left, Right, Root
void bst_print(void (*callback)(struct Node *root));
void bst_free(struct Node *root);

// Helper Function

int main()
{
  // int input[] = {15, 10, 20, 8, 12, 17, 25};
  struct Node *root = NULL;
  bst_insert(&root, 15);
  bst_insert(&root, 10);
  bst_insert(&root, 20);
  bst_insert(&root, 8);
  bst_insert(&root, 12);
  bst_insert(&root, 17);
  bst_insert(&root, 25);
  bst_traverse_inOrder(root);
  return 0;
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
  printf("Inserting value....... %d\n", value);
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

// Insert recursively without directly modifying the root-> left and root->right pointer
struct Node *bst_insert_recursive_singlePointer(struct Node *root, int value)
{
  if (root == NULL)
  {
    return bst_node_create(value);
  }
  else if (value <= root->value)
  {
    // Traverse Left
    root->left = bst_insert_recursive_singlePointer(root->left, value);
  }
  else
  {
    // Traverse Right
    root->right = bst_insert_recursive_singlePointer(root->right, value);
  }
  return root; // Updated root
}

// Insert into BST iteratively and doesnot allow duplicate
void bst_insert_iteratively(struct Node *root, int value)
{
  struct Node *newNode = calloc(1, sizeof(struct Node));

  if (!newNode)
  {
    printf("Node Create Fail: Memory allocation error.\n");
    exit(1);
  }
  newNode->value = value;
  // Check if tree is empty
  if (!root)
  {
    root = newNode;
    return;
  }
  // Check the value size to insert it in left or right of the parent
  struct Node *temp = root;
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
}

// Left, Root, Right traversal
void bst_traverse_inOrder(struct Node *root)
{
  // Go to the left most root of the tree
  // Print the root value
  // Move right

  if (root == NULL)
  {
    return;
  }
  // Traverse to the left most node
  bst_traverse_inOrder(root->left);
  printf("Val: %d\n", root->value);

  // Traverse to the current root right node
  bst_traverse_inOrder(root->right);
}