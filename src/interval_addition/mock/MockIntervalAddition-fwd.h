#ifndef SEGMENT_TREE_MOCKINTERVALADDITION_FWD_H
#define SEGMENT_TREE_MOCKINTERVALADDITION_FWD_H

#include <functional>
#include <vector>

template <
    class key_t,
    class operation1_t = std::function<key_t(const key_t &, const key_t &)>,
    class operation2_t = std::function<key_t(const key_t &, const key_t &)>>
struct MockIntervalAddition {
  template <class forward_iterator>
  explicit MockIntervalAddition(
      forward_iterator first, forward_iterator last,
      const operation1_t &operation1 = std::less<key_t>(),
      const operation2_t &operation2 = std::plus<key_t>(),
      const key_t &neutral1 = key_t(),
      [[maybe_unused]] const key_t &neutral2 = key_t());

  void add(const key_t &value, std::size_t left, std::size_t right);
  key_t get_min(std::size_t left, std::size_t right) const;

private:
  void validate_boundaries(std::size_t left, std::size_t right) const;

  std::vector<key_t> body;
  operation1_t operation1;
  operation2_t operation2;
  key_t neutral1;
  std::size_t initial_size;
};

#endif // SEGMENT_TREE_MOCKINTERVALADDITION_FWD_H
