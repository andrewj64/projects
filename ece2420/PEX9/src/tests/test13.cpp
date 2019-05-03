#include "numbers.hpp"
#include <iostream>
#include <vector>
#include "include.hpp"

void r1ll() {
#include "instantiate.hpp"
#include "rbti.hpp"
	std::cout << "+----------------------------------------------------------------------+" << std::endl;
	std::cout << "|                             Recurse-1 LL                             |" << std::endl;
	std::cout << "+----------------------------------------------------------------------+" << std::endl;
	std::vector<int> nums = {40, 60, 10, 5, 20, 30, 4, 7, 2};
	insertSet(nums);
}

void r1lr() {
#include "instantiate.hpp"
#include "rbti.hpp"
	std::cout << "+----------------------------------------------------------------------+" << std::endl;
	std::cout << "|                             Recurse-1 LR                             |" << std::endl;
	std::cout << "+----------------------------------------------------------------------+" << std::endl;
	std::vector<int> nums = {40, 60, 10, 5, 20, 30, 15, 35};
	insertSet(nums);
}

void r1rl() {
#include "instantiate.hpp"
#include "rbti.hpp"
	std::cout << "+----------------------------------------------------------------------+" << std::endl;
	std::cout << "|                             Recurse-1 RL                             |" << std::endl;
	std::cout << "+----------------------------------------------------------------------+" << std::endl;
	std::vector<int> nums = {40, 20, 70, 75, 60, 50, 65, 45};
	insertSet(nums);
}

void r1rr() {
#include "instantiate.hpp"
#include "rbti.hpp"
	std::cout << "+----------------------------------------------------------------------+" << std::endl;
	std::cout << "|                             Recurse-1 RR                             |" << std::endl;
	std::cout << "+----------------------------------------------------------------------+" << std::endl;
	std::vector<int> nums = {40, 20, 70, 75, 60, 50, 74, 76, 77};
	insertSet(nums);

}

int main() {
	r1ll();
	r1lr();
	r1rl();
	r1rr();
}
