#include "Digraph.h"

Digraph::Digraph(int V)
	: v{ V }
{
	adj = std::make_unique<std::vector<std::list<int>>>(V);
	marked = std::make_unique<std::vector<bool>>(V);
	edgeTo = std::make_unique<std::vector<int>>(V);
	distTo = std::make_unique<std::vector<int>>(V);
}

void Digraph::addEdge(int v, int w) {
	adj->at(v).push_back(w);
}

void Digraph::bfs(int s) {
	auto q = std::make_unique<std::queue<int>>();
	marked->at(s) = true;
	distTo->at(s) = 0;
	q->push(s);
	while (q->size() != 0) {
		int v = q->front();
		q->pop();
		for (auto w : adj->at(v)) {
			if (!marked->at(w)) {
				edgeTo->at(w) = v;
				distTo->at(w) = distTo->at(v) + 1;
				marked->at(w) = true;
				q->push(w);
			}
		}
	}
}

bool Digraph::hasPathTo(int v) {
	return marked->at(v);
}

std::unique_ptr<std::set<int>> Digraph::pathTo(int v) {
	std::unique_ptr<std::set<int>> path = std::make_unique<std::set<int>>();
	int x;
	for (x = v; distTo->at(x) != 0; x = edgeTo->at(x))
		path->insert(x);
	path->insert(x);
	return path;
}
