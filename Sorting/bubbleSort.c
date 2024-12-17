#include <stdio.h>

// Function prototype
void printArray(int arr[], int size);

int main()
{
  int arr[] = {2, 8, 5, 3, 9, 4, 1};
  // Length of Array = Total size of array in Bytes / Size of one element
  int arrayLength = sizeof(arr) / sizeof(arr[0]);
  printf("Unsorted Array:");
  // we need to pass the size of array(length) because
  // because when we pass the arr to function, it is passed as a pointer to base address of arr
  // i.e a[0] or *(a + 0)
  // So, the size of array(length) will be the size of the pointer to arr which is 8 bytes.
  printArray(arr, arrayLength);

  // Bubble Sort Algorithm
  int temp;
  for (int i = 0; i < arrayLength; i++) // Outer loop for passes
  {
    // When looping through the element if there is zero swap the list is already sorted.
    // This flag prevents unnecessary sorting when a sorted list is passed.
    int swapped = 0;                          // Flag to check if swap happen
    for (int j = 0; j < arrayLength - 1; j++) // Inner loop for comparison
    {
      if (arr[j] > arr[j + 1])
      {
        // Swap the elements if they are in wrong order.
        temp = arr[j + 1];
        arr[j + 1] = arr[j];
        arr[j] = temp;
        swapped = 1;
      }
    }
    if (!swapped)
    {
      break; // Break if no swaps occured, as the array is already sorted.
    }
  }

  printf("Sorted Array:");
  printArray(arr, arrayLength);

  return 0;
}

// Print array
void printArray(int arr[], int size)
{
  if (size <= 0)
  {
    printf("Array is empty or invalid size.\n");
    return;
  }

  for (int i = 0; i < size; i++)
  {
    printf("%d ", arr[i]);
  }
  printf("\n");
}