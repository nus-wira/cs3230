#include <iostream>
#include <vector>
#include <algorithm>

#define MOD 1000000007

using namespace std;

typedef long long ll;

/*
ID: A0149286R
Describe your algorithm and explain your time complexity here.

DP. Top-down approach using a memoization table is used.
For each index 1..n, we have a certain number of ways to split.
We can find this number by taking the first few indices away,
as long as the number inside the party is correct. 
Then, recursively call the function on the smaller array having
taken away some, and check for all possible splits, and add all
the recursive calls to the current call's value.
Also check if the entire array itself is a valid party,
and increment the value by 1 if so.

For time complexity, each subproblem (each index 1..n) is only
calculated once. A subproblem has a maximum of O(n) related subproblems.
So the recursive calls take O(n) * O(n) = O(n^2) complexity.
We also created a party array before the recursion which is  O(max(a[i])).
Then, we have O(n^2) + O(max(a[i])) overall.


*/

///You can declare global variables if needed.

// O(n^2)
ll solve(int i, int minC, int maxC, vector<int> &a, vector<ll> &m, vector<int> &party) {
    if (i == a.size()) return 0;
    // if already calculated return
    if (m[i] != -1) return m[i];
    
    // else calculate then store, O(n)

    // copy i to use to store
    int ci = i;
    

    // cnt tracks number of parties
    int cnt = 0;
 
    while (cnt < minC && i < a.size()) {
        // check if next class is already in party
        if (party[a[i]] != ci)
            cnt++;
        party[a[i]] = ci;
        i++;
    }

    // Reached the end (base case)
    if (i == a.size()) {
        // if reached min party size valid
        m[ci] = cnt == minC ? 1 : 0;
        return m[ci];
    }

    // copy start index
    int si = i;

    while (cnt <= maxC && i < a.size()) {
        if (party[a[i]] != ci)
            cnt++;
        party[a[i]] = ci;
        i++;
    }

    // res is result for given i
    ll res = 0;

    // delay calculation so party array can be used
    for (int j = si; j < i; j++) {
        // O(n)
        res += solve(j, minC, maxC, a, m, party);
        res %= MOD;
    }

    // if the array a itself is a valid party
    if (cnt <= maxC && i == a.size())
        res++;

    m[ci] = res;

    ///Return number of possible battle plans.
    return res;
}
int main() {
    int n, minC, maxC, hi = 0;
    cin >> n >> minC >> maxC;

    vector<int> a(n), cnt(n,0);
    for(int i = 0; i < n; i++){
        cin >> a[i];
        if (a[i] > hi)
            hi = a[i];
        a[i]--; // 0-indexed
    }

    // memoization table
    vector<ll> memo(n, -1);
    // track which class is in party, 0-indexed, O(max(a[i]))
    // this is done by assigning the value to be the
    // current index of the recursive call
    vector<int> party(hi, -1);

    cout << solve(0, minC, maxC, a, memo, party) << endl;
}
