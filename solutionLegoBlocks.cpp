#include <stddef.h>
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <limits>
#include <string>
#include <vector>

using namespace std;

vector<string> split_string(string);

/*
 * Complete the legoBlocks function below.
 */
int legoBlocks(int height, int width) {
	int mod = 1000000007;
	int ncs[width + 1];
	int ncu[width + 1];
	int nca[width + 1];
	ncs[0] = 1;
	nca[0] = 1;
	for (int l = 1; l <= width; l++) {
		int count = 0;
		count = 1 <= l ? (count + ncs[l - 1]) % mod : count;
		count = 2 <= l ? (count + ncs[l - 2]) % mod : count;
		count = 3 <= l ? (count + ncs[l - 3]) % mod : count;
		count = 4 <= l ? (count + ncs[l - 4]) % mod : count;
		int prod = 1;
		for (int g = 65536; 0 < g; g /= 2) {
			prod = (prod * (long) prod) % mod;
			if ((height & g) != 0) {
				prod = (prod * (long) count) % mod;
			}
		}
		ncs[l] = count;
		nca[l] = prod;
	}
	for (int l = 0; l <= width; l++) {
		int combos = nca[l];
		for (int sep = 1; sep < l; sep++) {
			combos = combos - ((ncu[sep] * (long) nca[l - sep]) % mod);
			combos = (mod + combos) % mod;
		}
		ncu[l] = combos;
	}
	return ncu[width];
}

int main() {
	ofstream fout(getenv("OUTPUT_PATH"));

	int t;
	cin >> t;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	for (int t_itr = 0; t_itr < t; t_itr++) {
		string nm_temp;
		getline(cin, nm_temp);

		vector<string> nm = split_string(nm_temp);

		int n = stoi(nm[0]);

		int m = stoi(nm[1]);

		int result = legoBlocks(n, m);

		fout << result << "\n";
	}

	fout.close();

	return 0;
}

vector<string> split_string(string input_string) {
	string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
		return x == y and x == ' ';
	});

	input_string.erase(new_end, input_string.end());

	while (input_string[input_string.length() - 1] == ' ') {
		input_string.pop_back();
	}

	vector<string> splits;
	char delimiter = ' ';

	size_t i = 0;
	size_t pos = input_string.find(delimiter);

	while (pos != string::npos) {
		splits.push_back(input_string.substr(i, pos - i));

		i = pos + 1;
		pos = input_string.find(delimiter, i);
	}

	splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

	return splits;
}
