#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <deque>

struct Grid {
	int columns = 0;
	int rows = 0;
	std::vector<int> height;
	std::vector<int> basin;
	int basinCounter = 1;

	long findBasinExtent(int point) {
		basinCounter++;
		std::deque<int> bfv = {point};
		long total = 0;
		while (!bfv.empty()) {
			int i = bfv.back();
			bfv.pop_back();

			if (height[i] == 9 || basin[i] != 0)
				continue;

			total++;
			basin[i] = basinCounter;
			int x = i % columns;
			int y = i / columns;

			if (x > 0 && height[i - 1] != 9 && basin[i - 1] == 0) {
				bfv.push_back(i - 1);
			}
			if (y > 0 && height[i - columns] != 9 && basin[i - columns] == 0) {
				bfv.push_back(i - columns);
			}
			if (x < columns - 1 && height[i + 1] != 9 && basin[i + 1] == 0) {
				bfv.push_back(i + 1);
			}
			if (y < rows - 1 && height[i + columns] != 9 && basin[i + columns] == 0) {
				bfv.push_back(i + columns);
			}
		}
		return total;
	}
};

std::ostream& operator<<(std::ostream& os, const Grid& g)
{
	std::cout << "size: " << (g.rows * g.columns) << std::endl;
	for (int r=0 ; r<g.rows ; r++) {
		for (int c=0 ; c<g.columns ; c++) {
			int i = r * g.columns + c;
			if (g.height[i] == 9)
				os << '+';
			else
				os << g.basin[i]; // alignment is off if number of basins > 9
		}
		os << "\n";
	}
	os << "\n";
	return os;
}

int main()
{
	Grid g;
	std::string line;
	std::getline(std::cin, line);
	g.columns = line.size();

	while (std::cin) {
		std::transform(line.begin(), line.end(), std::back_inserter(g.height),
				[](char c) { return c - '0'; });
		g.rows++;
		std::getline(std::cin, line);
	}
	g.basin.resize(g.height.size(), 0);

	std::vector<long> basinSizes;
	for (int i = 0 ; i < g.height.size() ; i++) {
		if (g.height[i] != 9 && g.basin[i] == 0) {
			// new basin
			basinSizes.push_back(g.findBasinExtent(i));
		}
	}

	long total = 1;
	std::make_heap(basinSizes.begin(), basinSizes.end());
	for (int i = 0 ; i < 3 ; i++) {
		std::pop_heap(basinSizes.begin(), basinSizes.end());
		total *= basinSizes.back();
		basinSizes.pop_back();
	}

	std::cout << total << std::endl;
}

