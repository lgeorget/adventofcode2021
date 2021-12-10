#include <iostream>
#include <vector>
#include <limits>

int line = 1;
int column = 0;

int score(char opening, char found)
{
	std::cout << "Invalid " << found << " at line " << line << ", character " << column << " for chunk starting with " << opening << std::endl;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	switch (found) {
		case ')':
			return 3;
		case ']':
			return 57;
		case '}':
			return 1197;
		case '>':
			return 25137;
	}
}

int main()
{
	std::vector<char> opening;

	long total = 0;
	for (;;) {
		char c = std::cin.get();
		if (!std::cin)
			break;

		column++;
		if (c == '\n') {
			column = 0;
			line++;
			opening.clear();
		} else if (c == '(' || c == '[' || c == '{' || c == '<') {
			opening.push_back(c);
		} else if (c == ')') {
			if (opening.back() == '(') {
				opening.pop_back();
			} else {
				total += score(opening.back(), c);
			}
		} else if (c == ']') {
			if (opening.back() == '[') {
				opening.pop_back();
			} else {
				total += score(opening.back(), c);
			}
		} else if (c == '}') {
			if (opening.back() == '{') {
				opening.pop_back();
			} else {
				total += score(opening.back(), c);
			}
		} else if (c == '>') {
			if (opening.back() == '<') {
				opening.pop_back();
			} else {
				total += score(opening.back(), c);
			}
		}
	}

	std::cout << total << std::endl;
}
