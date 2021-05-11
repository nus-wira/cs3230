#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> sub(const vector<vector<int>> &a, const vector<vector<int>> &b) {
    int n = a.size();
    vector<vector<int>> c(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            c[i][j] = a[i][j] - b[i][j];
        }
    }
    return c;
}

vector<vector<int>> add(const vector<vector<int>> &a, const vector<vector<int>> &b) {
    int n = a.size();
    vector<vector<int>> c(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            c[i][j] = a[i][j] + b[i][j];
        }
    }
    return c;
}

vector<vector<int>> mul(vector<vector<int>> &a, vector<vector<int>> &b) {
    int n = a.size();
    vector<vector<int>> c(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            c[i][j] = 0;
            for (int k = 0; k < n; ++k)
                c[i][j] += a[i][k] * b[k][j];
        }
    }
    return c;
}


vector<vector<int>> strassen(vector<vector<int>> a, vector<vector<int>> b) {
    int n = a.size();
    if (n <= 64)
        return mul(a, b);
    int m = n >> 1;
    vector<vector<int>> product(n, vector<int>(n));
    // From notes
    // a0:a,a1:b,a2:c,a3:d, b0:e,b1:f,b2:g,b3:h
    vector<vector<int>> a0, a1, a2, a3, b0, b1, b2, b3, p1, p2, p3, p4, p5, p6, p7, r, s, t, u;
    for (int i = 0; i < m; ++i) {
        a0.push_back(vector<int>((a.begin() + i)->begin(), (a.begin() + i)->begin() + m));
        
        a1.push_back(vector<int>((a.begin() + i)->begin() + m, (a.begin() + i)->end()));
        a2.push_back(vector<int>((a.begin() + m + i)->begin(), (a.begin() + m + i)->begin() + m));
        a3.push_back(vector<int>((a.begin() + m + i)->begin() + m, (a.begin() + m + i)->end()));
        
        b0.push_back(vector<int>((b.begin() + i)->begin(), (b.begin() + i)->begin() + m));
        b1.push_back(vector<int>((b.begin() + i)->begin() + m, (b.begin() + i)->end()));
        b2.push_back(vector<int>((b.begin() + m + i)->begin(), (b.begin() + m + i)->begin() + m));
        b3.push_back(vector<int>((b.begin() + m + i)->begin() + m, (b.begin() + m + i)->end()));
    }

    p1 = strassen(a0, sub(b1, b3));
    p2 = strassen(add(a0, a1), b3);
    p3 = strassen(add(a2, a3), b0);
    p4 = strassen(a3, sub(b2, b0));
    p5 = strassen(add(a0, a3), add(b0, b3));
    p6 = strassen(sub(a1, a3), add(b2, b3));
    p7 = strassen(sub(a0, a2), add(b0, b1));

    r = add(p5, add(p4, sub(p6, p2)));
    s = add(p1, p2);
    t = add(p3, p4);
    u = add(sub(p5, p3), sub(p1, p7));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i < m && j < m)
                product[i][j] = r[i][j];
            else if (i >= m && j < m)
                product[i][j] = t[i - m][j];
            else if (i < m && j >= m)
                product[i][j] = s[i][j - m];
            else
                product[i][j] = u[i - m][j - m];
        }
    }
    

    return product;
}
int main()
{
    int n; cin>>n;
    // input: two n by n matrices
    vector<vector<int>> a(n, vector<int>(n));
    vector<vector<int>> b(n, vector<int>(n));

    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            cin>>a[i][j];
        }
    }
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            cin>>b[i][j];
        }
    }
    vector<vector<int>> product = strassen(a,b);
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            cout << product[i][j] << " ";
        }
        cout << "\n";
    }
    return 0;
}
