#include <bits/stdc++.h>
#include<time.h>
#include<math.h>
#define MAX 100

using namespace std;

//Brute Force Approach
int find2DPeakElementBF(int arr[][MAX], int rows, int columns) {
   for (int i = 0; i < rows; i++) {
      for (int j = 0; j < columns; j++) {
         if (i == 0 && j == 0) {
            if (arr[i][j] > arr[i + 1][j] && arr[i][j] > arr[i][j + 1]) {
               return arr[i][j];
            }
         }
         else if (i == 0 && j == columns - 1) {
            if (arr[i][j] > arr[i + 1][j] && arr[i][j] > arr[i][j - 1]) {
               return arr[i][j];
            }
         }
         else if (i == rows - 1 && j == 0) {
            if (arr[i][j] > arr[i - 1][j] && arr[i][j] > arr[i][j + 1]) {
               return arr[i][j];
            }
         }
         else if (i == rows - 1 && j == columns - 1) {
            if (arr[i][j] > arr[i - 1][j] && arr[i][j] > arr[i][j - 1]) {
               return arr[i][j];
            }
         }
         else if (i == 0) {
            if (arr[i][j] > arr[i][j - 1] && arr[i][j] > arr[i][j + 1] && arr[i][j] > arr[i + 1][j]) {
               return arr[i][j];
            }
         }
         else if (i == rows - 1) {
            if (arr[i][j] > arr[i][j - 1] && arr[i][j] > arr[i][j + 1] && arr[i][j] > arr[i - 1][j]) {
               return arr[i][j];
            }
         }
         else if (j == 0) {
            if (arr[i][j] > arr[i - 1][j] && arr[i][j] > arr[i + 1][j] && arr[i][j] > arr[i][j + 1]) {
               return arr[i][j];
            }
         }
         else if (j == columns - 1) {
            if (arr[i][j] > arr[i - 1][j] && arr[i][j] > arr[i + 1][j] && arr[i][j] > arr[i][j - 1]) {
               return arr[i][j];
            }
         }
         else {
            if (arr[i][j] > arr[i][j - 1] && arr[i][j] > arr[i][j + 1] && arr[i][j] > arr[i - 1][j] && arr[i][j] > arr[i + 1][j]) {
               return arr[i][j];
            }
         }
      }
   }
   return -1;
}

//Divide and Conquer Approach
int findMaxMid(int arr[][MAX],int rows, int mid, int&max) {
   int maxIndex = 0;

   for (int i = 0; i < rows; i++) {    //find max element in the mid column
      if (max <arr[i][mid]) {
         max = arr[i][mid];
         maxIndex = i;
      }
   }
   return maxIndex;
}

int find2DPeakElementDC(int arr[][MAX],int rows, int columns, int mid) {
   int maxMid = 0;
   int maxMidIndex = findMaxMid(arr, rows, mid, maxMid);

   if (mid == 0 || mid == columns-1)    //for first and last column, the maxMid is maximum
      return maxMid;
   // If maxMid is also peak
   if (maxMid>= arr[maxMidIndex][mid-1] &&maxMid>= arr[maxMidIndex][mid+1])
      return maxMid;

   if (maxMid<arr[maxMidIndex][mid-1])     // If maxMid is less than its left element
      return find2DPeakElementDC(arr, rows, columns, mid - mid/2);
   return find2DPeakElementDC(arr, rows, columns, mid+mid/2);
}

//Greedy Approach
int recur(int a[][MAX],int i, int j, int n) {
    if (i > 0 && a[i - 1][j] > a[i][j]) return recur(a,i - 1, j,n);
    else if (i < n - 1 && a[i + 1][j] > a[i][j]) return recur(a,i + 1, j,n);
    else if (j > 0 && a[i][j - 1] > a[i][j]) return recur(a,i, j - 1,n);
    else if (j < n - 1 && a[i][j + 1] > a[i][j]) return recur(a,i, j + 1,n);
    else return a[i][j];
}

int find2DPeakElementGreedy(int a[][MAX], int rows, int columns) {
    
    return recur(a,0,0,rows);
}

int main() {
//    int arr[][MAX] = {
//       { 1, 2, 3, 4 },
//       { 2, 3, 4, 5 },
//       { 1, 3, 7, 5 },
//       { 1, 2, 6, 6 } };
//    int rows = 4, columns = 4;
//    int mid = rows/2;
//    cout << "Brute Force Peak Finding: " <<find2DPeakElementBF(arr, rows, columns) << endl;
//    cout << "Divide and Conquer Peak Finding: " <<find2DPeakElementDC(arr, rows, columns, mid) << endl;
//    cout << "Greedy Peak Finding: " <<find2DPeakElementGreedy(arr, rows, columns) << endl;

  int n;
    cout << "Enter the number of elements in the array: ";
    cin >> n;

    // Seed for random number generation
    srand(time(0));

    // Generating a random 2D array
    int arr[MAX][MAX];
    cout << "Inserting random values in the array..." << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            arr[i][j] = rand() % 100;
        }
    }

    // Displaying the generated 2D array
    cout << "Generated 2D array:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
 

// Timing the Brute Force approach
    auto startBF = chrono::high_resolution_clock::now();
    cout << "Brute Force Peak Finding: " << find2DPeakElementBF(arr, n, n) << endl;
    auto endBF = chrono::high_resolution_clock::now();
    auto durationBF = chrono::duration_cast<chrono::microseconds>(endBF - startBF);
    cout << "Time taken by Brute Force: " << durationBF.count() << " microseconds" << endl;

    // Timing the Divide and Conquer approach
    auto startDC = chrono::high_resolution_clock::now();
    cout << "Divide and Conquer Peak Finding: " << find2DPeakElementDC(arr, n, n, n / 2) << endl;
    auto endDC = chrono::high_resolution_clock::now();
    auto durationDC = chrono::duration_cast<chrono::microseconds>(endDC - startDC);
    cout << "Time taken by Divide and Conquer: " << durationDC.count() << " microseconds" << endl;

    // Timing the Greedy approach
    auto startGreedy = chrono::high_resolution_clock::now();
    cout << "Greedy Peak Finding: " << find2DPeakElementGreedy(arr, n, n) << endl;
    auto endGreedy = chrono::high_resolution_clock::now();
    auto durationGreedy = chrono::duration_cast<chrono::microseconds>(endGreedy - startGreedy);
    cout << "Time taken by Greedy: " << durationGreedy.count() << " microseconds" << endl;

    return 0;
 
 
 
 
 
 
 
 
 
 
 
   return 0;
}