#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <iterator>
#include <algorithm>
#include <numeric>

class Possibilities : public std::map<char, std::vector<char>>
{
public:
Possibilities() :
	std::map<char, std::vector<char>>{
		{ 'a', { 'a', 'b', 'c', 'd', 'e', 'f', 'g' } },
		{ 'b', { 'a', 'b', 'c', 'd', 'e', 'f', 'g' } },
		{ 'c', { 'a', 'b', 'c', 'd', 'e', 'f', 'g' } },
		{ 'd', { 'a', 'b', 'c', 'd', 'e', 'f', 'g' } },
		{ 'e', { 'a', 'b', 'c', 'd', 'e', 'f', 'g' } },
		{ 'f', { 'a', 'b', 'c', 'd', 'e', 'f', 'g' } },
		{ 'g', { 'a', 'b', 'c', 'd', 'e', 'f', 'g' } },
		{ 'h', { 'a', 'b', 'c', 'd', 'e', 'f', 'g' } }
	}
{}

void deduce(const std::string& s) {
	std::cout << "Deducing from '" << s << "'\n";
	int nb = s.size();
	if (nb == 2) { // 1
		for (char c = 'a' ; c <= 'g' ; c++) {
			if (c != s[0] && c != s[1]) {
				std::cerr << "c cannot be " << c << " because it's part of 1\n";
				remove('c', c);
				std::cerr << "f cannot be " << c << " because it's part of 1\n";
				remove('f', c);
			}
		}
	} else if (nb == 4) { // 4
		for (char c = 'a' ; c <= 'g' ; c++) {
			if (c != s[0] && c != s[1] && c != s[2] && c != s[3]) {
				std::cerr << "b cannot be " << c << " because it's part of 4\n";
				remove('b', c);
				std::cerr << "c cannot be " << c << " because it's part of 4\n";
				remove('c', c);
				std::cerr << "d cannot be " << c << " because it's part of 4\n";
				remove('d', c);
				std::cerr << "f cannot be " << c << " because it's part of 4\n";
				remove('f', c);
			}
		}
	} else if (nb == 3) { // 7
		for (char c = 'a' ; c <= 'g' ; c++) {
			if (c != s[0] && c != s[1] && c != s[2]) {
				std::cerr << "a cannot be " << c << " because it's part of 7\n";
				remove('a', c);
				std::cerr << "c cannot be " << c << " because it's part of 7\n";
				remove('c', c);
				std::cerr << "f cannot be " << c << " because it's part of 7\n";
				remove('f', c);
			}
		}
	} else if (nb == 5) { // 2, 3, or 5
		std::vector<char> left{'a', 'b', 'c', 'd', 'e', 'f', 'g'};
		auto e = left.end();
		for (char c : s)
			e = std::remove(left.begin(), e, c);

		std::cerr << "a cannot be " << left[0] << " because it's part of 2, 3, and 5\n";
		remove('a', left[0]);
		std::cerr << "d cannot be " << left[0] << " because it's part of 2, 3, and 5\n";
		remove('d', left[0]);
		std::cerr << "g cannot be " << left[0] << " because it's part of 2, 3, and 5\n";
		remove('g', left[0]);
		std::cerr << "a cannot be " << left[1] << " because it's part of 2, 3, and 5\n";
		remove('a', left[1]);
		std::cerr << "d cannot be " << left[1] << " because it's part of 2, 3, and 5\n";
		remove('d', left[1]);
		std::cerr << "g cannot be " << left[1] << " because it's part of 2, 3, and 5\n";
		remove('g', left[1]);
	} else if (nb == 6) { // 0, 6 or 9
		std::vector<char> left{'a', 'b', 'c', 'd', 'e', 'f', 'g'};
		auto e = left.end();
		for (char c : s)
			e = std::remove(left.begin(), e, c);
		std::cerr << "a cannot be " << left[0] << " because it's part of 0, 6, and 9\n";
		remove('a', left[0]);
		std::cerr << "b cannot be " << left[0] << " because it's part of 0, 6, and 9\n";
		remove('b', left[0]);
		std::cerr << "f cannot be " << left[0] << " because it's part of 0, 6, and 9\n";
		remove('f', left[0]);
		std::cerr << "g cannot be " << left[0] << " because it's part of 0, 6, and 9\n";
		remove('g', left[0]);
	}
}


void remove(char dst, char src) {
	auto& pos = at(src);
	if (pos.size() == 1)
		return; //base case to end the recursion below

	auto it = std::find(pos.begin(), pos.end(), dst);
	if (it != pos.end())
		pos.erase(it);

	if (pos.size() == 1) {
		char solution = pos[0];
		std::cerr << "Segment " << src << " is mapped to " << solution << std::endl;
		// no other segment is mapped to the solution
		for (char c = 'a' ; c <= 'g' ; c++) {
			if (c != src)
				remove(solution, c);
		}
	}
}

bool solved() {
	return std::all_of(begin(), end(), [](auto&& p) { return p.second.size() == 1; });
}

int decipher(std::string s) {
	// shortcut first
	int nb = s.size();
	if (nb == 2)
		return 1;
	else if (nb == 4)
		return 4;
	else if (nb == 3)
		return 7;
	else if (nb == 7)
		return 8;


	// rest of the solution
	for (char& c : s) {
		c = at(c)[0];
	}
	std::sort(s.begin(), s.end());

	if (s == "abcefg")
		return 0;
	else if (s == "cf")
		return 1;
	else if (s == "acdeg")
		return 2;
	else if (s == "acdfg")
		return 3;
	else if (s == "bcdf")
		return 4;
	else if (s == "abdfg")
		return 5;
	else if (s == "abdefg")
		return 6;
	else if (s == "acf")
		return 7;
	else if (s == "abcdefg")
		return 8;
	else if (s == "abcdfg")
		return 9;

	// ups
	std::cout << "ERROR: unmappable " << s << std::endl;
	return 0;
}

};

std::ostream& operator<<(std::ostream& os, const Possibilities& p)
{
	for (char c='a' ; c<='g' ; c++) {
		std::cout << c <<  ": ";
		std::copy(p.at(c).begin(), p.at(c).end(), std::ostream_iterator<char>(std::cout, " "));
		std::cout << "\n";
	}
	return os;
}

int main()
{
	long total = 0;

	for (;;) {
		std::string line;
		std::getline(std::cin, line, '|');

		if (!std::cin)
			break;

		Possibilities p;
		std::istringstream in{line};
		std::for_each(std::istream_iterator<std::string>{in},
			      std::istream_iterator<std::string>{},
			      [&p](const std::string& s) { p.deduce(s); std::cerr << p << std::endl; });

		std::cout << "\nFinal deductions:\n" << p << std::endl;

		std::getline(std::cin, line);
		std::istringstream segments{line};
		int nb = std::accumulate(std::istream_iterator<std::string>{segments},
			std::istream_iterator<std::string>{},
			0,
			[&p](int total, const std::string& s) -> int {
				return total * 10 + p.decipher(s);
			}
		);
		std::cout << nb << std::endl;
		total += nb;
	}

	std::cout << total << std::endl;
}

