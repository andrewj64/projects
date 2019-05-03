#include "numbers.hpp"
#include <iostream>
#include <vector>
#include "include.hpp"

int main() {
#include "instantiate.hpp"
#include "rbti.hpp"
	insertN(20, [](int i) { return 60 + i; });
	insertN(20, [](int i) { return 19 + i; });
	insertN(20, [](int i) { return 59 - i; });
	insertN(20, [](int i) { return 20 + i; });
}
