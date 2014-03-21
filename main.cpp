#include <iostream>
#include <string>
#include "kruskal.hpp"

class N: public Node {

public:
	N(std::string name) :
			name(name) {

	}

	std::string name;

};

class E: public Edge {

public:
	float w;

	E(Node *a, Node *b, float w) {
		this->a = a;
		this->b = b;
		this->w = w;
	}

	float getWeight() {
		return w;
	}

};

int main() {

	std::vector<Node *> nodes;
	std::vector<Edge *> edges;

	N na("a");
	N nb("b");
	N nc("c");
	N nd("d");

	E ea(&na, &nb, 6);
	E eb(&nb, &nc, 5);
	E ec(&nc, &nd, 4);
	E ed(&nd, &na, 3);
	E ee(&na, &nc, 2);
	E ef(&nb, &nd, 1);

	nodes.push_back(&na);
	nodes.push_back(&nb);
	nodes.push_back(&nc);
	nodes.push_back(&nd);

	edges.push_back(&ea);
	edges.push_back(&eb);
	edges.push_back(&ec);
	edges.push_back(&ed);
	edges.push_back(&ee);
	edges.push_back(&ef);

	Kruskal k(nodes, edges);
	float w = k.solve();
	std::cout << "Tree weight: " << std::endl << w << std::endl;

	std::cout << "Edges: " << std::endl;
	std::vector<Edge *> mst = k.getEdges();
	for (std::vector<Edge *>::iterator it = mst.begin(); it != mst.end();
			it++) {
		N *a = (N *) (*it)->a;
		N *b = (N *) (*it)->b;
		std::cout << a->name << " - " << b->name << std::endl;
	}

	return 0;
}
