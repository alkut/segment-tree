#ifndef SEGMENT_TREE_MOCKINTERVALADDITION_H
#define SEGMENT_TREE_MOCKINTERVALADDITION_H

#include "MockIntervalAddition-fwd.h"

template <class key_t, class operation1_t, class operation2_t>
template <class forward_iterator>
MockIntervalAddition<key_t, operation1_t, operation2_t>::MockIntervalAddition(
    forward_iterator first, forward_iterator last,
    const operation1_t &operation1, const operation2_t &operation2,
    const key_t &neutral1, [[maybe_unused]] const key_t &neutral2)
    : operation1(operation1), operation2(operation2), neutral1(neutral1),
      initial_size(std::distance(first, last)), body(first, last) {}

template <class key_t, class operation1_t, class operation2_t>
void MockIntervalAddition<key_t, operation1_t, operation2_t>::add(
    const key_t &value, std::size_t left, std::size_t right) {
  validate_boundaries(left, right);
  for (std::size_t i = left; i <= right; ++i) {
    body[i] = operation2(body[i], value);
  }
}

template <class key_t, class operation1_t, class operation2_t>
key_t MockIntervalAddition<key_t, operation1_t, operation2_t>::get_min(
    std::size_t left, std::size_t right) const {
  validate_boundaries(left, right);
  key_t ans = neutral1;
  for (size_t i = left; i <= right; ++i) {
    ans = operation1(ans, body[i]);
  }
  return ans;
}

template <class key_t, class operation1_t, class operation2_t>
void MockIntervalAddition<key_t, operation1_t,
                          operation2_t>::validate_boundaries(std::size_t left,
                                                             std::size_t right)
    const {
  if (left > right) {
    throw std::invalid_argument("left boundary more than right");
  }
  if (right >= initial_size) {
    throw std::out_of_range("right boundary is out of range");
  }
}

#endif // SEGMENT_TREE_MOCKINTERVALADDITION_H
