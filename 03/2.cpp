#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

int parseBinary(const std::string& s)
{
	int result = 0;
	for (char c : s)
		result = result * 2 + (c == '1');
	return result;
}

int main()
{
	std::vector<std::string> input;
	std::copy(std::istream_iterator<std::string>(std::cin),
		  std::istream_iterator<std::string>(),
		  std::back_inserter(input));

	int length = input.front().length();
	int count = input.size();

	std::vector<int> ones(length);
	for (int i=0 ; i<length ; i++) {
		ones[i] = std::count_if(
			input.begin(), input.end(),
			[i](const std::string& s) { return s[i] == '1'; }
		);
	}


	auto bOxygen = input.begin();
	auto eOxygen = input.end();
	auto bCo2 = input.begin();
	auto eCo2 = input.end();

	int nbOnes = std::count_if(input.begin(), input.end(),
		[](const std::string& s) { return s[0] == '1'; });
	char major = nbOnes * 2 >= std::distance(bOxygen, eOxygen) ? '1' : '0';
	bCo2 = eOxygen = std::partition(input.begin(), input.end(),
		[major](const std::string& s) { return s[0] == major; });

	for (int i=1 ; i<length ; i++) {
		int nbRemainingOxygen = std::distance(bOxygen, eOxygen);
		if (nbRemainingOxygen > 1) {
			int nbOnes = std::count_if(bOxygen, eOxygen,
				[i](const std::string& s) { return s[i] == '1'; });
			char major = nbOnes * 2 >= std::distance(bOxygen, eOxygen) ? '1' : '0';
			eOxygen = std::partition(bOxygen, eOxygen,
					[i, major](const std::string& s) { return s[i] == major; });
		}

		int nbRemainingCo2 = std::distance(bCo2, eCo2);
		if (nbRemainingCo2 > 1) {
			int nbOnes = std::count_if(bCo2, eCo2,
				[i](const std::string& s) { return s[i] == '1'; });
			char minor = nbOnes * 2 >= std::distance(bCo2, eCo2) ? '0' : '1';
			eCo2 = std::partition(bCo2, eCo2,
				[i, minor](const std::string& s) { return s[i] == minor; });
		}

		std::cout << "remaining candidates for oxygen: " << "\n";
		std::copy(bOxygen, eOxygen, std::ostream_iterator<std::string>(std::cout, "\n"));
		std::cout << "remaining candidates for CO2: " << "\n";
		std::copy(bCo2, eCo2, std::ostream_iterator<std::string>(std::cout, "\n"));
	}

	int oxygen = parseBinary(*bOxygen);
	int co2 = parseBinary(*bCo2);

	std::cout << (oxygen * co2) << std::endl;
}
