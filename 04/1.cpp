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

	int markNumber(int n) {
		auto it = std::find_if(numbers.begin(), numbers.end(),
				[n](auto&& p) { return p.second == n; });
		if (it != numbers.end()) {
			it->first = true;

			int index = std::distance(numbers.begin(), it);
			int x = index % size;
			int y = index / size;
			std::cout << "found number " << (it->second)
				<< " at coords (" << x << ";" << y << ")"
				<< std::endl;

			bool marked = true;
			for (int i=x ; i<size*size && marked ; i+=size) {
				std::cout << "x: comparing number " << (numbers[i].second) << " at pos " << i << std::endl;
				marked = numbers[i].first;
			}
			std::cout << std::endl;

			if (!marked) {
				marked = true;
				for (int i=y*size ; i<(y+1)*size && marked ; i++) {
					std::cout << "y: comparing number " << (numbers[i].second) << " at pos " << i << std::endl;
					marked = numbers[i].first;
				}
				std::cout << std::endl;
			}

			if (marked) {
				// it's a win!
				int unmarked = std::accumulate(numbers.begin(), numbers.end(),
					0,
					[](int r, auto&& p) {
						return r + (p.first ? 0 : p.second);
					}
				);
				std::cout << (it->second) << " is winning! "
					<< " Sum of unmarked: " << unmarked
					<< std::endl;
				return unmarked * it->second;
			}
		}
		return 0;
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
		std::cout << i << " " << parsed << std::endl;
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
		for (Grid& g : grids) {
			int result = g.markNumber(number);
			if (result != 0) {
				std::cout << result << std::endl;
				return 0; // the game is over
			}
		}
	}
}
