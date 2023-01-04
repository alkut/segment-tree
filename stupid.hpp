#include <functional>
#include <vector>
#include <stdexcept>

template<class key_t, class operation1_t = std::function<key_t(const key_t&, const key_t&)>
, class operation2_t = std::function<key_t(const key_t&, const key_t&)>>
struct stupid {
    template<class forward_iterator>
    explicit stupid(forward_iterator first, forward_iterator last, const operation1_t& operation1 = std::less<key_t>(),
                    const operation2_t& operation2 = std::plus<key_t>(), const key_t& neutral1 = key_t()
            , const key_t& neutral2 = key_t()) : operation1(operation1), operation2(operation2)
            , neutral1(neutral1), initial_size(std::distance(first, last)), body(first, last) {}

    void add(key_t value, std::size_t left, std::size_t right) {
        validate_boundaries(left, right);
        for (std::size_t i = left; i <= right; ++i)
            body[i] = operation2(body[i], value);
    }

    key_t get_min(std::size_t left, std::size_t right) const {
        validate_boundaries(left, right);
        key_t ans = neutral1;
        for (size_t i = left; i <= right; ++i)
            ans = operation1(ans, body[i]);
        return ans;
    }

private:
    std::vector<key_t> body;
    operation1_t operation1;
    operation2_t operation2;
    key_t neutral1;
    std::size_t initial_size;

    void validate_boundaries(std::size_t left, std::size_t right) const {
        if (left > right)
            throw std::invalid_argument("left boundary more than right");
        if (right >= initial_size)
            throw std::out_of_range("right boundary is out of range");
    }
};