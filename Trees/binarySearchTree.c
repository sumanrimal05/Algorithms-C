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
void bst_print(struct Node *root);              // Print the data in tree pattern
void bst_free(struct Node *root);
int bst_height(struct Node *root); // return the height of the binary tree

// Helper function
int max(int item1, int item2)
{
  printf("item1: %d, item2: %d \n", item1, item2);
  return (item1 > item2) ? item1 : item2;
}

int treeSize = 0; // No of elements in the tree
int main()
{
  // int input[] = {15, 10, 20, 8, 12, 17, 25};
  struct Node *root = NULL;
  bst_insert(&root, 15);
  bst_insert(&root, 14);
  bst_insert(&root, 20);
  bst_insert(&root, 8);
  bst_insert(&root, 12);
  bst_insert(&root, 17);
  bst_insert(&root, 25);
  bst_insert(&root, 9);
  bst_insert(&root, 10);
  bst_insert(&root, 11);

  printf("Inorder Traversal\n");
  bst_traverse_inOrder(root);
  // printf("Preorder Traversal\n");
  // bst_traverse_preOrder(root);
  // printf("Postorder Traversal\n");
  // bst_traverse_postOrder(root);
  printf("No of elements. %d\n", treeSize);
  int treeHeight = bst_height(root);
  printf("Tree Height %d\n", treeHeight);
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
  treeSize++;

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
  // Check the value treeSize to insert it in left or right of the parent
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

// Root, Left, Right Traversal
void bst_traverse_preOrder(struct Node *root)
{
  if (root == NULL)
  {
    return;
  }
  // First print the node you travel, root node
  printf("Val: %d\n", root->value);

  // Traverse to the left most end
  bst_traverse_preOrder(root->left);
  bst_traverse_preOrder(root->right);
}

// Left, Right, Root Traversal
void bst_traverse_postOrder(struct Node *root)
{
  if (root == NULL)
  {
    return;
  }

  // Traverse to the left most node
  bst_traverse_postOrder(root->left);
  // Traverst to the right node of the current root
  bst_traverse_postOrder(root->right);
  printf("Val: %d\n", root->value);
}

int bst_height(struct Node *root)
{
  if (root == NULL)
  {
    return -1;
  }

  // Traverse to the left most node
  int leftHeight = bst_height(root->left);

  // Traverse to the right of current node
  int rightHeight = bst_height(root->right);

  return max(leftHeight, rightHeight) + 1;
}