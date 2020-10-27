// O(log n) for each query

#include "bits/stdc++.h"
using namespace std;

typedef long long ll;
typedef long double ld;
typedef vector<ll> vi;
typedef pair<ll, ll> pii;
typedef vector<pii> vii;
typedef vector<vi> vvi;
const int MOD = 1e9 + 7;

#define fastIO \
ios_base::sync_with_stdio(false); cin.tie(nullptr);
#define endl '\n'
#define pb push_back
#define ff first
#define ss second
#define mp make_pair

class FenwickTree {
    vi ft;
public:
    FenwickTree(int n) {
        ft.assign(n + 1, 0);
    }

    ll rsq(int b) { // sum of freq. of pos 1 to pos b
        ll sum = 0;
        while (b > 0) {
            sum += ft[b];
            b -= b & (-b);
        }
        return sum;
    }

    ll rsq(int a, int b) {  // sum of freq. of pos a to pos b
        return rsq(b) - (a == 1 ? 0 : rsq(a - 1));
    }

    void add(int k, ll v) { // add freq. v to pos k
        while (k < ft.size()) {
            ft[k] += v;
            k += k & (-k);
        }
    }

    int find(ll k) {   // kth order statistics
        ll sum = 0;
        int pos = 0;
        int i = int(log2(ft.size() - 1));
        while (i >= 0) {
            if (pos + (1 << i) < ft.size() && sum + ft[pos + (1 << i)] < k) {
                sum += ft[pos + (1 << i)];
                pos += (1 << i);
            }
            i--;
        }
        return pos + 1;
    }
};

int main() {
    fastIO;
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (auto& i : a)    cin >> i;

    FenwickTree t(n);
    for (auto i : a)    t.add(i, 1);

    while (q--) {
        int k;
        cin >> k;
        if (1 <= k && k <= n) {
            t.add(k, 1);
        } else if (k < 0) {
            k = -k;
            int rmv = t.find(k);
            t.add(rmv, -1);
        }
    }
    int pos = t.find(1);
    cout << (pos <= n ? pos : 0) << endl;

    return 0;
}
