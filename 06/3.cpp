#include <iostream>
#include <array>
#include <numeric>

int main()
{
	std::array<unsigned long long int, 9> fish = {0};

	int f;
	std::cin >> f;
	while (std::cin) {
		fish[f]++;
		std::cin.ignore(1); // ignore the comma
		std::cin >> f;
	}

	for (int i=0 ; i<256 ; i++) {
		std::array<unsigned long long int, 9> nextGeneration;
		nextGeneration[0] = fish[1];
		nextGeneration[1] = fish[2];
		nextGeneration[2] = fish[3];
		nextGeneration[3] = fish[4];
		nextGeneration[4] = fish[5];
		nextGeneration[5] = fish[6];
		nextGeneration[6] = fish[0] + fish[7];
		nextGeneration[7] = fish[8];
		nextGeneration[8] = fish[0];

		std::swap(fish, nextGeneration);
	}

	unsigned long long int total = std::accumulate(fish.begin(), fish.end(), 0ULL);
	std::cout << total << std::endl;
}
