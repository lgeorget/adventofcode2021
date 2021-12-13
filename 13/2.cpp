#include <iostream>
#include <set>
#include <iterator>
#include <algorithm>
#include <numeric>
#include <cctype>
#include <regex>

struct Point {
	int x;
	int y;
};

bool operator<(const Point& p1, const Point& p2)
{
	return p1.x < p2.x || (p1.x == p2.x && p1.y < p2.y);
}

class point_iterator : public std::istream_iterator<Point>
{
private:
	std::istream* in = nullptr;

public:
	point_iterator(std::istream& stream) :
		in{&stream}
	{
	}

	point_iterator() = default;

	Point operator*()
	{
		*in >> std::ws;
		char c = in->peek();
		if (std::isdigit(c)) {
			int x, y;
			*in >> x;
			in->ignore(1);
			*in >> y;
			return Point{x, y};
		}
		return Point{};
	}

	point_iterator& operator++()
	{
		return *this;
	}

	bool operator!=(const point_iterator&)
	{
		// works only if lhs is a valid iterator
		// and rhs is not
		*in >> std::ws;
		return bool(*in) && std::isdigit(in->peek());
	}
};

int main()
{
	std::set<Point> dots;
	std::copy(point_iterator(std::cin), point_iterator(),
		  std::inserter(dots, dots.begin()));


	std::regex foldRegex{"fold along (x|y)=(\\d+)"};
	for (;;) {
		std::string fold;
		std::getline(std::cin, fold);
		if (fold.empty())
			break;

		std::smatch foldMatch;
		std::regex_match(fold, foldMatch, foldRegex);
		std::string dir = foldMatch.str(1);
		int line = std::stoi(foldMatch.str(2));

		std::set<Point> dotsAfterFolding;
		if (dir == "x") {
			for (const Point& p : dots) {
				if (p.x > line) {
					dotsAfterFolding.insert(Point{line - (p.x - line), p.y});
				} else {
					dotsAfterFolding.insert(p);
				}
			}
		} else /* dir == "y" */ {
			for (const Point& p : dots) {
				if (p.y > line) {
					dotsAfterFolding.insert(Point{p.x, line - (p.y - line)});
				} else {
					dotsAfterFolding.insert(p);
				}
			}
		}
		dots = std::move(dotsAfterFolding);
	}

	const auto [topleft, bottomright] = std::accumulate(dots.begin(), dots.end(),
			std::make_pair<Point, Point>(Point{10000, 10000}, Point{0, 0}),
			[](std::pair<Point, Point>& r, const Point& p) {
				if (p.x < r.first.x)
					r.first.x = p.x;
				if (p.x > r.second.x)
					r.second.x = p.x;
				if (p.y < r.first.y)
					r.first.y = p.y;
				if (p.y > r.second.y)
					r.second.y = p.y;
				return r;
			});

	for (int y=topleft.y ; y <= bottomright.y ; y++) {
		for (int x=topleft.x ; x <= bottomright.x ; x++) {
			std::cout << (dots.find(Point{x, y}) != dots.end() ? "▓" : " ");
		}
		std::cout << "\n";
	}
	std::cout << std::endl;
}
