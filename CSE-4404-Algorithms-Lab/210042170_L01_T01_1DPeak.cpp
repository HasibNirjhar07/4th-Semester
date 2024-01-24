// 1. Implementation of peak finding algorithm
// a) 1D peak finding
// i. Linear Approach
// ii. Divide and Conquer Approach

#include <bits/stdc++.h>
#include<time.h>
#include<math.h>

using namespace std;
//  a) 1D peak finding

// Find the peak element in the 1D array using linear search
int findPeakLinear(int arr[], int n)
{
    // first or last element is peak element
    if (n == 1)
        return 0;
    if (arr[0] >= arr[1])
        return 0;
    if (arr[n - 1] >= arr[n - 2])
        return n - 1;
 
    // check for every other element
    for (int i = 1; i < n - 1; i++) {
 
        // check if the neighbors are smaller
        if (arr[i] >= arr[i - 1] && arr[i] >= arr[i + 1])
            return i;
    }
}
 






// // Find the peak element in the 1D array using binary search(Divide and Conquer)


#include <bits/stdc++.h>
using namespace std;
 

int findPeakBinary(int arr[], int low,
                 int high, int n)
{
    // Find index of middle element
    // low + (high - low) / 2
    int mid = low + (high - low) / 2;
 
    // Compare middle element with its
    // neighbours (if neighbours exist)
    if ((mid == 0 || arr[mid - 1] <= arr[mid]) && 
        (mid == n - 1 || arr[mid + 1] <= arr[mid]))
        return mid;
 
    // If middle element is not peak and its
    // left neighbour is greater than it,
    // then left half must have a peak element
    else if (mid > 0 && arr[mid - 1] > arr[mid])
        return findPeakBinary(arr, low, (mid - 1), n);
 
    // If middle element is not peak and its
    // right neighbour is greater than it,
    // then right half must have a peak element
    else
        return findPeakBinary(
            arr, (mid + 1), high, n);
}
 
// A wrapper over recursive function findPeakUtil()
int findPeak(int arr[], int n)
{
    return findPeakBinary(arr, 0, n - 1, n);
}
 

int main()
{
    // int arr[] = { 1, 3, 20, 4, 1, 0 };
    // int n = sizeof(arr) / sizeof(arr[0]);

    // auto start=std::chrono::high_resolution_clock::now();
    // cout << "Index of a peak point through Binary Search is "
    //      << findPeak(arr, n)<<"\n";

    // auto end=std::chrono::high_resolution_clock::now();

    // std::chrono::duration<double> elapsed_seconds = end-start;

    // cout<<"Time taken by Binary Search: "<<elapsed_seconds.count()<<"s\n";     

         
         
    // auto start1=std::chrono::high_resolution_clock::now();

    // cout << "Index of a peak point through Linear Search is " << findPeakLinear(arr, n);
    

    // auto end1=std::chrono::high_resolution_clock::now();

    // std::chrono::duration<double> elapsed_seconds1 = end1-start1;

    // cout<<"Time taken by Linear Search: "<<elapsed_seconds1.count()<<"s\n";


      int n;
    cout << "Enter the number of elements in the array : ";
    cin >> n;

    srand(time(0));

    int *arr = new int[n];

    cout << "Inserting random values in the array..." << endl;
    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % 100;
    }

    cout << "Sorting the array..." << endl;


    // auto start = chrono::high_resolution_clock::now();
    //  findPeak(arr, n);
    // auto end = chrono::high_resolution_clock::now();

    // chrono::duration<double> duration = end - start;

    // cout << "Time taken by Binary Search : " << fixed << duration.count() << " seconds" << endl;


    auto start1 = chrono::high_resolution_clock::now();
     findPeakLinear(arr, n);

    auto end1 = chrono::high_resolution_clock::now();

    chrono::duration<double> duration1 = end1 - start1;

    cout << "Time taken by Linear Search : " << fixed << duration1.count() << " seconds" << endl;
    
//
 }


