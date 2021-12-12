#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <iterator>
#include <tuple>

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


	std::vector<std::tuple<std::vector<Node>,bool,Node>> visit = { { std::vector<Node>{}, false, "start" } };
	long paths = 0;
	while (!visit.empty()) {
		auto [currentPath, alreadyVisitedTheSameSmallCaveTwice, n] = std::move(visit.back());
		currentPath.push_back(n);
		visit.pop_back();

		if (n == "end") {
			// end of the path
			paths++;
			continue;
		}

		for (const Node& adj : g[n]) {
			if (adj == "start") {
				// cannot go back to the start
			} else if (adj[0] >= 'a' && adj[0] <= 'z') { // small cave
				auto it = std::find(currentPath.begin(), currentPath.end(), adj);
				if (it != currentPath.end()) {
					if (alreadyVisitedTheSameSmallCaveTwice) {
						// already visited, can't go that way
					} else {
						// first time we visit a single
						// small cave twice, it's ok
						visit.emplace_back(currentPath, true, adj);
					}
				} else {
					visit.emplace_back(currentPath, alreadyVisitedTheSameSmallCaveTwice, adj);
				}
			} else {
				visit.emplace_back(currentPath, alreadyVisitedTheSameSmallCaveTwice, adj);
			}
		}
	}

	std::cout << paths << std::endl;
}
