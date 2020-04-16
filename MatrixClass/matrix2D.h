//
//  Header.h
//  cmpt129
//
//  Created by Alex Lo on 2020-04-15.
//  Copyright © 2020 Alex Lo. All rights reserved.
//

#ifndef Header_h
#define Header_h

#include <iostream>
#include <iomanip>
#include <cstdlib>

class Matrix
{
    public:
        Matrix( int numRowsValue,  int numColsValue);
        Matrix();
        Matrix(Matrix &MatrixToCopy);
        ~Matrix();
        void setnumRows(int numRowsValue);
        void print();
    private:
        int numRows;
        int numCols;
        int** MatrixPtr;
};

#endif /* Header_h */
