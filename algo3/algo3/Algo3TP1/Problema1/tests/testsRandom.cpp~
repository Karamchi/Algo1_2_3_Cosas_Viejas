#include <iostream>
#include <stdlib.h>     /* srand, rand */

using namespace std;

int String2Int(const string& str) {
    string::const_iterator i = str.begin();
	int result;
    if (i == str.end())
        return 0;
	result = 0;
    for (; i != str.end(); ++i) {
        if (*i < '0' || *i > '9')
            return false;
        result *= 10;
        result += *i - '0';
    } return result;
}

int main(int argc, char** argv) {
	srand (time(NULL));
	int n=String2Int(argv[1]);
	char modo=*argv[2];
	cout << n << ' ';
	if (modo=='0') {
		int P=10*n;
		cout << P << endl;
		for (int i=0;i<n;i++) {
			int z = rand() % (n*20);
			cout << z << ' ';
			int s=0;
			if (z/9!=0) s= rand() % (z/9);
			int c = rand() % n;
			cout << s << ' ' << c << endl;
		}
	} if (modo=='1') {
		int P = 0;
		cout << P << endl;
		int s = 0;
		int c = 1; 
		int z = 0;
		for (int i=0;i<n;i++) {
			cout << z << ' ';
			cout << s << ' ' << c << endl;
		}
	} if (modo=='2') {
		int P = 65536;
		cout << P << endl;
		int c = 3;
		for (int i=0;i<n;i++) { 
			int z = rand() % (10)+1;
			cout << z << ' ';
			int s = 0;
			cout << s << ' ' << c << endl;
		}	
	} 
}
