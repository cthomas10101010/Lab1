#include <iostream>
#include <cassert>
#include <stdexcept>
#include <algorithm>   // for std::sort
#include <cstdlib>     // for rand(), srand()

using namespace std;

// ======================
// Part 1: Recursion
// ======================
int factorial(int n) {
    if (n < 0) {
        throw runtime_error("factorial: negative input not allowed.");
    }
    if (n == 0) {
        return 1;
    }
    return n * factorial(n - 1);
}

int fibonacci(int n) {
    // Based on the sequence [1, 2, 3, 5, ...]
    // so fibonacci(1) = 1, fibonacci(2) = 2
    if (n <= 0) {
        throw runtime_error("fibonacci: invalid input.");
    }
    if (n == 1) return 1;
    if (n == 2) return 2;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

long long towers(int n) {
    // Returns the number of moves for n rings in Towers of Hanoi
    // Either use the formula (1 << n) - 1 or do a recursion:
    if (n <= 0) {
        throw runtime_error("towers: invalid input.");
    }
    if (n == 1) return 1;
    return 1 + 2 * towers(n - 1);
}

// ======================
// Part 2: Unit Testing
// ======================
void testFactorial() {
    assert(factorial(0) == 1);
    assert(factorial(1) == 1);
    assert(factorial(5) == 120);
    // Optionally more tests...
    cout << "testFactorial passed!\n";
}

void testFibonacci() {
    // For the sequence [1,2,3,5,8...]
    assert(fibonacci(1) == 1);
    assert(fibonacci(2) == 2);
    assert(fibonacci(3) == 3); // 1 + 2
    assert(fibonacci(4) == 5); // 2 + 3
    assert(fibonacci(5) == 8);
    cout << "testFibonacci passed!\n";
}

void testTowers() {
    // For n=1, moves=1
    assert(towers(1) == 1);
    // For n=2, moves=3
    assert(towers(2) == 3);
    // For n=3, moves=7
    assert(towers(3) == 7);
    // For n=4, moves=15, etc.
    cout << "testTowers passed!\n";
}

// ======================
// Helpers for Part 4
// ======================
int* copyArray(const int arr[], int n) {
    int* r = new int[n];
    for (int i = 0; i < n; ++i) {
        r[i] = arr[i];
    }
    return r;
}

int chooseRandomPivotIndex(int arr[], int start, int end) {
    int n = (end + 1) - start;
    // pick a random pivot in range [start, end]
    return start + rand() % n;
}

int findKthSmallestValueViaSorting(int k, int arr[], int start, int end) {
    int n = (end + 1) - start;
    if (n == 0 || k >= n) {
        throw runtime_error("Invalid input to findKthSmallestValueViaSorting");
    }
    if (n == 1) {
        return arr[start];
    }
    // Sort the sub-array (0..n-1) only
    sort(arr + start, arr + end + 1);
    return arr[start + k];
}

// ======================
// Part 4: partition(...) and findKthSmallestValue(...)
// ======================
int partition(int pivotIndex, int arr[], int start, int end) {
    int pivotValue = arr[pivotIndex];
    
    // Move pivot out of the way: swap with end (for example)
    std::swap(arr[pivotIndex], arr[end]);
    int storeIndex = start;

    // Partition everything except the pivot (which is now at arr[end])
    for (int i = start; i < end; i++) {
        if (arr[i] <= pivotValue) {
            std::swap(arr[i], arr[storeIndex]);
            storeIndex++;
        }
    }

    // Move pivot to its final place
    std::swap(arr[storeIndex], arr[end]);
    int newPivotIndex = storeIndex;

    return newPivotIndex;
}

int findKthSmallestValue(int k, int arr[], int start, int end) {
    int n = (end + 1) - start;
    if (n == 0 || k >= n) {
        throw runtime_error("Invalid input.");
    }
    if (n == 1) {
        return arr[start];
    }
    // Choose a random pivot
    int chosenPivotIndex = chooseRandomPivotIndex(arr, start, end);

    // Partition
    int pivotIndex = partition(chosenPivotIndex, arr, start, end);

    // s1 is the size of the left side
    int s1 = pivotIndex - start;
    
    // If exactly s1 == k, pivot is the k-th smallest
    if (s1 == k) {
        return arr[pivotIndex];
    }
    // If k < s1, it's in the left side
    else if (k < s1) {
        return findKthSmallestValue(k, arr, start, pivotIndex - 1);
    }
    // Otherwise, it's in the right side. Adjust k by subtracting left side size + 1 pivot
    else {
        return findKthSmallestValue(k - s1 - 1, arr, pivotIndex + 1, end);
    }
}

// ======================
// Test function for Part 4
// ======================
void testFindKthSmallestValueForArraySizeN(int n) {
    if (n < 2) {
        throw runtime_error("Need array size >= 2 for test");
    }
    // Create random array
    int* arr = new int[n];
    for (int i = 0; i < n; ++i) {
        arr[i] = rand() % 100;  // random 0..99
    }

    // For each k in [0..n-1], compare the result of your function
    // to the sorted-based approach
    for (int k = 0; k < n; ++k) {
        int* copy1 = copyArray(arr, n);
        int expected = findKthSmallestValueViaSorting(k, copy1, 0, n - 1);
        delete[] copy1;

        int* copy2 = copyArray(arr, n);
        int actual = findKthSmallestValue(k, copy2, 0, n - 1);
        delete[] copy2;

        if (actual != expected) {
            throw runtime_error("Test failed for array size " + to_string(n));
        }
    }
    cout << "Success for input array of size " << n << endl;
    delete[] arr;
}

void testFindKthSmallestValue(int repetitions, int maxArraySize) {
    for (int n = 2; n <= maxArraySize; ++n) {
        for (int i = 0; i < repetitions; i++) {
            testFindKthSmallestValueForArraySizeN(n);
        }
    }
}
