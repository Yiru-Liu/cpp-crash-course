#include <cstdio>

char read_from(char* char_ptr, size_t char_len, size_t index) {
    if(index >= char_len) {
        return -1;
    }
    return char_ptr[index];
}

bool write_to(char* char_ptr, size_t char_len, size_t index, char char_to_write) {
    if(index >= char_len) {
        return false;
    }
    char_ptr[index] = char_to_write;
    return true;
}

int main() {
    char lower[] = "abc?e";
    char upper[] = "ABC?E";

    write_to(lower, sizeof(lower)/sizeof(lower[0]), 3, 'd');
    write_to(upper, sizeof(upper)/sizeof(upper[0]), 3, 'D');

    printf("Lower: ");
    for(size_t i = 0; i < sizeof(lower)/sizeof(lower[0]); i++) {
        printf("%c", read_from(lower, sizeof(lower)/sizeof(lower[0]), i));
    }

    printf("\nUpper: ");
    for(size_t i = 0; i < sizeof(upper)/sizeof(upper[0]); i++) {
        printf("%c", read_from(upper, sizeof(upper)/sizeof(upper[0]), i));
    }

    return 0;
}