#include <stdio.h>

// Binary Search
// This search algorithm only works on a sorted array
// We reduce the search operation nearly by half every time we look for the target element
// By comparing the target value with the mid value of the array
// If the mid value of the array is less than than the target value we discard all the element right to the mid value including the mid
// and increase the left to mid + 1
// If the mid value of the array is more than the target value we discard all the element left to the mid including the mid
// and bring down the right to mid -1
// we do this until we find the value in the array.

// Function Prototype
int binarySearch(int arr[], int arraySize, int target);

int main()
{
  int arr[] = {1, 2, 3, 4, 5, 6, 7};
  int target = 1; // Target element to search in the array
  int arraySize = sizeof(arr) / sizeof(arr[0]);

  // Handle empty array size
  if (arraySize == 0)
  {
    printf("Array is empty.\n");
    return 0;
  }

  int result = binarySearch(arr, arraySize, target);
  if (result != -1)
  {
    printf("The target value %d is found at index %d.\n", target, result);
  }
  else
  {
    printf("The target value %d is not present in the array.\n", target);
  }

  return 0;
}

int binarySearch(int arr[], int arraySize, int target)
{
  int left = 0;              // Left most index of the array we check to search
  int right = arraySize - 1; // Right most index of the array we check to search

  while (left <= right)
  {
    int mid = (left + right) / 2;
    if (arr[mid] == target)
    {
      return mid; // Target found, return index
    }
    // If the target vale is greater than the value at the array discard all the value left to the array including the mid
    // So we made our new search array left most pointer beside the mid value
    else if (arr[mid] < target)
    {
      left = mid + 1;
    }
    // If the target value is less than the value at the array index discard all the right most element to the mid
    // and reduce our search array infornt of the mid
    else
    {
      right = mid - 1;
    }
  }
  return -1; // Target not found
}