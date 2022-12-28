#include <cstdio>
#include <cstdlib>
#include <ctime>

constexpr int NUM_ARGUMENTS = 500;
constexpr int ARG_LENGTH_CENTER = 50;

char rand_char() {
    constexpr char chars[]{
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
        'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
        'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
        'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    constexpr int num_chars = sizeof(chars) / sizeof(char);
    return chars[rand() % num_chars];
}

int main() {
    srand(time(nullptr));
    for (int i{}; i < NUM_ARGUMENTS; i++) {
        for (int j{}; j < ARG_LENGTH_CENTER * 2; j++) {
            if (rand() % 2) {
                printf("%c", rand_char());
            }
        }
        printf(" ");
    }
}