#include "Rectangle.h"

int Rectangle::rectanglesExisting;
int Rectangle::rectanglesCreated;


Rectangle::Rectangle()
{
    // Set the values of the variable elements of class Rectangle
    // Note that realistic values are not given, when using the
    // default constructor it is expected that the user will
    // initialize the values of the members of the class using
    // the mutator functions after the default object has been
    // created
    height = 10;
    width = 10;
    xLocation = 10;
    yLocation = 10;
    blockColour = Colour(0, 0, 0, 255);

    // Increment the counters for rectangles created and
    // rectangles in existance: You are in the process of
    // creating another Rectangle
    rectanglesCreated++;
    rectanglesExisting++;
}


//For Rectangle you need to define your own copy constructor
//Any time the copy constructor is used a new object is
//created. To keep the count of objects consistent you
//must also count Rectangles created by the copy constructor
Rectangle::Rectangle(const Rectangle& toBeCopied)
{
    // Set the values of the variable elements of class Rectangle
    height    = toBeCopied.height;
    width    = toBeCopied.width;
    xLocation = toBeCopied.xLocation;
    yLocation = toBeCopied.yLocation;
    blockColour = toBeCopied.blockColour;

    // Increment the counters for Rectangles created and
    // Rectangles in existance: You are in the process of
    // creating another Rectangle ( a copy of Rectangle toBeCopied)
    rectanglesCreated++;
    rectanglesExisting++;
}


Rectangle::Rectangle( int xLocationValue, int yLocationValue,
                     int widthValue, int heightValue,
                     Colour blockColourValue)
{
    // Set the values of the non-static elements of class
    // Rectangle. The values of the elements are received
    // as values of the parameters of the constructor
    // Note that the names of the parameters are different
    // from the identifiers of the Class elements
    height    = heightValue;
    width    = widthValue;
	if(xLocationValue >= 0 && xLocationValue < pageWidth &&
		yLocationValue >= 0 && yLocationValue < pageLength	)
	{
		xLocation = xLocationValue;
		yLocation = yLocationValue;
	}
	else
	{
		cout << "Rectangle is off the page \n";
		cout << "x position and y position have been reset to 0\n";
		xLocation = 0;
		yLocation = 0;
	}

	if(xLocation + width > pageWidth )
	{
		cout << "Rectangle object partially off the page \n";
		cout << "width reset to include only the part of rectangle on the page \n";
		cout << "width was " << width;
		width = pageWidth - xLocation;
		cout << " width is " << width << endl;
	}
	if(yLocation + height > pageLength )
	{
		cout << "Rectangle object partially off the page \n";
		cout << "height reset to include only the part of rectangle on the page \n";
		cout << "height was " << height;
		height = pageLength - yLocation;
		cout << " height is " << height << endl;
	}

    blockColour= blockColourValue;


    // Increment the counters for rectangles created and
    // rectangles in existance: You are in the process of
    // creating another Rectangle
    rectanglesExisting++;
    rectanglesCreated++;
}


Rectangle::Rectangle( int xLocationValue, int yLocationValue,
                     Colour blockColourValue)
{
    // Set the values of the non-static elements of class
    // Rectangle. Some values of the elements are received
    // as values of the parameters of the constructor
    // Note that the names of the parameters are different
    // from the identifiers of the Class elements
    height    = 10;
    width    = 10;
    blockColour = blockColourValue;

	if(xLocationValue >= 0 && xLocationValue < pageWidth &&
		yLocationValue >= 0 && yLocationValue < pageLength	)
	{
		xLocation = xLocationValue;
		yLocation = yLocationValue;
	}
	else
	{
		cout << "Rectangle is off the page \n";
		cout << "x position and y position have been reset to 0\n";
		xLocation = 0;
		yLocation = 0;
	}


	if(xLocation + width > pageWidth )
	{
		cout << "Rectangle object partially off the page \n";
		cout << "width reset to include only the part of rectangle on the page \n";
		cout << "width was " << width;
		width = pageWidth - xLocation;
		cout << " width is " << width << endl;
	}
	if(yLocation + height > pageLength )
	{
		cout << "Rectangle object partially off the page \n";
		cout << "height reset to include only the part of rectangle on the page \n";
		cout << "height was " << height;
		height = pageLength - yLocation;
		cout << " height is " << height << endl;
	}

    // Increment the counters for rectangles created and
    // rectangles in existance: You are in the process of
    // creating another Rectangle
    rectanglesExisting++;
    rectanglesCreated++;
}

Rectangle::~Rectangle()
{
    //Destructor
    //Each time a rectangle is destroyed decrement the
    //number of existing rectangles
    rectanglesExisting--;
}

void Rectangle::RectanglePrint()
{
    cout << setw(20) << "Width " << setw(9) << width << endl;
    cout << setw(20) << "Height " << setw(9) << height << endl;
    cout << setw(20) << "xLocation " << setw(9) << xLocation << endl;
    cout << setw(20) << "yLocation " << setw(9) << yLocation << endl;
    cout << setw(20) << "rectanglesCreated " << setw(9) << rectanglesCreated << endl;
    cout << setw(20) << "rectanglesExisting " << setw(9) << rectanglesExisting << endl;
    cout << setw(20) << "blockColour " << setw(9) << blockColour << endl;
}

// A full Set of accessors (Get functions)
// to Get the values of each of the
// variable members of the class Rectangle
int Rectangle::GetHeight() const
{
    return(height);
}

int Rectangle::GetWidth() const
{
    return(width);
}


int Rectangle::GetXLocation() const
{
    return(xLocation);
}

int Rectangle::GetYLocation() const
{
    return(yLocation);
}

int Rectangle::GetRectanglesExisting()
{
    return(rectanglesExisting);
}

int Rectangle::GetRectanglesCreated()
{
    return(rectanglesCreated);
}

Colour Rectangle::GetBlockColour() const
{
    return(blockColour);
}


// A full Set of Set functions to Set each of the variable members
// of class Rectangle from outside of class Rectangle.
void Rectangle::SetWidth( const int widthValue)
{
    width = widthValue;
	if(xLocation + width >= pageWidth )
	{
		width = pageWidth - xLocation;
	}
}

void Rectangle::SetHeight( const int heightValue)
{
    height = heightValue;
	if(yLocation + height >= pageLength )
	{
		height = pageLength - yLocation;
	}
}

void Rectangle::SetXLocation(const int xLocationValue)
{
    xLocation = xLocationValue;
	if( xLocation >= pageWidth || xLocation < 0 )
	{
		xLocation = 0;
		yLocation = 0;
	}
	if( xLocation + width  > pageWidth )
	{
		width = pageWidth - xLocation;
	}
}

void Rectangle::SetYLocation(const int yLocationValue)
{
    yLocation = yLocationValue;
	if( yLocation >= pageLength || yLocation < 0 )
	{
		xLocation = 0;
		yLocation = 0;
	}
	if( yLocation + height > pageLength)
	{
		height = pageLength - yLocation;
	}
}

void Rectangle::SetRectangleColour(const Colour blockColourValue)
{
    blockColour = blockColourValue;
}

void Rectangle::SetRectanglesCreated(int rectanglesCreated)
{
    rectanglesCreated = rectanglesCreated;
}

void Rectangle::SetRectanglesExisting(int rectanglesExisting)
{
    rectanglesExisting = rectanglesExisting;
}

// member fuctions to test relations between rectangles
bool Rectangle::DoesOverlay(const Rectangle& rectangle2)
{
    // Check to see if rectangle 2 lies completely within rectangle1
    if( xLocation + width < rectangle2.xLocation+rectangle2.width &&
		xLocation > rectangle2.xLocation )
    {
        if( yLocation + height < rectangle2.yLocation+rectangle2.height &&
		yLocation > rectangle2.yLocation )
		{
			return true;
		}

    }
    return false;
}

bool Rectangle::DoesIntersect(const Rectangle& rectangle2)
{
    if( xLocation <= rectangle2.xLocation+rectangle2.width &&
        xLocation + width >= rectangle2.xLocation &&
        yLocation <= rectangle2.yLocation+rectangle2.height &&
        yLocation + height >= rectangle2.yLocation)
    {
        return true;
    }
    return false;
}

void Rectangle::RectangleDisplay(BMP& myImageValue, string theOutputFile)
{
    int i;
    int j;

    if(yLocation < 0|| yLocation >= pageLength ||
        yLocation + height > pageLength)
    {
        cerr << "point may be located outside of plotting page\n"
            << endl;
        return;
    }

    if(xLocation < 0 || xLocation >= pageWidth ||
        xLocation + width  > pageWidth )
    {
        cerr << "point may be located outside of plotting page\n"
            << endl;
        return;
    }

    // each pixel within the rectangle must be Set to the correct colour
    // myImageValue(i,j) is pixel j in row i
    // each value in the Colour object is Set for each pixel in
    // the Rectangle
    for(j=yLocation; j<(yLocation+height); j++)
    {
        for (i=xLocation; i<(xLocation+width); i++)
        {
            myImageValue(i,j)->Red = blockColour.GetRedNumber();
            myImageValue(i,j)->Blue = blockColour.GetBlueNumber();
            myImageValue(i,j)->Green = blockColour.GetGreenNumber();
            myImageValue(i,j)->Alpha = blockColour.GetAlphaNumber();
        }
    }

    //write generated bitmap image to a file
    myImageValue.WriteToFile(theOutputFile.c_str());

}


const Rectangle& Rectangle::operator=(const Rectangle &Rectangle2)
{
    width       = Rectangle2.width;
    height      = Rectangle2.height;
	xLocation   = Rectangle2.xLocation;
	yLocation   = Rectangle2.yLocation;
	blockColour = Rectangle2.blockColour;

	return *this;
}

//note: to make this operator work you must
//also add an == operator to Colour so that
// the last comparison is defined
bool Rectangle::operator ==(const Rectangle& Rectangle2) const
{
    if ( width		 == Rectangle2.width  &&
		 height		 == Rectangle2.height &&
		 xLocation   == Rectangle2.xLocation &&
		 yLocation   == Rectangle2.yLocation &&
		 blockColour == Rectangle2.blockColour)
	{
		return true;
	}
	else
	{
		return false;
	}
}


// Overloaded output operator
// Prints a description of each Rectangle class element and its value
// The value returned is the value of the output stream being printed to
ostream& operator << (ostream& os, const Rectangle& myRectangle)
{

    os << setw(20) << "Width " << setw(9) << myRectangle.width << endl;
    os << setw(20) << "Height " << setw(9) << myRectangle.height << endl;
    os << setw(20) << "xLocation " << setw(9) << myRectangle.xLocation << endl;
    os << setw(20) << "yLocation " << setw(9) << myRectangle.yLocation << endl;
    os << setw(20) << "rectanglesCreated " << setw(9) << myRectangle.rectanglesCreated << endl;
    os << setw(20) << "rectanglesExisting " << setw(9) << myRectangle.rectanglesExisting << endl;
    os << setw(20) << "blockColour" << setw(9) << myRectangle.blockColour << endl;
    return os;
}

void Rectangle::RectangleDivide(Rectangle* RectList)
{
    int xHalf = 0;
    int yHalf = 0;
    xHalf = width / 2;
    yHalf = height / 2;
    // constant below is  = sqrt(3.0)/4 * sidelength
    RectList[1] = Rectangle(xLocation + xHalf, yLocation + yHalf, xHalf, yHalf, blockColour);
    RectList[0] = Rectangle(xLocation, yLocation, xHalf, yHalf, blockColour);
}
