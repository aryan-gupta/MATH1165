
#include <iostream>
#include <utility>
#include <tuple>
#include <cmath>

// kms... https://stackoverflow.com/questions/19572512
template <typename T1, typename T2>
std::pair<T1, T2> mp(T1&& a, T2&& b) {
	return { a, b };
}

std::tuple<int, bool, int, int> perform_euclidean_algo(int a, int b) {
	// Check for the 0 cases
	if (a == 0 and b == 0) { // a nor b
		return { 0, false, 0, 0 };
	}

	int x = 0, o_x = 1,
	    y = 1, o_y = 0,
	    r = b, o_r = a;
	
	while (r != 0) {
		int q = std::floor(o_r / r);
		std::tie(o_r, r) = mp(r, o_r % r);
		std::tie(o_x, x) = mp(x, o_x - q * x);
		std::tie(o_y, y) = mp(y, o_y - q * y);
	}

	x = o_x % (b / o_r);
	y = o_y % (-a / o_r);
	return { o_r, true, x, y };
}

int main(int ac, char **av) {
	std::cout << "Enter Number 1::";
	int num1; 
	std::cin >> num1;
	std::cout << "Enter Number 2::";
	int num2;
	std::cin >> num2;

#ifdef __cpp_structured_bindings
	auto [gcd, valid, x, y] = ::perform_euclidean_algo(num1, num2);
#else
	int gcd; bool valid; int x, y;
	std::tie(gcd, valid, x, y) = ::perform_euclidean_algo(num1, num2);
#endif
	if (valid) {
		std::cout << "GCD:: " << gcd << std::endl;
		std::cout << "Bezout's Identity:: " << x << "*" << num1 << " + " << y<< "*" << num2 << " = " << gcd << std::endl;
	} else {
		std::cout << "No GCD found" << std::endl;
	}

	return 0;
}