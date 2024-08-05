// Name: Lawrence Menegus
// Date: 10/10/23  
// Course:Data Structures and Algorithms
// Description: This program will calculate the runtime functions of different algorthms: Selection sort, Bubble sort, 
// Insertion sort, Merge sort, Quick sort and Radix sort. The runtimes will occur with the following  array sizes : 8, 
// 16, 32, 64, 128, 256, 512, 1024, 2048, 8192, and 16384 filled with random values.  

#include <iostream>  
// for the time function
#include <time.h> 

// for the random function
#include <cstdlib>  

// For the Swap function
#include <algorithm>
#include <math.h>

using namespace std;

// Swap function 
void swap(int& a, int& b);

// Functions for Selection Sort 
int findIndexLargest(int array[], int n);
void selectionSort(int array[], int n);

// Function for Bubble Sort 
void bubbleSort(int array[], int n);

// Function for Insertion Sort 
void insertionSort(int array[], int n);

// Functions for merge sort
void merge(int array[], int first, int mid, int last);
void mergeSort(int array[], int first, int last);

// Functions for quick sort 
void sortFirstMidLast(int array[], int first, int mid, int last);
int partition(int* array, int first, int last);
void quickSort(int array[], int first, int last);

//Functions for radix sort 
void radixSort(int array[], int n, int d);

// The total size of the array that will be used for the program 
const int inputSize = 16320;

// Function to generate a new random array
void generateRandomArray(int array[], int size) {

	for (int i = 0; i < size; i++) {
		// Generates a random number between 0 - 99,999
		array[i] = rand() % 100000;
	}
}

int main()
{
	clock_t start, start1, start2, start3, start4, start5, stop, stop1, stop2, stop3, stop4, stop5;

	int originalArray[inputSize];
	int array[inputSize];
	int array1[inputSize];
	int array2[inputSize];
	int array3[inputSize];
	int array4[inputSize];


	// Generate the random array values once
	generateRandomArray(originalArray, inputSize);

	// Copy the original array into multiple arrays
	for (int i = 0; i < inputSize; i++) {
		array[i] = originalArray[i];
		array1[i] = originalArray[i];
		array2[i] = originalArray[i];
		array3[i] = originalArray[i];
		array4[i] = originalArray[i];

	}

	//======== Time for Selection Sort
	start = clock();
	selectionSort(originalArray, inputSize);
	stop = clock();

	// print out for Selection Sort 
	cout << "Running time for Selection Sort with array size of " << inputSize << " is " << static_cast<double>(stop - start) << endl; //in miliseconds

	//======== Time for Bubble Sort   
	start1 = clock();
	bubbleSort(array, inputSize);
	stop1 = clock();

	// print out for Bubble Sort 
	cout << "Running time for Bubble Sort with array size of " << inputSize << " is " << static_cast<double>(stop1 - start1) << endl; //in miliseconds

	//======== Insertion Sort 
	start2 = clock();
	insertionSort(array1, inputSize);
	stop2 = clock();

	// Print out for Insertion Sort 
	cout << "Running time for Insertion Sort with array size of " << inputSize << " is " << static_cast<double>(stop2 - start2) << endl; //in miliseconds

	//======== Merge Sort 
	start3 = clock();
	mergeSort(array2, 0, inputSize - 1);
	stop3 = clock();

	// Print out for Merge Sort 
	cout << "Running time for Merge Sort  with array size of " << inputSize << " is " << static_cast<double>(stop3 - start3) << endl; //in miliseconds

	//======== Quick Sort  
	start4 = clock();
	quickSort(array3, 0, inputSize - 1);
	stop4 = clock();

	// Print out for Quick Sort 
	cout << "Running time for Quick Sort  with array size of " << inputSize << " is " << static_cast<double>(stop4 - start4) << endl; //in miliseconds

	// Find the maximum number to know the number of digits for Redix sort 
	int maxVal = *max_element(array4, array4 + inputSize);
	int digits = floor(log10(maxVal)) + 1;

	//======== Radix Sort
	start5 = clock();
	radixSort(array4, inputSize, digits);
	stop5 = clock();

	// Print out for Radix Sort 
	cout << "Running time for Radix Sort  with array size of " << inputSize << " is " << static_cast<double>(stop5 - start5) << endl; // in miliseconds 
	cout << endl;
	return 0;
}

// Swap function 
void swap(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}

// Function is to find the largest index of the array 
int findIndexLargest(int array[], int n)
{
	int largest = 0;

	for (int currentIndex = 1; currentIndex < n; currentIndex++)
	{
		// If current index is larger than largest index, it will set largest to current index
		if (array[currentIndex] > array[largest])
			largest = currentIndex;
	}
	return largest;
}

// Selection Sort 
void selectionSort(int array[], int n)
{
	for (int last = n - 1; last >= 1; last--)
	{
		// Return index of largest element in array 
		int largest = findIndexLargest(array, last + 1);

		// Swaps largest element with last element 
		swap(array[largest], array[last]);
	}
}

// Bubble Sort Algorthm 
void bubbleSort(int array[], int n)
{
	bool sorted = false;
	int pass = 1;

	// Runs when the array is not sorted
	// and when the passes are less than the size of array 
	while (!sorted && (pass < n))
	{
		sorted = true;
		for (int index = 0; index < n - pass; index++)
		{
			int nextIndex = index + 1;

			// Runs if the array index is larger than next indext 
			if (array[index] > array[nextIndex])
			{
				// Swaps array index to the next index 
				swap(array[index], array[nextIndex]);
				sorted = false;
			}
		}
		pass++;
	}
}


//Insertion Sort Algorthm 
void insertionSort(int array[], int n)
{
	for (int unsorted = 1; unsorted < n; unsorted++)
	{

		// Next item equals the unsorted value in the array
		int nextItem = array[unsorted];
		int loc = unsorted;

		// Runs if current position is not first position and 
		// previous element is larger than the next Item 
		while (loc > 0 && (array[loc - 1] > nextItem))
		{
			array[loc] = array[loc - 1];
			loc--;
		}
		// Insert nextItem to its correct position 
		array[loc] = nextItem;
	}
}

// Merges two sorted sub arrays to one array and copies result to original array 
void merge(int array[], int first, int mid, int last)
{
	// Create temporary array 
	int tempArray[inputSize];

	// Initialize local indices to indicate the subarrays 
	int first1 = first;
	int last1 = mid;
	int first2 = mid + 1;
	int last2 = last;

	// While either subarray is not empty copy the smaller item to temp array   
	int index = 0;

	while ((first1 <= last1) && (first2 <= last2))
	{
		if (array[first1] <= array[first2])
		{
			tempArray[index] = array[first1];
			first1++;
		}
		else
		{
			tempArray[index] = array[first2];
			first2++;
		}
		index++;
	}

	// Finish off the first subarray if necessary 
	while (first1 <= last1)
	{
		// Sets Temp Array indext to partiion 1  first index in array 1
		tempArray[index] = array[first1];
		first1++;
		index++;
	}

	// Finish off the second subarray if necessary
	while (first2 <= last2)
	{
		// Sets Temp Array Index to partition 2 first index in array 2 
		tempArray[index] = array[first2];
		first2++;
		index++;
	}

	// Copy result back into original array.
	for (index = 0; index <= last - first; index++)
	{
		array[first + index] = tempArray[index];
	}
}

// Merge Sort Algorithm 
void mergeSort(int array[], int first, int last)
{
	// If the size of the array is less than or equal to 10 it runs insertion sort 
	if ((last - first + 1) <= 10)
	{
		insertionSort(array + first, last - first + 1);
	}
	else if (first < last)
	{
		// Mid index by adding first and last index and divided by two 
		int mid = (first + last) / 2;

		// Sorts the array from first to middle section 
		mergeSort(array, first, mid);

		// Sorts array from middle + 1 to last values 
		mergeSort(array, mid + 1, last);

		// Merges the sorted values together 
		merge(array, first, mid, last);
	}
}
// Function arranges the first middle and last entry in an array in ascending order
void sortFirstMidLast(int array[], int first, int mid, int last)
{
	// Compares if the first value of array is larger than mid values
	if (array[first] > array[mid])
		// Swaps first and mid values
		swap(array[first], array[mid]);

	// Compares if mid array value is larger than last value of array
	if (array[mid] > array[last])
		// Swaps mid and last values
		swap(array[mid], array[last]);

	// Recheck the first and mid values after the swaps
	if (array[first] > array[mid])
		// Swaps first and mid values
		swap(array[first], array[mid]);
}

// Partitioning for Quick Sort Algorithm
int partition(int array[], int first, int last)
{
	// Choose the first element as the pivot
	int pivot = array[first];

	// Index of the first element in the 'greater' region
	int low = first + 1;

	// Index of the last element in the array
	int high = last;

	while (true) {
		// Move right until you find an element greater than the pivot
		while (low <= high && array[low] <= pivot) {
			low++;
		}

		// Move left until you find an element less than the pivot
		while (low <= high && array[high] >= pivot) {
			high--;
		}

		// If there are elements in the wrong order, swap them
		if (low < high) {
			swap(array[low], array[high]);
		}
		else {
			// If the low and high pointers cross, the partition is complete
			break;
		}
	}

	// Swap the pivot element with the element at 'high' to place the pivot in the correct position
	swap(array[first], array[high]);

	// Return the index of the pivot element
	return high;
}

// Quick Sort Algorithm
void quickSort(int array[], int first, int last) {
	// If the size of the array is less than or equal to 10 it runs insertion sort 
	if ((last - first + 1) <= 10)
	{
		insertionSort(array + first, last - first + 1);
	}
	if (first < last) {

		// Makes Privot Index through Paration Function 
		int pivotIndex = partition(array, first, last);

		// Calls Quick Sort Functions 
		quickSort(array, first, pivotIndex - 1);
		quickSort(array, pivotIndex + 1, last);
	}
}

// Radix Sort Algorithm
void radixSort(int array[], int n, int d)
{
	// Allocate memory for 10 groups of size n
	int** groups = new int* [10];
	for (int i = 0; i < 10; i++) {
		groups[i] = new int[n];
	}
	// Allocate memory for counters of each group
	int* counters = new int[10];
	for (int j = 1; j <= d; j++)
	{
		// Initialize counters to zero
		for (int i = 0; i < 10; i++)
		{
			counters[i] = 0;
		}
		// Distribute elements into groups based on j-th digit
		for (int i = 0; i < n; i++)
		{
			int k = (array[i] / static_cast<int>(pow(10, j - 1))) % 10;
			groups[k][counters[k]++] = array[i];
		}
		// Copy elements back to the array in order
		int index = 0;
		for (int k = 0; k < 10; k++)
		{
			for (int i = 0; i < counters[k]; i++)
			{
				array[index++] = groups[k][i];
			}
		}
	}
	// Deallocate memory for groups and counters
	for (int i = 0; i < 10; i++) {
		delete[] groups[i];
	}
	// delete the counter and group
	delete[] groups;
	delete[] counters;
}


