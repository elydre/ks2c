#include "ks.h"

void print(int x) {
    cout << x;
}

void printn(int x) {
    cout << x << endl;
}

void printn(string x) {
    cout << x << endl;
}

int input(string prompt) {
    int x;
    cout << prompt;
    cin >> x;
    return x;
}

bool rev(int x) {
    return !x;
}

int mul(int x, int y) {
    return x * y;
}

int edv(int x, int y) {
    return x / y;
}

int add(int x, int y) {
    return x + y;
}

int sub(int x, int y) {
    return x - y;
}

int eql(int x, int y) {
    return x == y;
}

int neq(int x, int y) {
    return x != y;
}

int sup(int x, int y) {
    return x > y;
}

int inf(int x, int y) {
    return x < y;
}

int mod(int x, int y) {
    return x % y;
}
