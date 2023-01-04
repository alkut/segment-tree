#include "segment_tree.hpp"
#include "stupid.hpp"
#include <iostream>
#include <climits>

using namespace std;

void test(long long n) {
    vector<long long> sample(n);
    for (long long i = 0; i < n; ++i)
        sample[i] = (long long)(random() % 7);
    segment_tree<long long> tree(sample, min<long long>, plus<>(), LLONG_MAX, 0ll);
    stupid<long long> st(sample, min<long long>, plus<>(), LLONG_MAX, 0ll);
    vector<pair<long long, pair<long long, long long>>> q;
    for (int i = 0; i < n * n; ++i) {
        if (i & 1) {
            long long left = random() % n, right = random() % n, value = random() % 3;
            if (left > right)
                swap(left, right);
            q.push_back({value, {left, right}});
            tree.add(value, left, right);
            st.add(value, left, right);
            continue;
        }
        long long left = random() % n, right = random() % n;
        if (left > right)
            swap(left, right);
        q.push_back({-1, {left, right}});
        if (tree.get_min(left, right) != st.get_min(left, right)) {
            cout << "All Bad\n";
            return;
        }
    }
    cout << "All right\n";
}

void manual() {
    segment_tree<long long> tree({1, 3, 5, -6}, min<long long>, plus<>(), LLONG_MAX, 0ll);
    int n = 4;
    tree.add(1, 1, 3);
    for (int i = 0; i < n; ++i)
        cout << tree.get_min(i, i) << " ";
    cout << "\n";
    tree.add(1, 0, 2);
    for (int i = 0; i < n; ++i)
        cout << tree.get_min(i, i) << " ";
    cout << "\n";
    cout << tree.get_min(0, n - 1) << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    manual();

    for (int i = 2; i < 10; ++i) test(i); return 0;
}
