
class DisjointSet {
	struct Node {
		int data_;
		Node* next_;
		Node* prev_;
		Node* front_;
		Node* end_;
		Node(const int data = 0, Node* next = nullptr, Node* prev = nullptr) {
			data_ = data;
			next_ = next;
			prev_ = prev;
			front_ = nullptr;
			end_ = nullptr;
		}
	};

	int size = 0;
	Node** rep = nullptr;

public:
	DisjointSet(int max);
	bool makeSet(int object);
	int findSet(int object) const;
	bool unionSets(int rep1, int rep2);
	~DisjointSet();
	DisjointSet(const DisjointSet& other);
	DisjointSet& operator=(const DisjointSet& other);
	DisjointSet(DisjointSet&& other);
	DisjointSet& operator=(DisjointSet&& other);
};
