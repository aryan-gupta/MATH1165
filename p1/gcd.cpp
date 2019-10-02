
#include <iostream>
#include <utility>
#include <tuple>
#include <cmath>
#include <assert.h>

namespace detail {

/// Conducts the division algorithm.
/// @param num The numerator
/// @param den The denominator
/// @return The quotient
/// @return The remainder
std::pair<int, int> division_algo(int num, int den) {
	assert(den > 0);
	int quot = num / den; // will auto round down
	int rem = num - den * quot;
	return { quot, rem };
}



/// Conducts the euclidean algorithm
/// @param a The larger number of which to find the gcd for
/// @param b The smaller number of which to find the gcd for
/// @return The gcd
/// @return The linear combination for a
/// @return The linear combination for b
std::tuple<int, int, int> perform_euclidean_algo(int a, int b) {
	// Do division algo: a = b * quot + rem
#ifdef __cpp_structured_bindings
	auto [quot, rem] = detail::division_algo(a, b);
#else
	int quot, rem;
	std::tie(quot, rem) = detail::division_algo(a, b);
#endif

	std::cout << a << " = " << b << " * " << quot << " + " << rem << std::endl;

	// If we found the gcd
	if (rem == 0) {
		return { b, 0, quot };
	}

	// If not then recurse in the euclidean algo
#ifdef __cpp_structured_bindings
	auto [gcd, u, v] = perform_euclidean_algo(b, rem);
#else
	int gcd, u, v;
	std::tie(gcd, u, v) = perform_euclidean_algo(b, rem);
#endif

	// if (u == 0 and v == 0) {
	// 	return { gcd, 1, quot };
	// }

	// Do backwards substitution
	int new_v = v * quot + u;
	u = v;
	v = new_v;

	// std::cout << a << " (" << u << ") - (" << b << ") " << v << std::endl;

	return { gcd, u, v };
}

} // end namespace detail




/// Calculates the GCD of 2 numbers
/// @param a The first number
/// @param b The second number
/// @return The gcd
/// @return If the GCD is valid
/// @return The linear combination for a
/// @return The linear combination for b
std::tuple<int, bool, int, int> gcd_valid_lc(int a, int b) {
	// Check for the 0 cases
	if (a == 0 and b == 0) { // a nor b
		return { 0, false, 0, 0 };
	}

	// keep copy of original signs before abs()
	int orig_a = a, orig_b = b;
	a = std::abs(a);
	b = std::abs(b);

	// swap so a is the larger number ( a = b * x + y )
	if (a < b) {
		std::swap(a, b);
	}

#ifdef __cpp_structured_bindings
	auto [gcd, u, v] = detail::perform_euclidean_algo(a, b);
#else
	int gcd, u, v;
	std::tie(gcd, u, v) = detail::perform_euclidean_algo(a, b);
#endif

	if (orig_a < 0) u *= -1;
	if (orig_b > 0) v *= -1;

	return { gcd, true, u, v };
}



int main(int ac, char **av) {
	std::cout << "Enter Number 1::";
	int num1;
	std::cin >> num1;
	std::cout << "Enter Number 2::";
	int num2;
	std::cin >> num2;

/// Im not sure if your C++ compiler has this feature. It came out in 2017 and may need
/// special flags to compile it, so I'm adding these PPD if you have a legacy compiler
/// Both sections of code do the same thing, but the first one is newer.
#ifdef __cpp_structured_bindings
	auto [gcd, valid, x, y] = ::gcd_valid_lc(num1, num2);
#else
	int gcd; bool valid; int x, y;
	std::tie(gcd, valid, x, y) = ::gcd_valid_lc(num1, num2);
#endif

	if (valid) {
		std::cout << "GCD:: " << gcd << std::endl;
		std::cout << "Bezout's Identity:: " << x << "*" << num1 << " + " << y<< "*" << num2 << " = " << gcd << std::endl;
	} else {
		std::cout << "No GCD found" << std::endl;
	}

	return 0;
}