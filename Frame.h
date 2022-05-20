//
// Created by piotr on 5/17/2022.
//
#include <string>
#include <assert.h>
#ifndef OP_RAMKA_H
#define OP_RAMKA_H

using namespace std;
class Frame {
    int size_of_frame;
    string end_begin;
    string framebits;
    string generator;


public:
    explicit Frame(string bits);
    string get_framebits();

private:
    static string build_frame(string bits, string end_begin);
    static string xor1(string a, string b);
    static string mod2div(string divident, string divisor);
    static string encodeData(string data, string key);
};


#endif //OP_RAMKA_H
