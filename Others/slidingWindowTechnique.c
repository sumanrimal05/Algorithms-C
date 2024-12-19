#include <stdio.h>

// Program to find the maximum sub array of 5 elements
// Maximum Sub array = Sub Array with max sum
// We will be using sliding window technique and brute force method to find the solution

struct MaxArray
{
  int startingIndex; // Starting index of the max Sub array
  int sum;           // Max sub array sum
};
// Function prototype
struct MaxArray bruteForceMaxSum(int arr[], int arraySize, int subArraySize);
struct MaxArray slidingWindowMaxSum(int arr[], int arraySize, int subArraySize);

void printMaxSubArray(int arr[], int startingIndex, int subArraySize);

int main()
{
  int arr[] = {12, 9, 23, 17, 25, 19, 4, 8, 21, 34, 26, 17, 19, 14, 27, 22, 15, 7, 2, 14, 5, 18, 24};
  int size = sizeof(arr) / sizeof(arr[0]);
  int subArraySize = 5;
  struct MaxArray result;
  result = bruteForceMaxSum(arr, size, subArraySize);
  // result = slidingWindowMaxSum(arr, size, subArraySize);

  printf("Max arr starting Index: %d, sum: %d\n", result.startingIndex, result.sum);
  printMaxSubArray(arr, result.startingIndex, subArraySize);
  return 0;
}

struct MaxArray slidingWindowMaxSum(int arr[], int arraySize, int subArraySize)
{
  int currentSum = 0;
  for (int i = 0; i < subArraySize; i++)
  {
    currentSum += arr[i];
  }

  struct MaxArray maxArr;
  maxArr.startingIndex = 0;
  maxArr.sum = currentSum;

  // int firstPointer = 1;
  // int secondPointer = subArraySize;
  // int loopEnd = arraySize - subArraySize;
  // while (firstPointer <= loopEnd)
  // {
  //   printf("SecondPointer: %d\n", arr[secondPointer]);
  //   currentSum= currentSum- arr[firstPointer - 1] + arr[secondPointer];
  //   printf("Current Sum: %d\n", prefixSum);
  //   if (maxArr.sum < currentSum)
  //   {
  //     maxArr.sum = currentSum;
  //     maxArr.startingIndex = firstPointer;
  //   }
  //   firstPointer++;
  //   secondPointer++;
  // }

  for (int i = subArraySize; i < arraySize; i++)
  {
    currentSum = currentSum - arr[i - subArraySize] + arr[i];
    if (maxArr.sum < currentSum)
    {
      maxArr.sum = currentSum;
      maxArr.startingIndex = i - subArraySize + 1;
    }
  }

  return maxArr;
}

struct MaxArray bruteForceMaxSum(int arr[], int arraySize, int subArraySize)
{
  struct MaxArray maxArr;
  maxArr.startingIndex = 0;
  maxArr.sum = 0;
  int sum = 0;
  int loopEnd = arraySize - subArraySize;
  for (int i = 0; i < loopEnd; i++)
  {
    for (int j = i; j < subArraySize; j++)
    {
      sum += arr[j];
    }
    if (maxArr.sum < sum)
    {
      maxArr.sum = sum;
      maxArr.startingIndex = i;
    }
    subArraySize += 1;
    sum = 0;
  }
  return maxArr;
}

void printMaxSubArray(int arr[], int startingIndex, int subArraySize)
{
  for (int i = startingIndex; i < startingIndex + subArraySize; i++)
  {
    printf("%d, ", arr[i]);
  }
  printf("\n");
}