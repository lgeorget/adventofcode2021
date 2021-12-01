#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <numeric>

int main()
{
	std::vector<int> input;
	std::copy(std::istream_iterator<int>(std::cin), std::istream_iterator<int>(), std::back_inserter(input));

	auto it = input.begin();
	auto end = it;
	std::advance(end, 3);
	int previous = std::accumulate(it, end, 0);
	int current;
	int count = 0;

	do {
		++it;
		++end;
		current = std::accumulate(it, end, 0);
		count += current > previous;
		previous = current;
	} while (end != input.end());
	std::cout << count << std::endl;
}
