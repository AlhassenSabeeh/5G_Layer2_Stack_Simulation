# Page 2: System Architecture & User-Plane Flow

## 2.1 Protocol Stack Overview (Section 1: Task Analysis)
The implementation follows the 3GPP 38-series architecture for the 5G NR User Plane. Our software maps the data transition from high-level IP packets down to the Medium Access Control (MAC) layer. 

The data flow is structured as follows:
1. **Packet Layer**: Simulates the PDU Session Resource by generating raw IP traffic.
2. **PDCP Layer**: Acts as the security anchor, performing Ciphering and Integrity Protection.
3. **RLC Layer**: Manages the segmentation of Large SDUs into multiple PDUs based on the available grant size.
4. **MAC Layer**: Handles the final multiplexing into a Transport Block (TB) ready for the physical layer.



## 2.2 Software Module Design
To ensure maintainability and independent testing (as recommended in the Project Guidelines), we adopted a **Decoupled Orchestrator Pattern**. Each protocol sublayer is isolated in its own compilation unit:

| Component | File Path | Functional Responsibility |
| :--- | :--- | :--- |
| **Orchestrator** | `src/stack_integration.cpp` | Manages the SDU/PDU handovers between layers. |
| **PDCP Module** | `src/pdcp.cpp` | Header compression simulation and XOR encryption. |
| **RLC Module** | `src/rlc.cpp` | Segmentation, concatenation, and reassembly. |
| **MAC Module** | `src/mac.cpp` | MAC subheader insertion and Transport Block packing. |
| **Profiler** | `src/profiler.cpp` | High-resolution timing of the internal stack logic. |

## 2.3 Data Integrity & Loopback
A key technical achievement of this architecture is the **Receiver Loopback**. After the MAC layer generates a Transport Block, the system performs an inverse operation (Demultiplexing -> Reassembly -> Decryption) to verify that the final recovered packet is bit-identical to the original IP source.
