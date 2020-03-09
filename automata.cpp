// A program that implements Conway's Game of Life and the Sierpinski triangle
// Created by Alexander Lo
// March 8, 2020

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <string>

const int MAX_ARRAY_SIZE = 50;
const char X = 'X';

using namespace std;

//Conway's game of life functions
void InitGen(char lifeBoard[][MAX_ARRAY_SIZE], int& numRowsInBoard, int& numColsInBoard, int& generations);
 
void NextGen(char lifeBoard[][MAX_ARRAY_SIZE], int numRowsInBoard, int numColsInBoard);
 
void PrintGen(char lifeBoard[][MAX_ARRAY_SIZE], ostream& outStream, int numRowsInBoard, int numColsInBoard, int generationNum);

void SwapBoards(char lifeBoard[][MAX_ARRAY_SIZE], char nexGenBoard[][MAX_ARRAY_SIZE], int numRowsInBoard, int numColsInBoard);

//Sierpinski triangle functions
void InitGen(int sierpBoard[][MAX_ARRAY_SIZE], int& numRowsInBoard, int& numColsInBoard, int& generations);
 
void NextGen(int sierp[][MAX_ARRAY_SIZE], int numRowsInBoard, int numColsInBoard);
 
void PrintGen(int sierpBoard[][MAX_ARRAY_SIZE], ostream& outStream, int numRowsInBoard, int numColsInBoard, int generationNum);

int main() {
    int nrows = 0;
    int ncols = 0;
    int nGen = 0;
    ofstream outStream;
    string outputFileName = {'\0'};
    char lifeBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE];
    int sierpBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE];

    //initialize board
    InitGen(lifeBoard, nrows, ncols, nGen);
    
    cout << "Enter the name of the output file: ";
    cin >> outputFileName;
    
    outStream.open(outputFileName);
    if(outStream.fail()) {
        cerr << "ERROR: output file not opened correctly" << endl;
        exit(1);
    }
    
    //print gameboard
    for(int i = 0; i <= nGen; i++) {
        //initial gameboard
        PrintGen(lifeBoard, cout, nrows, ncols, i);
        //gameboard generations from 1 to i
        PrintGen(lifeBoard, outStream, nrows, ncols, i);
        NextGen(lifeBoard, nrows, ncols); //calculate next gameboard
    }
    outStream.close();
    
    // Sierpinski triangle
    InitGen(sierpBoard, nrows, ncols, nGen);
    cout << "Enter the name of the output file: ";
    cin >> outputFileName;
    
    outStream.open(outputFileName);
    if(outStream.fail()) {
        cerr << "ERROR: output file not opened correctly" << endl;
        exit(1);
    }
    
    //print gameboard
    for(int i = 0; i <= nGen; i++) {
        if(i == 0 || i == 1){
            //initial gameboard
            PrintGen(sierpBoard, cout, nrows, ncols, i);
            //gameboard generations from 1 to i
            PrintGen(sierpBoard, outStream, nrows, ncols, i);
            //calculate next gameboard locations
        }
        else if(i < nGen) {
            PrintGen(sierpBoard, outStream, nrows, ncols, i);
        }
        else {
            PrintGen(sierpBoard, cout, nrows, ncols, i);
            PrintGen(sierpBoard, outStream, nrows, ncols, i);
        }
        NextGen(sierpBoard, nrows, ncols);
    }
    
    outStream.close();
    return 0;
}

void InitGen(char lifeBoard[][MAX_ARRAY_SIZE], int& numRowsInBoard, int& numColsInBoard, int& generations) {
    ifstream inStream;
    string inputFileName = {'\0'};
    int start = 0;
    int colEnd = numColsInBoard - 1;
    int rowEnd = numRowsInBoard - 1;
    const int minBoardLength = 0;
    
    cout << "Enter the name of the input file: ";
    cin >> inputFileName;
    
    inStream.open(inputFileName);
    if(inStream.fail()) {
        cerr << "ERROR: input file not opened correctly" << endl;
        exit(1);
    }
    
    // read rows, columns, and generations for board
    if(!(inStream >> numRowsInBoard)) {
        cerr << "ERROR: Cannot read number of rows" << endl;
        exit(1);
    }
    if(numRowsInBoard > MAX_ARRAY_SIZE || numRowsInBoard <= minBoardLength) {
        cerr << "ERROR: Read an illegal number of rows for the board" << endl;
        exit(1);
    }

    if(!(inStream >> numColsInBoard)) {
        cerr << "ERROR: Cannot read number of columns" << endl;
        exit(1);
    }
    if(numColsInBoard > MAX_ARRAY_SIZE || numColsInBoard <= minBoardLength) {
        cerr << "ERROR: Read an illegal number of columns for board" << endl;
        exit(1);
    }

    if(!(inStream >> generations)) {
        cerr << "ERROR: Cannot read number of generations" << endl;
        exit(1);
    }
    if(generations > MAX_ARRAY_SIZE || numColsInBoard <= minBoardLength) {
        cerr << "ERROR: Read an illegal number generations" << endl;
        exit(1);
    }

    // skip line
    string line2;
    getline(inStream, line2);
    
    // initialize board
    for(int i = 0; i < numRowsInBoard; i++) {
        string line;
        getline(inStream, line);
        if(line.length() > numColsInBoard+1) {
            cerr << "ERROR: ignoring extra characters in line " << i << endl;
            cerr << line.length();
        }
        if(line.length() <= numColsInBoard || inStream.eof()) {
            cerr << "ERROR: Not enough characters in row " << i << " of the input array" << endl;
            exit(1);
        }
        for(int j = 0; j < numColsInBoard; j++) {
            lifeBoard[i][j] = line[j];
            if(lifeBoard[i][j] != ' ' && lifeBoard[i][j] != X) {
                cerr << "ERROR: Input data for initial board is incorrect" << endl;
                cerr << "Location (" << i << ", " << j  << ") is not valid" << endl;
                exit(1);
            }
            if((i == start || i == rowEnd || j == start || j == colEnd) && (lifeBoard[i][j] == 'X')) {
                cerr << "ERROR: organisms are present in the border of the board, please correct your input file" << endl;
                exit(1);
            }
        }
    }
    inStream.close();
}

void PrintGen(char lifeBoard[][MAX_ARRAY_SIZE], ostream& outStream, int numRowsInBoard, int numColsInBoard, int generationNum) {
    const int ten = 10;
    string edge = "|    |";
    
    if(generationNum == 0) {
        outStream << "LIFE initial game board" << endl;
    }
    else {
        outStream << "LIFE gameboard: generation " << generationNum << endl;
    }
        //board header
        for(int i = 0; i < (numColsInBoard + edge.length()*2); i++) {
            outStream << "_";
        }
        outStream << endl << edge;
        for(int i = 0; i < (numColsInBoard / ten); i++) {
            for (int k = 0; k < ten; k++) {
                outStream << i;
            }
        }
        for(int j = 0; j < (numColsInBoard % ten); j++) {
            outStream << numColsInBoard / ten;
        }
        outStream << edge << endl;
        outStream << edge;
        for(int i = 0; i < numColsInBoard / ten; i++) {
            for(int k = 0; k < ten; k++) {
                outStream << k;
            }
        }
        for(int i = 0; i < numColsInBoard % ten; i++) {
            outStream << i;
        }
        outStream << edge << endl;
        outStream << "|____|";
        for(int i = 0; i < numColsInBoard; i++) {
            outStream << "_";
        }
        outStream << "|____|" << endl;
        
        // body of board
        for(int i = 0; i < numRowsInBoard; i++) {
            if(i < 10) {
                outStream << "|  " << i << " |";
            }
            else {
                outStream <<"| " << i << " |";
            }
            for(int j = 0; j < numColsInBoard; j++) {
                outStream << lifeBoard[i][j];
            }
            if(i < ten) {
                outStream << "|  " << i << " |";
            }
            else {
                outStream <<"| " << i << " |";
            }
            outStream << endl;
        }
        outStream << "|____|";
        for(int i = 0; i < numColsInBoard; i++) {
            outStream << "_";
        }
        outStream << "|____|" << endl << endl << endl << endl;
}

void NextGen(char lifeBoard[][MAX_ARRAY_SIZE], int numRowsInBoard, int numColsInBoard) {
    char nexGenBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE];
    
    // initialize nexGenBoard to blank spaces
    for(int i = 0; i < numRowsInBoard; i++) {
        for(int j = 0; j < numColsInBoard; j++) {
            nexGenBoard[i][j] = {' '};
        }
    }
    
    // get number of neighbours for each square
    for(int i = 1; i < numRowsInBoard-1; i++) {
        for(int j = 1; j < numColsInBoard-1; j++) {
            int count = 0;
            for(int y = -1; y < 2; y++) {
                for(int x = -1; x < 2; x++) {
                    if(!(x == 0 && y == 0) && lifeBoard[i+y][j+x] == X) {
                        count++;
                    }
                }
            }

            if(lifeBoard[i][j] == X) {
                if(count == 2 || count == 3) {
                    nexGenBoard[i][j] = X;
                }
            }
            else if(lifeBoard[i][j] == ' ') {
                if(count == 3) {
                    nexGenBoard[i][j] = X;
                }
            }
        }
    }
    //copy temporary board into lifeBoard
    SwapBoards(lifeBoard, nexGenBoard, numRowsInBoard, numColsInBoard);
}

void SwapBoards(char lifeBoard[][MAX_ARRAY_SIZE], char nexGenBoard[][MAX_ARRAY_SIZE], int numRowsInBoard, int numColsInBoard) {
    for(int i = 0; i < numRowsInBoard; i++) {
        for(int j = 0; j < numColsInBoard; j++) {
            lifeBoard[i][j] = nexGenBoard[i][j];
        }
    }
}

void InitGen(int sierpBoard[][MAX_ARRAY_SIZE], int& numRowsInBoard, int& numColsInBoard, int& generations) {
    ifstream inStream;
    string inputFileName = {'\0'};
    const int minBoardLength = 0;
    
    cout << "Enter the name of the input file: ";
    cin >> inputFileName;
    
    inStream.open(inputFileName);
    if(inStream.fail()) {
        cerr << "ERROR: input file not opened correctly" << endl;
        exit(1);
    }
    
    // read rows, columns, and generations for board
    if(!(inStream >> numRowsInBoard)) {
        cerr << "ERROR: Cannot read number of rows" << endl;
        exit(1);
    }
    if(numRowsInBoard >= MAX_ARRAY_SIZE || numRowsInBoard <= minBoardLength) {
        cerr << "ERROR: Read an illegal number of rows for the board" << endl;
        exit(1);
    }

    if(!(inStream >> numColsInBoard)) {
        cerr << "ERROR: Cannot read number of columns" << endl;
        exit(1);
    }
    if(numColsInBoard >= MAX_ARRAY_SIZE || numColsInBoard <= minBoardLength) {
        cerr << "ERROR: Read an illegal number of columns for board" << endl;
        exit(1);
    }

    if(!(inStream >> generations)) {
        cerr << "ERROR: Cannot read number of generations" << endl;
        exit(1);
    }
    if(generations > MAX_ARRAY_SIZE || numColsInBoard <= minBoardLength) {
        cerr << "ERROR: Read an illegal number generations" << endl;
        exit(1);
    }
    
    //initialize board to 0s
    for(int i = 0; i < numRowsInBoard; i++) {
        for(int j = 0; j < numColsInBoard; j++) {
            sierpBoard[i][j] = 0;
        }
    }
    sierpBoard[2][4] = 1;
    inStream.close();
}

void NextGen(int sierp[][MAX_ARRAY_SIZE], int numRowsInBoard, int numColsInBoard) {
    int nexGenBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE];
    
    // initialize nexGenBoard to 0s
    for(int i = 0; i < numRowsInBoard; i++) {
        for(int j = 0; j < numColsInBoard; j++) {
            nexGenBoard[i][j] = 0;
        }
    }
    
    // determine locations for next generations
    for(int k = 1; k < numRowsInBoard-1; k++) {
        for(int j = 1; j < numColsInBoard-1; j++) {
            nexGenBoard[k][j] = (sierp[k][j] + sierp[k-1][j] + sierp[k][j-1] ) % 2;
        }
    }
    //copy temporary board into lifeBoard
    for(int i = 0; i < numRowsInBoard; i++) {
        for(int j = 0; j < numColsInBoard; j++) {
            sierp[i][j] = nexGenBoard[i][j];
        }
    }
}

void PrintGen(int sierpBoard[][MAX_ARRAY_SIZE], ostream& outStream, int numRowsInBoard, int numColsInBoard, int generationNum) {
    const int ten = 10;
    string edge = "|    |";
    
    if(generationNum == 0) {
        outStream << "Sierpinski initial game board" << endl;
    }
    else {
        outStream << "Sierpinski gameboard: generation " << generationNum << endl;
    }
        //board header
        for(int i = 0; i < (numColsInBoard + edge.length()*2); i++) {
            outStream << "_";
        }
        outStream << endl << edge;
        for(int i = 0; i < (numColsInBoard / ten); i++) {
            for (int k = 0; k < ten; k++) {
                outStream << i;
            }
        }
        for(int j = 0; j < (numColsInBoard % ten); j++) {
            outStream << numColsInBoard / ten;
        }
        outStream << edge << endl;
        outStream << edge;
        for(int i = 0; i < numColsInBoard / ten; i++) {
            for(int k = 0; k < ten; k++) {
                outStream << k;
            }
        }
        for(int i = 0; i < numColsInBoard % ten; i++) {
            outStream << i;
        }
        outStream << edge << endl;
        outStream << "|____|";
        for(int i = 0; i < numColsInBoard; i++) {
            outStream << "_";
        }
        outStream << "|____|" << endl;
        
        // body of board
        for(int i = 0; i < numRowsInBoard; i++) {
            if(i < 10) {
                outStream << "|  " << i << " |";
            }
            else {
                outStream <<"| " << i << " |";
            }
            for(int j = 0; j < numColsInBoard; j++) {
                if(sierpBoard[i][j] == 1) {
                    outStream << X;
                }
                else if(sierpBoard[i][j] == 0) {
                    outStream << ' ';
                }
            }
            if(i < ten) {
                outStream << "|  " << i << " |";
            }
            else {
                outStream <<"| " << i << " |";
            }
            outStream << endl;
        }
        outStream << "|____|";
        for(int i = 0; i < numColsInBoard; i++) {
            outStream << "_";
        }
        outStream << "|____|" << endl << endl << endl << endl;
}
