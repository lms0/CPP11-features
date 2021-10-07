// Ring buffer class
// Once buffer is full, elements shift and the new element comes in
// Own iterator nested class
// auto inference example

#include<iostream>
#include<typeinfo>
#include<vector>

using namespace std;

template<class T>
class ring {
	int length;         // number of elements
	int currentElement; // current element position
	T* buffer;          // ptr to heap memory, to the start of array of T-type elements 
	bool gotFull;       // buffer is full flag
public:
	ring(int l = 0) : 
		length(l){
		currentElement = 0;     // initialize position to 0
		buffer = new T[length]; // allocate needed memory on heap
		gotFull = false;
	}

	void add(T e) {

		// if full, do rotation, add @ beginning of buffer
		if (currentElement == length || gotFull == true)
		{
			gotFull = true;
			this->shiftElements();
			//printBuffer();
			currentElement = 0;
		}
		// add element
		buffer[currentElement++] = e;
		//printBuffer();
	}

	void printBuffer() {
		for (int i = 0; i < length; i++)
			cout << buffer[i] << endl;
	}

	// shift elements to right
	void shiftElements() {
		for (int i = length - 2; i >= 0; i--)
		{   
			buffer[i + 1] = buffer[i];
		}
	}

	int size() {
		return length;
	}

	T& get(int i) {
		return buffer[i];
	}
	
	~ring() {
		delete[] buffer;
	}

	class iterator;

	iterator begin() {
		return iterator(0, *this);
	}
	iterator end()  {
		return iterator(length, *this);
	}
};

template<class T>
class ring<T>::iterator {
	int pos;
	ring& it_r;
public:
	iterator(int p, ring& r) :
		pos(p), it_r(r){
	}
	T& operator*() {
		return it_r.get(pos);

	}
	iterator& operator++(int){ // dummy int for postfix operator overloading
		pos++;
		return *this;
	}
	iterator& operator++() {
		pos++;
		return *this;
	}
	bool operator!=(iterator otherIt) const  {
		return (pos != otherIt.pos);
    }

};

int main() {
	
	ring<string> textring(3);
	textring.add(string("one"));
	textring.add(string("two"));
	textring.add(string("three"));
	textring.add(string("four"));
	textring.add(string("five"));

	for (int i = 0; i < textring.size(); i++)
		cout << textring.get(i) << endl;

	for (ring<string>::iterator it = textring.begin(); it !=textring.end(); it++)
		cout << *it << endl;

	for (auto v : textring)
		cout << v << endl;

	return 0;
}