#include "numbers.hpp"
#include <iostream>
#include <vector>
#include "include.hpp"

void deli(int i) {
#include "instantiate.hpp"
#include "rbti.hpp"
	std::cout << "+---------------------------------------------------------------------+" << std::endl;
	std::cout << "|                             Basic Setup                             |" << std::endl;
	std::cout << "+---------------------------------------------------------------------+" << std::endl;
	std::vector<int> nums = {40, 20, 60, 10};
	insertSet(nums);
	std::cout << "Delete " << i << std::endl;
	numeric.del(i);
	numeric.printTree();
}

void basicTest() {
	deli(40);
	deli(60);
	deli(20);
	deli(10);
}

void doubleBlack() {
#include "instantiate.hpp"
#include "rbti.hpp"
	std::cout << "+----------------------------------------------------------------------+" << std::endl;
	std::cout << "|                             Double Black                             |" << std::endl;
	std::cout << "+----------------------------------------------------------------------+" << std::endl;
	std::vector<int> nums = {40, 60, 10, 5, 20, 30, 4, 7, 2, 15, 14}; //{40, 20, 60, 10};
	insertSet(nums);
	numeric.del(7);
}

void recurseRed() {
#include "instantiate.hpp"
#include "rbti.hpp"
	std::cout << "+----------------------------------------------------------------------+" << std::endl;
	std::cout << "|                             Double Black                             |" << std::endl;
	std::cout << "+----------------------------------------------------------------------+" << std::endl;
	std::vector<int> nums = {40, 60, 10, 5, 20, 30, 4, 7, 2, 15, 14}; //{40, 20, 60, 10};
	insertSet(nums);
	numeric.del(60);
}

int main(int argc, char** argv) {
	int i = atoi(argv[1]);
	switch(i) {
	case 1:
		basicTest();
		break;
	case 2:
		doubleBlack();
		break;
	case 3:
		recurseRed();
		break;
	}
}
