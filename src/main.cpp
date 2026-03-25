#include "../include/stack_integration.h"
#include <iostream>

int main() {
    std::cout << "==========================================" << std::endl;
    std::cout << "  5G NR LAYER 2 STACK SIMULATOR (SYSTEM)  " << std::endl;
    std::cout << "==========================================" << std::endl;

    // Calling the Orchestrator for Stage 5 Integration
    run_full_stack_simulation(1, 30);

    return 0;
}