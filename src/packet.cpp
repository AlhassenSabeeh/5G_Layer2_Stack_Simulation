#include "../include/packet.h"
#include <iostream>
using namespace std;

Packet generatePacket(int id, int size) {
    Packet p;
    p.id = id;
    p.size = size;
    p.data = "";

    char firstChar = 'A' + (id - 1);
    for(int i = 0; i < 5 && i < size; i++) {
        p.data = p.data + firstChar;
    }

    for(int i = p.data.length(); i < size; i++) {
        char digit = '0' + ((i - 5) % 10);
        p.data = p.data + digit;
    }

    return p;
}

void printPacket(Packet p) {
    cout << "================================" << endl;
    cout << "Packet ID: " << p.id << endl;
    cout << "Size: " << p.size << " bytes" << endl;
    cout << "Data: " << p.data << endl;
    cout << "================================" << endl;
}
