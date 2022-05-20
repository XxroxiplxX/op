//
// Created by piotr on 5/17/2022.
//

#ifndef OP_CLEARFRAME_H
#define OP_CLEARFRAME_H

#include <string>

using namespace std;
class ClearFrame {
    string bits;
public:
    bool crack;
    explicit ClearFrame(string ciphertext);
    string get_bits();

private:
    static string trim_remainder(string ciphertext);
    static string unbuild(string ciphertext);
    static string mod2div(string divident, string divisor);
    static string xor1(string a, string b);
};


#endif //OP_CLEARFRAME_H
