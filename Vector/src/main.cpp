#include <cstddef>
#include <stdio.h>
#include "../include/vector.h"

Vector<int> test() {
    Vector<int> v2(12);

    printf("test");
    return v2;
}

int main() {
    Vector<int> v(5);
    Vector<int> v1{ v };
    Vector<int> v3{ test() };

    return 1;
}
