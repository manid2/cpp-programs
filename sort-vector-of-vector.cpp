#include <bits/stdc++.h>

using namespace std;

void print_cuboids(const vector<vector<int>> &cuboids)
{
	cout << "  {";
	for (int i = 0; i < static_cast<int>(cuboids.size()); i++) {
		if (i) cout << ", ";
		cout << "{";
		int n = static_cast<int>(cuboids[i].size());
		for (int j = 0; j < n; j++) {
			if (j) cout << ", ";
			cout << cuboids[i][j];
		}
		cout << "}";
	}
	cout << "}" << endl;
}

int main(int, char **)
{
	vector<vector<int>> cuboids{{50, 45, 20}, {95, 37, 53}, {45, 23, 12}};
	if (getenv("SHOW_TEST_OUTPUT")) {
		cout << "Testing implementation " << 1 << " "
		     << "sort vector of vector of integers"
		     << "\n";
		print_cuboids(cuboids);
	}

	for (auto &c : cuboids) sort(c.begin(), c.end());
	if (getenv("SHOW_TEST_OUTPUT")) print_cuboids(cuboids);

	sort(cuboids.begin(), cuboids.end());
	if (getenv("SHOW_TEST_OUTPUT")) print_cuboids(cuboids);

	cout << "Executed " << 1 << " implementations"
	     << " with " << 1 << " tests." << endl;
	return 0;
}
