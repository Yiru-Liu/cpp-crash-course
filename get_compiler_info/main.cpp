// Code taken from https://youtu.be/Vj06cfj6LyI?t=70

#include <iostream>
#include <sstream>

std::string get_compiler_info() {
    std::stringstream str;

#if defined(__clang__)
    str << "clang " << __clang_major__ << '.' << __clang_patchlevel__;
#elif defined(__GNUC__) && !defined(__ICC)
    str << "gcc " << __GNUC__ << '.' << __GNUC_MINOR__ << '.' << __GNUC_PATCHLEVEL__;
#elif defined(_MSC_VER)
    str << "msvc " << _MSC_VER;
#elif defined(_ICC)
    str << "icc " << __VERSION__;
#endif

    return str.str();
}

int main() {
    std::cout << get_compiler_info() << std::endl;
}
