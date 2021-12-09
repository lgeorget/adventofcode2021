#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

struct Grid {
	int columns = 0;
	int rows = 0;
	std::vector<int> height;

	bool localMinimum(int i) {
		int x = i % columns;
		int y = i / columns;
		int v = height[i];

		if (x > 0) {
			if (height[i - 1] <= v)
				return false;
		}
		if (y > 0) {
			if (height[i - columns] <= v)
				return false;
		}
		if (x < columns - 1) {
			if (height[i + 1] <= v)
				return false;
		}
		if (y < rows - 1) {
			if (height[i + columns] <= v)
				return false;
		}
		return true;
	}
};

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

	long total = 0;
	for (int i = 0 ; i < g.height.size() ; i++) {
		if (g.localMinimum(i)) {
			std::cout << "Point " << i
				<< " (" << (i % g.columns) << "," << (i / g.columns) << ") "
				<< " with value " << g.height[i] << " is a local minimum\n";
			total += g.height[i] + 1;
		}
	}

	std::cout << total << std::endl;
}

