#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

// Complete the longestIncreasingSubsequence function below.
int longestIncreasingSubsequence(vector<int> arr) {
//	vector<int> sorted;
//	sorted.resize(arr.size());
//	for (int i = 0; i < arr.size(); i++)
//		sorted[i] = arr[i];
//	sort(sorted, sorted + arr.size());
//
//	auto get_idx = [=](int lvl) {
//		int s = 0;
//		int e = arr.size() - 1;
//		while (s < e) {
//			int mid = s + (e - s) / 2;
//			if (lvl <= sorted[mid])
//			e = mid;
//			else
//			s = mid + 1;
//		}
//		return s;
//	};

	int lvls[arr.size() + 1];
	for (int i = 0; i < arr.size(); i++)
		lvls[i] = 99999999;
	lvls[arr.size()] = 0;
	for (int p = 0; p < arr.size(); p++) {
		// given p
		// for longest_inc_subseq(arr[:p].filter(e => e > lvls[i])) = i
		// lvls is monotonically decreasing
		int val = /*get_idx*/(arr[p]);

		{
			int s = -1;
			int e = arr.size() - 1;
			int l;
			while (0 < (l = e - s)) {
				int mid = e - l / 2;
				if (val <= lvls[mid])
					s = mid;
				else
					e = mid - 1;
			}

			// cout << "lvls[" << s << "] = " << val << ";" << endl;
			lvls[s] = val;
		}
	}
	for (int i = 0; i <= arr.size(); i++)
		if (lvls[i] < 99999999)
			return arr.size() - i;
	return 0;
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

	int result = longestIncreasingSubsequence(arr);

	fout << result << "\n";

	fout.close();

	return 0;
}
