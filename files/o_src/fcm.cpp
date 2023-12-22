#include "ks.h"

// print and input

int f_cout(int x) {
    cout << x;
    return x;
}

int f_print(int x) {
    cout << x << endl;
    return x;
}

int f_input(string prompt) {
    int x;
    cout << prompt;
    cin >> x;
    return x;
}

void f_cout(string x) {
    cout << x;
}

void f_print(string x) {
    cout << x << endl;
}

// boolean

bool f_not(int x) {
    return !x;
}

bool f_eql(int x, int y) {
    return x == y;
}

bool f_neq(int x, int y) {
    return x != y;
}

bool f_sup(int x, int y) {
    return x > y;
}

bool f_inf(int x, int y) {
    return x < y;
}

bool f_and(int x, int y) {
    return x && y;
}

bool f_or(int x, int y) {
    return x || y;
}

// calculation

int f_mul(int x, int y) {
    return x * y;
}

int f_edv(int x, int y) {
    return x / y;
}

int f_add(int x, int y) {
    return x + y;
}

int f_sub(int x, int y) {
    return x - y;
}

int f_mod(int x, int y) {
    return x % y;
}
