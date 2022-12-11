#include <cstdio>

enum class Operation {
    Add,
    Subtract,
    Multiply,
    Divide
};

struct Calculator {
    Calculator(Operation op) {
        operation = op;
    }

    int calculate(int a, int b) {
        int result{};
        switch (operation) {
            case Operation::Add: {
                result = a + b;
            } break;
            case Operation::Subtract: {
                result = a - b;
            } break;
            case Operation::Multiply: {
                result = a * b;
            } break;
            case Operation::Divide: {
                result = a / b;
            } break;
        }
        return result;
    }

    Operation operation;
};

int main() {
    int a{ 120 };
    int b{ 3 };

    Calculator adder{ Operation::Add };
    Calculator subtracter{ Operation::Subtract };
    Calculator multiplier{ Operation::Multiply };
    Calculator divider{ Operation::Divide };

    printf("a + b: %d\n", adder.calculate(a, b));
    printf("a - b: %d\n", subtracter.calculate(a, b));
    printf("a * b: %d\n", multiplier.calculate(a, b));
    printf("a / b: %d\n", divider.calculate(a, b));
}
