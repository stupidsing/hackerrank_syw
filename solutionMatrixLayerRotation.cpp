#include <algorithm>
#include <cctype>
#include <functional>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

// Complete the matrixRotation function below.
vector<vector<int>> matrixRotation(vector<vector<int>> matrix, int r) {
	vector<vector<int>> matrix1 = matrix;
	int sizex = matrix.size();
	int sizey = matrix[0].size();
	int x0 = 0;
	int xx = sizex - 1;
	int y0 = 0;
	int yx = sizey - 1;

	while (x0 < xx && y0 < yx) {
		int h = xx - x0;
		int w = yx - y0;
		int len = h * 2 + w * 2;

		auto getPos = [=] (int x, int y) {
			if(x == x0) return 0 * (h + w) + yx - y;
			if(y == y0) return 0 * (h + w) + w + x - x0;
			if(x == xx) return 1 * (h + w) + y - y0;
			if(y == yx) return 1 * (h + w) + w + xx - x;
			return 9999;
		};

		auto getCor = [=] (int pos, int &x, int &y) {
			if(pos < w) {
				x = x0; y = yx - pos;
			} else if (pos < h + w) {
				pos -= w;
				x = pos + x0; y = y0;
			} else if(pos < h + w + w) {
				pos -= h + w;
				x = xx; y = pos + y0;
			} else {
				pos -= h + w + w;
				x = xx - pos; y = yx;
			}
		};

		int rot = r % len;
		int x1, y1;

		for (int x = x0; x <= xx; x++) {
			int y;
			y = y0;
			getCor((getPos(x, y) + rot) % len, x1, y1);
			matrix1[x1][y1] = matrix[x][y];
			y = yx;
			getCor((getPos(x, y) + rot) % len, x1, y1);
			matrix1[x1][y1] = matrix[x][y];
		}

		for (int y = y0; y <= yx; y++) {
			int x;
			x = x0;
			getCor((getPos(x, y) + rot) % len, x1, y1);
			matrix1[x1][y1] = matrix[x][y];
			x = xx;
			getCor((getPos(x, y) + rot) % len, x1, y1);
			matrix1[x1][y1] = matrix[x][y];
		}

		x0++;
		xx--;
		y0++;
		yx--;
	}

	return matrix1;
}

int main() {
	string mnr_temp;
	getline(cin, mnr_temp);

	vector<string> mnr = split(rtrim(mnr_temp));

	int m = stoi(mnr[0]);

	int n = stoi(mnr[1]);

	int r = stoi(mnr[2]);

	vector<vector<int>> matrix(m);

	for (int i = 0; i < m; i++) {
		matrix[i].resize(n);

		string matrix_row_temp_temp;
		getline(cin, matrix_row_temp_temp);

		vector<string> matrix_row_temp = split(rtrim(matrix_row_temp_temp));

		for (int j = 0; j < n; j++) {
			int matrix_row_item = stoi(matrix_row_temp[j]);

			matrix[i][j] = matrix_row_item;
		}
	}

	auto matrix1 = matrixRotation(matrix, r);

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			cout << matrix1[i][j] << " ";
		}
		cout << endl;
	}

	return 0;
}

string ltrim(const string &str) {
	string s(str);

	s.erase(s.begin(),
			find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace))));

	return s;
}

string rtrim(const string &str) {
	string s(str);

	s.erase(
			find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
			s.end());

	return s;
}

vector<string> split(const string &str) {
	vector<string> tokens;

	string::size_type start = 0;
	string::size_type end = 0;

	while ((end = str.find(" ", start)) != string::npos) {
		tokens.push_back(str.substr(start, end - start));

		start = end + 1;
	}

	tokens.push_back(str.substr(start));

	return tokens;
}
