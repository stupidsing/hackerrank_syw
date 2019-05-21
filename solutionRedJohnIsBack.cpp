#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <limits>

using namespace std;

// Complete the redJohn function below.
int redJohn(int n) {
	long a[n + 1];
	for (int m = 0; m <= n; m++) {
		if (m < 4)
			a[m] = 1;
		else
			a[m] = a[m - 1] + a[m - 4];
	}

	long s = a[n];

	char b[s + 1];
	memset(b, 1, sizeof(b));
	b[0] = 0;
	b[1] = 0;
	for (int d = 2; d < 65536; d++)
		if (d <= s && b[d] == 1)
			for (int g = d + d; g <= s; g += d)
				b[g] = 0;

	int sum = 0;

	for (long i = 0; i <= s; i++)
		sum += b[i];

	return sum;
}

int main() {
	ofstream fout(getenv("OUTPUT_PATH"));

	int t;
	cin >> t;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	for (int t_itr = 0; t_itr < t; t_itr++) {
		int n;
		cin >> n;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		int result = redJohn(n);

		fout << result << "\n";
	}

	fout.close();

	return 0;
}
