#ifndef SEGMENT_TREE_INTERVALADDITION_FWD_H
#define SEGMENT_TREE_INTERVALADDITION_FWD_H

#include <functional>
#include <stdexcept>
#include <vector>

template <
    class key_t,
    class operation1_t = std::function<key_t(const key_t &, const key_t &)>,
    class operation2_t = std::function<key_t(const key_t &, const key_t &)>>
struct IntervalAddition {
  template <class forward_iterator>
  explicit IntervalAddition(forward_iterator first, forward_iterator last,
                            const operation1_t &operation1 = std::min<key_t>(),
                            const operation2_t &operation2 = std::plus<key_t>(),
                            const key_t &neutral1 = key_t(),
                            const key_t &neutral2 = key_t());

  void add(const key_t &value, std::size_t left, std::size_t right);
  key_t get_min(std::size_t left, std::size_t right) const;
  void update(std::size_t root);

private:
  void validate_boundaries(std::size_t left, std::size_t right) const;
  key_t get_min(std::size_t root, std::size_t v_left, std::size_t v_right,
                std::size_t left, std::size_t right) const;
  void add(std::size_t root, key_t value, std::size_t v_left,
           std::size_t v_right, std::size_t left, std::size_t right,
           std::vector<std::size_t> &need_update);

  std::vector<std::pair<key_t, key_t>> body;
  operation1_t operation1;
  operation2_t operation2;
  key_t neutral1;
  std::size_t initial_size;
  std::size_t expanded_size;
};

#endif // SEGMENT_TREE_INTERVALADDITION_FWD_H
