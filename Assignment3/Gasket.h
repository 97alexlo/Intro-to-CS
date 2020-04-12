// Each Gasket has the a length (x extent)
// a width (y extent), a location used for graphic
// display (xlocation, ylocation), and a color
// for grapic display.All distances and
// locations are integers (number of pixels)
// The upper right hand corner is (0,0)
//  y coordinate increased downward
// Author: Janice Regan  March 2006

//#pragma warning(disable: 4996)

#ifndef GasketFlag
#define GasketFlag

#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>
#include <iomanip>
#include "Colour.h"
#include "Rectangle.h"

using namespace std;


class Gasket
{
public:
    //default constructor: no arguments, no return type
    //define if class has any other constructors, or if class
    //includes deep memory (pointers) or static counters
    Gasket();
    //other intializing constructors
    Gasket( int iterationsValue, int xLocationValue, int yLocationValue,
                int widthValue, int heightValue, Colour gasketColourValue);
	Gasket(const Gasket& toBeCopied);
    ~Gasket();

    //accessor functions
	int GetIterations() const;
	int GetXLocation() const;
    int GetYLocation() const;
	int GetWidth() const;
    int GetHeight() const;
    Colour GetGasketColour() const;


    //mutator functions,
    void SetIterations(const int iterationsValue);
    void SetXLocation(const int xLocationValue);
    void SetYLocation(const int yLocationValue);
	void SetWidth(const int widthValue);
    void SetHeight(const int heightValue);
    void SetGasketColour(const Colour gasketColorValue);

    //member function to plot a Gasket to a bitmap
    //myImageValue is a bitmap
    void GasketDisplay(BMP& myImageValue, string theOutputFile);
    void GasketPrint();

    //operators
    const Gasket& operator = (const Gasket& Gasket2);
    bool operator == (const Gasket& Gasket2) const;
    friend ostream& operator << (ostream& os,
        const Gasket& myGasket);

private:
	// helper functions
    int findLength(int numIter);
	void GasketDivide(Rectangle* listOfSubRectangles);
    // Members expressing properties of a Gasket
    int iterations;
	int xLocation;
	int yLocation;
	int width;   
    int height;
	Colour gasketColour;
	Rectangle* listOfSubRectangles;
	int lenSubRectList;
};


#endif
