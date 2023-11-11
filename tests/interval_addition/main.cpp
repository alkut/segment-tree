#include "../../src/interval_addition/actual/IntervalAddition.h"
#include "../../src/interval_addition/mock/MockIntervalAddition.h"
#include "gtest/gtest.h"
#include <climits>
#include <iostream>

using namespace std;

class SegmentTreeTester {
public:
  SegmentTreeTester() = default;
  void invoke(long long n) {
    sample.resize(n);
    for (long long i = 0; i < n; ++i)
      sample[i] = (long long)(rand() % 7);
    IntervalAddition<long long> tree(
        sample.begin(), sample.end(),
        [](long long x, long long y) { return min(x, y); },
        [](long long x, long long y) { return x + y; }, LLONG_MAX, 0ll);
    MockIntervalAddition<long long> st(
        sample.begin(), sample.end(),
        [](long long x, long long y) { return min(x, y); },
        [](long long x, long long y) { return x + y; }, LLONG_MAX, 0ll);
    for (int i = 0; i < n * n; ++i) {
      if (i & 1) {
        long long left = rand() % n, right = rand() % n, value = rand() % 3;
        if (left > right)
          swap(left, right);
        q.push_back({value, {left, right}});
        tree.add(value, left, right);
        st.add(value, left, right);
        continue;
      }
      long long left = rand() % n, right = rand() % n;
      if (left > right)
        swap(left, right);
      q.push_back({-1, {left, right}});
      if (tree.get_min(left, right) != st.get_min(left, right)) {
        test_completed = false;
        return;
      }
    }
  }

  vector<long long> sample;
  vector<pair<long long, pair<long long, long long>>> q;
  bool test_completed = true;

  void print() {
    if (test_completed)
      return;
    cout << "TEST FAILED!!!"
         << "\n"
         << "initial sample: \n";
    for (const auto &it : sample)
      cout << it << " ";
    cout << "\n"
         << "query stacktrace: \n";
    for (const auto &[value, bounds] : q) {
      if (value == -1)
        continue;
      cout << "add " << value << " to interval [" << bounds.first << "; "
           << bounds.second << "]\n";
    }
    cout << "get min on interval [" << q.back().second.first << "; "
         << q.back().second.second << "] failed!!!\n";
  }
};

class SegmentTreeParameterizedTestFixture
    : public ::testing::TestWithParam<int> {
protected:
  SegmentTreeTester tree;
};

TEST_P(SegmentTreeParameterizedTestFixture, AutoTest) {
  int size = GetParam();
  tree.invoke(size);
  tree.print();
  ASSERT_TRUE(tree.test_completed);
}

INSTANTIATE_TEST_SUITE_P(SegmentTreeTests, SegmentTreeParameterizedTestFixture,
                         ::testing::Values(100, 101, 102, 103, 104, 678, 475,
                                           686, 996));

TEST(Test, Manual) {
  vector<long long> sample = {1, 3, 5, -6};
  IntervalAddition<long long> tree(
      sample.begin(), sample.end(),
      [](long long x, long long y) { return min(x, y); },
      [](long long x, long long y) { return x + y; }, LLONG_MAX, 0ll);
  int n = 4;
  vector<long long> excepted = {1, 3, 5, -6};
  for (int i = 0; i < n; ++i)
    ASSERT_EQ(tree.get_min(i, i), excepted[i]);
  tree.add(1, 1, 3);
  excepted = {1, 4, 6, -5};
  for (int i = 0; i < n; ++i)
    ASSERT_EQ(tree.get_min(i, i), excepted[i]);
  tree.add(1, 0, 2);
  excepted = {2, 5, 7, -5};
  for (int i = 0; i < n; ++i)
    ASSERT_EQ(tree.get_min(i, i), excepted[i]);
  ASSERT_EQ(tree.get_min(0, n - 1), -5);
  ASSERT_ANY_THROW(tree.get_min(0, n));
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
