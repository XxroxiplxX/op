//
// Created by piotr on 5/17/2022.
//

#include "ClearFrame.h"

ClearFrame::ClearFrame(string ciphertext) {
    this->bits = unbuild(ciphertext);
    if (mod2div(this->bits, "1101") == "000") {
        this->bits = trim_remainder(this->bits);
        this->crack = false;
    } else {
        this->bits = ":(((((";
        this->crack = true;
    }
}
string ClearFrame::unbuild(string ciphertext) {
    ciphertext.erase(0, 8);
    ciphertext.erase(ciphertext.length() - 8, 8);
    int one_counter = 0;
    for (int i = 0; i < ciphertext.length(); i++) {
        if (one_counter == 5) {
            ciphertext.erase(i, 1);
            one_counter = 0;
        }
        if (ciphertext[i] == '1') {
            one_counter++;
        }
    }
    return ciphertext;
}

string ClearFrame::mod2div(string divident, string divisor) {
    // Number of bits to be XORed at a time.
    int pick = divisor.length();

    // Slicing the divident to appropriate
    // length for particular step
    string tmp = divident.substr(0, pick);

    int n = divident.length();

    while (pick < n)
    {
        if (tmp[0] == '1')

            // Replace the divident by the result
            // of XOR and pull 1 bit down
            tmp = xor1(divisor, tmp) + divident[pick];
        else

            // If leftmost bit is '0'.
            // If the leftmost bit of the dividend (or the
            // part used in each step) is 0, the step cannot
            // use the regular divisor; we need to use an
            // all-0s divisor.
            tmp = xor1(std::string(pick, '0'), tmp) +
                  divident[pick];

        // Increment pick to move further
        pick += 1;
    }

    // For the last n bits, we have to carry it out
    // normally as increased value of pick will cause
    // Index Out of Bounds.
    if (tmp[0] == '1')
        tmp = xor1(divisor, tmp);
    else
        tmp = xor1(std::string(pick, '0'), tmp);

    return tmp;
}
string ClearFrame::xor1(string a, string b) {
    // Initialize result
    string result = "";

    int n = b.length();

    // Traverse all bits, if bits are
    // same, then XOR is 0, else 1
    for(int i = 1; i < n; i++)
    {
        if (a[i] == b[i])
            result += "0";
        else
            result += "1";
    }
    return result;
}

string ClearFrame::get_bits() {
    return this->bits;
}

string ClearFrame::trim_remainder(string ciphertext) {
    ciphertext.erase(ciphertext.length() - 3, 3);
    return ciphertext;
}
