#include <iostream>
#include <numeric>
#include <algorithm>
#include <utility>
#include <vector>
#include <iterator>
#include <cmath>

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

	long r;
	int s = crabs.size();
	if (s % 2 == 0) {
		r = std::round((crabs[s / 2 - 1] + crabs[s / 2]) / 2.);
	} else {
		r = crabs[s / 2];
	}

	long fuel = std::accumulate(crabs.begin(), crabs.end(),
			0L,
			[r](long sum, long element) {
				return sum + std::abs(element - r);
			});


	std::cout << fuel << std::endl;
}
