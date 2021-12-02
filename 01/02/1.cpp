#include <iostream>
#include <string>

int main()
{
	std::string dir;
	int distance;
	int x = 0, y = 0;
	std::cin >> dir >> distance;
	while (std::cin) {
		if (dir == "forward")
			x += distance;
		else if (dir == "down")
			y += distance;
		else /* dir == "up" */
			y -= distance;
		std::cin >> dir >> distance;
	}
	std::cout << (x * y) << std::endl;
}
