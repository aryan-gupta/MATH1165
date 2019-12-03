

#include <iostream>
#include <tuple>
#include <cmath>
#include <complex>
#include <string>

using num_t = std::complex<float>;

std::pair<num_t, num_t> get_factors(num_t a, num_t b, num_t c) {
	num_t is = std::pow(b, 2) - (num_t{ 4 } * a * c);
	num_t s = std::sqrt(is);
	num_t r1 = (-b + s) / (num_t{ 2 } * a);
	num_t r2 = (-b - s) / (num_t{ 2 } * a);
	return { r1, r2 };
}

std::pair<num_t, num_t> get_closed_form_coeff(num_t c1, num_t c2, num_t a0, num_t a1) {
	if (c1 == c2) {
		num_t u = a0;
		num_t v = (a1 - u * c1) / c1;

		return { u, v };
	} else {
		num_t u = (c2 * a0 - a1) / (c2 - c1);
		num_t v = a0 - u;

		return { u, v };
	}
}

// https://stackoverflow.com/questions/16605967
template <typename T>
std::string to_string_with_precision(const T a_value, const int n = 6)
{
	std::ostringstream out;
	out.precision(n);
	out << a_value;
	return out.str();
}

template<typename T>
std::string str(T var) {
	int prec = 3;

	std::string ans{  };
	if (var.real() != 0) {
		ans += to_string_with_precision( var.real(), prec );
	}

	if (var.imag() != 0) {
		if (var.imag() < 0) {
			ans += "-";
		} else if (var.real() != 0) {
			ans += "+";
		}
		ans += to_string_with_precision( std::abs(var.imag()), prec ) + "i";
	}
	return ans;
}

int main() {
	float c, d, a0, a1;

	std::cout << "What is c: ";
	std::cin >> c;

	std::cout << "What is d: ";
	std::cin >> d;

	std::cout << "What is a0: ";
	std::cin >> a0;

	std::cout << "What is a1: ";
	std::cin >> a1;

	num_t r1, r2;
	std::tie(r1, r2) = get_factors(1, -c, -d);

	num_t u, v;
	std::tie(u, v) = get_closed_form_coeff(r1, r2, a0, a1);

	std::cout << "The closed form is: a_n = ("
	          << str(u) << ") * (" << str(r1) << ")^n + (" << str(v) << ((r1 == r2)? ") * n " : ") ") << "* (" << str(r2) << ")^n" << std::endl;

	return 0;
}