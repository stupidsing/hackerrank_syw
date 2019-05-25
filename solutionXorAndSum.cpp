#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

/*
 * Complete the xorAndSum function below.
 */
int xorAndSum(string a, string b) {
	int sizea = a.size();
	int sizeb = b.size();
	int mod = 1000000007;
	int loop = 314159 + 1;
	int sum = 0;
	int pow = 1;
	int nsd = 0;
	int sd = 0;

	for (int i = 0; i < max(sizea, sizeb + loop); i++) {
		if (i < sizeb) {
			nsd++;
			sd += (b[sizeb - 1 - i] - '0');
		}
		if (0 <= i - loop && i - loop < sizeb) {
			nsd--;
			sd -= (b[sizeb - 1 - (i - loop)] - '0');
		}
		int sd1;
		if ((i < sizea ? a[sizea - 1 - i] : '0') == '0') {
			sd1 = sd;
		} else {
			sd1 = loop - sd;
		}
		int add = (sd1 * (long) pow) % mod;
		sum = (sum + add) % mod;
		pow = (2 * pow) % mod;
	}
	return sum;
}

int main() {
	ofstream fout(getenv("OUTPUT_PATH"));
	string a;
	string b;
	getline(cin, a);
	getline(cin, b);

	int result = xorAndSum(a, b);

	fout << result << "\n";
	fout.close();

	return 0;
}
