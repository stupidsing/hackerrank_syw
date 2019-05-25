#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

/*
 * Complete the bricksGame function below.
 */
long bricksGame(vector<int> arr) {
	long sum = 0;
	long sums[arr.size() + 1];
	sums[arr.size()] = 0;
	for (int i = arr.size() - 1; 0 <= i; i--) {
		sum += arr[i];
		sums[i] = sum;
	}

	long maxs[arr.size() + 1];
	memset(maxs, 0, sizeof(maxs));

	for (int i = arr.size() - 1; 0 <= i; i--) {
		long t1 = arr[i] + sums[i + 1] - maxs[i + 1];
		long t2 =
				i + 1 < arr.size() ?
						arr[i] + arr[i + 1] + sums[i + 2] - maxs[i + 2] :
						-99999;
		long t3 =
				i + 2 < arr.size() ?
						arr[i] + arr[i + 1] + arr[i + 2] + sums[i + 3]
								- maxs[i + 3] :
						-99999;
		maxs[i] = max(t1, max(t2, t3));
	}
	return maxs[0];
}

int main() {
	ofstream fout(getenv("OUTPUT_PATH"));

	int t;
	cin >> t;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	for (int t_itr = 0; t_itr < t; t_itr++) {
		int arr_count;
		cin >> arr_count;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		string arr_temp_temp;
		getline(cin, arr_temp_temp);

		vector<string> arr_temp = split_string(arr_temp_temp);

		vector<int> arr(arr_count);

		for (int arr_itr = 0; arr_itr < arr_count; arr_itr++) {
			int arr_item = stoi(arr_temp[arr_itr]);

			arr[arr_itr] = arr_item;
		}

		long result = bricksGame(arr);

		fout << result << "\n";
	}

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
