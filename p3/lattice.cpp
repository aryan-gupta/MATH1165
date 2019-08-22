
#include <iostream>
#include <vector>
#include <utility>
#include <tuple>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

using ull = unsigned long long;

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
			map[ii][jj] = left + top;

			// std::cout << "(" << ii << ", " << jj << ")" << "   ";
			// std::cout << left << ' ' << top << ' ';
			// std::cout << map[ii][jj] << std::endl;
		}
	}

	return map[n - 1][n - 1];
}

int main(int ac, char **av) {
	cout << "Enter dimensions:: ";
	int n;
	cin >> n;

	ull num = calculate_lattice_paths(n);

	cout << num << endl;
}