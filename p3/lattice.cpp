
#include <iostream>
#include <vector>
#include <utility>
#include <tuple>
#include <limits>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

#ifdef USE_FLOAT
using ull = long double;
constexpr ull MAX = std::numeric_limits<ull>::max();
#else
using ull = uintmax_t;
constexpr ull MAX = UINTMAX_MAX;
#endif

ull get_map_element(vector<vector<ull>> &map, size_t x, size_t y) {
	if (y < x) { // The top triangle is the same as the bottom one
		std::swap(x, y);
	}

	if (x == 0 or y == 0) {
		return 1;
	}

	return map[y][x];
}

ull calculate_lattice_paths(size_t n) {
	++n;
	vector<vector<ull>> map{ n, vector<ull>(n) }; // n x n array
	for (size_t ii = 1; ii < n; ++ii) {
		for (size_t jj = 1; jj <= ii; ++jj) {
			ull left = get_map_element(map, jj - 1, ii);
			ull top = get_map_element(map, jj, ii - 1);
			if ((left > 0) && (top > MAX - left)) {
				cout << "Overflow error" << endl;
				return 0;
			}
			map[ii][jj] = left + top;

			// std::cout << "(" << ii << ", " << jj << ")" << "   ";
			// std::cout << left << ' ' << top << ' ';
			// std::cout << map[ii][jj] << std::endl;
		}
	}

	return map[n - 1][n - 1];
}

int main(int ac, char **av) {
#ifdef USE_FLOAT
	cout << "Using floating point. Max dim is 8195. Compile with g++ <file> to use uintmax_t\n";
#else
	cout << "Max dim is 33. If larger dim (up to 8195) is needed compile with g++ -DUSE_FLOAT <file>\n";
#endif
	cout << "Enter dimensions:: ";
	int n;
	cin >> n;

	ull num = calculate_lattice_paths(n);

	cout << std::fixed << num << endl;
}