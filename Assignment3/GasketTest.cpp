#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cmath>
#include <string>
#include "EasyBMP.h"
#include "Colour.h"
#include "Gasket.h"
#include "DisplayBackground.h"
using namespace std;
//Using Xcode

// main program to test class Rectangle
// Creates and prints a rectangle
int main()
{
    //Please note that this is the correct location for BMP myImage
    //The program will work if you make this declaration global (as indicated in lab writeup)
    //However global variables should not be used as arguments of functions
    BMP myImage;
    Colour C1(0, 0, 255, 255);     //dark blue
    Colour C2(0, 0, 0, 255);	   //black
    Colour CB(0, 255, 0, 255);     //green
    Colour C3(255,0,0,255);		   //red
    Colour C4(128,128,128,128);	   //grey
    Colour C5( 100, 200, 255, 170);//light blue
    Colour C6( 255, 0, 255, 255);  //Pink
	Colour C7( 255, 255, 0, 255 ); //Yellow
	Colour C8( 155, 155,255,255);  //Purple



    cout << "BEGIN GASKET TEST" << endl << endl;


    cout << "TESTING CONSTRUCTORS: ON AND OFF PAGE" << endl << endl;



    InitBackground(myImage, CB, 600, 800);

    cout << endl << "Gasket constructor 6 arguments, x and y location on page " << endl
        << "height and width too large, gasket would extend beyond edge of page " << endl
        << "width and height of gasket reduced to fit on page:: plotted in RED" << endl;
    cout << "create G10" << endl;
    Gasket G10(1, 400, 700, 450, 225, C3);
    G10.GasketDisplay(myImage, "GasketConstructors.bmp");
    G10.GasketPrint();
    cout << endl << endl;


    cout << "TESTING COPY CONSTRUCTOR" << endl;
    cout << "gasket to copy" << endl;
    G10.GasketPrint();
    Gasket G11(G10);
    cout << "copied gasket" << endl;
    G11.GasketPrint();
    cout << endl << endl << endl;
    cout << endl << "Constructor 6 arguments, on page:: RED" << endl;
    cout << "create g6" << endl;

    cout << endl << "Gasket constructor 6 arguments x and y locations off the page, set to 0 0 " << endl
         << "Then width too large, truncated in width to fit on page:: plotted in DARK BLUE" << endl;
	cout << "create G9" << endl;
	Gasket G9( 0, 700, 900, 700, 400, C1);
	G9.GasketDisplay(myImage, "GasketConstructors.bmp" );
	G9.GasketPrint();
    cout << endl << endl;


    cout << endl << "Gasket contructor with 6 arguments x and y locations off the page" << endl
         << "moved to location 0 0:: plotted in YELLOW" << endl;
	cout << "create G1" << endl;
    Gasket G0(1, -1, -1, 370, 330, C7);
	G0.GasketDisplay(myImage,  "GasketConstructors.bmp");
	G0.GasketPrint();
    cout << endl << endl;


    cout << endl << "Gasket constructor with 6 arguments xLocation off page, moved to 0 0:: " 
         << endl << "plotted in PURPLE" << endl;
    cout << "create G2" << endl;
    Gasket G2(1, 606, 480, 440, 250, C8);
    G2.GasketDisplay(myImage, "GasketConstructors.bmp");
    G2.GasketPrint();
    cout << endl << endl;


    cout << endl << "Gasket constructor 6 arguments, x and y location on page " << endl
         << "width too large, gasket would extend beyond edge of page " << endl
         << "width of gasket reduced to fit on page:: plotted in GREY" << endl;
	cout << "create G3" << endl;
    Gasket G3(1, 450, 330, 300, 360, C4);
    G3.GasketDisplay(myImage, "GasketConstructors.bmp");
    G3.GasketPrint();
    cout << endl << endl;


    cout << "create G0" << endl;
    cout << endl << "Default gasket constructor: BLACK" << endl;
    Gasket G1;
    G1.GasketDisplay(myImage, "GasketConstructors.bmp");
    G1.GasketPrint();
    cout << endl << endl;


    cout << endl << "Gasket constructor 6 arguments, yLocation off page:: LIGHT BLUE" << endl;
    cout << "create g7" << endl;
    Gasket G7(3, 300, 811, 165, 145, C5);
    G7.GasketDisplay(myImage, "GasketConstructors.bmp");
    G7.GasketPrint();
    cout << endl << endl;

    cout << endl << "Gasket constructor 6 arguments, x and y location on page " << endl
        << "height too large, gasket would extend beyond edge of page " << endl
        << "height of gasket reduced to fit on page:: plotted in PINK" << endl;
	cout << "create G8" << endl;
	Gasket G8( 2, 50, 600, 160, 390, C6);
	G8.GasketDisplay(myImage, "GasketConstructors.bmp" );
	G8.GasketPrint();
	cout << endl << endl;


    cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
    cout << endl << "TESTING MUTATORS" << endl;

    ResetBackground(myImage, CB, 600, 800);

    cout << endl << "changing Xlocation of G0 to 150: ";
	cout << " :displayed in GREY" << endl;
    G0.SetGasketColour(C4);
    G0.SetXLocation(150);
    G0.GasketDisplay(myImage, "GasketMutators.bmp");
    G0.GasketPrint();

    cout << endl << "changing  Xlocation of G1 so gasket is partially off the page"<< endl;
	cout << "xlocation to 520: "  << endl;
	cout << "displayed in BLACK" << endl;
    G1.SetXLocation(520);
    G1.GasketDisplay(myImage, "GasketMutators.bmp");
    G1.GasketPrint();

    cout << "moving Y location of G7 so gasket is partially off the page" << endl;
    cout << "yLocation set to 720: displayed in LIGHT BLUE" << endl;
    G7.SetIterations(1);
    G7.SetYLocation(720);
    G7.GasketDisplay(myImage, "GasketMutators.bmp");
    G7.GasketPrint();
    G7.SetGasketColour(C6);

	cout << "moving x location of G7 and increasing width to 350" << endl;
    cout << "xLocation set to 200 : displayed in LIGHT BLUE" << endl;
    G7.SetWidth(350);
    G7.SetXLocation( 200 );
    G7.SetYLocation(550);
    G7.SetHeight(220);
    G7.GasketDisplay(myImage, "GasketMutators.bmp");
    G7.GasketPrint();

    cout << "changing G2 colour from light blue: ";
    cout << "displayed in RED" << endl;
    G2.SetGasketColour(C3);
    G2.SetXLocation(80);
    G2.SetYLocation(280);
    G2.GasketDisplay(myImage, "GasketMutators.bmp");
    G2.GasketPrint();

    cout << "changing G2 number of iterations from 1 to 3: " ;
    cout << "displayed in YELLOW" << endl;
    G2.SetIterations(3);
    G2.SetGasketColour(C7);
    G2.GasketDisplay(myImage, "GasketMutators.bmp");
    G2.GasketPrint();

    cout << endl << "changing  size y location and iterations of G1"<< endl;
	cout << "location to 200: "  << endl;
	cout << "displayed in DARK BLUE" << endl;
    G1.SetXLocation(20);
    G1.SetHeight(600);
    G1.SetIterations(2);
    G1.SetGasketColour(C1);
    G1.GasketDisplay(myImage, "GasketMutators.bmp");
    G1.GasketPrint();
    
    cout << "TESTING = OPERATOR"<< endl;
    G2 = G1;
    cout << "printing G1"<< endl;
    G1.GasketPrint();
    cout << "printing G2 after G2=G1"<< endl;
    G2.GasketPrint();
    cout << endl << endl;

    cout << "TESTING THE << OPERATOR" << endl;
    cout << "G7" << endl << G7;
    cout << endl;
    
    cout << "TESTING == OPERATOR. Checking if G2==G1. Answer should be true (1) " << (G2==G1);
    cout << endl;
    cout << "TESTING == OPERATOR. Checking if G2==G7. Answer should be false (0) " << (G2==G7);
    cout << endl;

    return 0;
}


