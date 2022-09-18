#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <limits>
#include <deque>
#include <set>

struct Point {
	int c;
	int r;
};

struct Grid {
	int columns = 0;
	int rows = 0;
	std::vector<uint8_t> state; // 0: unvisited, 1: started, 2: finished
	std::vector<unsigned int> weight;
	std::vector<uint8_t> level;
	std::vector<unsigned int> started;
};

int main()
{
	Grid g;
	std::string line;
	std::getline(std::cin, line);
	g.columns = line.size() * 5;

	while (std::cin) {
		std::transform(line.begin(), line.end(), std::back_inserter(g.level),
				[](char c) { return c - '0'; });
		std::transform(line.begin(), line.end(), std::back_inserter(g.level),
				[](char c) { return (c - '0' + 1 - 1) % 9 + 1; });
		std::transform(line.begin(), line.end(), std::back_inserter(g.level),
				[](char c) { return (c - '0' + 2 - 1) % 9 + 1; });
		std::transform(line.begin(), line.end(), std::back_inserter(g.level),
				[](char c) { return (c - '0' + 3 - 1) % 9 + 1; });
		std::transform(line.begin(), line.end(), std::back_inserter(g.level),
				[](char c) { return (c - '0' + 4 - 1) % 9 + 1; });
		g.rows++;
		std::getline(std::cin, line);
	}
	g.level.resize(g.level.size() * 5);

	for (int r=1 ; r < 5 ; r++) {
		std::transform(g.level.begin(), std::next(g.level.begin(), g.rows * g.columns),
				std::next(g.level.begin(), g.rows * r * g.columns),
				[r](int l) { return (l + r - 1) % 9 + 1; });
	}
	g.rows *= 5;
	g.weight.resize(g.level.size(), std::numeric_limits<unsigned int>::max());
	g.state.resize(g.level.size(), 0);

	std::cout << g.level.size() << std::endl;

	/*
	for (int r=0 ; r<g.rows ; r++) {
		for (int c=0 ; c<g.columns ; c++) {
			std::cout << g.level[r * g.columns + c];
			if (c % 10 == 9)
				std::cout << " ";
		}
		std::cout << "\n";
		if (r % 10 == 9)
			std::cout << "\n";
	}
	std::cout << "\n";
	*/

	g.weight[0] = 0;
	g.state[0] = 1;
	g.started.push_back(0);

	while (true) {
		auto it = std::min_element(g.started.begin(), g.started.end(),
			[&g](int coords1, int coords2){ return g.weight[coords1] < g.weight[coords2]; });
		int idx = *it;

		// if it's the final node, exit
		if (idx == g.columns * g.rows - 1)
			break;

		// otherwise, update the neighbours, mark the node as finished,
		// the new neighbours as started, and restart
		Point p = { idx % g.columns, idx / g.columns };
		for (const Point& neighbour : std::initializer_list<Point>{ {p.c-1, p.r}, {p.c+1, p.r}, {p.c,p.r-1}, {p.c,p.r+1} } ) {
			if (neighbour.c >= 0 && neighbour.c < g.columns && neighbour.r >= 0 && neighbour.r < g.rows) {
				int coords = neighbour.r * g.columns + neighbour.c;
				long newWeight = g.weight[idx] + g.level[coords];
				if (newWeight < g.weight[coords]) {
					g.weight[coords] = newWeight;
					if (g.state[coords] == 0) {
						g.state[coords] = 1;
						g.started.push_back(coords);
					}
				}
			}
		}
		g.state[idx] = 2;
		g.started.erase(std::remove(g.started.begin(), g.started.end(), idx));
	}

	/*
	std::vector<int> path;
	int coords = g.columns * g.rows - 1;
	while (coords != 0) {
		path.push_back(coords);
		coords = g.pred[coords];
	}
	path.push_back(0);
	for (auto it = path.rbegin() ; it != path.rend() ; ++it) {
		std::cout << " -> (" << (*it % g.columns) << "," << (*it / g.columns) << ")";
	}
	std::cout << std::endl;

	for (int r=0 ; r<g.rows ; r++) {
		for (int c=0 ; c<g.columns ; c++) {
			if (std::find(path.begin(), path.end(), r*g.columns + c) != path.end())
				std::cout << "\x1b[38;5;34m" << g.level[r * g.columns + c] << "\x1b[0m";
			else
				std::cout << g.level[r * g.columns + c];
		}
		std::cout << "\n";
	}
	std::cout << "\n";
	*/

	std::cout << g.weight[g.columns * g.rows - 1] << std::endl;
}

