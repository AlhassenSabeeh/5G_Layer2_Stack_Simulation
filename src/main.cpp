#include <iostream>
#include <vector>
#include "../include/packet.h"
#include "../include/pdcp.h"

int main() {
    // --- STAGE 1: Generate Packet ---
    Packet p = generatePacket(1, 30);
    printPacket(p);

    // --- STAGE 2: PDCP Uplink ---
    std::cout << "\n[System] Passing Packet to PDCP..." << std::endl;
    
    // 1. Integrity
    int maci = generateMACI(p.data);
    
    // 2. Encryption (Convert string to bytes first)
    std::vector<uint8_t> dataBytes(p.data.begin(), p.data.end());
    std::vector<uint8_t> key = {0xAA}; // Simplified key from guidelines
    
    std::vector<uint8_t> encrypted = pdcp_encrypt(dataBytes, 0, 1, UPLINK, key);

    std::cout << "[PDCP] Encryption Complete. MAC-I: " << maci << std::endl;
    return 0;
}