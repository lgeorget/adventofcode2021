#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <iterator>

using Node = std::string;

using Graph = std::map<Node, std::vector<Node>>;

int main()
{
	Graph g;
	do {
		std::string src, dest;
		std::getline(std::cin, src, '-');
		std::getline(std::cin, dest, '\n');

		if (std::cin) {
			g[src].push_back(dest);
			g[dest].push_back(src);
		}
	} while (std::cin);

	// print the graph
	for (const auto& [s,d] : g) {
		std::cout << s << ": ";
		std::copy(d.begin(), d.end(), std::ostream_iterator<std::string>(std::cout, " "));
		std::cout << "\n";
	}


	std::vector<std::pair<std::vector<Node>,Node>> visit = { std::make_pair(std::vector<Node>{}, "start") };
	long paths = 0;
	while (!visit.empty()) {
		auto [currentPath, n] = std::move(visit.back());
		currentPath.push_back(n);
		visit.pop_back();

		if (n == "end") {
			// end of the path
			paths++;
			std::cout << "Found a path: ";
			std::copy(currentPath.begin(), currentPath.end(),
				std::ostream_iterator<Node>(std::cout, "-"));
			std::cout << std::endl;
			continue;
		}


		for (const Node& adj : g[n]) {
			std::cout << "Considering neighbour cave " << adj << ": ";
			std::copy(currentPath.begin(), currentPath.end(),
				std::ostream_iterator<Node>(std::cout, "-"));
			std::cout << "\n";
			if (adj[0] >= 'a' && adj[0] <= 'z') { // small cave
				auto it = std::find(currentPath.begin(), currentPath.end(), adj);
				if (it != currentPath.end()) {
					// already visited, can't go that way
					continue;
				}
			}
			visit.push_back(std::make_pair(currentPath, adj));
		}
	}

	std::cout << paths << std::endl;
}
