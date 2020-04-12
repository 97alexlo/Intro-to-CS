

// Each rectangle has the a length (x extent)
// a width (y extent), a location used for graphic
// display (xlocation, ylocation), and a color
// for grapic display.All distances and
// locations are integers (number of pixels)
// The upper right hand corner is (0,0)
//  y coordinate increased downward 
// Author: Janice Regan  2017

#ifndef RectangleFlag
#define RectangleFlag

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <iomanip>
#include "Colour.h"
using namespace std;


class Rectangle
{
public:
    //default constructor: no arguments, no return type
    //define if class has any other constructors, or if class
    //includes deep memory (pointers) or static counters
    Rectangle();
    //other intializing constructors
    Rectangle( int xLocationValue, int yLocationValue, 
        int lengthValue, int HeightValue,
        Colour blockColourValue);
    Rectangle( int xLocationValue, int yLocationValue,
        Colour blockColourValue);
    //copy constructor: needed for function calls
    Rectangle(const Rectangle& toBeCopied);
    //destructor: define when class has deep memory or static counters
    ~Rectangle();
    //accessor functions
    int GetHeight() const;
    int GetWidth() const;
    int GetXLocation() const;
    int GetYLocation() const;
    Colour GetBlockColour() const;
    //accessor functions for static members are static functions
    //this allows the static members to be accessed before any
    //object of the class are created
    static int GetRectanglesCreated();
    static int GetRectanglesExisting();
    //mutator functions, in an actual application you would
    //write mutator functions only for member variable that
    //NEED to be accessed from outside the class, This would
    //be the smallest subSet of member variables possible 
    //(to preserve encapsulation)
    void SetRectangleColour(const Colour blockColorValue);
    void SetWidth(const int widthValue);
    void SetHeight(const int heightValue);
    void SetXLocation(const int xLocationValue);
    void SetYLocation(const int yLocationValue);
    //mutator functions for static members are static functions
    //this allows the static members to be changed before any
    //object of the class are created
    static void SetRectanglesCreated(int numberCreated);
    static void SetRectanglesExisting(int numberExisting);

    //friend function
    //A friend function is not a member function but is
    //allowed to directly access the private members of the class
    friend ostream& operator << (ostream& os, 
        const Rectangle& myRectangle);
    //member function to plot a Rectangle to a bitmap
    //myImageValue is a bitmap
    void RectangleDisplay(BMP& myImageValue, string theOutputFile);
    void RectanglePrint();
    bool DoesOverlay(const Rectangle& rectangle2);
    bool DoesIntersect(const Rectangle& rectangle2);

	//add overloaded operator for last part of problem 1
    const Rectangle& operator = (const Rectangle& Rectangle2);
    bool operator==(const Rectangle& Rectangle2) const; 
    void RectangleDivide(Rectangle* RectList);
	
private:
    // static members counting the number of objects in this
    // class have been created by the application, and how 
    // many objects of this class presently exist
    static int rectanglesCreated;
    static int rectanglesExisting;
    // Members expressing properties of a Rectangle
    int width;
    int height;
    int xLocation;
    int yLocation;
    Colour blockColour;
};


//extern ostream& operator << (ostream& os, const Rectangle& myRectangle);
#endif
