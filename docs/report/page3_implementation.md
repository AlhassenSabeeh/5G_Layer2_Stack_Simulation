# Page 3: Technical Implementation Details

## 3.1 Stage 1 & 2: IP Generation and PDCP (Security)
The entry point of our stack is a customizable **IP Dummy Packet Generator**. It allows for variable Payload sizes to test the stack's limits. 
* **PDCP Ciphering**: We implemented a stream-cipher simulation using bitwise XOR operations. This ensures that the Data Radio Bearer (DRB) content is protected before being passed to the lower layers.
* **Integrity Protection**: A 4-byte Message Authentication Code (MAC-I) simulation is appended to the SDU to verify data origin.

## 3.2 Stage 3: RLC (Segmentation & Reassembly)
The Radio Link Control (RLC) module is the "engine" of our data flow. 
* **Segmentation**: If the Service Data Unit (SDU) from PDCP exceeds the 10-byte PDU limit, our algorithm splits it into multiple segments.
* **Sequence Numbering**: Each RLC PDU is assigned a 12-bit Sequence Number (SN) to allow the receiver to reorder and reassemble the original data packet correctly.

## 3.3 Stage 4: MAC (Multiplexing & Padding)
The MAC layer acts as the interface to the Physical Layer (simulated).
* **Multiplexing**: The MAC layer takes multiple RLC PDUs and wraps them into a single **Transport Block (TB)**. 
* **Subheader Insertion**: Each PDU is prefixed with a MAC Subheader containing the Logical Channel ID (LCID) and Length fields.
* **Padding**: If the data does not fill the requested Grant Size, the MAC layer automatically inserts Padding bits to maintain a constant TB size.

## 3.4 Stage 5: System Integration (Uplink/Downlink)
Our integration logic bridges the two paths:
1. **Uplink**: IP -> PDCP Encrypt -> RLC Segment -> MAC Pack.
2. **Downlink**: MAC Unpack -> RLC Reassemble -> PDCP Decrypt -> Verified IP.
This "Round-Trip" architecture ensures that any bug in any layer is immediately detected by a mismatch in the final recovered data.
