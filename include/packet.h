#ifndef PACKET_H
#define PACKET_H

#include <string>
using namespace std;

struct Packet {
    int id;
    int size;
    string data;
};

Packet generatePacket(int id, int size);
void printPacket(Packet p);

#endif
