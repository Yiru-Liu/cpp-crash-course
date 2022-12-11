#include <cstdio>

struct Element {
    Element* next{};
    Element* previous{};

    Element(const char pf0, const char pf1, const short operating_number) {
        prefix[0] = pf0;
        prefix[1] = pf1;
        this->operating_number = operating_number;
    }

    void insert_after(Element* new_element) {
        if(next) {
            next->previous = new_element;
            new_element->next = next;
        }
        new_element->previous = this;
        next = new_element;
    }

    void insert_before(Element* new_element) {
        if(previous) {
            previous->next = new_element;
            new_element->previous = previous;
        }
        new_element->next = this;
        previous = new_element;
    }

    void print() const {
        printf("%c%c-%d\n", prefix[0], prefix[1], operating_number);
    }

    char prefix[2]{};
    short operating_number{};
};


int main() {
    Element trooper1{'T', 'K', 421},
            trooper2{'F', 'N', 2187},
            trooper3{'L', 'S', 5};

    trooper1.insert_after(&trooper3);
    trooper3.insert_before(&trooper2);

    printf("Traversing forward:\n");
    for(Element *trooper = &trooper1; trooper; trooper = trooper->next) {
        trooper->print();
    }

    printf("\nTraversing backward:\n");
    for(Element *trooper = &trooper3; trooper; trooper = trooper->previous) {
        trooper->print();
    }

    return 0;
}
