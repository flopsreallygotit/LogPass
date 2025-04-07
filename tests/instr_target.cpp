#include <iostream>

void foo() { std::cout << "f\n"; }

void bar(int a) {
    if (a > 0)
        std::cout << "b\n";
    else
        bar(a + 1);
}

int main() { 
    foo();
    bar(7);

    return 0; 
}
