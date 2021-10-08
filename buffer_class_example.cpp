// Buffer class example:
// dynamic allocation and memory set, memory copy
// rule of 5: default/parametrized/copy/move constructors definition
// lvalues, rvalues
#include <iostream>
#include <algorithm> // copy_n()
#include <vector>

using namespace std;

class Test {
	static const int SIZE = 100; 
	int* _pBuffer{ nullptr }; // good practice, dont allocate memory if not necessary
public:

	Test() {
		_pBuffer = new int[SIZE] {};
	}

	Test(int n) {
		// memset(_pBuffer, 0, sizeof(int) * SIZE); C old way
		_pBuffer = new int[SIZE] {}; // sets all elements to 0
		for (int i = 0; i < SIZE; i++)
			_pBuffer[i] = n * i; // Fill the buffer with the n-times table 
	}

	Test(const Test& other) {
		_pBuffer = new int[SIZE] {};
		// memcpy(_pBuffer, other._pBuffer, sizeof(int) * SIZE); C old way
		copy_n(_pBuffer, SIZE, other._pBuffer);
	}

	// move constructor
	Test(Test&& other) { // rvalue reference as argument! this works on modern c++ only
		cout << "move ctr" << endl;
		_pBuffer = other._pBuffer; // we copy from other
		other._pBuffer = nullptr;  // avoid rvalue memory de-allocation 
	};

	Test& operator=(const Test& other) {
		_pBuffer = new int[SIZE] {};
		copy_n(_pBuffer, SIZE, other._pBuffer);
		return *this;
	}

	// move assignment operator
	Test& operator=(Test&& other) {
		delete [] _pBuffer;        // free already allocated memory
		_pBuffer = other._pBuffer; // assign
		other._pBuffer = nullptr;  // avoid de-allocation 
		cout << "move assignment op" << endl;
		return *this;
	}

	~Test() {
		delete[] _pBuffer; // delete allocated heap memory (is a must!)
	}

	friend ostream& operator<<(ostream& os, const Test& test);

};

ostream& operator<<(ostream& os, const Test& test) {
	os << "Hello from test!" << endl;
	return os;
}

Test getTest() {
	return Test();
}

void check(int& ref)
{
	cout << "this is lvalue reference function!" << endl;
}

void check(int&& ref)
{
	cout << "this is rvalue reference function!" << endl;
}



int main()
{
	Test t1;      // default ctr
	Test t2(4);   // parametrized ctr
	Test t3 = t2; // copy ctr
	Test t4;
	t4 = t3;      // assignment op
	
	Test& r_t1 = t1; // lvalue reference (r_t1 is a reference to lvalue t1)
	const Test& r_t2 = getTest(); // rvalue reference (reference to object returned by getTest(), 
	                              // which returns a temporal rvalue object that is kept alive until r_t2 goes out of scope)

	Test t5(Test(1)); // Test(1) is an rvalue (does not have a name, we don't know the actual address) 
	                  // However we pass it by const reference to the Test copy constructor (different but like doing Test t2 = lvalue)
	                  // const lvalue reference can refer to rvalues  

	vector<Test> vec;
	vec.push_back(Test()); // this calls the move ctr and does not need
	                       // to allocate memory
	// if the move ctr was not defined, the best next match is the 
	// copy constructor

	Test t6;
	t6 = getTest(); // uses move assignment op, same advantage as before as
	                // no new memory is allocated!


    // Note on rvalues and lvalies:
	int i = 3;
	// these two call different functions of the overloaded check()
	check(i++); // takes a copy of i, then it increments it, and returns an rvalue
	check(++i); // ++i increments i by lvalue reference



}

