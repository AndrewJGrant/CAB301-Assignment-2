#include <iostream>
#include <fstream>
#include <math.h>
#include <random>
#include <windows.h>
#include <chrono>

using namespace std;

ofstream outputOps("OutputOps.csv");
ofstream outputTime("OutputTime.csv");

//Following all taken from Report Reference [4], Except for 'STOP_TIMER' which is modified to suit our tests
#define TIMING

#ifdef TIMING
#define INIT_TIMER auto start = std::chrono::high_resolution_clock::now();
#define START_TIMER  start = std::chrono::high_resolution_clock::now();
#define STOP_TIMER  etime += std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now()-start).count();
#define STOP_TIMER2  etime2 += std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now()-start).count();
#else
#define INIT_TIMER
#define START_TIMER
#define STOP_TIMER
#define STOP_TIMER2
#endif

#define MIN_ARRAY_SIZE 25
#define MAX_ARRAY_SIZE 10000
#define ARRAY_SIZE_STEP 25
#define NUM_ARRAY_TRIALS 50

#define RANDOM_MIN -500000000
#define RANDOM_MAX 500000000

bool FunctionalTesting();
int MinDistance(int* A, int n);
int MinDistance2(int* A, int n);
int MinDistance_OpsCount(int* A, int n);
int MinDistance2_OpsCount(int* A, int n);

long long int basic = 0;  //basic op counter for MinDistance()
long long int basic2 = 0;  //basic op counter for MinDistance2()
long long int etime = 0;  //execution time counter for MinDistance()
long long int etime2 = 0;  //execution time counter for MinDistance2()

int main()
{
    // Verify the algoritms work correctly, and exit the program if not
    if (!FunctionalTesting()) {
            cout << "Tests Failed, exiting program..." << endl;
            return 1;
    } else cout << "Tests Passed, begin data collection..." << endl;

    //The following lines are for RNG - Report Reference [2]:
    std::mt19937 gen(GetTickCount());
    std::uniform_int_distribution<> dis(RANDOM_MIN, RANDOM_MAX);

    //header for .csv file - Report Reference [3]:
    outputOps << "Array length" << "," << "MinDistance()" << "," << "MinDistance2()" << std::endl;
    outputTime << "Array length" << "," << "Avg MinDistance() etime (ms)" << "," << "Avg MinDistance2() etime (ms)" << std::endl;

    INIT_TIMER
    for (int n = MIN_ARRAY_SIZE; n <= MAX_ARRAY_SIZE; n += ARRAY_SIZE_STEP){     //Where n is the size of the test array
        cout << "Testing arrays of size " << n << endl;
        for (int i = 0; i < NUM_ARRAY_TRIALS; i++){        //Determines how many arrays of each n itteration is tested
            int A[n];
            for (int j = 0; j < n; j++){      //Populating test array with RNG
                A[j] = dis(gen);
            }

            /* TESTING BASIC OPERATIONS */
            //We don't need to average multiple trials for counting the basic operation since the variation in results is negligible
            if (i == 0){
                // Run First algorithm
                MinDistance_OpsCount(A, n);

                // Run Second algorithm
                MinDistance2_OpsCount(A, n);
            }

            /* TESTING EXECUTION TIME */
            // Time execution of First Algorithm
            START_TIMER
            MinDistance(A, n);
            STOP_TIMER // Adds milliseconds since 'START_TIMER' to 'etime' counter.

            // Time execution of Second Algorithm
            START_TIMER
            MinDistance2(A, n);
            STOP_TIMER2  //Adds milliseconds since 'START_TIMER' to 'etime2' counter.
        }

        // Output Basic Operation Counting results to Operatons CSV file
        outputOps << n << "," << basic << "," << basic2 << std::endl;
        // Reset counters to 0
        basic = 0;
        basic2 = 0;

        // Output Execution Time results to Time CSV file
        outputTime << n << "," << etime/NUM_ARRAY_TRIALS << "," << etime2/NUM_ARRAY_TRIALS << std::endl;
        // Reset counters to 0
        etime = 0;
        etime2 = 0;
    }

    outputOps.close();
    outputTime.close();
    return 0;
}

bool FunctionalTesting() {
    cout << "Running Functional Tests..." << endl;

    // Test General Case
    int testArrayA[8] = {1, 5, 9, 52, 46, 10, 13, 22};
    int expectedA = 1;
    int resultA_1 = MinDistance(testArrayA, 8);
    int resultA_2 = MinDistance2(testArrayA, 8);
    cout << "Test 1 Expected Result: " << expectedA << "\tResult of Algorithm 1: " << resultA_1 << "\tResult of Algorithm 2: " << resultA_2 << endl;
    bool resultA = ((expectedA == resultA_1)&&(expectedA == resultA_2));

    // Test when dmin is between the first and last numbers
    int testArrayB[7] = {100, 3, 92, 66, 12, 22, 97};
    int expectedB = 3;
    int resultB_1 = MinDistance(testArrayB, 7);
    int resultB_2 = MinDistance2(testArrayB, 7);
    cout << "Test 2 Expected Result: " << expectedB << "\tResult of Algorithm 1: " << resultB_1 << "\tResult of Algorithm 2: " << resultB_2 << endl;
    bool resultB = ((expectedB == resultB_1)&&(expectedB == resultB_2));

    // Test when dmin is between the two last numbers
    int testArrayC[9] = {50, 7, 30, 21, 56, 78, 15, 40, 44};
    int expectedC = 4;
    int resultC_1 = MinDistance(testArrayC, 9);
    int resultC_2 = MinDistance2(testArrayC, 9);
    cout << "Test 3 Expected Result: " << expectedC << "\tResult of Algorithm 1: " << resultC_1 << "\tResult of Algorithm 2: " << resultC_2 << endl;
    bool resultC = ((expectedC == resultC_1)&&(expectedC == resultC_2));

    // Test extreme case when two elements are the same (dmin = 0)
    int testArrayD[5] = {20, 12, 40, 12, 43};
    int expectedD = 0;
    int resultD_1 = MinDistance(testArrayD, 5);
    int resultD_2 = MinDistance2(testArrayD, 5);
    cout << "Test 4 Expected Result: " << expectedD << "\tResult of Algorithm 1: " << resultD_1 << "\tResult of Algorithm 2: " << resultD_2 << endl;
    bool resultD = ((expectedD == resultD_1)&&(expectedD == resultD_2));

    // Verify that the algorithm still works on negative numbers
    int testArrayE[6] = {39, -47, -5, -7, 6, -39};
    int expectedE = 2;
    int resultE_1 = MinDistance(testArrayE, 6);
    int resultE_2 = MinDistance2(testArrayE, 6);
    cout << "Test 5 Expected Result: " << expectedE << "\tResult of Algorithm 1: " << resultE_1 << "\tResult of Algorithm 2: " << resultE_2 << endl;
    bool resultE = ((expectedE == resultE_1)&&(expectedE == resultE_2));

    //Return true if all tests passed, false otherwise
    return resultA && resultB && resultC && resultD && resultE;
}

int MinDistance(int* A, int n){
    int dmin = INT_MAX;   /* the initial value of dmin doesn't have to actually be
    infinity. Just large enough that it can be overiden by the actual minimum */
    for (int i = 0; i <= n-1; i++) {
        for (int j = 0; j <= n-1; j++) {
            if ((i != j) && (abs(A[i] - A[j]) < dmin)){
                dmin = abs(A[i] - A[j]);
                }
        }
    }
    return dmin;
}

int MinDistance2(int* A, int n){
    int dmin = INT_MAX;   /* the initial value of dmin doesn't have to actually be
    infinity. Just large enough that it can be overiden by the actual minimum */
    for (int i = 0; i <= n-2; i++) {
        for (int j = i+1; j <= n-1; j++) {
            int temp = abs(A[i] - A[j]);
            if (temp < dmin){
                dmin = temp;
            }
        }
    }
    return dmin;
}

int MinDistance_OpsCount(int* A, int n){
    int dmin = INT_MAX;   /* the initial value of dmin doesn't have to actually be
    infinity. Just large enough that it can be overiden by the actual minimum */
    for (int i = 0; i <= n-1; i++) {
        for (int j = 0; j <= n-1; j++) {
            if (i != j){
                basic++;  // Increments the basic operation count for this algorithm.
                if (abs(A[i] - A[j]) < dmin){
                    dmin = abs(A[i] - A[j]);
                    basic++;  // Increments the basic operation count for this algorithm.
                }
            }
        }
    }
    return dmin;
}

int MinDistance2_OpsCount(int* A, int n){
    int dmin = INT_MAX;   /* the initial value of dmin doesn't have to actually be
    infinity. Just large enough that it can be overiden by the actual minimum */
    for (int i = 0; i <= n-2; i++) {
        for (int j = i+1; j <= n-1; j++) {
            int temp = abs(A[i] - A[j]);
            basic2++;  // Increments the basic operation count for this algorithm.
            if (temp < dmin){
                dmin = temp;
            }
        }
    }
    return dmin;
}
