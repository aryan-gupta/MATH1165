

#include <iostream>

int main() {
	std::cout << (sizeof(long double) * 8) << std::endl;
	std::cout << (sizeof(double) * 8) << std::endl;
	std::cout << (sizeof(float) * 8) << std::endl;
	std::cout << "---" << std::endl;
	std::cout << (sizeof(uintmax_t) * 8) << std::endl;

}