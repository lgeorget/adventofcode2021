#include <list>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <tuple>
#include <map>

using Element = char;

using Group = std::tuple<char, char>;

int main()
{
	std::string firstLine;
	std::cin >> firstLine;
	std::list<Element> base;
	std::copy(firstLine.begin(), firstLine.end(), std::back_inserter(base));

	std::map<Group, Element> insertions;

	do {
		Group group;
		Element insertion;
		std::cin >> std::get<0>(group) >> std::get<1>(group);
		std::cin.ignore(4); // " -> "
		std::cin >> insertion;

		if (std::cin)
			insertions[group] = insertion;
	} while (std::cin);

	for (auto [b, i]: insertions) {
		std::cout << std::get<0>(b) << std::get<1>(b) << " -> " << i << "\n";
	}


	for (int step = 1 ; step <= 10 ; step++) {
		for (auto itm1 = base.begin(), it = std::next(base.begin(), 1) ; it != base.end() ; std::advance(itm1, 2), ++it) {
			Group g = { *itm1, *it };
			base.insert(it, insertions[g]);
		}

		std::cout << "After step " << step << ", ";
		std::copy(base.begin(), base.end(),
			  std::ostream_iterator<Element>(std::cout, ""));
		std::cout << "\n";
	}


	std::map<Element, long> counts;
	for (auto&& e: base) {
		counts[e]++;
	}
	auto [min,max] = std::minmax_element(counts.begin(), counts.end(),
			[](auto&& p1, auto&& p2) { return p1.second < p2.second; });

	std::cout << min->first << ": " << min->second << "\n"
	          << max->first << ": " << max->second << "\n";

	std::cout << (max->second - min->second) << std::endl;
}
