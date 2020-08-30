#include <iostream>

template <typename T>
class DList {
	struct Node {
		T data_;
		Node* next_;
		Node* prev_;
		Node(const T& data = T{}, Node* next = nullptr, Node* prev = nullptr) {
			data_ = data;
			next_ = next;
			prev_ = prev;
		}
	};
	Node* front_;
	Node* back_;
public:
	DList() {
		front_ = nullptr;
		back_ = nullptr;
	}
	void push_front(const T& data);
	void push_back(const T& data);
	void pop_front();
	void pop_back();
	void print() const;
	void reversePrint() const;
	~DList();
};


template <typename T>
void DList<T>::push_front(const T& data) {

	Node* nn = new Node(data, front_);
	if (front_ != nullptr) {
		front_->prev_ = nn;
	}
	else {
		back_ = nn;
	}
	front_ = nn;
}
template <typename T>
void DList<T>::push_back(const T& data) {

}
template <typename T>
void DList<T>::pop_front() {
	if (front_ != nullptr) {
		Node* rm = front_;
		if (front_->next_ != nullptr) {
			front_ = front_->next_;
			front_->prev_ = nullptr;
		}
		else {
			front_ = nullptr;
			back_ = nullptr;
		}

		delete rm;
	}

}
template <typename T>
void DList<T>::pop_back() {

}
template <typename T>
void DList<T>::print() const {
	Node* curr = front_;
	while (curr != nullptr) {
		std::cout << curr->data_ << " ";
		curr = curr->next_;
	}
	if (!front_) {
		std::cout << "empty list";
	}
	std::cout << std::endl;
}
template <typename T>
void DList<T>::reversePrint() const {
	Node* curr = back_;
	while (curr != nullptr) {
		std::cout << curr->data_ << " ";
		curr = curr->prev_;
	}
	if (!back_) {
		std::cout << "empty list";
	}
	std::cout << std::endl;
}
template <typename T>
DList<T>::~DList() {

}
template <typename T>
class Sentinel {
	struct Node {
		T data_;
		Node* next_;
		Node* prev_;
		Node(const T& data = T{}, Node* next = nullptr, Node* prev = nullptr) {
			data_ = data;
			next_ = next;
			prev_ = prev;
		}
	};
	Node* front_;
	Node* back_;
public:
	Sentinel() {
		front_ = new Node();
		back_ = new Node();
		front_->next_ = back_;
		back_->prev_ = front_;
	}
	void push_front(const T& data);
	void push_back(const T& data);
	void pop_front();
	void pop_back();
	void print() const;
	void reversePrint() const;
	~Sentinel();
};


template <typename T>
void Sentinel<T>::push_front(const T& data) {
	Node* nn = new Node(data, front_->next_, front_);
	front_->next_ = nn;
	nn->next_->prev_ = nn;
}
template <typename T>
void Sentinel<T>::push_back(const T& data) {
	Node* nn = new Node(data, back_, back_->prev_);
	back_->prev_->next_ = nn;
	back_->prev_ = nn;

}
template <typename T>
void Sentinel<T>::pop_front() {
	if (front_->next_ != back_) {
		Node* nn = front_->next_; //point to new node to the one we want removed
		front_->next_ = nn->next_; // make front sentinel point to node after the one removed
		front_->next_->prev_ = front_; //make prev pointer of the node point back to front sentinel
		delete nn; //deallocate
	}
}
template <typename T>
void Sentinel<T>::pop_back() {
	if (back_->prev_ != front_) {

		Node* nn = back_->prev_;
		back_->prev_ = nn->prev_;
		back_->prev_->next_ = back_;
		delete nn;


	}
}
template <typename T>
void Sentinel<T>::print() const {
	Node* curr = front_->next_;
	while (curr != back_) {
		std::cout << curr->data_ << " ";
		curr = curr->next_;
	}
	if (front_->next_ == back_) {
		std::cout << "empty list";
	}
	std::cout << std::endl;
}
template <typename T>
void Sentinel<T>::reversePrint() const {
	Node* curr = back_->prev_;
	while (curr != front_) {
		std::cout << curr->data_ << " ";
		curr = curr->prev_;
	}
	if (back_->prev_ == front_) {
		std::cout << "empty list";
	}
	std::cout << std::endl;
}
template <typename T>
Sentinel<T>::~Sentinel() {

}

