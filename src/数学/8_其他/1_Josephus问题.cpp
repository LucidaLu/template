#include <iostream>
using namespace std;
int main() {
	int num, m, r
	while (cin >> num >> m) {
		r = 0;
		for (int k = 1; k <= num; ++k)
			r = (r + m) % k;
		cout << r + 1 << endl;
	}
	return 0;
}
