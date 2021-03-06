#include <iostream>
#include <stdlib.h>     /* srand, rand */

using namespace std;

int String2Int(const string& str) {
    string::const_iterator i = str.begin();
	int result=0;
    if (i == str.end())
        return 0;
    for (; i != str.end(); ++i) {
        if (*i < '0' || *i > '9')
            return 0;
        result *= 10;
        result += *i - '0';
    } return result;
}

int main(int argc, char** argv) {
	srand (time(NULL));
	int n=String2Int(argv[1]);
	int k=String2Int(argv[2]);
	cout << n << ' ' << k << endl;
	for (int i=0;i<k;i++) {
		int f = rand() % n +1;
		int c = rand() % n +1;
		cout << f << ' ' << c << endl;
	}
}
