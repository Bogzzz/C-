#include "disjointset.h"

DisjointSet::DisjointSet(int max) {
	if (max > 0) {
		rep = new Node * [max];
		size = max;
		for (int i = 0; i < max; i++) {
			rep[i] = nullptr;
		}
	}
}
bool DisjointSet::makeSet(int object) {
	if (object >= 0 && object < size) {
		if (rep[object] == nullptr) {
			Node* nn = new Node(object);
			nn->front_ = nn;
			nn->end_ = nn;
			rep[object] = nn;
			return true;
		}
	}
	return false;
}


int DisjointSet::findSet(int object) const {
	if (object >= 0 && object < size) {
		if (rep[object] != nullptr) {
			return rep[object]->data_;
		}
	}
	return -1;
}
bool DisjointSet::unionSets(int rep1, int rep2) {
	if (rep1 >= 0 && rep2 >= 0 && rep1 < size && rep2 < size) {
		Node* rep1_node = rep[rep1];
		Node* rep2_node = rep[rep2];
		if (rep1_node != nullptr && rep2_node != nullptr) {
			if (rep1_node != rep2_node) {
				Node* last = rep1_node->end_;
				rep2_node->prev_ = last;
				last->next_ = rep2_node;
				rep2_node->front_ = rep1_node;
				rep1_node->end_ = rep2_node->end_;

				Node* current = rep2_node;
				while (current != nullptr) {
					rep[current->data_] = rep1_node;
					current = current->next_;
				}
			}
				return true;
		}

	}
	return false;
}

DisjointSet::~DisjointSet() {
	delete[] rep;
}

DisjointSet::DisjointSet(const DisjointSet& other) {
	size = other.size;
	rep = new Node * [size];

	for (int i = 0; i < size; i++) {
		rep[i] = other.rep[i];
	}
}

DisjointSet& DisjointSet::operator=(const DisjointSet& other) {
	if (this != &other) {

		delete[] rep;

		size = other.size;
		rep = new Node * [size];

		for (int i = 0; i < size; i++) {
			rep[i] = other.rep[i];
		}
	}
	return *this;
}

DisjointSet::DisjointSet(DisjointSet&& other) {
	size = other.size;
	rep = other.rep;
}

DisjointSet& DisjointSet::operator=(DisjointSet&& other) {
	if (&other == this) {
		return *this;
	}

	delete[] rep;
	size = other.size;
	rep = other.rep;
	other.size = 0;
	other.rep = nullptr;

	return *this;
}

