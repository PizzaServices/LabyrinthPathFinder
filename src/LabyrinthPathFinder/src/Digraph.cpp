#include "Digraph.h"
#include <queue>

digraph::digraph(int v)
{
	adj_ = std::make_unique<std::vector<std::list<int>>>(v);
	marked_ = std::make_unique<std::vector<std::bitset<2>>>(v);
	edge_to_start_ = std::make_unique<std::vector<int>>(v);
	edge_to_end_ = std::make_unique<std::vector<int>>(v);
	intersect_node_ = -1;
}

void digraph::add_edge(const int v, const int w) const
{
	adj_->at(v).push_back(w);
}

void digraph::bfs(const int s, const int e)
{
	auto q_start = std::make_unique<std::queue<int>>();
	auto q_end = std::make_unique<std::queue<int>>();

	marked_->at(s)[0] = true;
	marked_->at(e)[1] = true;

	edge_to_end_->at(s) = -1;
	edge_to_start_->at(e) = -1;

	q_start->push(s);
	q_end->push(e);

	while (!q_start->empty() && !q_end->empty()) {
		const auto v_start = q_start->front();
		q_start->pop();

		const auto v_end = q_end->front();
		q_end->pop();

		for (auto w : adj_->at(v_start)) {
			if (marked_->at(w)[1]){
				edge_to_end_->at(w) = v_start;
				intersect_node_ = w;
				return;
			}

			if (!marked_->at(w)[0]) {
				edge_to_end_->at(w) = v_start;
				marked_->at(w)[0] = true;
				q_start->push(w);
			}
		}

		for (auto w : adj_->at(v_end)) {
			if (marked_->at(w)[0]){
				edge_to_start_->at(w) = v_end;
				intersect_node_ = w;
				return;
			}

			if (!marked_->at(w)[1]) {
				edge_to_start_->at(w) = v_end;
				marked_->at(w)[1] = true;
				q_end->push(w);
			}
		}

	}
}

auto digraph::has_path_to(const int v) const -> bool
{
	return marked_->at(v)[0] || marked_->at(v)[1];
}

auto digraph::path_to(const int v) const -> std::unique_ptr<std::set<int>>
{
	auto path = std::make_unique<std::set<int>>();
	int x;
	for (x = intersect_node_; edge_to_end_->at(x) != -1; x = edge_to_end_->at(x))
		path->insert(x);

	path->insert(x);

	for (x = intersect_node_; edge_to_start_->at(x) != -1; x = edge_to_start_->at(x))
		path->insert(x);

	path->insert(x);

	return path;
}
