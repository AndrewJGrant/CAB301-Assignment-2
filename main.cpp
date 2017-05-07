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
#else
#define INIT_TIMER
#define START_TIMER
#define STOP_TIMER
#endif

int MinDistance(int* A, int n);
int MinDistance2(int* A, int n);

long long int basic = 0;  //basic op counter
long long int etime = 0;  //execution time counter

int main()
{
//The following lines are for RNG - Report Reference [2]:
    std::mt19937 gen(GetTickCount());
    std::uniform_int_distribution<> dis(1, 2147483647);

//header for .csv file - Report Reference [3]:
    output << "Array length" << "," << "Avg basic ops" << std::endl; //Disable when testing executiong time
    //output << "Array length" << "," << "Avg execution time (ms)" << std::endl; //Disable when testing basic ops

    INIT_TIMER
    for (int n = 400; n<=10000; n+=25){     //Where n is the size of the test array
        for (int i = 0; i<100; i++){        //Determines how many arrays of each n itteration is tested
            int A[n];
            for (int j = 0; j<n; j++){      //Populating test array with RNG
                A[j] = dis(gen);
            }
            //FOR TESTING//cout << "minimum distance = " << MinDistance(A, n) << endl;
            //START_TIMER //Disable when testing basic ops

            MinDistance(A, n);
            MinDistance2(A, n);

            //STOP_TIMER  //Disable when testing basic ops - adds milliseconds since 'START_TIMER' to 'etime' counter.
            //FOR TESTING//cout << "basic operations performed = " << basic/(i+1) << endl;
        }
    //Disable Following for testing basic ops:
        //output << n << "," << etime/100 << std::endl; //output for each row of .csv file - Report Reference [3]
        //etime = 0;

    //Disable Following for testing execution time:
        output << n << "," << basic/100 << std::endl; //output for each row of .csv file - Report Reference [3]
        basic = 0;
    }

    output.close();
    return 0;
}

int MinDistance(int* A, int n){
    int dmin = 0;   //SHOULD BE INFINITE NOT ZERO??? May need: "double dmin = std::numeric_limits<double>::infinity();"
    for (int i = 0; i <= n-1; i++) {
        for (int j = 0; j <= n-1; j++) {
            basic++;  // Increments the basic operation count. Disable when testing execution time
            if ((i != j) && (ceil(A[i] - A[j]) < dmin)){
                dmin = ceil(A[i] - A[j]);
            }
        }
    }
    return dmin;
}

int MinDistance2(int* A, int n){
    int dmin = 0;   //SHOULD BE INFINITE NOT ZERO??? May need: "double dmin = std::numeric_limits<double>::infinity();"
    for (int i = 0; i <= n-2; i++) {
        for (int j = i+1; j <= n-1; j++) {
            int temp = ceil(A[i] - A[j]);
            basic++;  // Increments the basic operation count. Disable when testing execution time
            if (temp < dmin){
                dmin = temp;
            }
        }
    }
    return dmin;
}
