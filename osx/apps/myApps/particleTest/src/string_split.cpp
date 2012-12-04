#include <iostream>
#include <string>

using namespace std;

int main(){
	string str("This is a very long string with far too many characters. If this were a twitter message, no one would read it because it had TL;DR written all over it.");

	if(str.length() > 70){
		//if the lengrth is over this threshold, find the last punctuation mark or space
		size_t mid_space = str.rfind(70, ' ');
		//cout << mid_space << endl;
		string first = str.substr(mid_space);
		//string second = str.substr(mid_space);
		cout << first << endl;
		//cout << second << endl;
	}
	cout << "The string in question is " << str.length() << " characters long" << endl;

	return 0;
}