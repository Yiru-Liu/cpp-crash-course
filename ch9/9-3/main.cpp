#include <cstdio>

template <typename Fn, typename In>
constexpr bool all(Fn function, In* input, size_t length) {
    for (size_t i{}; i < length; i++) {
        if (!function(input[i])) {
            return false;
        }
    }
    return true;
}

int main() {
    int data[]{100, 200, 300, 400, 500};
    size_t data_len = sizeof(data) / sizeof(data[0]);
    auto all_gt100 = all([](auto x) { return x < 300; }, data, data_len);
    printf("%d\n", all_gt100);
}
