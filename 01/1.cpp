#include <iostream>
#include <algorithm>

int main()
{
	int previous, current;
	int count = 0;
	std::cin >> previous;
	while (std::cin) {
		std::cin >> current;
		count += current > previous;
		previous = current;
	}
	std::cout << count << std::endl;
}
