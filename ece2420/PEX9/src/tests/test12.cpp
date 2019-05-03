#include "numbers.hpp"
#include <iostream>
#include <vector>
#include "include.hpp"

void bll() {
#include "instantiate.hpp"
#include "rbti.hpp"
	std::cout << "+----------------------------------------------------------------------+" << std::endl;
	std::cout << "|                               Basic LL                               |" << std::endl;
	std::cout << "+----------------------------------------------------------------------+" << std::endl;
	std::vector<int> nums = {40, 20, 10};
	insertSet(nums);
}

void blr() {
#include "instantiate.hpp"
#include "rbti.hpp"
	std::cout << "+----------------------------------------------------------------------+" << std::endl;
	std::cout << "|                               Basic LR                               |" << std::endl;
	std::cout << "+----------------------------------------------------------------------+" << std::endl;
	std::vector<int> nums = {40, 20, 30};
	insertSet(nums);
}

void brl() {
#include "instantiate.hpp"
#include "rbti.hpp"
	std::cout << "+----------------------------------------------------------------------+" << std::endl;
	std::cout << "|                               Basic RL                               |" << std::endl;
	std::cout << "+----------------------------------------------------------------------+" << std::endl;
	std::vector<int> nums = {40, 60, 50};
	insertSet(nums);
}

void brr() {
#include "instantiate.hpp"
#include "rbti.hpp"
	std::cout << "+----------------------------------------------------------------------+" << std::endl;
	std::cout << "|                               Basic RR                               |" << std::endl;
	std::cout << "+----------------------------------------------------------------------+" << std::endl;
	std::vector<int> nums = {40, 60, 70};
	insertSet(nums);

}

int main() {
	bll();
	blr();
	brl();
	brr();
}
