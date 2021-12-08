#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cmath>

int parseBinary(const std::string& s)
{
	int result = 0;
	for (char c : s)
		result = result * 2 + (c == '1');
	return result;
}

int main()
{
	// first, get the length of the numbers, we can't rely on log10()
	// because the first entry might start with a 0
	std::string s;
	std::cin >> s;
	int length = s.size() - 1;

	std::vector<int> input;
	input.push_back(parseBinary(s));
	std::transform(std::istream_iterator<std::string>(std::cin),
		  std::istream_iterator<std::string>(),
		  std::back_inserter(input),
		  &parseBinary
		  );

	auto bOxygen = input.begin();
	auto eOxygen = input.end();
	auto bCo2 = input.begin();
	auto eCo2 = input.end();

	int nbOnes = std::count_if(input.begin(), input.end(),
		[length](long l) -> bool { return l & (1 << length); });
	long major = nbOnes * 2 >= std::distance(bOxygen, eOxygen) ? (1 << length) : 0;
	bCo2 = eOxygen = std::partition(input.begin(), input.end(),
		[length, major](long l) { return (l & (1 << length)) == major; });

	for (int i=length-1 ; i>=0 ; i--) {
		int nbRemainingOxygen = std::distance(bOxygen, eOxygen);
		if (nbRemainingOxygen > 1) {
			int nbOnes = std::count_if(bOxygen, eOxygen,
				[i](long l) -> bool { return l & (1 << i); });
			long major = nbOnes * 2 >= std::distance(bOxygen, eOxygen) ? (1 << i) : 0;
			eOxygen = std::partition(bOxygen, eOxygen,
				[i, major](long l) { return (l & (1 << i)) == major; });
		}

		int nbRemainingCo2 = std::distance(bCo2, eCo2);
		if (nbRemainingCo2 > 1) {
			int nbOnes = std::count_if(bCo2, eCo2,
				[i](long l) -> bool { return l & (1 << i); });
			long minor = nbOnes * 2 >= std::distance(bCo2, eCo2) ? 0 : (1 << i);
			eCo2 = std::partition(bCo2, eCo2,
				[i, minor](long l) { return (l & (1 << i)) == minor; });
		}
	}

	std::cout << (*bOxygen * *bCo2) << std::endl;
}
