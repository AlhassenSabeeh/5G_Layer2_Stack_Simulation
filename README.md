# 5G NR Layer 2 Protocol Stack Simulation

This project implements a high-performance User Plane (U-Plane) 5G NR Layer 2 stack for simulation and analysis [1] [3] [11].

## 1. Project Overview

This software simulates the packet flow from IP Generation to MAC Transport Block creation, featuring both Uplink and Downlink paths with a focus on data integrity and security [4] [13].

## 2. Installation and Execution (User Manual)

To run this project on a target system (Windows/Linux/MacOS), follow these steps [22] [23] [27]:

### Step 1: Clone the Repository

```bash
git clone https://github.com/AlhassenSabeeh/5G_Layer2_Stack_Simulation.git
cd 5G_Layer2_Stack_Simulation
```

### Step 2: The "Golden Command"

Run the following PowerShell command to compile all sublayers and execute the full-stack simulation along with the performance profiler:

```powershell
g++ -I./include src/*.cpp -o 5G_Sim; if ($?) { .\5G_Sim }
```

## 3. Implemented Features

| Stage | Component | Description |
| :--- | :--- | :--- |
| **Stage 1** | **Packet** | IP Dummy Packet Generator with customizable size and content. |
| **Stage 2** | **PDCP** | Data encryption and integrity protection. |
| **Stage 3** | **RLC** | Dynamic data segmentation and SDU reassembly. |
| **Stage 4** | **MAC** | Multiplexing RLC PDUs into Transport Blocks with subheaders and padding. |
| **Stage 5** | **Loopback** | Full Uplink-to-Downlink data flow verification ("Bit-Perfect Recovery"). |
| **Stage 6** | **Profiling** | High-resolution performance analysis across varying packet sizes. |

## 4. Group Members and Roles

According to the project guidelines, each member contributed to a specific sublayer and documentation:

- **[ريم عثمان (184040)]**: Stage 1 - IP Dummy Packet Generator Implementation
- **[ريان نور الدين (184039)]**: Stage 2 - PDCP Layer Protocol Logic
- **[محمد فيصل (204114)]**: Stage 3 - RLC Segmentation & Reassembly
- **[ملاذ عبد الرحمن (184101)]**: Stage 4 - MAC Multiplexing & Downlink Extraction
- **[الحسن محمد (184025)]**: Stage 5 - System Integration & Orchestrator Logic
- **[احمد علي (184017)]**: Stage 6 - High-Resolution Profiler & Performance Analysis
- **[ليلى الامين حسن  (184065)]**: Stage 7 - Documentation (User Manual & Technical Report)

## 5. Directory Structure

- `/src`: Source code (.cpp) for all protocol layers.
- `/include`: Header files (.h) defining protocol interfaces.
- `/docs`: Profiling data, performance analysis, and the User Manual.
