/*
Name: Wira Azmoon
Describe your algorithm and explain your time complexity here:

Greedy algorithm. First we sort by a_i as mentioned, then label with indices.
Then greedily choose the best b_i at each position starting from position 1
(0 if 0-indexed). For this analysis we stick with 0-indexed.
For each position i, we only need to consider up to index 2i, since no 
further position can take up such a space. 
This works optimally since Tuan will keep taking the best possible index,
and never choose such that it is invalid.

Sorting is O(nlogn), PQ is O(nlogn)

Space complexity depends on arrays a, b, ab, pq
which are all O(n), so space is O(n) overall.

*/

#include <iostream>
#include <vector> 
#include <utility>
#include <algorithm>
#include <queue>

using namespace std;

typedef pair<int, int> pp;

int main() {
	int n;
	cin >> n;
	vector<int> a(n), b(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	for (int i = 0; i < n; i++) {
		cin >> b[i];
	}

	long long answer = 0;
	///write your code here

	// Creating a,b vector: O(n)
	vector<pp> ab(n);

	for (int i = 0; i < n; i++) {
		ab[i] = {a[i], b[i]};
	}

	// sort by a_i: O(nlogn)
	sort(ab.begin(), ab.end(), [](const pp &left, const pp &right) {
		return left.first < right.first; 
	});

	// Tuan always picks the first one
	answer += ab[0].second;

	// Using PQ: O(nlogn)
	priority_queue<int> pq;

	// Insert & delete: O(logn)
	// Done O(n) times: O(nlogn)
	for (int i = 1; i < n/2; i++) {
		pq.push(ab[2*i].second);
		pq.push(ab[2*i-1].second);
		int hi = pq.top();
		answer += hi;
		pq.pop();
	}
	
	cout << answer << endl;

	return 0;
}
