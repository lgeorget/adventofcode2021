#include <string>
#include <iostream>

int main()
{
	std::string capture;
	int count = 0;
	while (std::cin) {
		std::getline(std::cin, capture, '|');
		for (int i=0 ; i<4 ; i++) {
			std::cin >> capture;
			int nb = capture.size();
			count += nb == 7 || nb == 4 || nb == 2 || nb == 3;
		}
	}

	std::cout << count << std::endl;
}

