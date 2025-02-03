#ifndef LAB1_HPP
#define LAB1_HPP

#include <iostream>
#include <stdexcept>

// Part 1: Recursion
int factorial(int n);
int fibonacci(int n);
long long towers(int n);  // or unsigned long long, etc.

// Part 2: Unit Testing
void testFactorial();
void testFibonacci();
void testTowers();

// Part 4: Partitioning & K-th smallest
int partition(int pivotIndex, int arr[], int start, int end);
int findKthSmallestValue(int k, int arr[], int start, int end);

// Helpers
int chooseRandomPivotIndex(int arr[], int start, int end);
int findKthSmallestValueViaSorting(int k, int arr[], int start, int end);
void testFindKthSmallestValue(int repetitions, int maxArraySize);

#endif
