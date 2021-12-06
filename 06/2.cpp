#include <iostream>
#include <array>
#include <numeric>
#include <gmp.h>

int main(int argc, char** argv)
{
	int iterations = 80;
	if (argc > 1) {
		iterations = std::stoi(argv[1]);
	}
	std::cout << "Number of iterations: " << iterations << std::endl;


	std::array<mpz_t, 9> fish;
	for (int i=0 ; i<9 ; i++) {
		mpz_init(fish[i]);
		mpz_set_ui(fish[i], 0);
	}

	int f;
	std::cin >> f;
	while (std::cin) {
		mpz_add_ui(fish[f], fish[f], 1);
		std::cin.ignore(1); // ignore the comma
		std::cin >> f;
	}

	for (int i=0 ; i<iterations ; i++) {
		std::array<mpz_t, 9> nextGeneration;
		std::swap(nextGeneration[0], fish[1]);
		std::swap(nextGeneration[1], fish[2]);
		std::swap(nextGeneration[2], fish[3]);
		std::swap(nextGeneration[3], fish[4]);
		std::swap(nextGeneration[4], fish[5]);
		std::swap(nextGeneration[5], fish[6]);
		mpz_init(nextGeneration[6]);
		mpz_add(nextGeneration[6], fish[0], fish[7]);
		mpz_clear(fish[7]);
		std::swap(nextGeneration[7], fish[8]);
		std::swap(nextGeneration[8], fish[0]);

		std::swap(nextGeneration, fish);
	}

	mpz_t total;
	mpz_init(total);
	mpz_set_ui(total, 0);
	for (int i=0 ; i<9 ; i++) {
		mpz_add(total, total, fish[i]);
	}
	mpz_out_str(stdout, 10, total);

	mpz_clear(total);
	for (int i=0 ; i<9 ; i++) {
		mpz_clear(fish[i]);
	}
	std::cout << std::endl;
}
