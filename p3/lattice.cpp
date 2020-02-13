
#include <iostream>
#include <vector>
#include <utility>
#include <tuple>
#include <limits>
#include <array>
#include <iomanip>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

// https://stackoverflow.com/questions/18531782
#ifdef __SIZEOF_INT128__
using ull = __uint128_t;
// https://stackoverflow.com/questions/31461318/
// constexpr ull MAX = (__uint128_t)340'282'366'920'938'463'463'374'607'431'768'211'455;
constexpr ull MAX = ((__uint128_t)340'282'366'920'938 * 1'000'000'000'000 + 463'463'374'607) * 1'000'000'000'000 + 431'768'211'455;
#else
using ull = uint64_t;
constexpr ull MAX = UINT64_MAX;
#endif

// https://stackoverflow.com/questions/11656241/
int print_ull(ull n) {
  if (n == 0)  return printf("0\n");

  char str[40] = {0}; // log10(1 << 128) + '\0'
  char *s = str + sizeof(str) - 1; // start at the end
  while (n != 0) {
    if (s == str) return -1; // never happens

    *--s = "0123456789"[n % 10]; // save last digit
    n /= 10;                     // drop it
  }
  return printf("%s\n", s);
}

ull half_factorize(ull num) {
	ull ans = 1;
	for (ull i = num; i > (num / 2); --i) {
		if (ans * i <= ans) {
			std::cerr << "Would overflow, exiting..." << std::endl;
			std::exit(-1);
		}
		ans *= i;
	}

	return ans;
}

constexpr int FACTOR_MAX = 21;
ull factorize(ull num) {
	// https://www.mymathtables.com/numbers/100-factorial-tables-chart.html
	static constexpr std::array<ull, FACTOR_MAX> FACTORS = {
		0, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800, 39916800, // 0..11
		479001600, 6227020800, 87178291200, 1307674368000, 20922789888000, // 12..16
		355687428096000, 6402373705728000, 121645100408832000, 2432902008176640000, // 17..20
	};

	if (num < FACTOR_MAX) {
		return FACTORS[num];
	} else {
		ull fac = FACTORS[FACTOR_MAX - 1];
		for (int i = FACTOR_MAX; i <= num; ++i) {
			if (fac * i <= fac) {
				std::cerr << "Would overflow, exiting..." << std::endl;
				std::exit(-1);
			}
			fac *= i;
		}
		return fac;
	}
}

ull calculate_lattice_paths(ull n) {
	ull num = half_factorize(2 * n);
	ull den = factorize(n);

	return num / den;
}

int main(int ac, char **av) {
	cout << "Using " << (sizeof(ull) * 8) << "-bit unsigned integers.\nMax dim is 24 (tested with 128-bit unsigned integers).\n";
	cout << "Enter dimensions:: ";
	int n;
	cin >> n;

	if (n >= 25) {
		std::cout << "Too high of a value, would overflow. exiting...\n";
		std::exit(-1);
	}

	ull num = calculate_lattice_paths(n);

	print_ull(num);
}