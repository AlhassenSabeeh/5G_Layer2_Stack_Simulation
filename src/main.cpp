#include "../include/stack_integration.h"
#include "../include/profiler.h"
#include <iostream>

int main() {
    std::cout << "5G NR Layer 2 Stack Simulation" << std::endl;

    // Execute Stage 5 (Functional Loopback)
    run_full_stack_simulation(1, 30);

    // Execute Stage 6 (Performance Analysis)
    run_performance_test(1000, 30);

    return 0;
}