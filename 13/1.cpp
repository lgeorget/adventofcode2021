#include <iostream>
#include <vector>
#include <set>
#include <iterator>
#include <algorithm>
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
	std::vector<Point> dots;
	std::copy(point_iterator(std::cin), point_iterator(),
		  std::back_inserter(dots));


	std::regex foldRegex{"fold along (x|y)=(\\d+)"};
	std::string fold;
	std::getline(std::cin, fold);
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

	std::cout << dotsAfterFolding.size() << std::endl;
}
