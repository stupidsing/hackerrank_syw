#include <stddef.h>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

using namespace std;

vector<string> split_string(string);

// Complete the longestCommonSubsequence function below.
vector<int> longestCommonSubsequence(vector<int> a, vector<int> b) {
	int lcs[a.size() + 1][b.size() + 1];
	memset(lcs, 0, sizeof(lcs));

	for (int i = 1; i <= a.size(); i++)
		for (int j = 1; j <= b.size(); j++) {
			int lcs1 = max(lcs[i - 1][j], lcs[i][j - 1]);
			if (a[i - 1] == b[j - 1])
				lcs1 = max(lcs1, lcs[i - 1][j - 1] + 1);
			lcs[i][j] = lcs1;
		}

	vector<int> stack;
	int x = a.size();
	int y = b.size();
	while (0 < x && 0 < y) {
		// cout << x << "," << y << ":" << lcs[x][y] << endl;
		if (lcs[x - 1][y] == lcs[x][y])
			x--;
		else if (lcs[x][y - 1] == lcs[x][y])
			y--;
		else if (lcs[x - 1][y - 1] + 1 == lcs[x][y]) {
			stack.push_back(a[x - 1]);
			x--;
			y--;
		}
//		else
//			return {};
	}
	vector<int> ret;
	for (auto iter = stack.end(); iter != stack.begin();)
		ret.push_back(*--iter);
	return ret;
}

int main() {
	ofstream fout(getenv("OUTPUT_PATH"));

	string nm_temp;
	getline(cin, nm_temp);

	vector<string> nm = split_string(nm_temp);

	int n = stoi(nm[0]);

	int m = stoi(nm[1]);

	string a_temp_temp;
	getline(cin, a_temp_temp);

	vector<string> a_temp = split_string(a_temp_temp);

	vector<int> a(n);

	for (int i = 0; i < n; i++) {
		int a_item = stoi(a_temp[i]);

		a[i] = a_item;
	}

	string b_temp_temp;
	getline(cin, b_temp_temp);

	vector<string> b_temp = split_string(b_temp_temp);

	vector<int> b(m);

	for (int i = 0; i < m; i++) {
		int b_item = stoi(b_temp[i]);

		b[i] = b_item;
	}

	vector<int> result = longestCommonSubsequence(a, b);

	for (int i = 0; i < result.size(); i++) {
		fout << result[i];

		if (i != result.size() - 1) {
			fout << " ";
		}
	}

	fout << "\n";

	fout.close();

	return 0;
}

vector<string> split_string(string input_string) {
	string::iterator new_end = unique(input_string.begin(), input_string.end(),
			[] (const char &x, const char &y) {
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

	splits.push_back(
			input_string.substr(i, min(pos, input_string.length()) - i + 1));

	return splits;
}
