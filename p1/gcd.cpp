
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
	if (a == 0 and b == 0) { // a nor b
		return { 0, false };
	} else if (a == 0) {
		return { b, true };
	} else if (b == 0) {
		return { a, true };
	}

	// gcd of 5, 5 is 5
	if (a == b) {
		return { a, true };
	}

	// get the difference between the numbers (positive difference)
	// and reperform eucl algo. This is a bit complecated shorthand
	// for the non-structural binding version.
	// python equvilant: na, nb = (a, b - a) if (a < b) else (b, a - b) 
#ifdef __cpp_structured_bindings
	auto [na, nb] = (a < b) ? mp(a, b - a) : mp(b, a - b);
#else
	int na, nb;
	if (a < b) {
		na = a;
		nb = b - a;
	} else {
		na = b;
		nb = a - b;
	}
#endif
	return perform_euclidean_algo(na, nb);
}

int main(int ac, char **av) {
	std::cout << "Enter Number 1::";
	int num1; 
	std::cin >> num1;
	std::cout << "Enter Number 2::";
	int num2;
	std::cin >> num2;

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