#include <stdio.h>

// Function prototype
void printArr(int arr[], int size);

int main()
{
  // First loop through the entire loop to find the smallest element in the array
  //  Then swap the smallest element with the first element
  //  Repeat the above step until you pass through the end of the loop
  //  And the array will be sorted.

  int arr[] = {2, 8, 5, 3, 9, 4, 1};
  int arrayLength = sizeof(arr) / sizeof(arr[0]);
  printf("Unsorted Array:");
  printArr(arr, arrayLength);

  for (int i = 0; i < arrayLength; i++)
  {                         // outer loop for passes
    int min_value = arr[i]; // Used for comparing min value in the array
    int min_index = i;      // Used for swapping the min value with the left most element in the array
                            // Temp variable to temporarily store the swap values
    for (int j = i + 1; j < arrayLength; j++)
    { // Inner loop for comparing and finding the smallest element
      // Finging the min value in the array
      if (min_value > arr[j])
      {
        min_value = arr[j];
        min_index = j;
      }
    }
    // Swapping the min value with the left element if it is the min value
    int tempValue;
    tempValue = arr[i];
    arr[i] = arr[min_index];
    arr[min_index] = tempValue;
  }

  printf("Sorted Array:");
  printArr(arr, arrayLength);
  return 0;
}

void printArr(int arr[], int size)
{
  if (size <= 0)
  {
    printf("Array is empty or invalid size.\n");
  }

  for (int i = 0; i < size; i++)
  {
    printf("%d ", arr[i]);
  }
  printf("\n");
}