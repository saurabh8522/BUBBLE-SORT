// Optimized implementation of Bubble sort 
//added comments
//added some more comments
//comments and comments
//And this
//wow
#include <stdio.h> 

void swap(int *xp, int *yp) 
{ 
	int t = *xp; 
	*xp = *yp; 
	*yp = t; 
} 
	if (swapped == false) 
		break; 
} 
} 

/* Function to print an array */
void printArray(int arr[], int size) 
{ 
	int i; 
	for (i=0; i < size; i++) 
		printf("%d ", arr[i]); 
	printf("n"); 
} 

// Driver program to test above functions 
int main() 
{ 
	int array[] = {64, 34, 25, 12, 22, 11, 90}; 
	int n = sizeof(array)/sizeof(array[0]); 
	bubbleSort(array, n); 
	printf("Sorted array: \n"); 
	printArray(array, n); 
	return 0; 
} 
