#pragma once

#include <iostream>
#include <math.h>

using namespace std;

// fcm.cpp
int f_cout(int x);
int f_print(int x);

int f_input(string prompt);

void f_cout(string x);
void f_print(string x);

bool f_not(int x);
bool f_eql(int x, int y);
bool f_neq(int x, int y);
bool f_sup(int x, int y);
bool f_inf(int x, int y);
bool f_and(int x, int y);
bool f_or(int x, int y);

int f_mul(int x, int y);
int f_edv(int x, int y);
int f_add(int x, int y);
int f_sub(int x, int y);
int f_mod(int x, int y);
