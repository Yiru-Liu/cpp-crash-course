#include <cstdio>

int step_function(int x) {
    int response{ 0 };
    if(x > 0) {
        response = 1;
    } else if(x < 0) {
        response = -1;
    }
    return response;
}

int main() {
    int num1 = 42;
    int result1 = step_function(num1);

    int num2 = 0;
    int result2 = step_function(num2);

    int num3 = -0x7FFF;
    int result3 = step_function(num3);

    printf("Num1: %d, Step: %d\n", num1, result1);
    printf("Num2: %d, Step: %d\n", num2, result2);
    printf("Num3: %d, Step: %d\n", num3, result3);

    return 0;
}
