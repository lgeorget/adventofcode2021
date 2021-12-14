#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <map>

int main(int argc, char** argv)
{
	int turns = 40;
	if (argc > 1) {
		turns = std::stol(argv[1]);
	}

	std::string base;
	std::cin >> base;

	std::map<std::string, char> insertions;
	do {
		std::string group;
		char insertion;
		std::cin >> group;
		std::cin.ignore(4); // " -> "
		std::cin >> insertion;

		if (std::cin)
			insertions[group] = insertion;
	} while (std::cin);

	for (auto [b, i]: insertions) {
		std::cout << b << " -> " << i << "\n";
	}

	std::map<std::string, unsigned long long> groups;
	std::map<char, unsigned long long> counts;
	for (auto itm1 = base.begin(), it = std::next(base.begin(), 1) ; it != base.end() ; ++itm1, ++it) {
		groups[std::string{ *itm1, *it }]++;
		counts[*itm1]++;
	}
	// add the last element, skipped in the loop above
	counts[base.back()]++;

	for (int turn = 1 ; turn <= turns ; turn++) {
		std::map<std::string, unsigned long long> newGroups;
		for (const auto& [g, count] : groups) {
			char inserted = insertions[g];
			newGroups[{ g[0], inserted }] += count;
			newGroups[{ inserted, g[1] }] += count;
			counts[inserted] += count;
		}
		groups = std::move(newGroups);
	}

	auto [min,max] = std::minmax_element(counts.begin(), counts.end(),
			[](auto&& p1, auto&& p2) { return p1.second < p2.second; });

	std::cout << min->first << ": " << min->second << "\n"
	          << max->first << ": " << max->second << "\n";

	std::cout << (max->second - min->second) << std::endl;
}
