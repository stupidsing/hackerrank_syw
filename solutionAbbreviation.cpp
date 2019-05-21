#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>

using namespace std;

string lcs(string a, string b, bool flag) {
	short l[a.length()][b.length()];
	memset(l, 0, sizeof(l));

	for (int i = 0; i < a.length(); i++)
		for (int j = 0; j < b.length(); j++) {
			int l0 = 0 < i && 0 < j ? l[i - 1][j - 1] : 0;
			int c = 0;
			if ('a' <= a[i]) {
				c = max(c, 0 < i ? l[i - 1][j] : 0);
				c = max(c, 0 < j ? l[i][j - 1] : 0);
			}
			if (a[i] == b[j])
				c = max(c, l0 + 1);
			if (flag && a[i] - 'a' + 'A' == b[j])
				c = max(c, l0 + 1);
			l[i][j] = c;
		}

	int i = a.length() - 1;
	int j = b.length() - 1;
	int p = l[i][j];
	char s[p + 1];
	s[p] = 0;

	while (0 <= i || 0 <= j) {
		if (0 < i && l[i - 1][j] == l[i][j])
			i--;
		else if (0 < j && l[i][j - 1] == l[i][j])
			j--;
		else {
			s[--p] = a[i];
			i--;
			j--;
		}
	}

	return s;
}

// Complete the abbreviation function below.
string abbreviation(string a, string b) {
	char asps[a.length() + 1];
	int p = 0;

	for (int i = 0; i < a.length(); i++)
		if ('A' <= a[i] && a[i] <= 'Z')
			asps[p++] = a[i];
	asps[p++] = 0;

	string a0(asps);
	auto ab = lcs(a, b, true);

	if (ab.length() == b.length())
		return "YES";
	else
		return "NO";
}

int main() {
	ofstream fout(getenv("OUTPUT_PATH"));

	int q;
	cin >> q;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	for (int q_itr = 0; q_itr < q; q_itr++) {
		string a;
		getline(cin, a);

		string b;
		getline(cin, b);

		string result = abbreviation(a, b);

		fout << result << "\n";
	}

	fout.close();

	return 0;
}
