#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <numeric>
#include <iterator>

int main()
{
	int line = 1;
	std::vector<char> opening;
	std::vector<unsigned long> scores;

	for (;;) {
		char c = std::cin.get();
		if (!std::cin)
			break;

		if (c == '\n') {
			std::cout << "Line " << line << " to be completed by ";
			std::copy(opening.rbegin(), opening.rend(),
				  std::ostream_iterator<char>(std::cout, ""));
			unsigned long points = std::accumulate(opening.rbegin(), opening.rend(), 0UL,
					[](unsigned long total, char c) {
						int points = c == ')' ?  1 :
							     c == ']' ?  2 :
							     c == '}' ?  3 :
							  /* c == '>' */ 4;
						return total * 5 + points;
					}
				);
			std::cout << " for a total of " << points << " points" << std::endl;;
			scores.push_back(points);
			line++;
			opening.clear();
		} else if (c == '(') {
			opening.push_back(')');
		} else if (c == '[') {
			opening.push_back(']');
		} else if (c == '{') {
			opening.push_back('}');
		} else if (c == '<') {
			opening.push_back('>');
		} else {
			if (opening.back() == c) {
				opening.pop_back();
			} else {
				std::cout << "Corrupted line " << line << ", ignoring" << std::endl;
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				line++;
				opening.clear();
			}
		}
	}

	// find the median
	auto middle = scores.begin() + scores.size() / 2;
	std::nth_element(scores.begin(), middle, scores.end());
	std::cout << *middle << std::endl;
}
