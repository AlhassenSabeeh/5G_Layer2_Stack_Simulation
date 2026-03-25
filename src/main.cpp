#include "../include/stack_integration.h"
#include "../include/profiler.h"
#include <iostream>

int main() {
    std::cout << "============================================" << std::endl;
    std::cout << "  5G NR LAYER 2 PERFORMANCE ANALYSIS TEST  " << std::endl;
    std::cout << "============================================" << std::endl;

    // Test 1: Small Packet (Standard IP Control/Keep-alive)
    std::cout << "\nTEST A: 30 Byte Packets" << std::endl;
    run_performance_test(1000, 30);

    // Test 2: Medium Packet (Small Data Segment)
    std::cout << "\nTEST B: 100 Byte Packets" << std::endl;
    run_performance_test(1000, 100);

    // Test 3: Large Packet (Video/File Transfer segment)
    std::cout << "\nTEST C: 500 Byte Packets" << std::endl;
    run_performance_test(1000, 500);

    std::cout << "\n[System] All profiling tests complete. Data ready for report." << std::endl;
    return 0;
}