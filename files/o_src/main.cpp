#include "ks.h"

int pairz(int number) {
    return eql(mod(number, 2), 0);
}

int main() {
    while (1) {
        printn(pairz(input("number: ")));
    }
}
