#include <iostream>
#include <vector>
#include "../include/packet.h"
#include "../include/pdcp.h"
#include "../include/rlc.h"

int main() {
    // Stage 1: Generate Packet
    Packet p = generatePacket(1, 30);
    printPacket(p);

    // Stage 2: PDCP (Encryption)
    std::vector<uint8_t> dataBytes(p.data.begin(), p.data.end());
    std::vector<uint8_t> key = {0xAA};
    std::vector<uint8_t> encrypted = pdcp_encrypt(dataBytes, 0, 1, UPLINK, key);
    std::cout << "\n[PDCP] Encryption Complete. MAC-I: " << generateMACI(p.data) << std::endl;

    // Stage 3: RLC (Segmentation)
    uint16_t maxRlcSize = 10; // This will split our 30-byte packet into 3 pieces
    RLC_Process(encrypted, UPLINK, maxRlcSize);

    std::cout << "\n[System] Simulation Finished Successfully." << std::endl;
    return 0;
}