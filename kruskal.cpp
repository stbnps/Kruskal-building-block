#include <algorithm>
#include "kruskal.hpp"

UnionFind::UnionFind(std::vector<Node *> &nodes, std::vector<Edge *> &edges) {
	this->nodes = nodes;
	this->edges = edges;
	for (std::vector<Node *>::iterator it = nodes.begin(); it != nodes.end();
			it++) {
		ufTable[(*it)] = *it;
	}
}

UnionFind::~UnionFind() {

}

bool UnionFind::join(Node *nodeA, Node *nodeB) {
	Node *a = find(nodeA);
	Node *b = find(nodeB);

	// Reference comparison, we want to know if they are the same object
	if (a == b)
		return false;

	if (a->rank > b->rank) {
		std::swap(a, b);
	}

	// if both are equal, the combined tree becomes 1 deeper
	if (a->rank == b->rank)
		b->rank++;

	ufTable[a] = b;
	return true;
}

Node *UnionFind::find(Node *node) {
	if (ufTable[node] != ufTable[ufTable[node]]) {
		ufTable[node] = find(ufTable[node]);
	}
	return ufTable[node];
}

Kruskal::Kruskal(std::vector<Node *> &nodes, std::vector<Edge *> &edges) :
		uf(nodes, edges), nodes(nodes), edges(edges) {
	solved = false;
}

bool Kruskal::sortFunction(Edge* first, Edge* second) {
	return first->getWeight() < second->getWeight();
}

std::vector<Edge *> Kruskal::getEdges() {
	if (!solved) {
		solve();
	}
	return mst;
}

float Kruskal::solve() {
	solved = true;
	std::sort(edges.begin(), edges.end(), sortFunction);

	int treeCount = nodes.size();
	float weight = 0;

	for (unsigned int i = 0; i < edges.size() && treeCount > 1; i++) {
		if (uf.join(edges[i]->a, edges[i]->b)) {
			treeCount--;
			weight += edges[i]->getWeight();

			// Save the edge, it may be useful for the user
			Edge *e = edges[i];
			mst.push_back(e);
		}
	}

	return weight;
}
