# 5G NR Layer 2 U-Plane Simulation

**University of Khartoum — Faculty of Engineering**  
**Department of Electrical & Electronic Engineering**  
**Course:** EEE 52515 – Telecommunications Software Design  
**Submitted to:** Dr. Anas Showk  
**Date:** March 2026

---

## Group Members & Stage Assignments

| Member Name | Stage | Responsibility | Student ID |
|---|---|---|:---:|
| ريم عثمان | Stage 1 | IP Packet Generator | 184040 |
| ريان نور الدين | Stage 2 | PDCP Layer Protocol | 184039 |
| محمد فيصل | Stage 3 | RLC Segmentation & Reassembly | 204114 |
| ملاذ عبد الرحمن | Stage 4 | MAC Multiplexing & Downlink | 184101 |
| الحسن محمد | Stage 5 | System Integration & Orchestrator | 184025 |
| احمد علي | Stage 6 | Performance Profiling | 184017 |
| ليلى الامين حسن | Stage 7 | Documentation & Report | 184065 |

---

## Section 1: Task Analysis & System Architecture

### 1.1 Protocol Stack Overview

This project implements the 3GPP 38-series User Plane (U-Plane) data path for 5G New Radio (NR), encompassing Layer 2 sublayers from IP packet generation down to MAC Transport Block assembly. The software maps each protocol stage to a discrete compilation unit, reflecting the architectural separation prescribed in the 3GPP standard.

The uplink data flow is structured in four consecutive processing stages:

- **Packet Layer:** Simulates the PDU Session Resource by generating raw IP traffic payloads of configurable size.
- **PDCP Layer:** Acts as the security anchor, performing header compression, ciphering via XOR keystream generation, and appending a Message Authentication Code for Integrity (MAC-I).
- **RLC Layer:** Manages the segmentation of large Service Data Units (SDUs) into fixed-size Protocol Data Units (PDUs), each carrying a sequence number for ordered reassembly.
- **MAC Layer:** Handles the final multiplexing of RLC PDUs into a single Transport Block (TB), inserting subheaders and padding to meet the allocated grant size.

### 1.2 Decoupled Orchestrator Pattern

To ensure module independence and enable isolated unit testing, the team adopted a **Decoupled Orchestrator Pattern**. Rather than allowing sublayers to call one another directly, all inter-layer data handovers are managed by a single orchestrator file: `src/stack_integration.cpp`. This design confines the integration logic to one location, so modifications to an individual sublayer do not require changes to adjacent modules.

| Component | File Path | Functional Responsibility |
|---|---|---|
| Orchestrator | `src/stack_integration.cpp` | Manages SDU/PDU handovers between all sublayers. |
| PDCP Module | `src/PDCP.cpp` | Header compression simulation and XOR-based ciphering. |
| RLC Module | `src/RLC.cpp` | Segmentation, sequence numbering, and reassembly of SDUs. |
| MAC Module | `src/MAC.cpp` | MAC subheader insertion, Transport Block packing, and padding. |
| Profiler | `src/profiler.cpp` | High-resolution per-sublayer timing using `<chrono>`. |

### 1.3 Repository Directory Structure

All source code resides in `/src`, all interface declarations in `/include`, and all supplementary documentation and profiling data in `/docs`.

```plain
alhassensabeeh-5g_layer2_stack_simulation/
├── README.md
├── docs/
│   ├── PROFILING_ANALYSIS.md
│   ├── PROFILING_RESULTS.md
│   ├── USER_MANUAL.md
│   └── report/
│       ├── page1_intro.md
│       ├── page2_architecture.md
│       ├── page3_implementation.md
│       ├── page4_performance.md
│       └── page5.md
├── include/
│   ├── mac.h
│   ├── packet.h
│   ├── pdcp.h
│   ├── profiler.h
│   ├── rlc.h
│   └── stack_integration.h
└── src/
    ├── MAC.cpp
    ├── PDCP.cpp
    ├── RLC.cpp
    ├── main.cpp
    ├── packet.cpp
    ├── profiler.cpp
    └── stack_integration.cpp
```

---

## Section 2: Technical Implementation

### 2.1 Stage 1 – IP Dummy Packet Generator (`packet.cpp`)

The entry point of the simulation is a configurable IP dummy packet generator implemented in `src/packet.cpp`. The `generatePacket()` function constructs a `Packet` struct with a user-defined payload size. The first five bytes of the payload are set to a character derived from the packet ID (e.g., `'A'` for packet 1), followed by a repeating decimal digit sequence. This deterministic pattern provides a consistent baseline for verifying data integrity at the end of the loopback cycle.

For example, a 30-byte packet with ID 1 produces:

```plain
AAAAA0123456789012345678901234
```

The `Packet` struct, defined in `include/packet.h`, stores the integer ID, declared size in bytes, and the `std::string` data payload, which is passed as raw input to the PDCP layer.

---

### 2.2 Stage 2 – PDCP Layer: Security and Integrity Protection (`PDCP.cpp`)

The Packet Data Convergence Protocol layer is responsible for header compression, payload ciphering, and integrity protection through MAC-I generation. These functions ensure efficient, secure, and reliable data transmission between the User Equipment (UE) and the network in both uplink and downlink directions.

#### 2.2.1 Header Compression

The `compressHeader()` function in `PDCP.cpp` simulates Robust Header Compression (ROHC). It parses a pipe-delimited IP header string and retains only the Version, Source IP, and Destination IP fields, discarding lower-priority fields to reduce overhead.

#### 2.2.2 Encryption

AES (Advanced Encryption Standard) is the standard algorithm used for PDCP ciphering in 3GPP specifications. However, in this project a simplified XOR-based encryption scheme is used to facilitate easier simulation and testing. The design can be extended in future work to support standard algorithms such as AES-CTR.

Ciphering is performed by `pdcp_encrypt()`. For each byte index `i` of the payload, a keystream byte is derived by XOR-ing the following parameters:

- `key[i % key.size()]` — cyclic application of the secret key (`0xAA` in simulation).
- `count >> ((i % 4) * 8)` — a portion of the PDCP COUNT value, providing per-packet freshness.
- `bearer & 0x1F` — the 5-bit Logical Channel ID.
- `direction & 0x01` — indicates the transmission direction (`UPLINK = 0x01`).

The final encrypted byte: `encrypted[i] = payload[i] ^ keystream_byte`. Because XOR is its own inverse, `pdcp_decrypt()` calls `pdcp_encrypt()` with identical parameters, restoring the original data without a separate routine.

#### 2.2.3 Integrity Protection

The `generateMACI()` function produces a Message Authentication Code for Integrity (MAC-I) by accumulating the integer values of all characters in the SDU. This value is appended on the uplink path. On the downlink, `verifyMACI()` recomputes and compares the value to detect any data corruption.

---

### 2.3 Stage 3 – RLC Layer: Segmentation and Reassembly (`RLC.cpp`)

> **Scope Note:** The 3GPP RLC specification (TS 38.322) also defines Automatic Repeat reQuest (ARQ) retransmission. This simulation implements the Acknowledged Mode (AM) segmentation and reassembly functions only. ARQ retransmission is outside the scope of this implementation, as the loopback channel is lossless by design.

#### 2.3.1 Segmentation Logic

The `rlc_segment()` function iterates over the input byte vector, extracting chunks of up to `maxPduSize` bytes (fixed at **10 bytes**). Each chunk is assigned to an `RlcPdu` struct containing a `uint16_t sequenceNumber` and a `std::vector<uint8_t> data` payload. A 16-bit unsigned integer provides 65,536 addressable sequence numbers, exceeding standard 12-bit RLC SN requirements and ensuring adequate headroom for long bursts.

For a 100-byte encrypted SDU, this produces 10 RLC PDUs (PDUs 0 through 9), each carrying exactly 10 bytes. For a 30-byte SDU, three PDUs are produced.

#### 2.3.2 Reassembly Logic

The `rlc_reassemble()` function accepts a vector of `RlcPdu` objects, sorts them by `sequenceNumber` in ascending order, and concatenates their data fields to reconstruct the original SDU. The sorting step handles any out-of-order arrival scenarios.

---

### 2.4 Stage 4 – MAC Layer: Multiplexing and Transport Block Assembly (`MAC.cpp`)

> **Scope Note:** The 3GPP MAC specification (TS 38.321) includes uplink scheduling and Hybrid ARQ (HARQ) management. This simulation implements the multiplexing and de-multiplexing functions only. Scheduling and HARQ are outside the scope, consistent with a software-layer simulation that does not model the physical radio channel.

#### 2.4.1 Transport Block Header

The `mac_uplink()` function constructs the Transport Block as a `std::string`, beginning with a subheader in the format `_MAC_Nsegs`, where N is the number of RLC PDU segments.

#### 2.4.2 PDU Delimiter: the `||` Separator

Each RLC PDU's byte vector is converted to a string and appended to the TB prefixed by the double-pipe delimiter `||`. The `mac_downlink()` function uses `tb.find("||")` to locate the first PDU boundary and then applies a substring split loop on the same delimiter to extract all subsequent PDUs.

#### 2.4.3 Padding with the `#` Character

If the assembled TB is shorter than `max_tb_size` (100 bytes in the orchestrator, 150 bytes in the profiler), `mac_uplink()` appends `#` characters to maintain a constant-length Transport Block as required by the 5G NR air interface. On the downlink, `mac_downlink()` strips all trailing `#` characters before parsing via a `pop_back()` loop.

---

## Section 3: Performance Profiling

### 3.1 Profiling Methodology

A high-resolution performance profiler was developed in `src/profiler.cpp` using `std::chrono::high_resolution_clock`. For each packet size, the profiler executes **1,000 independent iterations**. Each sublayer (PDCP, RLC, MAC) is timed independently using bracketed start/end timestamps. Accumulated times are divided by the iteration count to yield mean execution time per packet in microseconds (μs).

Three traffic scenarios were defined in `main.cpp`:

- **Test A – 30 Bytes:** Small IP control packets or keep-alive frames.
- **Test B – 100 Bytes:** Typical small data segment.
- **Test C – 500 Bytes:** Video stream or file transfer segment.

### 3.2 Comparative Results

| Traffic Scenario | Packet Size | PDCP Avg (μs) | RLC Avg (μs) | MAC Avg (μs) | Total L2 Delay (μs) |
|---|:---:|:---:|:---:|:---:|:---:|
| Test A (Control) | 30 Bytes | 1.14 | 2.50 | 2.02 | **5.66** |
| Test B (Data) | 100 Bytes | 3.97 | 10.99 | 6.21 | **21.17** |
| Test C (Heavy) | 500 Bytes | 11.37 | 32.35 | 18.42 | **62.14** |

*All values represent the arithmetic mean over 1,000 iterations. Total L2 Delay is the sum of all three sublayer averages.*

### 3.3 Technical Bottleneck Analysis

#### 3.3.1 RLC – Primary Scaling Bottleneck

The RLC sublayer exhibited the steepest growth, rising from 2.50 μs (30 B) to 32.35 μs (500 B), an increase of approximately **1,194%**. The `rlc_segment()` function in `RLC.cpp` iterates over the input in 10-byte increments. A 30-byte payload produces 3 `RlcPdu` objects; a 500-byte payload produces 50. Each object requires dynamic memory allocation for its data vector and a `push_back()` call. The combined overhead of heap allocation, data copying, and vector reallocation scales directly with PDU count, making RLC the dominant contributor to total Layer 2 latency for large packets.

#### 3.3.2 PDCP – Efficient Linear Scaling

PDCP showed consistent linear growth of approximately 10x (from 1.14 μs to 11.37 μs). This near-linear relationship reflects the byte-by-byte XOR operation in `pdcp_encrypt()`: each additional byte requires one keystream computation and one XOR, with no branching or auxiliary data structure creation.

#### 3.3.3 MAC – Consistent Multiplexing Performance

MAC demonstrated moderate and stable scaling, rising from 2.02 μs to 18.42 μs (approximately 9.1x). The `mac_uplink()` function appends PDU data to a `std::string` using the `||` delimiter. The constant-time `#` padding operation contributes a fixed overhead that diminishes in relative significance as the packet size grows, confirming that the multiplexing logic is efficient and well-suited for high-throughput 5G NR scenarios.

---

## Section 4: Conclusion

### 4.1 Summary of Results

This project demonstrates a functional and verifiable software implementation of the 5G NR Layer 2 User-Plane protocol stack. All four uplink processing stages — IP generation, PDCP ciphering, RLC segmentation, and MAC multiplexing — were implemented as independent, testable modules conforming to the Decoupled Orchestrator Pattern.

The primary verification mechanism was the **Receiver Loopback** in `src/stack_integration.cpp`. After `mac_uplink()` assembled the Transport Block, the system executed the full inverse path: `mac_downlink()` stripped `#` padding and extracted RLC PDUs via the `||` delimiter, `rlc_reassemble()` restored the ordered byte sequence, and `pdcp_decrypt()` applied the same XOR keystream to recover the plaintext. The final comparison (`p.data == finalResult`) confirmed byte-for-byte identity between the transmitted and received data in every tested scenario.

### 4.2 Key Technical Findings

- The XOR keystream in `PDCP.cpp`, parameterized by COUNT, bearer ID, and direction (per adapted 3GPP TS 33.401 principles), provides efficient stream ciphering with near-linear latency scaling.
- The 10-byte PDU segmentation in `RLC.cpp` with 16-bit sequence numbering correctly partitioned SDUs of all tested sizes and produced bit-perfect reassembly on the downlink.
- The `||` delimiter and `#` padding scheme in `MAC.cpp` produced well-formed Transport Blocks reliably parsed by `mac_downlink()`.
- RLC segmentation is the primary computational bottleneck at larger packet sizes (~1,194% latency increase from 30B to 500B), driven by proportional growth in PDU object heap allocations.
- Total Layer 2 latency remained below 65 μs across all tested sizes, confirming acceptable performance for a software-based 5G simulation.

---

## Installation & Execution

### Step 1: Clone the Repository

```bash
git clone https://github.com/AlhassenSabeeh/5G_Layer2_Stack_Simulation.git
cd 5G_Layer2_Stack_Simulation
```

### Step 2: Compile and Run — The Golden Command

Run the following command from **inside the `5G_Layer2_Stack_Simulation` root folder**:

```powershell
g++ -I./include src/*.cpp -o 5G_Sim; if ($?) { .\5G_Sim }
```

> **Important:** You must run this command from the project root directory so the compiler can resolve the relative header paths in `./include`.

---

## References

1. 3GPP TS 38.323, "NR; Packet Data Convergence Protocol (PDCP) specification," 3rd Generation Partnership Project, Release 17.
2. 3GPP TS 38.322, "NR; Radio Link Control (RLC) protocol specification," 3rd Generation Partnership Project, Release 17.
3. 3GPP TS 38.321, "NR; Medium Access Control (MAC) protocol specification," 3rd Generation Partnership Project, Release 17.
4. 3GPP TS 33.401, "System Architecture for the Evolved Packet System (EPS); Security Architecture," 3rd Generation Partnership Project, Release 17. *(Basis for PDCP ciphering algorithm adaptation.)*
5. ISO/IEC 14882:2020, "Programming Languages – C++," International Organization for Standardization, 2020.
6. AlhassenSabeeh, "5G_Layer2_Stack_Simulation," GitHub Repository, 2026. Available: https://github.com/AlhassenSabeeh/5G_Layer2_Stack_Simulation.git