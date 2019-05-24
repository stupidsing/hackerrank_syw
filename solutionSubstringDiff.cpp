#include <stddef.h>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iterator>
#include <limits>
#include <string>
#include <vector>

using namespace std;

vector<string> split_string(string);

// Complete the substringDiff function below.
int substringDiff(int k, string s0, string s1) {
	int size0 = s0.size();
	int size1 = s1.size();
	char bs[size0];
	int maxl = 0;
	for (int d = -size0; d <= size1; d++) {
		memset((void*) bs, 0, sizeof(bs));
		int start = max(0, -d);
		int ndiff = 0; // this is bs[start..end].filter(b).count()
		// i from 0 to s0.size()
		// i from -d to s1.size() - d
		for (int end = start; end < min(size0, size1 - d); end++) {
			auto b = s0[end] != s1[end + d];
			if ((bs[end] = b))
				ndiff++;
			if (ndiff > k) {
				while (bs[start++] != 1)
					;
				ndiff--;
			}
			maxl = max(maxl, end - start + 1);
		}
	}
	return maxl;
}

int main() {
	ofstream fout(getenv("OUTPUT_PATH"));

	int t;
	cin >> t;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	for (int t_itr = 0; t_itr < t; t_itr++) {
		string kS1S2_temp;
		getline(cin, kS1S2_temp);

		vector<string> kS1S2 = split_string(kS1S2_temp);

		int k = stoi(kS1S2[0]);

		string s1 = kS1S2[1];

		string s2 = kS1S2[2];

		int result = substringDiff(k, s1, s2);

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
