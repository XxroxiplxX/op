//
// Created by piotr on 5/17/2022.
//

#include "Frame.h"
#include <string>
#include <cmath>
#include <iostream>

using namespace std;
Frame::Frame(const string bits) {

    this->end_begin = "01111110";
    //this->framebits = end_begin + build_frame(bits) + end_begin;
    this->generator = "1101";
    this->framebits = build_frame(encodeData(bits, generator), this->end_begin);
    //this->framebits = encodeData(bits, generator);
    //cout << mod2div(this->generator, encodeData(bits, generator));
    //cout << encodeData(bits, generator) << endl;
    //cout << mod2div("1001001111110100", this->generator) << endl;

}

string Frame::build_frame(string bits, string end_begin) {
    int one_counter = 0;
    bool frame_warn = false;
    string output = end_begin;
    for (auto iterator : bits) {
        if (iterator == '0') {
            frame_warn = true;
            output = output + iterator;
            one_counter = 0;
            //cout << "zero" << endl;
        } else if (frame_warn and iterator == '1') {
            if (one_counter == 5) {
                output = output + "01";
                one_counter = 0;
                frame_warn = false;
                //cout << "rozpycham" << endl;
            } else {    //1 ale nie przerywamuy ciagu
                output = output + iterator;
                one_counter++;
                //cout << "1 w podekrzanym ciagu, counter = " << one_counter << endl;
            }
        } else {    //1 ale nie ma zagrozenia podrobienia znacznika
            output = output + iterator;
            //cout << "niepodejrzana 1" << endl;
        }
    }
    output = output + end_begin;
    return output;
}

string Frame::get_framebits() {
    return this->framebits;
}

string Frame::xor1(string a, string b) {
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

string Frame::encodeData(string data, string key) {
    cout << "data to encode: " << data << endl;
    int l_key = key.length();

    // Appends n-1 zeroes at end of data
    string appended_data = (data +
                            std::string(
                                    l_key - 1, '0'));

    string remainder = mod2div(appended_data, key);

    // Append remainder in the original data
    string codeword = data + remainder;
    cout << "encoded: " << codeword << endl;
    return codeword;
}

string Frame::mod2div(string divident, string divisor) {
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


