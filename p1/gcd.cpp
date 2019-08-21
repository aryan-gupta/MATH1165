
#include <iostream>
#include <utility>
#include <tuple>

// kms... https://stackoverflow.com/questions/19572512
template <typename T1, typename T2>
std::pair<T1, T2> mp(T1&& a, T2&& b) {
	return { a, b };
}

std::pair<int, bool> perform_euclidean_algo(int a, int b) {
	// Check for the 0 cases
	if (a == 0 and b == 0) {
		return { 0, false };
	} else if (a == 0) {
		return { b, true };
	} else if (b == 0) {
		return { a, true };
	}

	if (a == b) { // gcd of 5, 5 is 5
		return { a, true };
	}

	// get the difference between the numbers (positive difference)
	// and reperform eucl algo
	auto [na, nb] = (a < b) ? mp(a, b - a) : mp(b, a - b);
	return perform_euclidean_algo(na, nb);
}

int main(int ac, char **av) {
	std::cout << "Enter Number 1" << std::endl;
	int num1, num2; 
	std::cin >> num1 >> num2;

#ifdef __cpp_structured_bindings
	auto [gcd, valid] = ::perform_euclidean_algo(num1, num2);
#else
	int gcd; bool valid;
	std::tie(gcd, valid) = ::perform_euclidean_algo(num1, num2);
#endif
	if (valid) {
		std::cout << "GCD:: " << gcd << std::endl;
	} else {
		std::cout << "No GCD found" << std::endl;
	}

	return 0;
}