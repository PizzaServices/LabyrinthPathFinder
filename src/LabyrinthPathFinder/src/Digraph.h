#pragma once

#include <list>
#include <vector>
#include <memory>
#include <queue>
#include <set>

class Digraph
{
public:
	void addEdge(int v, int w);
	void bfs(int v);
	bool hasPathTo(int v);
	std::unique_ptr<std::set<int>> pathTo(int v);
	Digraph(int v);
private:
	const int v;
	std::unique_ptr<std::vector<std::list<int>>> adj;
	std::unique_ptr<std::vector<int>> edgeTo;
	std::unique_ptr<std::vector<int>> distTo;
	std::unique_ptr<std::vector<bool>> marked;
};

