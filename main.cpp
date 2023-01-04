#include <bits/stdc++.h>
using namespace std;

#define ll long long

//struct segment_tree {
//    explicit segment_tree(const vector<ll>& x) {
//        auto n = x.size();
//        ll size = 1;
//        while (size < n)
//            size *= 2;
//        body.resize(2 * size);
//        shift = size;
//        for (ll i = 0; i < x.size(); ++i)
//            body[i + shift] = {x[i], 0ll};
//        for (size_t i = x.size() + shift; i < body.size(); ++i)
//            body[i] = {LLONG_MAX, 0ll};
//        for (ll i = shift - 1; i > 0; --i)
//            body[i] = min(body[2 * i], body[2 * i + 1]);
//
//    }
//
//    void add(ll value, size_t left, size_t right) {
//        vector<ll> need_update;
//        add(1, value, 0, body.size() / 2 - 1, left, right, need_update);
//        for (const auto& it: need_update)
//            update(it);
//    }
//
//    void add(ll root, ll value, size_t v_left, size_t v_right, size_t left, size_t right, vector<ll>& need_update) {
//        if (v_left > right || v_right < left) return;
//        if (left <= v_left && v_right <= right) {
//            body[root].second += value;
//            need_update.push_back(root);
//            return;
//        }
//        auto border = (v_left + v_right) / 2;
//        add(2 * root, value, v_left, border, left, right, need_update);
//        add(2 * root + 1, value, border + 1, v_right, left, right, need_update);
//    }
//
//    ll get_min(size_t left, size_t right) {
//        return get_min(1, 0, body.size() / 2 - 1, left, right);
//    }
//    ll get_min(ll root, size_t v_left, size_t v_right, size_t left, size_t right) {
//        if (v_right < left || v_left > right)
//            return LLONG_MAX;
//        if (left <= v_left && v_right <= right)
//            return body[root].first + body[root].second;
//        auto border = (v_left + v_right) / 2;
//        return min(get_min(2 * root, v_left, border, left, right), get_min(2 * root + 1, border + 1, v_right, left, right)) + body[root].second;
//    }
//    void update(ll root) {
//        while (root) {
//            root /= 2;
//            if (root)
//                body[root].first = min(body[2 * root].second + body[2 * root].first, body[2 * root + 1].second + body[2 * root + 1].first);
//        }
//    }
//
//    vector<pair<ll, ll>> body;
//    ll shift;
//};
//
//struct stupid {
//    explicit stupid(const vector<ll>& x) {
//        body = x;
//    }
//
//    void add(ll value, ll left, ll right) {
//        for (ll i = left; i <= right; ++i)
//            body[i] += value;
//    }
//
//    ll get_min(ll left, ll right) {
//        ll ans = LLONG_MAX;
//        for (ll i = left; i <= right; ++i)
//            ans = min(ans, body[i]);
//        return ans;
//    }
//    vector<ll> body;
//};
//
//void test(ll n) {
//    vector<ll> sample(n);
//    for (ll i = 0; i < n; ++i)
//        sample[i] = (ll)(random() % 7);
//    segment_tree tree(sample);
//    stupid st(sample);
//    vector<pair<ll, pair<ll, ll>>> q;
//    for (int i = 0; i < n * n; ++i) {
//        if (i & 1) {
//            ll left = random() % n, right = random() % n, value = random() % 3;
//            if (left > right)
//                swap(left, right);
//            q.push_back({value, {left, right}});
//            tree.add(value, left, right);
//            st.add(value, left, right);
//            continue;
//        }
//        ll left = random() % n, right = random() % n;
//        if (left > right)
//            swap(left, right);
//        q.push_back({-1, {left, right}});
//        if (tree.get_min(left, right) != st.get_min(left, right)) {
//            cout << "All Bad\n";
//            return;
//        }
//    }
//    cout << "All right\n";
//}
//
//void manual() {
//    segment_tree tree({1, 3, 5, -6});
//    int n = 4;
//    tree.add(1, 1, 3);
//    for (int i = 0; i < n; ++i)
//        cout << tree.get_min(i, i) << " ";
//    cout << "\n";
//    tree.add(1, 0, 2);
//    for (int i = 0; i < n; ++i)
//        cout << tree.get_min(i, i) << " ";
//    cout << "\n";
//    cout << tree.get_min(0, n - 1) << "\n";
//}
//
//int main() {
//    ios_base::sync_with_stdio(false);
//    cin.tie(nullptr);
//
//    manual();
//
//    for (int i = 2; i < 10; ++i) test(i); return 0;
//}
