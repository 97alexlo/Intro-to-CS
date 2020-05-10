// Alexander Lo
// 301284737
// Xcode
// I would like my final to be 100% based on the problems instead of MC
#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <string>

using namespace std;

#define max 1.5
#define min -1.5
#define minRow 0
#define maxRow 26

double get3(double x);
double get4(double x);
double error(double a, double b);

int main() {
    double xMin = 0;
    double xMax = 0;
    int numx = 0;
    const double increment = 2.0/9.0;
    
    cout << "enter xMin, the smallest x used in the table -1.5 < x < 1.5 ";
    cin >> xMin;
    if (xMin >= max || xMin <= min) {
        cerr << "You entered a value of xMin that was out of range" << endl;
        exit(1);
    }
    
    cout << "enter xMax, the largest x used in the table -1.5 < x < 1.5 ";
    cin >> xMax;
    if(xMax >= max || xMax <= min) {
        cerr << "You entered a value of xMax that was out of range" << endl;
        exit(1);
    }
    
    if(xMin > xMax) {
        cerr << "You entered a minimum limit larger than your maximum!" << endl;
        exit(1);
    }
    
    cout << "enter numx, the number of rows in the table 0 < x < 26 ";
    cin >> numx;
    if(numx >= maxRow || numx <= minRow) {
        cerr << "You entered an illegal number of rows" << endl;
        exit(1);
    }
    
    cout
    << setw(13) << right << "X"
    << setw(13) << right << "sin3Term(3x)"
    << setw(13) << right << "sin4Term(3x)"
    << setw(13) << right << "sin(3x)"
    << setw(13) << right << "error1"
    << setw(13) << right << "error2" << endl;
    
    for(int i = 0; i < numx; i++) {
        cout <<
        setw(13) << fixed << right << setprecision(8) << xMin <<
        setw(13) << fixed << right << setprecision(8) << get3(xMin) <<
        setw(13) << fixed << right << setprecision(8) << get4(xMin) <<
        setw(13) << fixed << right << setprecision(8) << sin(3 * xMin) <<
        setw(13) << fixed << right << setprecision(8) << error(sin(3 * xMin), get3(xMin)) <<
        setw(13) << fixed << right << setprecision(8) << error(sin(3 * xMin), get4(xMin)) <<
        endl;
        xMin += increment;
    }
    return 0;
}

double get3(double x) {
    x = 3 * x;
    return x - pow(x, 3) / 6 + pow(x, 5) / 120;
}

double get4(double x) {
    x = 3 * x;
    return x - pow(x, 3) / 6 + pow(x, 5) / 120 - pow(x, 7) / 5040;
}

double error(double a, double b) {
    return a - b;
}
