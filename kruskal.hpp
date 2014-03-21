#ifndef KRUSKAL_H
#define KRUSKAL_H

#include <vector>
#include <map>

class Node {
public:
	Node() :
			rank(1) {
	}
	virtual ~Node() {
	}
	int rank;

};

class Edge {

public:

	virtual ~Edge() {
	}

	/*
	 * An edge should, at last, have 2 end points and a weight
	 */
	Node *a;
	Node *b;
	virtual float getWeight() = 0;

};

class UnionFind {

private:
	std::vector<Node *> nodes;
	std::vector<Edge *> edges;
	/*
	 * Union-Find table; for each node, store its parent.
	 * It's not as efficient as an array, but flexibility comes with a price.
	 */
	std::map<Node *, Node *> ufTable;

public:
	UnionFind() {
	}
	UnionFind(std::vector<Node *> &nodes, std::vector<Edge *> &edges);
	virtual ~UnionFind();
	bool join(Node *nodeA, Node *nodeB);
	Node *find(Node *node);

};

class Kruskal {

private:
	UnionFind uf;
	std::vector<Node *> nodes;
	std::vector<Edge *> edges;
	std::vector<Edge *> mst;
	bool solved;

protected:
	/*
	 * Edges will be sorted this way
	 */
	static bool sortFunction(Edge* first, Edge* second);

public:
	Kruskal(std::vector<Node *> &nodes, std::vector<Edge *> &edges);
	// Get the edges that belong to the minimum spanning tree
	std::vector<Edge *> getEdges();
	float solve();

};

#endif
