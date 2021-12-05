#include <iostream>
#include <map>
#include <utility>
#include <algorithm>

struct Point {
	int x;
	int y;
};

bool operator<(const Point& p1, const Point& p2)
{
	return p1.x < p2.x || (p1.x == p2.x && p1.y < p2.y);
}

std::ostream& operator<<(std::ostream& os, const Point& p)
{
	os << "(" << p.x << "," << p.y << ")";
	return os;
}

int main()
{
	std::map<Point, int> map;

	auto mark = [&map](const Point& p) {
		auto it = map.find(p);
		if (it != map.end())
			it->second++;
		else
			map[p] = 1;
	};


	while (std::cin) {
		int x1, y1, x2, y2;
		std::cin >> x1;
		if (!std::cin)
			break;
		std::cin.ignore(1); // ","
		std::cin >> y1;
		std::cin.ignore(4); // " -> "
		std::cin >> x2;
		std::cin.ignore(1); // ","
		std::cin >> y2;

		if (x1 == x2) {
			if (y1 > y2)
				std::swap(y1, y2);
			for (int y=y1 ; y<=y2 ; y++) {
				mark(Point{x1, y});
			}
		} else if (y1 == y2) {
			if (x1 > x2)
				std::swap(x1, x2);
			for (int x=x1 ; x<=x2 ; x++) {
				mark(Point{x, y1});
			}
		} else if (x1 < x2 && y1 < y2) {
			for (int x=x1, y=y1 ; x<=x2 ; x++, y++) {
				mark(Point{x, y});
			}
		} else if (x1 > x2 && y1 < y2) {
			for (int x=x1, y=y1 ; x>=x2 ; x--, y++) {
				mark(Point{x, y});
			}
		} else if (x1 < x2 && y1 > y2) {
			for (int x=x1, y=y1 ; x<=x2 ; x++, y--) {
				mark(Point{x, y});
			}
		} else if (x1 > x2 && y1 > y2) {
			for (int x=x1, y=y1 ; x>=x2 ; x--, y--) {
				mark(Point{x, y});
			}
		}
	}

	int c = std::count_if(map.begin(), map.end(),
		[](auto&& p) {
			return p.second >= 2;
		});
	std::cout << c << std::endl;
}
