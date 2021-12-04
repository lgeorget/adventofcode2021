#include <iostream>
#include <sstream>
#include <vector>
#include <utility>
#include <string>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <functional>

struct Grid {
	int size;
	std::vector<std::pair<bool, int>> numbers;

	bool markNumber(int n) {
		auto it = std::find_if(numbers.begin(), numbers.end(),
				[n](auto&& p) { return p.second == n; });
		if (it != numbers.end()) {
			it->first = true;

			int index = std::distance(numbers.begin(), it);
			int x = index % size;
			int y = index / size;
			/*
			std::cout << "found number " << (it->second)
				<< " at coords (" << x << ";" << y << ")"
				<< std::endl;
			*/

			bool marked = true;
			for (int i=x ; i<size*size && marked ; i+=size) {
				marked = numbers[i].first;
			}

			if (!marked) {
				marked = true;
				for (int i=y*size ; i<(y+1)*size && marked ; i++) {
					marked = numbers[i].first;
				}
			}

			return marked;
		}
		return false;
	}

	int getSumOfUnmarked()
	{
		return std::accumulate(numbers.begin(), numbers.end(),
			0,
			[](int r, auto&& p) {
				return r + (p.first ? 0 : p.second);
			}
		);
	}
};

int main()
{
	std::vector<int> drawn;

	std::string allNumbers;
	std::cin >> allNumbers;
	const char* asCstring = allNumbers.data();

	// parse numbers
	std::size_t parsed = 0;
	while (parsed < allNumbers.size()) {
		std::size_t processed;
		int i = std::stoi(asCstring + parsed, &processed);
		drawn.push_back(i);
		parsed = parsed + processed + 1; // ignore the comma after each number
	}


	// parse the grids
	std::cin >> std::ws;
	std::vector<Grid> grids;

	while (std::cin) {
		std::string line;
		std::getline(std::cin, line);

		Grid g;
		int count = 0;
		do {
			std::istringstream is{line};
			std::transform(
				std::istream_iterator<int>{is},
				std::istream_iterator<int>{},
				std::back_inserter(g.numbers),
				[](int n) { return std::make_pair(false, n); }
			);
			count++;
			std::getline(std::cin, line);
		} while (!line.empty());
		g.size = count;
		grids.push_back(std::move(g));

	}

	// print grids
	/* for (const Grid& g: grids) {
		std::cout << g.size << "x" << g.size << "\n";
		std::transform(g.numbers.begin(), g.numbers.end(), std::ostream_iterator<int>(std::cout, " "), std::mem_fn(&std::pair<bool,int>::second));
		std::cout << std::endl;
	} */


	// Play the game
	for (int number : drawn) {
		for (auto b = grids.begin() ; b != grids.end() ;) {
			bool result = b->markNumber(number);
			if (result && grids.size() == 1) {// last grid, get the result
				std::cout << (b->getSumOfUnmarked() * number) << std::endl;
				return 0;
			} else if (result) {
				b = grids.erase(b);
			} else {
				++b;
			}
		}
	}
}
