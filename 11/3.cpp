#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <cstring>
#include <random>

char original[10][10];
char levels[12][12];
bool flashed[12][12];

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> distrib('0', '9');

void generate() {
	for (int r=1 ; r<11 ; r++) {
		for (int c=1 ; c<11 ; c++) {
			char n = distrib(gen);
			original[r - 1][c - 1] = n;
			levels[r][c] = n;
			flashed[r][c] = false;
		}
	}
}



void flash(int r, int c) {
	flashed[r][c] = true;
	for (int dr=-1 ; dr<=1 ;dr++) {
		for (int dc=-1 ; dc<=1 ;dc++) {
			if (!flashed[r + dr][c + dc])
				levels[r + dr][c + dc]++;
		}
	}
}

void print()
{
	for (int r=1 ; r<11 ; r++) {
		for (int c=1 ; c<11 ; c++) {
			if (levels[r][c] == '0')
				std::cout << "\x1b[38;5;34m0\x1b[0m";
			else
				std::cout << levels[r][c];
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}

void printOriginal()
{
	for (int r=0 ; r<10 ; r++) {
		for (int c=0 ; c<10 ; c++) {
			std::cout << original[r][c];
		}
		std::cout << " ";
	}
}

int main()
{
	int max = -1;
	char maxGrid[10][10];

	std::memset(original, '0', 100);

	for (unsigned long long grid = 0 ; grid < 10'000'000 ; grid++) {
		generate();
		for (int turn=1 ; ; turn++) {
			for (int r=1 ; r<11 ; r++) {
				for (int c=1 ; c<11 ; c++) {
					levels[r][c]++;
				}
			}

			bool finished;
			do {
				finished = true;
				for (int r=1 ; r<11 ; r++) {
					for (int c=1 ; c<11 ; c++) {
						if (levels[r][c] > '9' && !flashed[r][c]) {
							flash(r, c);
							finished = false;
						}
					}
				}
			} while (!finished);

			// verify if all flashed and reset
			int flashes = 0;
			for (int r=1 ; r<11 ; r++) {
				for (int c=1 ; c<11 ; c++) {
					if (levels[r][c] > '9') {
						levels[r][c] = '0';
						flashes++;
					}
					flashed[r][c] = false;
				}
			}

			if (flashes == 100) {
				if (turn > max) {
					max = turn;
					std::memcpy(maxGrid, original, 100);
					std::cout << grid << ": ";
					printOriginal();
					std::cout << ": " << turn << "\n";
				}
				if (grid % 1000 == 0)
					std::cerr << "Grid number " << grid << ": " << turn << std::endl;
				break;
			} else if (turn >= 999'999'999) {
				std::cout << grid << ": ";
				printOriginal();
				std::cout << ": >" << turn << "\n";
				break;
			}
		}
	}
}
