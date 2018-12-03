#include"bmp.h"

using namespace std;

/*******************************************************************
* Function title: main
********************************************************************
* Pseudocode
* Begin
*	Generate random number between 1 and 5
*	Open bmp file
*	If file fails to open
*		Exit
*	EndIf
*	Write bmp and dib headers to file
*	Loop through each pixel
*		Determine if pixel at x, y is in the Mandelbrot set
*		Set Colors
*		Write colors to file
*	EndLoop
* End
********************************************************************/

int main()
{
	array<unsigned char, 14> bmp_header = {
		0x42, 0x4D, 				//BM
		0x76, 0xF3, 0x89, 0x06,		// Size of BMP file
		0x00, 0x00,
		0x00, 0x00,
		0x36, 0x00, 0x00, 0x00 
	};

	array<unsigned char, 40> dib_header = {
		0x28, 0x00, 0x00, 0x00, 	//40
		0x40, 0x1F, 0x00, 0x00,		//width 8000
		0xDB, 0x11, 0x00, 0x00,		//height
		0x01, 0x00,					// 
		0x18, 0x00,
		0x00, 0x00, 0x00, 0x00,
		0x10, 0x00, 0x00, 0x00,		// raw bitmap data
		0x13, 0x0B, 0x00, 0x00,
		0x13, 0x0B, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00
	};
	
	ofstream output;
	double x0, y0, x, y, xtemp;
	int iter, max_iter, i, j;
	RGB a;					// RGB class
	//unsigned char color;
	iter = 0;
	max_iter = 1000;
	
	unsigned int seed, rnd;
	
	seed = chrono::system_clock::now().time_since_epoch().count();			// Generate random number between 1 and 5
	default_random_engine generator(seed);
	uniform_int_distribution<int> distribution(1,5);
	rnd = distribution(generator);
	
	cout << "Generating mandelbrot_" << rnd << ".bmp" << endl;
	cout << "Here's a walrus while you wait." << endl;
	walrus();
	
	
	output.open("mandelbrot_x.bmp", ios::out | ios::binary);				// Open bmp file
	if(!output.good())														// If fails to open
	{
		cout << "OOOOOOPs file could not be opened." << endl;				// 	Exit
		return 1;
	}
	
	for(auto it = bmp_header.begin(); it != bmp_header.end(); it++)			// Write bmp and dib headers to file
		output << *it;
	
	for(auto it = dib_header.begin(); it != dib_header.end(); it++)
		output << *it;
	
	for(j = 0; j < 4571; j++)											// Loop through each pixel
	{
		for(i = 0; i < 8000; i++)
		{
			x0 = ((i*3.5)/7999.0) - 2.5;		// scaled x coord
			y0 = ((j*2.0)/4570.0) - 1.0;		// scaled y coord
			x = 0.0;
			y = 0.0;
			iter = 0;
			for(iter = 0; x*x + y*y < 4.0 && iter < max_iter; iter++)	//	Compute if pixel at (x, y) is in Mandelbrot set
			{
				xtemp = x*x - y*y + x0;		
				y = 2*x*y + y0;
				x = xtemp;
			}
			a.color(iter, rnd);											// 	Set colors
			output << a.B << a.G << a.R;								//	Write colors to file
		}
	}
	
	return 0;
}