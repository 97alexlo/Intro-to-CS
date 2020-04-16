// Alexander Lo
// Using Xcode

#include "Header.h"
#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

Matrix::Matrix() {
    numRows = 1;
    numCols = 1;
    MatrixPtr = NULL;
}

Matrix::Matrix(int numRowsValue,  int numColsValue) {
    if(numRowsValue > 20 || numRowsValue < 0) {
        cerr << "number of rows invalid" << endl;
        cerr << "number of rows has been set to 1" << endl;
        numRows = 1;
    }
    else {
        numRows = numRowsValue;
    }
    if(numColsValue > 20 || numColsValue < 0) {
        cerr << "number of columns invalid" << endl;
        cerr << "number of columns has been set to 1" << endl;
        numCols = 1;
    }
    else {
        numCols = numColsValue;
    }
    MatrixPtr = new (nothrow) int*[numRows];
    MatrixPtr[0] = new(nothrow) int[numRows*numCols];
    for(int i = 1; i < numRows; i++) {
        MatrixPtr[i] = MatrixPtr[0] + i*numCols;
    }
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            MatrixPtr[i][j] = 0;
        }
    }
}

Matrix::~Matrix() {
    delete [] MatrixPtr[0];
    delete [] MatrixPtr;
}

void Matrix::setnumRows(int numRowsValue) {
    if(numRowsValue > 0 && numRowsValue < 20) {
        numRows = numRowsValue;
    }
    else {
        numRows = 0;
    }
}

Matrix::Matrix(Matrix &MatrixToCopy) {
    numRows = MatrixToCopy.numRows;
    numCols = MatrixToCopy.numCols;
    for(int i = 0; i < numRows; i++) {
        for(int j = 0; i < numCols; j++) {
            MatrixPtr[i][j] = MatrixToCopy.MatrixPtr[i][j];
        }
    }
}

void Matrix::print() {
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            cout << MatrixPtr[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}
