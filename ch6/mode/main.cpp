#include <cstdio>
#include <stdexcept>
#include <concepts>

template<typename T>
concept Integer = std::is_integral<T>::value;

template<typename T>
concept Number = std::is_integral<T>::value || std::is_floating_point<T>::value;

template<Integer T>
T mode(const T *values, size_t length) {
    if (length == 1) return values[0];

    T *sorted_values = new T[length];
    for (size_t i = 0; i < length; i++) {
        sorted_values[i] = values[i];
    }
    std::sort(sorted_values, sorted_values + length);

    T mode{};
    int num_modes{};
    int max_counter{};
    int current_counter{1};

    for (size_t i = 1; i < length; i++) {
        if (sorted_values[i] == sorted_values[i-1]) {
            current_counter++;
        } else {
            if(current_counter > max_counter) {
                max_counter = current_counter;
                mode = sorted_values[i-1];
                num_modes = 1;
            } else if(current_counter == max_counter) {
                num_modes++;
            }
            current_counter = 1;
        }
    }
    if(current_counter > max_counter) {
        mode = sorted_values[length-1];
        num_modes = 1;
    } else if(current_counter == max_counter) {
        num_modes++;
    }

    delete[] sorted_values;

    if(num_modes != 1) {
        return 0;
    }

    return mode;
}

template<size_t Length, Number T>
T mean(T (arr)[Length]) {
    T result{};
    for(size_t i{}; i < Length; i++) {
        result += arr[i];
    }
    return result / Length;
}

int main() {
    double arr[]{1, 101};
    auto result = mean<2>(arr);
    printf("%f\n", result);
}