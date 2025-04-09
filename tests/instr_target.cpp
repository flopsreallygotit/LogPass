#include <cstdlib>
#include <iostream>

void foo() { std::cout << "f\n"; }

void bar(int a) {
    if (a > 0)
        std::cout << "b\n";
    else
        bar(a + 1);
}

int main(int argc, char *argv[]) { 
    foo();

    if (argc == 2)
        abort();

    bar(7);

    if (argc > 2)
        abort();

    return 0; 
}
