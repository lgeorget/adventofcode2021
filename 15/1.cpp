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
	std::vector<int> level;
	std::vector<long> weight;
	std::vector<int> pred;

};

int main()
{
	Grid g;
	std::string line;
	std::getline(std::cin, line);
	g.columns = line.size();

	while (std::cin) {
		std::transform(line.begin(), line.end(), std::back_inserter(g.level),
				[](char c) { return c - '0'; });
		g.rows++;
		std::getline(std::cin, line);
	}
	g.weight.resize(g.level.size(), std::numeric_limits<int>::max());
	g.pred.resize(g.level.size());
	g.weight[0] = 0;

	std::deque<int> visit = { 0 };

	while (!visit.empty()) {
		int idx = std::move(visit.front());
		visit.pop_front();

		Point p = { idx % g.columns, idx / g.columns };
		for (const Point& neighbour : std::initializer_list<Point>{ {p.c-1, p.r}, {p.c+1, p.r}, {p.c,p.r-1}, {p.c,p.r+1} } ) {
			if (neighbour.c >= 0 && neighbour.c < g.columns && neighbour.r >= 0 && neighbour.r < g.rows) {
				int coords = neighbour.r * g.columns + neighbour.c;
				long newWeight = g.weight[idx] + g.level[coords];
				if (newWeight < g.weight[coords]) {
					if (std::find(visit.begin(), visit.end(), coords) == visit.end())
						visit.push_back(coords);
					g.weight[coords] = newWeight;
					g.pred[coords] = idx;
				}
			}
		}
	}

	std::cout << g.weight[g.columns * g.rows - 1] << std::endl;

	std::vector<int> path;
	int coords = g.columns * g.rows - 1;
	while (coords != 0) {
		path.push_back(coords);
		coords = g.pred[coords];
	}
	std::cout << "(0,0)";
	for (auto it = path.rbegin() ; it != path.rend() ; ++it) {
		std::cout << " -> (" << (*it % g.columns) << "," << (*it / g.columns) << ")";
	}
	std::cout << std::endl;



}

