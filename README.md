# 5G Layer 2 Stack Simulation
This project implements a simplified 5G NR User-Plane protocol stack based on 3GPP 38-series specifications.

## Team Assignments
* **Member 1**: Stage 1 - IP Dummy Packet Generator
* **Member 2**: Stage 2 - PDCP Layer
* **Member 3**: Stage 3 - RLC Layer
* **Member 4**: Stage 4 - MAC Layer
* **Member 5**: Stage 5 - Integration & Loopback
* **Member 6**: Stage 6 - Profiling & Performance
* **Member 7**: Stage 7 - Documentation (Manual & Report)

## Project Structure
* `/src`: Source code implementations (e.g., packet.cpp, PDCP.cpp, RLC.cpp).
* `/include`: Header files and protocol definitions (e.g., packet.h, pdcp.h, rlc.h).
* `/docs`: Project reports and user manuals.

## How to Run
To compile and link all currently integrated stages (Stage 1, 2, & 3), run the following command in your terminal:

```bash
# Automated build for all layers
g++ -I./include src/*.cpp -o 5G_Sim; if ($?) { .\5G_Sim }
