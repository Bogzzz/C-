
/**************************************************/
/*  Put your linked list code into this file      */
/**************************************************/

#include <iostream>
using namespace std;

template <typename T>
struct Node {                               // Node with the Key string and a data which is T type but we are using Int in this test
	string key_;
	T data_;
	Node* next_;  // pointer to next node
	Node* prev_;   // pointer to prev node
	Node(const string& key, T& data, Node* next = nullptr, Node* prev = nullptr) {  // node  constuctor 
		this->key_ = key;
		this->data_ = data;
		this->next_ = next;
		this->prev_ = prev;
}
};

template <typename T>
class DList {                    // link list with 
	Node<T>* front_;					// pointer to Front Node
	Node<T>* current_;					// pointer to current Node
	Node<T>* back_;						// pointer to Back Node
public:
	DList() {							// Construstor Linked List
		front_ = nullptr;
		current_ = nullptr;
		back_ = nullptr;
	};
	void insert(const string& key, T value); 
	void setData(T value);
	T getData();
	void remove();
	void begin();
	void end();
	string getKey();
	Node<T>* getFront();
	Node<T>* getNext();
	Node<T>* getCurrent();
	Node<T>* goNext();
	~DList();

};

template<typename T>
T DList<T>::getData() {              // returns the Data(value) inside the current node
	return current_->data_;
};
template <class T>
void DList<T>::setData(T value) {    // sets the data(value) to current node
	current_->data_ = value;
};


template<typename T>
void DList<T>::begin() {             // sets the current of the linked list to front
	current_ = front_;
}

template<typename T>
void DList<T>::end() {              // sets the current of the linked lit to back
	current_ = back_;
}

template<typename T>
string DList<T>::getKey() {          // returns the key(string) of the current node

	return current_->key_;

}

template<typename T>
Node<T>* DList<T>::getFront() {    // return the front of the linked list

	return front_;
}

template<typename T>
Node<T>* DList<T>::getNext() {      // returns the next node from the current in the linked list
	return current_->next_;
}

template <typename T>
Node<T>* DList<T>::goNext() {        // sets the current of the linked list to the next node
	current_ = current_->next_;
}

template<typename T>
Node<T>* DList<T>::getCurrent() {     // returns current node of the linked list

	return current_;

}
template <typename T>
void DList<T>::insert(const string& key, T value) {     // Takes a key and a T value ( Data) which you want to insert in to the linked list
														// function checks if front exists 
	if (front_) {										// if it does , function creates a new Node at the back and sets the created node as a Back of the Linked List
		Node<T>* n = new Node<T>(key, value);
		back_->next_ = n;
		n->prev_ = back_;
		back_ = n;

	}
	else {												// if it doesnt , creates a new Node pointer in the front and makes the Front, Current and the Back look at that Node
		Node<T>* n = new Node<T>(key, value);
		front_ = n;
		current_ = n;
		back_ = front_;
	}
}



template <typename T>
void DList<T>::remove() {							// Deletes the current node

	if (current_ == front_) {						// checkes if the Current is the Front Node

		front_ = front_->next_;						// we will make Next of Front as a new Front , delete Current Node and make Current equal to new Front
		delete current_;
		current_ = front_;


	}
	else if (current_ == back_) {					// if the Current Node is at the Back of the list

		back_ = back_->prev_;						// Make the previus Node from the Back as Back Node of Linked List, delete Current Node and make the Current as new Back
		back_->next_ = nullptr;
		delete current_;
		current_ = back_;
	}
	else {

		current_->next_->prev_ = current_->prev_;		// if the Current Node somewhere in the middle of the Linked List
		current_->prev_->next_ = current_->next_;			// we will make the next of current equal to previus of current
		delete current_;									// previus of current to next of current 
		current_ = front_;									// and delete current 
															// make current look to the front
	}

};


template <typename T>
DList<T>::~DList() {			// Destructor

	begin();

	while (current_) {								// while current exists 
		Node<T>* n = current_->next_;				// create a node pinter to the next of the current
		delete current_;					// delete current
		current_ = n;							//make current be equal to new node poiner.

	}

};

