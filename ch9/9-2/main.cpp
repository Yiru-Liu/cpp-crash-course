#include <cstdio>
#include <cstring>
#include <limits>
#include <stdexcept>

int main(int argc, char** argv) {
    if (argc <= 1) throw std::runtime_error{"Please provide arguments."};

    int num_arguments{argc - 1};
    auto* lengths = new size_t[num_arguments];
    int max{};
    int min{std::numeric_limits<int>::max()};
    for (int i{}; i < num_arguments; i++) {
        lengths[i] = strlen(argv[i + 1]);
        if (lengths[i] > max) max = lengths[i];
        if (lengths[i] < min) min = lengths[i];
    }

    auto* histogram = new int[max - min + 1]{};
    for (int i{}; i < num_arguments; i++) {
        histogram[lengths[i] - min]++;
    }

    for (int i{}; i <= max - min; i++) {
        printf("%d:\t", i + min);
        for (int j{}; j < histogram[i]; j++) {
            printf("*");
        }
        printf("\n");
    }

    delete[] histogram;
    delete[] lengths;

    return 0;
}