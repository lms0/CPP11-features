#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

bool checkESTA(string& s) {
	return(s == "ESTA");
}

class FunctorCheckESTA {
public:
	bool operator()(string& s) {
		return(s == "ESTA");
	}
} check1;

int main() {

	vector<string> v = { "ILE", "LOQUISIMA", "ESTA", "ESTA" };

	int count = 0;
	count = count_if(v.begin(), v.end(), checkESTA); // ptr to function
	cout << count << endl;
	
	string sTest = "ESTA";
	count = count_if(v.begin(), v.end(), [sTest](string s) {return (s == sTest); }); // lambda
	cout << count << endl;

	count = count_if(v.begin(), v.end(), check1); // functor
	cout << count << endl;




	return 0;
}