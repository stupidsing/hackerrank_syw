#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

// Complete the candies function below.
long candies(int n, vector<int> arr) {
	long sum = 0;
	int p = 0;
	while (p + 1 < n) {
		int p1 = p;
		while (p1 + 1 < n && arr[p1] < arr[p1 + 1])
			p1++;

		int p2 = p1;
		while (p2 + 1 < n && arr[p2 + 1] < arr[p2])
			p2++;

		int p3 = p2;
		while (p3 + 1 < n && arr[p3] == arr[p3 + 1])
			p3++;

		int ni = p1 - p;
		int nd = p2 - p1;
		int ne = p3 - p2;
		if (ni < nd) {
			sum += ((ni + 1) * (long) ni) / 2;
			sum += ((nd + 2) * (long) (nd + 1)) / 2;
		} else {
			sum += ((ni + 2) * (long) (ni + 1)) / 2;
			sum += ((nd + 1) * (long) nd) / 2;
		}
		sum += ne - 1;
		p = p3;
	}
	return sum + 1;
}

int main() {
	ofstream fout(getenv("OUTPUT_PATH"));

	int n;
	cin >> n;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	vector<int> arr(n);

	for (int i = 0; i < n; i++) {
		int arr_item;
		cin >> arr_item;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		arr[i] = arr_item;
	}

	long result = candies(n, arr);

	fout << result << "\n";

	fout.close();

	return 0;
}
