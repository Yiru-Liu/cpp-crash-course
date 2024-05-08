#include <unistd.h>

#include <cstdio>
#include <cstdlib>
#include <stdexcept>

char* get_program_name(char* fullpath) {
    auto* program_name{fullpath};
    for (auto* current_index{fullpath}; *current_index; current_index++) {
        if (*current_index == '\\') program_name = current_index + 1;
    }
    return program_name;
}

int main(int argc, char** argv) {
    char input_file[261]{};
    long int out_radix = 27;
    bool print_debug = true;
    bool print_nums = false;
    bool print_progress = true;
    int opt;
    while ((opt = getopt(argc, argv, "i:r:dNp")) != -1) {
        switch (opt) {
            case 'i': {
                strcpy(input_file, optarg);
                printf("Input file: %s\n", input_file);
            } break;
            case 'r': {
                out_radix = atoi(optarg);
                if (out_radix < 2 || out_radix > 62)
                    throw std::runtime_error{
                        "Out radix must be in the range 2..62."};
                printf("Out radix set to %d.\n", out_radix);
            } break;
            case 'd': {
                print_debug = false;
                printf("Print debug disabled.\n");
            } break;
            case 'N': {
                print_nums = true;
                printf("Print nums enabled.\n");
            } break;
            case 'p': {
                print_progress = false;
                printf("Print progress disabled.\n");
            } break;
            default: {
                fprintf(stderr, "Usage: %s [-d] [file...]\n",
                        get_program_name(argv[0]));
            }
        }
    }
    if (input_file[0] == '\0') {
        throw std::runtime_error{
            "Input file not specified. "
            "Please specify the path to the input file using the -i flag."};
    }

    return 0;
}
