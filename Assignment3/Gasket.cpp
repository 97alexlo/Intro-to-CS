//Alexander Lo
//Using Xcode

#include "Gasket.h"
#include <cmath>

//Default
Gasket::Gasket() {
    iterations = 0;
    xLocation = 0;
    yLocation = 0;
    width = 100;
    height = 100;
    gasketColour = Colour(0, 0, 0, 255);
    lenSubRectList = 1;
    listOfSubRectangles = new Rectangle[lenSubRectList];
    listOfSubRectangles[0] = Rectangle(xLocation, yLocation, width, height, gasketColour);
}

Gasket::Gasket( int iterationsValue, int xLocationValue, int yLocationValue, int widthValue, int heightValue, Colour gasketColourValue) {
    width = widthValue;
    height = heightValue;
    iterations = iterationsValue;
    if (iterationsValue < 0) {
        cout << "Iterations value was out of bound" << endl;
        cout << "It has been set to 0" << endl;
        iterations = 0;
    }
    gasketColour = gasketColourValue;
    
    
    if(xLocationValue >= 0 && xLocationValue < pageWidth)
    {
        xLocation = xLocationValue;
    }
    else
    {
        cout << "y position of Gasket object is off the page " << endl;
        cout << "x position and y position have been reset to 0" << endl;
        yLocationValue = 0;
        xLocation = 0;
        yLocation = 0;
    }
    if(yLocationValue >= 0 && yLocationValue < pageLength)
    {
        yLocation = yLocationValue;
    }
    else
    {
        cout << "x position of Gasket object is off the page " << endl;
        cout << "x position and y position have been reset to 0" << endl;

        xLocation = 0;
        yLocation = 0;
    }
    if(xLocation + width > pageWidth)
    {
        cout << "scaling in x " << endl;
        cout << "width was " << width;
        width = pageWidth - xLocation;
        cout << " width is now " << width << endl;
    }
    if(yLocation + height > pageLength)
    {
        ::cout << "scaling in y " << endl;
        cout << "height was " << height;
        height = pageLength - yLocation;
        cout << " height is now " << height << endl;
    }
    
    lenSubRectList = findLength(iterations);
    listOfSubRectangles = new Rectangle[lenSubRectList];
    listOfSubRectangles[0] = Rectangle(xLocation, yLocation, width, height, gasketColour);
    for(int i = 1; i < lenSubRectList; i++) {
        GasketDivide(listOfSubRectangles);
    }
}

//Copy contructor
Gasket::Gasket(const Gasket& toBeCopied) {
    height = toBeCopied.height;
    width = toBeCopied.width;
    xLocation = toBeCopied.xLocation;
    yLocation = toBeCopied.yLocation;
    gasketColour = toBeCopied.gasketColour;
    lenSubRectList = toBeCopied.lenSubRectList;
    listOfSubRectangles = new Rectangle[lenSubRectList];
    for(int i = 0; i < lenSubRectList; i++) {
        listOfSubRectangles[i] = toBeCopied.listOfSubRectangles[i];
    }
}

//Destructor
Gasket::~Gasket() {
    delete[] listOfSubRectangles;
}

//Accessor functions
int Gasket::GetIterations() const {
    return iterations;
}

int Gasket::GetXLocation() const{
    return xLocation;
}

int Gasket::GetYLocation() const {
    return yLocation;
}

int Gasket::GetHeight() const {
    return height;
}

int Gasket::GetWidth() const {
    return width;
}

Colour Gasket::GetGasketColour() const {
    return gasketColour;
}

void Gasket::SetIterations(const int iterationsValue) {
    iterations = iterationsValue;
    if(iterationsValue < 0) {
        iterations = 0;
    }
    lenSubRectList = findLength(iterations);
    delete [] listOfSubRectangles;
    listOfSubRectangles = NULL;
    listOfSubRectangles = new Rectangle[lenSubRectList];
    listOfSubRectangles[0] = Rectangle(xLocation, yLocation, width, height, gasketColour);
    for(int i = 0; i < iterations; i++) {
        GasketDivide(listOfSubRectangles);
    }
}

void Gasket::SetGasketColour(const Colour gasketColorValue) {
    gasketColour = gasketColorValue;
}

void Gasket::SetWidth(const int widthValue) {
    width = widthValue;
    if(xLocation + width > pageWidth ) {
        width = pageWidth - xLocation;
    }
    delete [] listOfSubRectangles;
    listOfSubRectangles = NULL;
    listOfSubRectangles = new Rectangle[lenSubRectList];
    listOfSubRectangles[0] = Rectangle(xLocation, yLocation, width, height, gasketColour);
    for(int i = 0; i < iterations; i++) {
        GasketDivide(listOfSubRectangles);
    }
}


void Gasket::SetHeight(const int heightValue) {
    height = heightValue;
    if(yLocation + height > pageLength ) {
        height = pageLength - yLocation;
    }
    delete [] listOfSubRectangles;
    listOfSubRectangles = NULL;
    listOfSubRectangles = new Rectangle[lenSubRectList];
    listOfSubRectangles[0] = Rectangle(xLocation, yLocation, width, height, gasketColour);
    for(int i = 0; i < iterations; i++) {
        GasketDivide(listOfSubRectangles);
    }
}

void Gasket::SetYLocation(const int yLocationValue) {
    if(yLocationValue >= 0 && yLocationValue < pageLength)
    {
        yLocation = yLocationValue;
    }
    else
    {
        xLocation = 0;
        yLocation = 0;
    }
    delete [] listOfSubRectangles;
    listOfSubRectangles = NULL;
    listOfSubRectangles = new Rectangle[lenSubRectList];
    listOfSubRectangles[0] = Rectangle(xLocation, yLocation, width, height, gasketColour);
    for(int i = 0; i < iterations; i++) {
        GasketDivide(listOfSubRectangles);
    }
}

void Gasket::SetXLocation(const int xLocationValue) {
    if(xLocationValue >= 0 && xLocationValue < pageWidth)
    {
        xLocation = xLocationValue;
    }
    else
    {
        xLocation = 0;
        yLocation = 0;
    }
    delete [] listOfSubRectangles;
    listOfSubRectangles = NULL;
    listOfSubRectangles = new Rectangle[lenSubRectList];
    listOfSubRectangles[0] = Rectangle(xLocation, yLocation, width, height, gasketColour);
    for(int i = 0; i < iterations; i++) {
        GasketDivide(listOfSubRectangles);
    }
}

void Gasket::GasketDisplay(BMP &myImageValue, string theOutputFile) {
    for (int i = 0; i < lenSubRectList ;i++)
    {
         listOfSubRectangles[i].RectangleDisplay(myImageValue, theOutputFile);
    }
}

void Gasket::GasketPrint() {
    cout << setw(19) << "iterations" << setw(10) << iterations << endl;
    cout << setw(19) << "xLocation" << setw(10) << xLocation << endl;
    cout << setw(19) << "yLocation" << setw(10) << yLocation << endl;
    cout << setw(20) << "width" << setw(9) << width << endl;
    cout << setw(20) << "height" << setw(9) << height << endl;
    cout << setw(20) << "gasketColour" << setw(9) << gasketColour << endl;
    cout << setw(20) << "lenSubTriList" << setw(9) << lenSubRectList << endl << endl;
    for(int i = 0; i < lenSubRectList; i++) {
        listOfSubRectangles[i].RectanglePrint();
        cout << endl;
    }
}

ostream& operator << (ostream& os, const Gasket& myGasket) {
    os << setw(19) << "iterations" << setw(10) << myGasket.iterations << endl;
    os << setw(19) << "xLocation" << setw(10) << myGasket.xLocation << endl;
    os << setw(19) << "yLocation" << setw(10) << myGasket.yLocation << endl;
    os << setw(20) << "width" << setw(9) << myGasket.width << endl;
    os << setw(20) << "height" << setw(9) << myGasket.height << endl;
    os << setw(20) << "gasketColour" << setw(9) << myGasket.gasketColour << endl;
    os << setw(20) << "lenSubTriList" << setw(9) << myGasket.lenSubRectList << endl << endl;
    for(int i = 0; i < myGasket.lenSubRectList; i++) {
        myGasket.listOfSubRectangles[i].RectanglePrint();
        os << endl << endl;
    }
    return os;
}
    
const Gasket& Gasket::operator = (const Gasket& Gasket2) {
    iterations = Gasket2.iterations;
    xLocation = Gasket2.xLocation;
    yLocation = Gasket2.yLocation;
    width = Gasket2.width;
    height = Gasket2.height;
    gasketColour = Gasket2.gasketColour;
    lenSubRectList = Gasket2.lenSubRectList;
    for(int i = 0; i < lenSubRectList; i++) {
        listOfSubRectangles[i] = Gasket2.listOfSubRectangles[i];
    }
    
    return *this;
}

bool Gasket::operator ==(const Gasket& Gasket2) const {
    if ( width == Gasket2.width  &&
         height == Gasket2.height &&
         xLocation == Gasket2.xLocation &&
         yLocation == Gasket2.yLocation &&
         gasketColour == Gasket2.gasketColour &&
        iterations == Gasket2.iterations &&
        lenSubRectList == Gasket2.lenSubRectList) {
        return true;
    }
    else {
        return false;
    }
}
    
//void Gasket::GasketDivide(Rectangle *listOfSubRectangles) {
//    for (int i = lenSubRectList-1; i >= 0; i--) {
//        listOfSubRectangles[i].RectangleDivide(&listOfSubRectangles[i*2] );
//    }
//}

void Gasket::GasketDivide(Rectangle *listOfSubRectangles) {
    Rectangle *temp = new Rectangle[lenSubRectList];
    for(int i = 0; i < lenSubRectList; i++) {
    temp[i] = listOfSubRectangles[i];
    }
        for(int j = 0; j < iterations; j++) {
            temp[j].RectangleDivide(&listOfSubRectangles[j*2]);
        }
    }

int Gasket::findLength(int numIter) {
    if (numIter == 0) {
        return 1;
    }
    else if (numIter == 1) {
        return 2;
    }
    else {
        return pow(2, numIter);
    }
}
