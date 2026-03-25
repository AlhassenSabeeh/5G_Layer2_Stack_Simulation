#include <iostream>
#include <vector>
#include "../include/packet.h"
#include "../include/pdcp.h"
#include "../include/rlc.h"
#include "../include/mac.h"

int main() {
    // --- STAGE 1 & 2: Generate & Encrypt ---
    Packet p = generatePacket(1, 30);
    std::vector<uint8_t> dataBytes(p.data.begin(), p.data.end());
    std::vector<uint8_t> encrypted = pdcp_encrypt(dataBytes, 0, 1, UPLINK, {0xAA});
    std::cout << "[System] Packet Encrypted." << std::endl;

    // --- STAGE 3: RLC Segmentation ---
    std::vector<RlcPdu> segments = rlc_segment(encrypted, 10);
    std::cout << "[System] RLC Segmented into " << segments.size() << " pieces." << std::endl;

    // --- STAGE 4: MAC Multiplexing (UPLINK) ---
    int max_tb_size = 100;
    std::string transportBlock = mac_uplink(segments, max_tb_size);
    std::cout << "\n[MAC Uplink] Transport Block Created:\n" << transportBlock << std::endl;

    // --- STAGE 4: MAC Demultiplexing (DOWNLINK) ---
    std::vector<std::string> extracted = mac_downlink(transportBlock);
    std::cout << "\n[MAC Downlink] Extracted " << extracted.size() << " segments from TB." << std::endl;

    for(size_t i = 0; i < extracted.size(); i++) {
        std::cout << "  Extracted Segment " << i << " size: " << extracted[i].size() << " bytes." << std::endl;
    }

    std::cout << "\n[System] Integration of Stages 1-4 Complete!" << std::endl;
    return 0;
}