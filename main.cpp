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

#define MIN_ARRAY_SIZE 100
#define MAX_ARRAY_SIZE 10000
#define ARRAY_SIZE_STEP 25
#define NUM_ARRAY_TRIALS 50

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
//The following lines are for RNG - Report Reference [2]:
    std::mt19937 gen(GetTickCount());
    std::uniform_int_distribution<> dis(1, 2147483647);

//header for .csv file - Report Reference [3]:
    outputOps << "Array length" << "," << "MinDistance()" << "," << "MinDistance2()" << std::endl; //Disable when testing executiong time
    outputTime << "Array length" << "," << "Avg MinDistance() etime (ms)" << "," << "Avg MinDistance2() etime (ms)" << std::endl; //Disable when testing basic ops

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


        // Output Basic Operation Counting results
        outputOps << n << "," << basic << "," << basic2 << std::endl; //output for each row of .csv file - Report Reference [3]
        // Reset counters to 0
        basic = 0;
        basic2 = 0;

        // Output Execution Time results
        outputTime << n << "," << etime/NUM_ARRAY_TRIALS << "," << etime2/NUM_ARRAY_TRIALS << std::endl; //output for each row of .csv file -  Reference [3]
        // Reset counters to 0
        etime = 0;
        etime2 = 0;
    }

    outputOps.close();
    outputTime.close();
    return 0;
}

int MinDistance(int* A, int n){
    int dmin = INT_MAX;   //doesn't have to actually be infinity. Just large enough that it can be overiden by the actual minimum
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
    int dmin = INT_MAX;   //doesn't have to actually be infinity. Just large enough that it can be overiden by the actual minimum
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
    int dmin = INT_MAX;   //doesn't have to actually be infinity. Just large enough that it can be overiden by the actual minimum
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
    int dmin = INT_MAX;   //doesn't have to actually be infinity. Just large enough that it can be overiden by the actual minimum
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
