//  Assignment 1a
//  By Alexander Lo
//  301284737
//  January 26, 2020
//  This program produces a table with aach row showing information about the approximations to the roots
//  of the polynomial for a different initial estimate of the root. Within each row successive
//  approximations are calculated using the formula derived using Newton’s method.

#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <string>

using namespace std;

// Functions
double newtonsMethod(double, double, double);
double fx(double, int, double x[]);
double fxPrime(double, int, double x[]);

int main() {
    
    // Inputs
    double initialEstimate = 0.0;
    double increment = 0.0;
    string inputFileName;
    string outputFileName;

    // Streams for input and output
    ifstream inputStream;
    ofstream outputStream;

    // Other variables
    int tries = 1;
    int numRows = 1;
    double tempEstimate = 0;
    double  prevEst = 0.0;
    double nextEst = 0.0;
    int size = 4;
    double coeff[5];

    // Constants
    const double maxInitialEst = 8.0;
    const double minInitialEst = -8.0;
    const double maxIncrementEst = 4.0;
    const double minIncrementEst = 0.1;
    const int estimateWidth = 12;
    const int sub1Width = 12;
    const int sub2Width = 12;
    const int sub3Width = 12;
    const int numIterWidth = 8;
    const int rootWidth = 12;
    const int estimateDecimal = 4;
    const int subDecimal = 5;
    const int rootDecimal = 4;
    const double epsilon = 0.00001;
    const int maxTries = 4;
    const int maxRows = 20;
    const int maxIterations = 30;
    const char invalid1[] = "------------------------";
    const char invalid2[] = "------------";
    const double coeffMax = 20;
    const double coeffMin = -20;
    const int outputWidth = 16;
    const int outputDecimal = 9;
    
    //Prompt for initial estimate input
    do {
        cout << "Enter initial estimate of root : ";
        if(!(cin  >> initialEstimate) ) {
            if(tries == maxTries) {
                cerr << "ERROR: Exceeded max number of tries entering data" << endl;
                return 0;
            }
            cout << endl << "ERROR: initial estimate was not a number" << endl;
            cin.clear();
            cin.ignore(1024, '\n');
        }
        else if (initialEstimate < minInitialEst || initialEstimate > maxInitialEst) {
            if(tries == maxTries) {
                cerr << "ERROR: Exceeded max number of tries entering data" << endl;
                return 0;
            }
            cout << endl << "Value you entered was not in range";
            cout << endl <<" -8.000 <= initial estimate <= 8.000" << endl;
        }
        else {
            break;
        }
        tries++;
    } while(tries <= maxTries);

    tries = 1;

    //Prompt for increment input
    do
    {
        cout << "Enter increment for estimate of root : ";
        if(!(cin  >> increment) )
        {
            if(tries == maxTries) {
                cerr << "ERROR: Exceeded max number of tries entering data" << endl;
                return 0;
            }
            cout << endl<<  "ERROR: increment was not a number" << endl;
            cin.clear();
            cin.ignore(1024, '\n');
            // first argument is maximum number of characters to read
            // ignore stops reading when it encounters the character in
            // the second argument
        }
        else if (increment < minIncrementEst || increment > maxIncrementEst)
        {
            if(tries == maxTries) {
                cerr << "ERROR: Exceeded max number of tries entering data" << endl;
                return 0;
            }
            cout << endl << "Value you entered was not in range";
            cout << endl <<" 0.100 <= initial estimate <= 4.000" << endl;
        }
        else
        {
            break;
        }
        tries++;
    }while ( tries <= maxTries);
    
    tries = 1;
    
    // Get number of rows possible for the table.
    // Number of rows won't exceed 20 and have a minimum of 1 row
    tempEstimate = initialEstimate;
    while(1) {
        tempEstimate += increment;
        if(tempEstimate >= maxInitialEst) {
            break;
        }
        if(numRows > maxRows) {
            numRows = maxRows;
            break;
        }
        numRows++;
    }
    
    // Prompt for the input file name and check if it can be opened
    cout << "Enter the name of the input file containing coefficients : ";
    cin >> inputFileName;
    inputStream.open(inputFileName);
    if(inputStream.fail()) {
        cerr << "Cannot open coefficient file" << endl;
        return 0;
    }
    
    // read the coefficients from the input file into an array and check for errors
    for(int i = size; i >= 0; i--) {
        if(!(inputStream >> coeff[i])) {
            if(inputStream.eof()) {
                cout << "The value of the coefficient for x**" << i << " is not in the input file" << endl;
                return 0;
            }
            else {
                cout << "The value of the coefficient for x**" << i << " is not a floating point number" << endl;
                return 0;
            }
        }
        else if(coeff[i] > coeffMax || coeff[i] < coeffMin) {
            cout << "The value of the coefficient for x**" << i << " is not in range" << endl;
            return 0;
        }
    }
    
    inputStream.close();

    // Prompt for the onput file name and check if it can be opened
    cout << "Enter the name of the output file: ";
    cin >> outputFileName;
    outputStream.open(outputFileName);
    if(outputStream.fail()) {
        cerr << "Cannot open the output file" << endl;
        return 0;
    }
    
    cout << endl << endl;
    
    // Create headers for the columns of the table
    cout
    << setw(estimateWidth) << right << "estimate"
    << setw(sub1Width) << right << "XSub1"
    << setw(sub2Width) << right << "XSub2"
    << setw(sub3Width) << right << "XSub3"
    << setw(numIterWidth) << right << "# Iter"
    << setw(rootWidth) << right << "Root" << endl;

    // Create numRow rows for the table
    for (int i = 0; i < numRows; i++) {
        
        //headers for columns in the output file
        outputStream
        << right << setw(outputWidth) << "it#"
        << right << setw(outputWidth) << "X value" << endl;
        
        outputStream
        << right << setw(outputWidth) << 0
        << right << setw(outputWidth) << fixed << setprecision(outputDecimal) << initialEstimate << endl;
        
        // write initial estimate in the first column
        cout << setw(estimateWidth) << right << fixed << setprecision(estimateDecimal) << initialEstimate;
        
        prevEst = initialEstimate;
        
        for( int j = 1; j <= maxIterations; j++) {
            nextEst = newtonsMethod(prevEst, fx(prevEst, size, coeff), fxPrime(prevEst, size, coeff));
            if (j < 3) {
                if(fabs(nextEst - prevEst) < epsilon && j == 1) {
                    cout
                    << setw(sub1Width) << right << fixed << setprecision(subDecimal) << nextEst
                    << invalid1
                    << setw(numIterWidth) << right << j
                    << setw(rootWidth) << right << fixed << setprecision(rootDecimal) << nextEst << endl;
                    
                    // write to output file
                    outputStream << "The value of the root is "
                    << fixed << setprecision(subDecimal) << nextEst << endl;
                    outputStream << "The root took  " << j << " iterations to calculate" << endl << endl << endl;
                    break;
                }
                else if(fabs(nextEst - prevEst) < epsilon && j == 2) {
                    cout << setw(sub1Width) << right << fixed << setprecision(subDecimal) << nextEst
                    << invalid2
                    << setw(numIterWidth) << right << j
                    << setw(rootWidth) << right << fixed << setprecision(rootDecimal) << nextEst << endl;
                    
                    // write to output file
                    outputStream << "The value of the root is "
                    << fixed << setprecision(subDecimal) << nextEst << endl;
                    outputStream << "The root took  " << j << " iterations to calculate" << endl << endl << endl;
                    break;
                }
                else if(prevEst == 0) {
                    cout << "horizontal tangent, cannot continue iterations" << endl;
                    break;
                }
                else {
                    cout << setw(sub1Width) << right << fixed << setprecision(subDecimal) << nextEst;
                }
            }
            else if(j == 3) {
                cout << setw(sub1Width) << right << fixed << setprecision(subDecimal) << nextEst;
            }
            else if(fabs(nextEst - prevEst) < epsilon && j > 3) {
                cout
                << setw(numIterWidth) << right << j
                << setw(rootWidth) << right << fixed << setprecision(rootDecimal) <<  nextEst << endl;
                
                // write to output file
                outputStream << "The value of the root is "
                << fixed << setprecision(subDecimal) << nextEst << endl;
                outputStream << "The root took  " << j << " iterations to calculate" << endl << endl << endl;
                break;
            }
            else if(fabs(nextEst - prevEst) >= epsilon && j == maxIterations){
                cout
                << "  DID NOT CONVERGE" << endl;
                // print to output file
                outputStream << "DID NOT CONVERGE" << endl << endl << endl;
                break;
            }
            
            //write to output file
            outputStream
            << right << setw(outputWidth) << j
            << right << setw(outputWidth) << fixed << setprecision(outputDecimal) << nextEst << endl;
            
            prevEst = nextEst;
        }
    initialEstimate += increment;
    }
    
    outputStream.close();
    
    return 0;
}

// Create functions to calculate the approximations using newtons method
double fx(double x, int size, double coeff[5]) {
    double a = 0.0;
    for(int i = size; i >= 0; i--){
        a += coeff[i] * pow(x, i);
    }
    return a;
}

double fxPrime(double x, int size, double coeff[5]) {
    double a = 0.0;
    for(int i = size-1; i >= 0; i--){ //start from i = size - 1 because the derivative of a constant is 0
        a += i * coeff[i] * pow(x, i-1);
    }
    return a;
}

double newtonsMethod(double initial, double func, double deriv) {
    return initial - func / deriv;
}
