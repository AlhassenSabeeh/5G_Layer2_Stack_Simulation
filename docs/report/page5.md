# Page 5: User Manual & Project Conclusion

## 5.1 Target System Configuration (Section 2)

The 5G NR Layer 2 Simulator is designed for cross-platform compatibility with a focus on high-performance C++ execution. The following environment was used for development and verification:

*   **Operating System**: Windows 10/11 (PowerShell 7+)
*   **Compiler**: GCC/G++ v11.0 or higher (MinGW-w64)
*   **Build Tool**: Manual CLI integration for maximum transparency.

## 5.2 Installation and Setup

To deploy the project from the version control system, execute the following commands in a terminal:

```bash
# Clone the official repository
git clone https://github.com/AlhassenSabeeh/5G_Layer2_Stack_Simulation.git

# Navigate to the workspace
cd 5G_Layer2_Stack_Simulation
```

## 5.3 Execution Guide (The "Golden Command")

To compile all protocol sublayers (Packet, PDCP, RLC, MAC) and run the integrated simulation with the performance profiler, use the optimized build string:

```powershell
g++ -I./include src/*.cpp -o 5G_Sim; if ($?) { .\5G_Sim }
```

## 5.4 Expected Output Verification

Upon successful execution, the system provides:

*   **Functional Trace**: Real-time logs of encryption, segmentation, and TB generation.
*   **Loopback Result**: A "Bit-Perfect Recovery" confirmation, verifying that the Downlink output matches the Uplink input exactly.
*   **Profiling Table**: Average processing delays for 30B, 100B, and 500B packets.

## 5.5 Final Conclusion

This project successfully demonstrates the feasibility of a modular 5G NR Layer 2 User-Plane implementation. By strictly adhering to 3GPP 38-series logic, our group developed a system that is both functionally correct and computationally efficient. The performance profiling confirms that the stack is capable of handling varying traffic loads with minimal latency, providing a solid foundation for further research into 5G protocol optimization.


