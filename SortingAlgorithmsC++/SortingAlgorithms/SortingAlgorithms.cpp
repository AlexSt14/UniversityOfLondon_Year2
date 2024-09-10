#include "ComparisonSorts.h"
#include <iostream>

int main()
{
    ComparisonSorts comparisonSorts;
    std::vector<int> A = { 5, 2, 4, 6, 1, 3 };
    int N = A.size();
    std::vector<int> sortedA = comparisonSorts.bubbleSort(A, N);
    std::vector<int> sortedInsert = comparisonSorts.insertionSort(A, N);
    std::vector<int> sortedSelection = comparisonSorts.selectionSort(A, N);
    std::vector<int> sortedQuick = comparisonSorts.quickSort(A, 0, N - 1);
    std::vector<int> sortedMerge = comparisonSorts.mergeSort(A, 0, N - 1);
    //Bubble sort showing functionality
    std::cout << "Bubble Sort demonstration " << std::endl;
    for (int i = 0; i < N; ++i)
    {
        std::cout << "Unsorted A " << A[i] << std::endl;
        std::cout << sortedA[i] << std::endl;
    }
    std::cout << "Insertion Sort Demonstration " << std::endl;
    //Insertion sort showing functionality
    for (int i = 0; i < N; ++i)
    {
        std::cout << "Unsorted A " << A[i] << std::endl;
    }
    for (int i = 0; i < N; ++i)
    {
        std::cout << sortedInsert[i] << std::endl;
    }
    //Selection sort showing functionality
    std::cout << "Selection Sort Implementation" << std::endl;
    for (int i = 0; i < N; ++i)
    {
        std::cout << "Unsorted A " << A[i] << std::endl;
    }
    for (int i = 0; i < N; ++i)
    {
        std::cout << sortedSelection[i] << std::endl;
    }
    //Quick sort showing functionality
    std::cout << "Quick Sort Implementation" << std::endl;
    for (int i = 0; i < N; ++i)
    {
		std::cout << "Unsorted A " << A[i] << std::endl;
	}
    for (int i = 0; i < N; ++i)
    {
		std::cout << sortedQuick[i] << std::endl;
	}
    //Merge sort showing functionality
    std::cout << "Merge Sort Implementation" << std::endl;
    for (int i = 0; i < N; ++i)
    {
        std::cout << "Unsorted A " << A[i] << std::endl;
    }
    for (int i = 0; i < N; ++i)
    {
		std::cout << sortedMerge[i] << std::endl;
	}
	return 0;
} 
