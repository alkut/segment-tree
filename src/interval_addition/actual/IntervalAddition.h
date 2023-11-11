#ifndef SEGMENT_TREE_INTERVALADDITION_H
#define SEGMENT_TREE_INTERVALADDITION_H

#include "IntervalAddition-fwd.h"

template <class key_t, class operation1_t, class operation2_t>
template <class forward_iterator>
IntervalAddition<key_t, operation1_t, operation2_t>::IntervalAddition(
    forward_iterator first, forward_iterator last,
    const operation1_t &operation1, const operation2_t &operation2,
    const key_t &neutral1, const key_t &neutral2)
    : operation1(operation1), operation2(operation2), neutral1(neutral1),
      initial_size(std::distance(first, last)) {
  expanded_size = 1;
  while (expanded_size < initial_size)
    expanded_size *= 2;
  body.resize(2 * expanded_size);
  std::size_t shift = expanded_size;
  expanded_size *= 2;
  for (std::size_t i = 0; i < initial_size; ++i)
    body[i + shift] = {*(first++), neutral2};
  for (std::size_t i = initial_size + shift; i < body.size(); ++i)
    body[i] = {neutral1, neutral2};
  for (std::size_t i = shift - 1; i > 0; --i)
    body[i] = {operation1(body[2 * i].first, body[2 * i + 1].first), neutral2};
}

template <class key_t, class operation1_t, class operation2_t>
void IntervalAddition<key_t, operation1_t, operation2_t>::add(
    const key_t &value, std::size_t left, std::size_t right) {
  validate_boundaries(left, right);
  std::vector<std::size_t> need_update;
  add(1, value, 0, body.size() / 2 - 1, left, right, need_update);
  for (const auto &it : need_update)
    update(it);
}

template <class key_t, class operation1_t, class operation2_t>
key_t IntervalAddition<key_t, operation1_t, operation2_t>::get_min(
    std::size_t left, std::size_t right) const {
  validate_boundaries(left, right);
  return get_min(1, 0, body.size() / 2 - 1, left, right);
}

template <class key_t, class operation1_t, class operation2_t>
void IntervalAddition<key_t, operation1_t, operation2_t>::update(
    std::size_t root) {
  while (root) {
    root /= 2;
    if (root)
      body[root].first = operation1(
          operation2(body[2 * root].second, body[2 * root].first),
          operation2(body[2 * root + 1].second, body[2 * root + 1].first));
  }
}

template <class key_t, class operation1_t, class operation2_t>
void IntervalAddition<key_t, operation1_t, operation2_t>::validate_boundaries(
    std::size_t left, std::size_t right) const {
  if (left > right)
    throw std::invalid_argument("left boundary more than right");
  if (right >= initial_size)
    throw std::out_of_range("right boundary is out of range");
}

template <class key_t, class operation1_t, class operation2_t>
key_t IntervalAddition<key_t, operation1_t, operation2_t>::get_min(
    std::size_t root, std::size_t v_left, std::size_t v_right, std::size_t left,
    std::size_t right) const {
  if (v_right < left || v_left > right)
    return neutral1;
  if (left <= v_left && v_right <= right)
    return body[root].first + body[root].second;
  auto border = (v_left + v_right) / 2;
  return operation2(
      operation1(get_min(2 * root, v_left, border, left, right),
                 get_min(2 * root + 1, border + 1, v_right, left, right)),
      body[root].second);
}

template <class key_t, class operation1_t, class operation2_t>
void IntervalAddition<key_t, operation1_t, operation2_t>::add(
    std::size_t root, key_t value, std::size_t v_left, std::size_t v_right,
    std::size_t left, std::size_t right,
    std::vector<std::size_t> &need_update) {
  if (v_left > right || v_right < left)
    return;
  if (left <= v_left && v_right <= right) {
    body[root].second = operation2(body[root].second, value);
    need_update.push_back(root);
    return;
  }
  auto border = (v_left + v_right) / 2;
  add(2 * root, value, v_left, border, left, right, need_update);
  add(2 * root + 1, value, border + 1, v_right, left, right, need_update);
}

#endif // SEGMENT_TREE_INTERVALADDITION_H
