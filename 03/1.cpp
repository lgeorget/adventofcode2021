#include <iostream>
#include <vector>

int main()
{
	std::string row;
	std::cin >> row;
	int length = row.length();
	int count = 0;
	std::vector<int> ones(length);

	while (std::cin) {
		count++;
		for (int i=0 ; i<length ; i++) {
			ones[i] += row[i] == '1';
		}
		std::cin >> row;
	}

	int gamma = 0, epsilon = 0;
	for (int i=0 ; i<length ; i++) {
		bool moreOnesThanZeroes = ones[i] * 2 > count;
		gamma = gamma * 2 + 1 * moreOnesThanZeroes;
		epsilon = epsilon * 2 + 1 * !moreOnesThanZeroes;
	}

	std::cout << (gamma * epsilon) << std::endl;
}
