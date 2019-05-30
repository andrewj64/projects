#include<iostream>

/******************************************
* RGB class 
* members: R, G, B variables; color function
********************************************/

using namespace std;

class RGB
{
public:
	unsigned char R, G, B;

	void color(int i, unsigned int rnd);
	//void plot(ofstream output);
};

void RGB::color(int i, unsigned int rnd)		// Set color values
{
	
	
	switch (rnd)			// Color Schemes	
	{						// Yes I know it's supposed to be 3, but I had fun mmk?
		case 1:				// cool pink and green to black
			R = i % 256;
			G = R*R % 256;
			B = i / 4;
			break;
		case 2:				// Willy Wonka
			R = i*i % 256;
			G = R*R % 256;
			B = R*G % 256;
			break;
		case 3:				// Electric blue
			R = i % 256;
			G = R*R % 256;
			B =  G * 14 % 256;
			break;
		case 4:				// eighties
			R = i*i*i % 256;
			G = R*17 % 256;
			B =  G * G % 256;
			break;
		case 5:				// blue fire beetle (favorite)
			R = 1000 - i % 256;
			G = R*R % 256;
			B =  i * 4 % 256;
			break;
		case 6:				// black and white
			R = ~i;
			G = ~i;
			B = ~i;
			break;
		default:			// white and black
			//well poop
			R = i;
			G = i;
			B = i;
			cout << "Ya done messed up A Aron." << endl;
			
			break;
	}
	
}

