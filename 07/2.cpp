#include <iostream>
#include <numeric>
#include <algorithm>
#include <utility>
#include <vector>
#include <iterator>
#include <cmath>
#include <limits>

struct csv_iterator : public std::istream_iterator<long>
{
private:
	long lastRead;
	std::istream* in = nullptr;

public:
	csv_iterator(std::istream& stream) :
		in{&stream}
	{
		*in >> lastRead;
		in->ignore(1);
	}

	csv_iterator() = default;

	int operator*()
	{
		long r = lastRead;
		*in >> lastRead;
		in->ignore(1);
		return r;
	}

	csv_iterator& operator++()
	{
		return *this;
	}

	bool operator!=(const csv_iterator&)
	{
		return bool(*in);
	}
};


int main()
{
	std::vector<long> crabs;
	std::copy(csv_iterator(std::cin), csv_iterator(),
		  std::back_inserter(crabs));
	std::sort(crabs.begin(), crabs.end());

	auto minmax = std::minmax_element(crabs.begin(), crabs.end());
	long minFuel = std::numeric_limits<long>::max();
	for (long candidate = *(minmax.first) ; candidate <= *(minmax.second) ; candidate++) {
		long fuel = std::accumulate(crabs.begin(), crabs.end(),
				0L,
				[candidate](long sum, long element) {
					long distance = std::abs(element - candidate);
					return sum + (distance * (distance + 1)) / 2;
				});
		std::cout << "For candidate pos " << candidate << ", we need " << fuel << " units of fuel" << std::endl;
		if (fuel < minFuel)
			minFuel = fuel;
	}


	std::cout << minFuel << std::endl;
}
