
#include <iostream>
#include <utility>
#include <tuple>
#include <cmath>
#include <assert.h>

// kms... https://stackoverflow.com/questions/19572512
template <typename T1, typename T2>
std::pair<T1, T2> mp(T1&& a, T2&& b) {
	return { a, b };
}

std::pair<int, int> division_algo(int num, int den) {
	assert(den > 0);
	int quot = num / den; // will auto round down
	int rem = num - den * quot;
	return { quot, rem };
}

std::tuple<int, bool, int, int> perform_euclidean_algo(int a, int b) {
	// Check for the 0 cases
	if (a == 0 and b == 0) { // a nor b
		return { 0, false, 0, 0 };
	}

	// Do division algo: a = b * quot + rem
#ifdef __cpp_structured_bindings
	auto [quot, rem] = ::division_algo(a, b);
#else
	int quot, rem;
	std::tie(quot, rem) = ::division_algo(a, b);
#endif

	std::cout << a << " = " << b << " * " << quot << " + " << rem << std::endl;

	// if we found the gcd then return true
	if (rem == 0) {
		return { b, true, 0, 0 };
	}

#ifdef __cpp_structured_bindings
	auto [gcd, found, u, v] = perform_euclidean_algo(b, rem);
#else
	int gcd, u, v;
	bool found;
	std::tie(gcd, found, u, v) = perform_euclidean_algo(b, rem);
#endif

	assert(found == true); // for debugging

	if (u == 0 and v == 0) {
		return { gcd, found, 1, 1 };
	}

	int new_v = v * quot + u;
	u = v;
	v = new_v;

	return { gcd, true, u, v };
}

int main(int ac, char **av) {
	std::cout << "Enter Number 1::";
	int num1;
	std::cin >> num1;
	std::cout << "Enter Number 2::" << std::endl;
	int num2;
	std::cin >> num2;

	if (num1 < num2) {
		std::swap(num2, num1);
	}

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