#include <cassert>
#include <cstdint>
#include <cstdio>

constexpr size_t min_subdiv = 20;
constexpr bool print_each_permu = false;

// 0 - Rest
// 1 - Start note
// 2 - Continue note
int8_t rhythm[min_subdiv]{};

// void next_permu() {
//     assert(min_subdiv > 0);
//     rhythm[0]++;
//     for (size_t i{}; i < min_subdiv; i++) {
//         assert(rhythm[i] >= 0 && rhythm[i] <= 3);
//         if (rhythm[i] == 3) {
//             rhythm[i] = 0;
//             rhythm[i + 1]++;
//         }
//     }
// }

bool is_final_permu() {
    if (rhythm[min_subdiv - 1] != 1) {
        return false;
    }
    for (size_t i{0}; i < min_subdiv - 1; i++) {
        if (rhythm[i] != 2) {
            return false;
        }
    }
    return true;
}

bool permu_is_valid() {
    bool note_started = false;
    for (size_t i{min_subdiv}; i-- > 0;) {
        if (rhythm[i] == 1) {
            note_started = true;
        } else if (rhythm[i] == 2 && !note_started) {
            return false;
        } else if (rhythm[i] == 0) {
            note_started = false;
        }
    }
    return true;
}

void next_valid_permu() {
    // assert(min_subdiv > 0);
    rhythm[0]++;
    for (size_t i{}; i < min_subdiv; i++) {
        // assert(rhythm[i] >= 0 && rhythm[i] <= 3);
        if (rhythm[i] == 3) {
            rhythm[i] = 0;
            rhythm[i + 1]++;
        }
    }

    // Check for 0 followed by 2:
    for (size_t i{min_subdiv}; i-- > 1;) {
        if (rhythm[i] == 0 && rhythm[i - 1] == 2) {
            rhythm[i] = 1;
            rhythm[i - 1] = 0;
            break;
        }
    }
}

void print_permu() {
    for (size_t i{min_subdiv}; i-- > 0;) {
        printf("%d", rhythm[i]);
    }
    printf("\n");
}

int main() {
    long long count{};
    while (true) {
        // if (permu_is_valid()) {
        //     if constexpr (print_each_permu) {
        //         printf("Valid:   ");
        //         print_permu();
        //     }
        //     count++;
        // } else if constexpr (print_each_permu) {
        //     printf("Invalid: ");
        //     print_permu();
        // }
        count++;
        next_valid_permu();
        if (is_final_permu()) {
            printf("Final:   ");
            print_permu();
            count++;
            break;
        }
    }
    printf("\nFinal result: %lld possible rhythms\n", count);
    return 0;
}
