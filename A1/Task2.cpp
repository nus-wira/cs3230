#include <cstdio>
#include <vector>
#include <algorithm>
#include <utility>
#include <iostream>
#include <set>
using namespace std;

typedef pair<int, int> ii;
typedef pair<ii, ii> pp;

// T(n) = T(n-1) + O(nlogn) --> T(n) = O(n^2 logn)
int maximum_pieces(int n, vector<pp> xy, int r, int c) {
    if (n == 1)
        return n;
        
    // Sort by ymax O(nlogn)
    // vector<pp> ymax(xy.begin(), xy.end()), ymin(xy.begin(), xy.end());
    sort(xy.begin(), xy.end(), [](const pp &left, const pp &right) {
        if (left.second.second == right.second.second)
            return left.second.first < right.second.first;
        return left.second.second < right.second.second;
    });
    // set sorted by ymin O(nlogn)
    auto cmp1 = [](pp a, pp b) {
        if (a.second.first == b.second.first) {
            if (a.second.second == b.second.second)
                return a.first < b.first;
            return a.second.second < b.second.second;
        }
        return a.second.first < b.second.first;
    };
    set<pp, decltype(cmp1)> s(xy.begin(), xy.end(), cmp1);
    // O(nlogn) if not returning
    for (int i = 0; i < n - 1; ++i) {
        pp p = xy[i];
        s.erase(p);
        
        // If current ymax is greater than smallest ymin skip
        if (p.second.second > s.begin()->second.first ) continue;
        return maximum_pieces(i + 1, vector<pp>(xy.begin(), xy.begin() + i + 1), r, c)
                + maximum_pieces(n - i - 1, vector<pp>(xy.begin() + i + 1, xy.end()), r, c);
            
    }
    // If y cannot
    // Sort by xmax
    sort(xy.begin(), xy.end(), [](const pp &left, const pp &right) {
        if (left.first.second == right.first.second)
            return left.first.first < right.first.first;
        return left.first.second < right.first.second;
    });
    // set sorted by xmin
    auto cmp2 = [](pp a, pp b) {
        if (a.first.first == b.first.first) {
            if (a.first.second == b.first.second)
                return a.second < b.second;
            return a.first.second < b.first.second;
        }
        return a.first.first < b.first.first;
    };
    set<pp, decltype(cmp2)> t(xy.begin(), xy.end(), cmp2);
    for (int i = 0; i < n - 1; ++i) {
        pp p = xy[i];
        t.erase(p);
        // If current ymax is greater than smallest ymin skip
        if (p.first.second > t.begin()->first.first ) continue;
        return maximum_pieces(i + 1, vector<pp>(xy.begin(), xy.begin() + i + 1), r, c)
                + maximum_pieces(n - i - 1, vector<pp>(xy.begin() + i + 1, xy.end()), r, c);
            
    }

    // If cannot split anymore
    return 1;

}

int main() {
    int r,c,n;
    scanf("%d%d%d",&r,&c,&n);
    vector<pp> xy(n);
    for(int i=0; i<n; i++) {
        scanf("%d%d%d%d", &xy[i].first.first, &xy[i].second.first, &xy[i].first.second, &xy[i].second.second);
    }
    printf("%d\n", maximum_pieces(n, xy, r, c));
    return 0;
}
