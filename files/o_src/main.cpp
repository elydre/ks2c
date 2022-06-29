#include "ks.h"

int main() {
    int max = 0;
    int n = 1;
    for (int i = 0; i < 500000; i++) {
        n = add(n, 2);
        int j = 1;
        int prime = 1;
        max = sqrt(n);
        for (int i = 0; i < edv(max, 2); i++) {
            j = add(j, 2);
            if (not(mod(n, j))) {
                prime = 0;
                break;
            }
        }
    }
}
