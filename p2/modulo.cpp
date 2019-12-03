
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
	int quot = std::floor(num / (float)den); // will round toward -inf
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
	auto [quot, rem] = division_algo(a, b);
#else
	int quot, rem;
	std::tie(quot, rem) = division_algo(a, b);
#endif

	// If we found the gcd
	if (rem == 0) {
		return { b, 0, 1 };
	}

	// If not then recurse in the euclidean algo
#ifdef __cpp_structured_bindings
	auto [gcd, u, v] = perform_euclidean_algo(b, rem);
#else
	int gcd, u, v;
	std::tie(gcd, u, v) = perform_euclidean_algo(b, rem);
#endif

	// Do backwards substitution
	int new_v = v * quot + u;

	return { gcd, v, new_v };
}

} // end namespace detail


/// Normalizes a number into the mod space.
/// EX. normalizing 8 mod 5 will be 3 mod 5 because
///     8 mod 5 === 3 mod 5 and 3 < 5 and 3 > 0
/// @param num The number to normalize
/// @param mod The modulus to normalize under
/// @retern The base congruence class of \p num
int normalize(int num, int mod) {
#ifdef __cpp_structured_bindings
	auto [quot, rem] = detail::division_algo(num, mod);
#else
	int quot, rem;
	std::tie(quot, rem) = detail::division_algo(num, mod);
#endif
	return rem;
}


/// Calculates the GCD of 2 numbers
/// @param a The first number
/// @param b The second number
/// @return The gcd
/// @return If the GCD is valid
/// @return The linear combination for a
/// @return The linear combination for b
std::tuple<int, bool, int, int> gcd_valid_lc(int a, int b) {
	using namespace detail;

	// Check for the 0 cases
	if (a == 0 and b == 0) { // a nor b
		return { 0, false, 0, 0 };
	}

	if (a == 0) {
		int gcd = std::abs(b);
		int lc = (b < 0) ? -1 : 1;
		return { gcd, true, 0, lc };
	}

	if (b == 0) {
		int gcd = std::abs(a);
		int lc = (a < 0) ? -1 : 1;
		return { gcd, true, lc, 0 };
	}

	// keep copy of original signs before abs()
	int orig_a = a, orig_b = b;
	a = std::abs(a);
	b = std::abs(b);

	// swap so a is the larger number ( a = b * x + y )
	bool swapped = false;
	if (a < b) {
		std::swap(a, b);
		swapped = true;
	}

#ifdef __cpp_structured_bindings
	auto [gcd, u, v] = perform_euclidean_algo(a, b);
#else
	int gcd, u, v;
	std::tie(gcd, u, v) = perform_euclidean_algo(a, b);
#endif

	// swap our u and v if we swapped out a and b
	if (swapped) {
		std::swap(u, v);
	}

	// fix for sign issues
	if (orig_a < 0) u = -u;
	if (orig_b < 0) v = -v;

	if (orig_a * u > orig_b * v) v = -v;
	else u = -u;

	assert(gcd == (orig_a * u + orig_b * v));

	return { gcd, true, u, v };
}



int main(int ac, char **av) {
	int num = 0, mod = 0;
	if (ac == 3) {
		num = std::atoi(av[1]);
		mod = std::atoi(av[2]);
	} else {
		std::cout << "Enter The Number:: ";
		std::cin >> num;
		std::cout << "Enter The Mod:: ";
		std::cin >> mod;
	}

	// If our num is not valid in mod space then normalize it (find congruence class)
	// Also save a copy so we can print it to the screen later
	int orig_num = num;
	if (num >= mod or num < 0) {
		num = normalize(num, mod);
	}

/// Im not sure if your C++ compiler has this feature. It came out in 2017 and may need
/// special flags to compile it, so I'm adding these PPD if you have a legacy compiler
/// Both sections of code do the same thing, but the first one is newer.
#ifdef __cpp_structured_bindings
	auto [gcd, valid, x, y] = gcd_valid_lc(num, mod);
#else
	int gcd; bool valid; int x, y;
	std::tie(gcd, valid, x, y) = gcd_valid_lc(num, mod);
#endif

	if (valid and gcd == 1) {
		// Normalize the inverse if its out of our mod space
		if (x >= mod or x < 0) {
			x = normalize(x, mod);
		}

		// Please ignore this next part as I only did to check if my program
		// was giving the correct results.

		// excuse me as I give every programmer an aneurysm
		// The lambda function compares if the fractional part of 2 floats
		// is he same. In this case it makes sure that if we multiply our
		// number and the inverse then the fractional part is 1/mod. In other
		// words its converting the number ( x * num / mod) in to a proper
		// fraction and making sure its X + 1/mod.
		// EX. 5 (mod 7) inverse is 3 (mod 7)
		//     operand 1: 5 * 3 / 7 = 2.1428
		//     operand 2: 1 / 7 = 0.1428
		//     lambda strips the 2 from 2.1428 and compares 0.1428 if its the
		//            same as operand 2
		assert(
			[](float a, float b) -> bool {
				float tmp;
				a = std::modf(a, &tmp);
				return std::abs(a - b) < 0.01;
			} (
				x * num / (float)mod, // operand 1
				1.0 / mod // operand 2
			)
		);

		std::cout << "Inverse of " << orig_num << " (mod " << mod << ") is " << x << std::endl;
	} else {
		std::cout << "Inverse of " << orig_num << " (mod " << mod << ") does not exist" << std::endl;
	}

	return 0;
}