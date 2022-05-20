#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Frame.h"
#include "ClearFrame.h"
using namespace std;


int main() {
    ifstream odczyt("Z.txt");
    ofstream save("W.txt");
    string pakiet = "";
    int counter = 0;
    vector<Frame> kolekcja;
    string b;
    odczyt >> b;

    for (auto item : b) {
        //cout << item << endl;

        if (counter == 20) {
            //cout << pakiet << "aaaa" << endl;
            Frame frame = Frame(pakiet);
            kolekcja.push_back(frame);
            pakiet = item;
            counter = 0;
        } else {
            pakiet = pakiet += item;
            counter++;
        }
    }

    Frame frame = Frame(pakiet);
    kolekcja.push_back(frame);

    //cout << pakiet << endl;
    //cout << read_from_buffer(odczyt);
    //Frame frame("100100111110");
    //cout << frame.get_framebits() << endl;
    for (auto iterator : kolekcja) {
        save << iterator.get_framebits();
    }
    save.close();
    string tmp = kolekcja[0].get_framebits().erase(11, 1);
    ClearFrame clearFrame = ClearFrame(kolekcja[0].get_framebits());
    if (!clearFrame.crack) {
        cout << clearFrame.get_bits() << endl;
    }


    //ifstream read_ciphertext("W.txt");
    //ofstream save_copy("Zcopy.txt");


    //cout << unbuild("0111111001111101000000000000111101111110") << endl;


    return 0;
}
