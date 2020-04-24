// Alexander Lo
// 301284737
// Xcode
// I would like my final to be 100% based on the problems instead of MC
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

void printPattern(unsigned int nRows, const unsigned int totalRows);

int main() {
    int totalRows = 0;
    int minRows = 0;
    int maxRows = 10;
    int tries = 0;
    int maxTries = 4;
    
    do {
        cout << "Enter number of rows ";
        if(!(cin  >> totalRows) ) {
            if(tries == maxTries) {
                cerr << "ERROR: Exceeded max number of tries entering data" << endl;
                return 0;
            }
            cerr << endl << "ERROR: initial estimate was not a number" << endl;
            cin.clear();
            cin.ignore(1024, '\n');
        }
        else if (totalRows < minRows || totalRows > maxRows) {
            if(tries == maxTries) {
                cerr << "ERROR: Exceeded max number of tries entering data" << endl;
                return 0;
            }
            cerr << endl << "Value you entered was not in range" << endl;
        }
        else {
            break;
        }
        tries++;
    } while(tries < maxTries);
    
    printPattern(totalRows, totalRows);
    return 0;
}

void printPattern(unsigned int nRows, const unsigned int totalRows) {
    if(nRows <= 0) {
        return;
    }
    else {
        printPattern(nRows - 1, totalRows);
        for(int i = 0; i < totalRows - nRows + 1; i++) {
            cout << setw(4) << "   ";
        }
        for(int i = 1; i <= nRows; i++) {
            cout << setw(2) << right << pow(i,2) << "  ";
        }
        cout << endl;
    }
}
