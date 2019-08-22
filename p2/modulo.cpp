
#include <iostream>

int calc_inverse_modulo(int n, int a) {
	for (int ii = 1; ii < n; ++ii) {
		if ((ii * a) % n == 1) {
			return ii;
		}
	}
	return -1;
}


int main(int ac, char **av) {
	std::cout << "Enter modulo:: ";
	int n;
	std::cin >> n;

	std::cout << "Enter a:: ";
	int a;
	std::cin >> a;

	int b = calc_inverse_modulo(n, a);
	
	if (b == -1) {
		std::cout << "Inverse not found" << std::endl;
	} else {
		std::cout << "Inverse is: ";
		std::cout << b << std::endl;
	}
	
	return 0;
}