#pragma once

#include <list>
#include <vector>
#include <memory>
#include <set>
#include <bitset>

class digraph
{
public:
	auto add_edge(int v, int w) const -> void;
	auto bfs(int s, int e) -> void;
	auto has_path_to(int v) const -> bool;
	auto path_to(int v) const -> std::unique_ptr<std::set<int>>;
	explicit digraph(int v);
private:
	std::unique_ptr<std::vector<std::list<int>>> adj_;
	std::unique_ptr<std::vector<int>> edge_to_end_;
	std::unique_ptr<std::vector<int>> edge_to_start_;
	std::unique_ptr<std::vector<std::bitset<2>>> marked_;
	size_t intersect_node_;
};

