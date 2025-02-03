#include <iostream>
#include <cstdlib>     // for srand()
#include <ctime>       // for time()
#include "Lab1.h"

using namespace std;

int main() {
    // Seed random # generator
    srand((unsigned)time(nullptr));

    // 1) Test Recursion
    testFactorial();
    testFibonacci();
    testTowers();

    // 2) (Optional) Gather some towers(n) data for the chart
    cout << "\nTowers of Hanoi Data:\n";
    for (int n = 1; n <= 10; n++) {
        cout << "n=" << n << " => towers=" << towers(n) << endl;
    }
    // For very large n, the number is huge, e.g. n=100 => 2^100 - 1

    // 3) Test Kth smallest
    cout << "\nTesting findKthSmallestValue...\n";
    testFindKthSmallestValue(3, 5);

    cout << "\nAll tests passed!\n";
    return 0;
}
