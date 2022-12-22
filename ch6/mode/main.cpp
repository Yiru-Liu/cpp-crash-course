#include <cstdio>
#include <stdexcept>
#include <algorithm>

int mode(const int *values, size_t length) {
    if (length == 1) return values[0];

    int *sorted_values = new int[length];
    for (size_t i = 0; i < length; i++) {
        sorted_values[i] = values[i];
    }
    std::sort(sorted_values, sorted_values + length);

    int mode{};
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

    printf("num_modes: %d\n", num_modes);
    if(num_modes != 1) {
        return 0;
    }

    return mode;
}

int main() {
    int arr[]{1, 2, 3, 4, 5};
    auto result = mode(arr, sizeof(arr)/ sizeof(arr[0]));
    printf("%d\n", result);
}