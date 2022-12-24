#include <cstdio>
#include <cstdint>
#include <cstring>
#include <algorithm>
#include <stdexcept>

class UnsignedBigInteger {
    size_t size;
    uint8_t *bytes;

    static char to_hex_digit(uint8_t half_byte) {
        if (half_byte <= 9) {
            return half_byte + '0';
        }
        if (half_byte <= 15) {
            return half_byte - 10 + 'A';
        }
        throw std::logic_error("Argument greater than 15.");
    }

    static uint8_t from_hex_digit(char hex) {
        if (hex >= '0' && hex <= '9') {
            return hex - '0';
        }
        if (hex >= 'A' && hex <= 'F') {
            return hex - 'A' + 10;
        }
        if (hex >= 'a' && hex <= 'f') {
            return hex - 'a' + 10;
        }
        throw std::logic_error("Invalid character.");
    }

    uint8_t get_digit_b256(size_t index) const {
        if (index >= size) {
            return 0;
        } else {
            return bytes[index];
        }
    }

public:
    UnsignedBigInteger(size_t size) : size{size} {
        bytes = new uint8_t[size]{};
    }

    UnsignedBigInteger(size_t size, uint64_t value) : size{size} {
        bytes = new uint8_t[size]{};
        for (int8_t i{}; i < 8; i++) {
            bytes[i] = value >> (i * 8);
        }
    }

    UnsignedBigInteger(const char *literal_string) {
        if (literal_string[0] == '0' && literal_string[1] == 'x') {
            size = (strlen(literal_string) - 1) / 2;
            bytes = new uint8_t[size];
            from_hex(literal_string);
        }
    }

    ~UnsignedBigInteger() {
        delete[] bytes;
    }

    void shrink() {
        size_t necessary_size = size;
        for (size_t i{size}; i > 0; i--) {
            if (bytes[i - 1] == 0) {
                necessary_size--;
            } else {
                break;
            }
        }
        auto *new_bytes = new uint8_t[necessary_size];
        for (size_t i{}; i < necessary_size; i++) {
            new_bytes[i] = bytes[i];
        }
        delete[] bytes;
        bytes = new_bytes;
        size = necessary_size;
    }

    void zero() {
        for (size_t i = 0; i < size; i++) {
            bytes[i] = 0;
        }
    }

    char *to_hex() {
        char *hex_string = new char[size * 2 + 1];
        for (size_t i = size; i > 0; i--) {
            hex_string[(size - i) * 2] = to_hex_digit(bytes[i - 1] >> 4);
            hex_string[(size - i) * 2 + 1] = to_hex_digit(bytes[i - 1] & 15);
        }
        hex_string[size * 2] = '\0';
        return hex_string;
    }

    void from_hex(const char *hex_string) {
        zero();
        size_t len{strlen(hex_string)};
        size_t string_i{};
        if (hex_string[0] == '0' && hex_string[1] == 'x') {
            len -= 2;
            string_i += 2;
        }
        if (len % 2 == 1) {
            bytes[len / 2] = from_hex_digit(hex_string[0]);
            string_i++;
        }
        for (size_t i{len / 2}; i > 0; i--) {
            bytes[i - 1] = (from_hex_digit(hex_string[string_i]) << 4) + from_hex_digit(hex_string[string_i + 1]);
            string_i += 2;
        }
    }

    UnsignedBigInteger operator+(const UnsignedBigInteger &other) const {
        size_t result_size{std::max(size, other.size) + 1};
        UnsignedBigInteger result{result_size};
        uint8_t overflow{};
        uint16_t sum16;
        for (size_t i{}; i < result_size; i++) {
            sum16 = get_digit_b256(i) + other.get_digit_b256(i) + overflow;
            result.bytes[i] = sum16;
            if (sum16 > 255) {
                overflow = 1;
            } else {
                overflow = 0;
            }
        }
        result.shrink();
        return result;
    }

    UnsignedBigInteger operator+(const uint64_t &other) const {
        UnsignedBigInteger o{8,other};
        return this->operator+(o);
    }
};

int main() {
    UnsignedBigInteger num1{"0x5E2DA078BE7A1BB9FEDE93E2FD3BACF2D6ABEFA9159A05D68348E8570BE93E5F"};
    char *num1str = num1.to_hex();
    printf("%s\n", num1str);
    delete[] num1str;
    UnsignedBigInteger num2{"0xF47FBCB7AE4191D7EE44F9BAE774C7C1296D9BD6487A77B2385657F62CCD9B12"};
    UnsignedBigInteger num3{"0xEFA6C8151D6907ADEB891FD49919A0CC43ECDD6CCB65EA5231049AB1AC3CC740"};
    UnsignedBigInteger sum = num1 + 2457004513404769234;
    char *result = sum.to_hex();
    printf("%s\n", result);
    delete[] result;
    return 0;
}
