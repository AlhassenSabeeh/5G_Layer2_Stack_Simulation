# 5G Layer 2 Stack Simulation
This project implements a simplified 5G NR User-Plane protocol stack based on 3GPP 38-series specifications[cite: 238, 246].

## Team Assignments
* **Member 1**: Stage 1 - IP Dummy Packet Generator [cite: 7, 203]
* **Member 2**: Stage 2 - PDCP Layer [cite: 7, 203]
* **Member 3**: Stage 3 - RLC Layer [cite: 7, 203]
* **Member 4**: Stage 4 - MAC Layer [cite: 7, 203]
* **Member 5**: Stage 5 - Integration & Loopback [cite: 7, 203]
* **Member 6**: Stage 6 - Profiling & Performance [cite: 7, 203]
* **Member 7**: Stage 7 - Documentation (Manual & Report) [cite: 257, 259]

## Project Structure
* `/src`: Source code implementations (e.g., packet.cpp).
* `/include`: Header files and protocol definitions (e.g., packet.h).
* `/docs`: Project reports and user manuals[cite: 257, 259].
## How to Run
To compile and link all current stages (Stage 1 & 2), run the following command in your terminal:

```bash
g++ -I./include src/packet.cpp src/PDCP.cpp src/main.cpp -o 5G_Sim
./5G_Sim
