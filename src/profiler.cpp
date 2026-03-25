#include "../include/profiler.h"
#include "../include/packet.h"
#include "../include/pdcp.h"
#include "../include/rlc.h"
#include "../include/mac.h"
#include <iostream>
#include <vector>
#include <chrono>

void run_performance_test(int iterations, int packetSize) {
    std::cout << "\n[Stage 6] Starting Performance Profiling..." << std::endl;

    double total_pdcp = 0, total_rlc = 0, total_mac = 0;

    for (int i = 0; i < iterations; i++) {
        // Prepare Data
        Packet p = generatePacket(i, packetSize);
        std::vector<uint8_t> data(p.data.begin(), p.data.end());

        // 1. Profile PDCP
        auto s1 = std::chrono::high_resolution_clock::now();
        std::vector<uint8_t> enc = pdcp_encrypt(data, 0, 1, UPLINK, {0xAA});
        auto e1 = std::chrono::high_resolution_clock::now();
        total_pdcp += std::chrono::duration<double, std::micro>(e1 - s1).count();

        // 2. Profile RLC
        auto s2 = std::chrono::high_resolution_clock::now();
        std::vector<RlcPdu> segs = rlc_segment(enc, 10);
        auto e2 = std::chrono::high_resolution_clock::now();
        total_rlc += std::chrono::duration<double, std::micro>(e2 - s2).count();

        // 3. Profile MAC
        auto s3 = std::chrono::high_resolution_clock::now();
        mac_uplink(segs, 150);
        auto e3 = std::chrono::high_resolution_clock::now();
        total_mac += std::chrono::duration<double, std::micro>(e3 - s3).count();
    }

    // Output for Project Report Section 3d
    std::cout << "--- Average Execution Time per Packet (" << iterations << " runs) ---" << std::endl;
    std::cout << "PDCP Sublayer: " << total_pdcp / iterations << " us" << std::endl;
    std::cout << "RLC Sublayer:  " << total_rlc / iterations << " us" << std::endl;
    std::cout << "MAC Sublayer:  " << total_mac / iterations << " us" << std::endl;
    std::cout << "----------------------------------------------------------" << std::endl;
}