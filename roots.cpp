//  Assignment 1a
//  By Alexander Lo
//  301284737
//  January 26, 2020
//  This program produces a table with aach row showing information about the approximations to the roots
//  of the polynomial for a different initial estimate of the root. Within each row successive
//  approximations are calculated using the formula derived using Newton’s method.  It will solve any polynomial of order 0 < order < 4 and prompt for the values of five coefficients through a text file.

#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

// Inputs
double initialEstimate = 0.0;
double increment = 0.0;

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
int tries = 1;
int numRows = 1;
double tempEstimate = 0;
double x = 0.0;
int i = 0;
double  prevEst = 0.0;
double nextEst = 0.0;

// Functions
double newtonsMethod(double, double, double);
double fx(double);
double fxPrime(double);

int main() {
    
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
    
    cout << endl << endl;
    
    // Create headers for the columns of the table
    cout << setw(estimateWidth) << right << "estimate"
    << setw(sub1Width) << right << "XSub1"
    << setw(sub2Width) << right << "XSub2"
    << setw(sub3Width) << right << "XSub3"
    << setw(numIterWidth) << right << "# Iter"
    << setw(rootWidth) << right << "Root" << endl;

    // Create numRow rows for the table
    //
    for (int i = 0; i < numRows; i++) {
        
        cout << setw(estimateWidth) << right << fixed << setprecision(estimateDecimal) << initialEstimate;
        
        prevEst = initialEstimate;
        for( int j = 1; j <= maxIterations; j++) {
            nextEst = newtonsMethod(prevEst, fx(prevEst), fxPrime(prevEst));
            if (j < 3) {
                if(fabs(nextEst - prevEst) < epsilon && j == 1) {
                    cout
                    << setw(sub1Width) << right << fixed << setprecision(subDecimal) << nextEst
                    << invalid1
                    << setw(numIterWidth) << right << j
                    << setw(rootWidth) << right << fixed << setprecision(rootDecimal) << nextEst << endl;
                    break;
                }
                else if(fabs(nextEst - prevEst) < epsilon && j == 2) {
                    cout << setw(sub1Width) << right << fixed << setprecision(subDecimal) << nextEst
                    << invalid2
                    << setw(numIterWidth) << right << j
                    << setw(rootWidth) << right << fixed << setprecision(rootDecimal) << nextEst << endl;
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
                break;
            }
            else if(fabs(nextEst - prevEst) >= epsilon && j == maxIterations){
                cout
                << "  DID NOT CONVERGE" << endl;
                break;
            }
        prevEst = nextEst;
        }
    initialEstimate += increment;
    }
}

// Create functions to calculate the approximations using newtons method
double fx(double x) {
    return 4 * pow(x, 3) - 18 * pow(x, 2) + 6 * x + 8;
}

double fxPrime(double x) {
    return (12 * pow(x, 2) - 36 * x + 6);
}

double newtonsMethod(double initial, double func, double deriv) {
    return initial - func / deriv;
}
