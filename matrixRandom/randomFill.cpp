// Alexander Lo
// 301284737
// Xcode
// I would like my final to be 100% based on the problems instead of MC
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

void randomFill( int **randomArray, int dimension, unsigned int seed );
void addColumn ( int **randomArray, int * sumArray, int dimension);

int main(void)
{
    //  Declare variables
    unsigned int seed = 12345;
    int N = 0;
    int **randomArray = NULL;
    int *sumArray = NULL;
    
    // 2D Array
    cout << "Please enter a seed ";
    cin >> seed;
    cout << "Please enter number of rows in the 2D array ";
    cin >> N;
    
    randomArray = new (nothrow) int*[N];
    if ( randomArray == nullptr)
    {
        cerr << "ERROR: unable to allocate pointer array for 2-D array";
        cerr << endl;
    }
    randomArray[0] = new (nothrow) int[N*N];
    if (randomArray[0] == nullptr)
    {
        cerr << "ERROR: unable to allocate 2-D array storage for array E";
        cerr << endl;
    }
    for (int i = 1; i < N; i++)
    {
        randomArray[i] = randomArray[0]+i*N;
    }
    
    // 1D array
    sumArray = new (nothrow) int[N];
    if (sumArray == nullptr)
    {
        cerr << "ERROR: unable to allocate pointer array for 1-D array A";
        cerr << endl;
    }
    
    randomFill(randomArray, N, seed);
    addColumn(randomArray, sumArray, N);
    
    //testing
    cout << "the 2d matrix is:" << endl;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            cout << randomArray[i][j] << "  ";
        }
        cout << endl;
    }
    
    cout << endl;
    cout << "the sums of each columns are:" << endl;
    for(int i = 0; i < N; i++) {
        cout << sumArray[i] << "  ";
    }
    
    delete sumArray;
    delete [] randomArray[0];
    delete [] randomArray;
}

void randomFill( int **randomArray, int dimension, unsigned int seed ) {
    srand(seed);
    for(int i = 0; i < dimension; i++) {
        for(int j = 0; j < dimension; j++) {
            randomArray[i][j] = rand() % 40 + 10;
        }
    }
}

void addColumn ( int **randomArray, int * sumArray, int dimension) {
    int sum;
    for(int i = 0; i < dimension; i++) {
        sum = 0;
        for(int k = 0; k < dimension; k++) {
            sum += randomArray[k][i];
            sumArray[i] = sum;
        }
    }
}
