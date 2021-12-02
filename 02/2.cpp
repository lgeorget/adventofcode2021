#include <iostream>
#include <string>

int main()
{
	std::string dir;
	int distance;
	long horiz = 0, depth = 0, aim = 0;
	std::cin >> dir >> distance;
	while (std::cin) {
		if (dir == "forward") {
			horiz += distance;
			depth += aim * distance;
		} else if (dir == "down") {
			aim += distance;
		} else /* dir == "up" */ {
			aim -= distance;
		}
		std::cin >> dir >> distance;
	}
	std::cout << (horiz * depth) << std::endl;
}
