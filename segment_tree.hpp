#include <functional>
#include <vector>
#include <stdexcept>

template<class key_t, class operation1_t = std::function<key_t(const key_t&, const key_t&)>
        , class operation2_t = std::function<key_t(const key_t&, const key_t&)>>
struct segment_tree {
    explicit segment_tree(const std::vector<key_t>& x, const operation1_t& operation1 = std::min<key_t>(),
            const operation2_t& operation2 = std::plus<key_t>(), const key_t& neutral1 = key_t()
                    , const key_t& neutral2 = key_t()) : operation1(operation1), operation2(operation2)
                    , neutral1(neutral1), initial_size(x.size()) {
        expanded_size = 1;
        while (expanded_size < initial_size)
            expanded_size *= 2;
        body.resize(2 * expanded_size);
        std::size_t shift = expanded_size;
        expanded_size *= 2;
        for (std::size_t i = 0; i < x.size(); ++i)
            body[i + shift] = {x[i], neutral2};
        for (std::size_t i = x.size() + shift; i < body.size(); ++i)
            body[i] = {neutral1, neutral2};
        for (std::size_t i = shift - 1; i > 0; --i)
            body[i] = min(body[2 * i], body[2 * i + 1]);
    }

    void add(key_t value, std::size_t left, std::size_t right) {
        validate_boundaries(left, right);
        std::vector<std::size_t> need_update;
        add(1, value, 0, body.size() / 2 - 1, left, right, need_update);
        for (const auto& it: need_update)
            update(it);
    }

    key_t get_min(std::size_t left, std::size_t right) const {
        validate_boundaries(left, right);
        return get_min(1, 0, body.size() / 2 - 1, left, right);
    }

    void update(std::size_t root) {
        while (root) {
            root /= 2;
            if (root)
                body[root].first = operation1(operation2(body[2 * root].second, body[2 * root].first), operation2(body[2 * root + 1].second, body[2 * root + 1].first));
        }
    }
private:
    std::vector<std::pair<key_t, key_t>> body;
    operation1_t operation1;
    operation2_t operation2;
    key_t neutral1;
    std::size_t initial_size;
    std::size_t expanded_size;

    void validate_boundaries(std::size_t left, std::size_t right) const{
        if (left > right)
            throw std::invalid_argument("left boundary more than right");
        if (right >= initial_size)
            throw std::out_of_range("right boundary is out of range");
    }

    key_t get_min(std::size_t root, std::size_t v_left, std::size_t v_right, std::size_t left, std::size_t right) const {
        if (v_right < left || v_left > right)
            return neutral1;
        if (left <= v_left && v_right <= right)
            return body[root].first + body[root].second;
        auto border = (v_left + v_right) / 2;
        return operation2(operation1(get_min(2 * root, v_left, border, left, right), get_min(2 * root + 1, border + 1, v_right, left, right)), body[root].second);
    }

    void add(std::size_t root, key_t value, std::size_t v_left, std::size_t v_right, std::size_t left, std::size_t right, std::vector<std::size_t>& need_update) {
        if (v_left > right || v_right < left) return;
        if (left <= v_left && v_right <= right) {
            body[root].second = operation2(body[root].second, value);
            need_update.push_back(root);
            return;
        }
        auto border = (v_left + v_right) / 2;
        add(2 * root, value, v_left, border, left, right, need_update);
        add(2 * root + 1, value, border + 1, v_right, left, right, need_update);
    }
};