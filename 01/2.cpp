#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <numeric>

int main()
{
	std::vector<int> input;
	std::copy(std::istream_iterator<int>(std::cin), std::istream_iterator<int>(), std::back_inserter(input));

	int count = 0;
	for (auto windowBegin = input.begin(), windowEnd = std::next(input.begin(), 3) ;
	     windowEnd != input.end() ;
	     ++windowBegin, ++windowEnd) {
		count += *windowEnd > *windowBegin;
	}
	std::cout << count << std::endl;
}
