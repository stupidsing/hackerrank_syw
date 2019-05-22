#include <stddef.h>
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

using namespace std;

vector<string> split_string(string);

/*
 * Complete the coinOnTheTable function below.
 */
int coinOnTheTable(int m_, int k, vector<string> board) {
	int m = board.size();
	int n = board[0].size();
	int nsts[m][n][100 + 1];
	int fx, fy;
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++) {
			for (int o = 0; o <= 100; o++)
				nsts[i][j][o] = 99999999;
			if (board[i][j] == '*') {
				fx = i;
				fy = j;
			}
		}

	nsts[0][0][0] = 0;

	for (int o = 0; o < 100; o++) {
		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++) {
				int i0 = i;
				int j0 = j;

				while (true) {
					int nstep0 = nsts[i][j][o];
					int nstep1 = nstep0 + 1;

					if (0 < i && board[i][j] == 'U' && nsts[i - 1][j][o] > nstep1)
						nsts[--i][j][o] = (nstep1);
					else if (i < m - 1 && board[i][j] == 'D' && nsts[i + 1][j][o] > nstep1)
						nsts[++i][j][o] = (nstep1);
					else if (0 < j && board[i][j] == 'L' && nsts[i][j - 1][o] > nstep1)
						nsts[i][--j][o] = (nstep1);
					else if (j < n - 1 && board[i][j] == 'R' && nsts[i][j + 1][o] > nstep1)
						nsts[i][++j][o] = (nstep1);
					else
						break;
				}

				i = i0;
				j = j0;
			}

		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++) {
				int nstep0 = nsts[i][j][o];
				int o1 = o + 1;

				if (0 < i)
					nsts[i - 1][j][o1] = min(nsts[i - 1][j][o1], nstep0 + 1);
				if (i < m - 1)
					nsts[i + 1][j][o1] = min(nsts[i + 1][j][o1], nstep0 + 1);
				if (0 < j)
					nsts[i][j - 1][o1] = min(nsts[i][j - 1][o1], nstep0 + 1);
				if (j < n - 1)
					nsts[i][j + 1][o1] = min(nsts[i][j + 1][o1], nstep0 + 1);
			}
	}

	for (int o = 0; o < 100; o++)
		if (nsts[fx][fy][o] <= k)
			return o;

	return -1;
}

int main() {
	ofstream fout(getenv("OUTPUT_PATH"));

	string nmk_temp;
	getline(cin, nmk_temp);

	vector<string> nmk = split_string(nmk_temp);
	int n = stoi(nmk[0]);
	int m = stoi(nmk[1]);
	int k = stoi(nmk[2]);

	vector<string> board(n);

	for (int board_itr = 0; board_itr < n; board_itr++) {
		string board_item;
		getline(cin, board_item);

		board[board_itr] = board_item;
	}

	int result = coinOnTheTable(m, k, board);

	fout << result << "\n";

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
