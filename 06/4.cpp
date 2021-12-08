#include <iostream>
#include <array>
#include <numeric>
#include <gmp.h>

int main(int argc, char** argv)
{
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

	mpz_t i;
	mpz_init(i);
	mpz_ui_pow_ui(i, 10, 100);
	while (mpz_cmp_ui(i, 0) > 0) {
		std::cout << "Number of iterations: " << i << std::endl;
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
		mpz_sub_ui(i, i, 1);
	}

	mpz_t total;
	mpz_init(total);
	mpz_set_ui(total, 0);
	for (int i=0 ; i<9 ; i++) {
		mpz_add(total, total, fish[i]);
	}
	mpz_t last20Digits;
	mpz_init(last20Digits);
	mpz_ui_pow_ui(last20Digits, 10, 20);
	mpz_mod(total, total, last20Digits);
	std::cout << total << std::endl;

	mpz_clear(total);
	mpz_clear(last20Digits);
	for (int i=0 ; i<9 ; i++) {
		mpz_clear(fish[i]);
	}
}
