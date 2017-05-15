#include <iostream>
#include <fstream>
#include <math.h>
#include <random>
#include <windows.h>
#include <chrono>

using namespace std;

ofstream output("Output.csv");

//Following all taken from Report Reference [4], Except for 'STOP_TIMER' which is modified to suit our tests
//#define TIMING    //disable this line when measuring basic operations

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

int MinDistance(int* A, int n);
int MinDistance2(int* A, int n);

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
    output << "Array length" << "," << "Avg MinDistance() basic ops" << "," << "Avg MinDistance2() basic ops" << std::endl; //Disable when testing executiong time
    //output << "Array length" << "," << "Avg MinDistance() execution time (ms)" << "," << "Avg MinDistance2() execution time (ms)" << std::endl; //Disable when testing basic ops

    INIT_TIMER
    for (int n = 100; n<=1000; n+=20){     //Where n is the size of the test array
        for (int i = 0; i<10; i++){        //Determines how many arrays of each n itteration is tested
            int A[n];
            for (int j = 0; j<n; j++){      //Populating test array with RNG
                A[j] = dis(gen);
            }

            //START_TIMER //Disable when testing basic ops
            cout << "minimum distance = " << MinDistance(A, n) << endl;
            //MinDistance(A, n); //Disable when testing output above^
            //STOP_TIMER  //Disable when testing basic ops - adds milliseconds since 'START_TIMER' to 'etime' counter.
        //TESTING//cout << "etime1 = " << etime/(i+1) << endl;

            //START_TIMER //Disable when testing basic ops
            cout << "minimum distance2 = " << MinDistance2(A, n) << endl;
            //MinDistance2(A, n); //Disable when testing output above^
            //STOP_TIMER2  //Disable when testing basic ops - adds milliseconds since 'START_TIMER' to 'etime' counter.
        //TESTING//cout << "etime2 = " << etime2/(i+1) << endl;

            cout << "basic operations performed = " << basic/(i+1) << endl;
            cout << "basic operations performed2 = " << basic2/(i+1) << endl;
        }

    //Disable Following for testing execution time:
        output << n << "," << basic/10 << "," << basic2/10 << std::endl; //output for each row of .csv file - Report Reference [3]
        basic = 0;
        basic2 = 0;

    //Disable Following for testing basic ops:Report
        //output << n << "," << etime/100 << "," << etime2/100 << std::endl; //output for each row of .csv file -  Reference [3]
        //etime = 0;
        //etime2 = 0;
    }

    output.close();
    return 0;
}

int MinDistance(int* A, int n){
    int dmin = INT_MAX;   //doesn't have to actually be infinity. Just large enough that it can be overiden by the actual minimum
    for (int i = 0; i <= n-1; i++) {
        for (int j = 0; j <= n-1; j++) {
            if (i != j){
                basic++;  // Increments the basic operation count for this algorithm. Disable when testing execution time
                if (abs(A[i] - A[j]) < dmin){
                    dmin = abs(A[i] - A[j]);
                    basic++;  // Increments the basic operation count for this algorithm. Disable when testing execution time
                }
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
            basic2++;  // Increments the basic operation count for this algorithm. Disable when testing execution time
            if (temp < dmin){
                dmin = temp;
            }
        }
    }
    return dmin;
}
