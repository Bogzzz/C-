/*************************************************************/
/*                                                           */
/*    starter file for a2                                    */
/*                                                           */
/*                                                           */
/*************************************************************/

#include <string>
#include <utility>
#include <functional>
#include "mylist.h"
using namespace std;
template <class TYPE>
class Table {
public:
	Table() {}
	virtual void update(const std::string& key, const TYPE& value) = 0;
	virtual bool remove(const std::string& key) = 0;
	virtual bool find(const std::string& key, TYPE& value) = 0;
	virtual int numRecords() const = 0;
	virtual bool isEmpty() const = 0;
	virtual ~Table() {}
};

template <class TYPE>
class SimpleTable :public Table<TYPE> {

	struct Record {
		TYPE data_;
		std::string key_;
		Record(const std::string& key, const TYPE& data) {
			key_ = key;
			data_ = data;
		}

	};




	Record** records_;   //the table
	int capacity_;       //capacity of the array

	void grow() {
		Record** tmp = new Record * [capacity_ + 10];
		for (int i = 0; i < capacity_; i++) {
			tmp[i] = records_[i];
		}
		for (int i = capacity_; i < capacity_ + 10; i++) {
			tmp[i] = nullptr;
		}
		delete[] records_;
		records_ = tmp;
		capacity_ += 10;
	}
public:
	SimpleTable(int capacity);
	SimpleTable(const SimpleTable& other);
	SimpleTable(SimpleTable&& other);
	virtual void update(const string& key, const TYPE& value);
	virtual bool remove(const string& key);
	virtual bool find(const string& key, TYPE& value);
	virtual const SimpleTable& operator=(const SimpleTable& other);
	virtual const SimpleTable& operator=(SimpleTable&& other);
	virtual ~SimpleTable();
	virtual bool isEmpty() const { return numRecords() == 0; }
	virtual int numRecords() const;
};

template <class TYPE>
int SimpleTable<TYPE>::numRecords() const {
	int rc = 0;
	for (int i = 0; records_[i] != nullptr; i++) {
		rc++;
	}
	return rc;
}



template <class TYPE>
SimpleTable<TYPE>::SimpleTable(int capacity) : Table<TYPE>() {
	records_ = new Record * [capacity];
	capacity_ = capacity;
	for (int i = 0; i < capacity_; i++) {
		records_[i] = nullptr;
	}
}

template <class TYPE>
SimpleTable<TYPE>::SimpleTable(const SimpleTable<TYPE>& other) {
	records_ = new Record * [other.capacity_];
	capacity_ = other.capacity_;
	for (int i = 0; i < other.numRecords(); i++) {
		update(other.records_[i]->key_, other.records_[i]->data_);
	}
}
template <class TYPE>
SimpleTable<TYPE>::SimpleTable(SimpleTable<TYPE>&& other) {
	capacity_ = other.capacity_;
	records_ = other.records_;
	other.records_ = nullptr;
	other.capacity_ = 0;
}

template <class TYPE>
void SimpleTable<TYPE>::update(const std::string& key, const TYPE& value) {
	int idx = -1;
	int size = numRecords();
	for (int i = 0; i < size; i++) {
		if (records_[i]->key_ == key) {
			idx = i;
		}
	}
	if (idx == -1) {
		if (size == capacity_) {
			grow();
		}
		records_[size++] = new Record(key, value);
		for (int i = 0; i < size - 1; i++) {
			for (int j = 0; j < size - 1 - i; j++) {
				if (records_[j]->key_ > records_[j + 1]->key_) {
					Record* tmp = records_[j];
					records_[j] = records_[j + 1];
					records_[j + 1] = tmp;
				}
			}
		}
	}
	else {
		records_[idx]->data_ = value;
	}

}

template <class TYPE>
bool SimpleTable<TYPE>::remove(const std::string& key) {
	int idx = -1;
	for (int i = 0; i < numRecords(); i++) {
		if (records_[i]->key_ == key) {
			idx = i;
		}
	}
	if (idx != -1) {
		delete records_[idx];
		int size = numRecords();
		for (int i = idx; i < size - 1; i++) {
			records_[i] = records_[i + 1];
		}
		records_[size - 1] = nullptr;
		return true;
	}
	else {
		return false;
	}
}

template <class TYPE>
bool SimpleTable<TYPE>::find(const std::string& key, TYPE& value) {
	int idx = -1;
	for (int i = 0; i < numRecords(); i++) {
		if (records_[i]->key_ == key) {
			idx = i;
		}
	}
	if (idx == -1)
		return false;
	else {
		value = records_[idx]->data_;
		return true;
	}
}

template <class TYPE>
const SimpleTable<TYPE>& SimpleTable<TYPE>::operator=(const SimpleTable<TYPE>& other) {
	if (this != &other) {
		if (records_) {
			int sz = numRecords();
			for (int i = 0; i < sz; i++) {
				remove(records_[0]->key_);
			}
			delete[] records_;
		}
		records_ = new Record * [other.capacity_];
		capacity_ = other.capacity_;
		int size = other.numRecords();
		for (int i = 0; i < size; i++) {
			update(other.records_[i]->key_, other.records_[i]->data_);
		}

	}
	return *this;
}
template <class TYPE>
const SimpleTable<TYPE>& SimpleTable<TYPE>::operator=(SimpleTable<TYPE>&& other) {
	swap(records_, other.records_);
	swap(capacity_, other.capacity_);
	return *this;
}
template <class TYPE>
SimpleTable<TYPE>::~SimpleTable() {
	if (records_) {
		int sz = numRecords();
		for (int i = 0; i < sz; i++) {
			remove(records_[0]->key_);
		}
		delete[] records_;
	}
}

template <class TYPE>
class ChainingTable :public Table<TYPE> {

	DList<TYPE>* table;				// Linked List
	int capacity_;					
	int numRecord_;
	double loadFactor_;

	int rehash(const string& key, int newcap) {   // returns a new hash using the key and a new capacity 
		hash<string> hash;
		return hash(key) % newcap;
	}

	void grow() {								// Grow the array twice the size of the previus array
		int newcap = capacity_ * 2;					// calculates a new capacity
		
		DList<TYPE>* tmp = new DList<TYPE>[newcap];					// creates a table with a new capacity
		
		for (int i = 0; i < capacity_; i++) {						// moves the data from the old array to the new array
			table[i].begin();										
			while (table[i].getCurrent() != nullptr) {					// while current is existing is the same as if the there are any data in the first Node of the Linked List
				string k = table[i].getKey();							// takes the key from the old table
				TYPE v = table[i].getData();							// takes data from the old table
				int new_hash = rehash(k, newcap);						// rehashing using our function
				tmp[new_hash].insert(k, v);								// inserts the old data in the new table using new hash
				table[i].goNext();										// goes to next Node
			}
		}
		delete[] table;													// deletes old table
			
		table = tmp;													// make the Table equal to the new table
		capacity_ =  newcap;											// sets capacity to new capacity
	}


public:


	ChainingTable(int maxExpected, double maxLoadFactor);
	ChainingTable(const ChainingTable& other);
	ChainingTable(ChainingTable&& other);
	virtual void update(const string& key, const TYPE& value);
	virtual bool remove(const string& key);
	virtual bool find(const string& key, TYPE& value);
	virtual const ChainingTable& operator=(const ChainingTable& other);
	virtual const ChainingTable& operator=(ChainingTable&& other);
	virtual ~ChainingTable();
	virtual bool isEmpty() const;
	virtual int numRecords() const { return numRecord_; }
	virtual int capacity() const { return capacity_; }

};
template <class TYPE>
ChainingTable<TYPE>::ChainingTable(int maxExpected, double maxLoadFactor) {         // constructor of the table with the inputs for size and max load 


	capacity_ = maxExpected;										
	loadFactor_ = maxLoadFactor;
	numRecord_ = 0;
	table = new DList<TYPE>[maxExpected];									// creates a table of Linked Lists 
}

template <class TYPE>
bool ChainingTable<TYPE>::isEmpty()const {		// fucntion is checking is the table is empty or not

	if (numRecords() == 0) {									
		return true;
	}
	return false;

}

template <class TYPE>
ChainingTable<TYPE>::ChainingTable(const ChainingTable<TYPE>& other) { // copy constructor 
	*this = other;
}
template <class TYPE>
ChainingTable<TYPE>::ChainingTable(ChainingTable<TYPE>&& other) { // move constructor
	loadFactor_ = other.loadFactor_;
	capacity_ = other.capacity_;
	numRecord_ = other.numRecords();
	table = other.table;

	other.loadFactor_ = 0;
	other.capacity_ = 0;
	other.numRecord_ = 0;
	other.table = nullptr;
}


template <class TYPE>
void ChainingTable<TYPE>::update(const string& key, const TYPE& value) {  // update funtction which takes a key and changes the value

	hash<string> hash;									

	double newcap = (numRecord_ + 1) / (double)capacity_;						// created a new factor load using the amount of records entered and capacity of the table to compare later

	int hashindex = hash(key) % capacity_;										// hashing the key string
	
	table[hashindex].begin();													// gets the current to the Front so we would be looking on the first node of the linked list

	if (!table[hashindex].getFront()) { // if the node doesnt exist under this hashindex
		if ((newcap) > loadFactor_) { // if the new factor is larger then loadfactor 
			grow();					// we grow out array capacity by 2
		}
		int hashindex = hash(key) % capacity_; // and then we create a new hash with new capacity
		table[hashindex].insert(key, value);		// and insert the key with a value in the correct spot
		numRecord_++;			// increase Record Count
	}
	else {


		while (table[hashindex].getNext() != nullptr && (table[hashindex].getKey() != key)) {  // making sure its somewhere in the list
			table[hashindex].goNext();		// go to the next node in the linked list
		}

		if ((table[hashindex].getKey() == key)) {		// if the key is the one we are looking for
			table[hashindex].setData(value);			// change the data (value)
		}
		else {
			if ((newcap) > loadFactor_) {			// if the new factor is larger then the old one
				grow();								// we grow array 
			}
			int hashindex = hash(key) % capacity_; // and then we create a new hash with new capacity
			table[hashindex].insert(key, value);		// and insert the key with a value in the correct spot
			numRecord_++;			// increase Record Count
		}

	}
}

template <class TYPE>
bool ChainingTable<TYPE>::remove(const string& key) {   // remove function takes the key(string) 

	hash<string> hash;

	int hashindex = hash(key) % capacity_;         // hashing the key we got to get the location of it

	table[hashindex].begin();					// go to first node

	if (table[hashindex].getFront() == nullptr) { // making sure there are nodes at all
		return false;
	}
	else {
		while (table[hashindex].getNext() != nullptr && (table[hashindex].getKey() != key)) {  // making sure its somewhere in the list
			table[hashindex].goNext();			// go next node
		}

		if ((table[hashindex].getKey() == key)) { // if the key is the one we are looking for

			table[hashindex].remove(); // remove the node

			return true;
		}

	}
	return false;

}

template <class TYPE>
bool ChainingTable<TYPE>::find(const string& key, TYPE& value) {// find function takes they key string and a data(value)
	hash<string> hash;

	int hashindex = hash(key) % capacity_;						// hashing the key we recived 

	table[hashindex].begin();								// go to the first node of the list
	if (!table[hashindex].getFront()) {			
		return false;				//empty list
	}
	else {

		while (table[hashindex].getNext() != nullptr && (table[hashindex].getKey() != key)) {  // making sure its somewhere in the list
			table[hashindex].goNext();//go next node
		}
		if ((table[hashindex].getKey() == key)) {// if key found
			value = table[hashindex].getData(); // return the value that is in the node
			return true;
		}

	}

	return false;
}

template <class TYPE>
const ChainingTable<TYPE>& ChainingTable<TYPE>::operator=(const ChainingTable<TYPE>& other) { // assignment operator
	if (this != &other) {

		table = new DList<TYPE>[other.capacity_];
		numRecord_ = other.numRecords();
		loadFactor_ = other.loadFactor_;
		capacity_ = other.capacity_;
		for (int i = 0; i < capacity_; i++) {
			other.table[i].begin();
			table[i].begin();
			while (other.table[i].getCurrent()) {
				table[i].insert(other.table[i].getKey(), other.table[i].getData());
				other.table[i].goNext();
			}

		}

	}
	return *this;
}
template <class TYPE>
const ChainingTable<TYPE>& ChainingTable<TYPE>::operator=(ChainingTable<TYPE>&& other) { // move operator
	if (this != &other)
	{

		delete[] table;

		loadFactor_ = other.loadFactor_;
		capacity_ = other.capacity_;
		numRecord_ = other.numRecords();
		table = other.table;

		other.loadFactor_ = 0;
		other.capacity_ = 0;
		other.numRecord_ = 0;
		other.table = nullptr;
	}


	return *this;
}
template <class TYPE>
ChainingTable<TYPE>::~ChainingTable() {

}
