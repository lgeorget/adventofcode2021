#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

char levels[12][12] = { 0 };
bool flashed[12][12] = { false };


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

int main()
{
	for (int r=1 ; r<11 ; r++) {
		for (int c=1 ; c<11 ; c++) {
			std::cin >> levels[r][c];
		}
	}

	unsigned long total = 0;
	for (int turn=1 ; turn<=100 ; turn++) {
		print();
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
						total++;
						flash(r, c);
						finished = false;
					}
				}
			}
		} while (!finished);

		// reset
		for (int r=1 ; r<11 ; r++) {
			for (int c=1 ; c<11 ; c++) {
				if (levels[r][c] > '9') {
					levels[r][c] = '0';
				}
				flashed[r][c] = false;
			}
		}

		std::cout << "After turn " << turn << ", " << total << " flashes" << std::endl;
	}
}
