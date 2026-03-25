#include "../include/stack_integration.h"
#include "../include/packet.h"
#include "../include/pdcp.h"
#include "../include/rlc.h"
#include "../include/mac.h"
#include <iostream>
#include <vector>

void run_full_stack_simulation(int packetId, int packetSize) {
    std::cout << "\n>>> BEGINNING 5G LAYER 2 FULL STACK TEST <<<\n" << std::endl;

    // --- UPLINK PATH (Sender) ---

    // STAGE 1: IP Packet Generation
    Packet p = generatePacket(packetId, packetSize);
    printPacket(p);
    std::vector<uint8_t> rawData(p.data.begin(), p.data.end());

    // STAGE 2: PDCP (Security & Integrity)
    // Encrypting the raw data
    std::vector<uint8_t> encrypted = pdcp_encrypt(rawData, 0, 1, UPLINK, {0xAA});
    std::cout << "[Stage 2] PDCP Encryption Complete." << std::endl;

    // STAGE 3: RLC (Segmentation)
    // Breaking the encrypted SDU into 10-byte PDUs
    std::vector<RlcPdu> rlcSegments = rlc_segment(encrypted, 10);
    std::cout << "[Stage 3] RLC Segmentation: Created " << rlcSegments.size() << " PDUs." << std::endl;

    // STAGE 4: MAC (Multiplexing)
    // Packing RLC segments into a single Transport Block
    std::string transportBlock = mac_uplink(rlcSegments, 100);
    std::cout << "[Stage 4] MAC Uplink: Transport Block (TB) Generated." << std::endl;


    // --- DOWNLINK PATH (Receiver / Loopback) ---

    std::cout << "\n--- STARTING RECEIVER LOOPBACK ---" << std::endl;

    // STAGE 4: MAC (Demultiplexing)
    std::vector<std::string> macExtracted = mac_downlink(transportBlock);
    
    // STAGE 3: RLC (Reassembly)
    std::vector<RlcPdu> receivedPdus;
    for(size_t i = 0; i < macExtracted.size(); i++) {
        RlcPdu pdu;
        pdu.sequenceNumber = i;
        pdu.data = std::vector<uint8_t>(macExtracted[i].begin(), macExtracted[i].end());
        receivedPdus.push_back(pdu);
    }
    std::vector<uint8_t> reassembled = rlc_reassemble(receivedPdus);

    // STAGE 2: PDCP (Decryption)
    std::vector<uint8_t> decrypted = pdcp_decrypt(reassembled, 0, 1, UPLINK, {0xAA});
    std::string finalResult(decrypted.begin(), decrypted.end());

    // STAGE 5: INTEGRATION VERIFICATION
    std::cout << "\n[FINAL VERIFICATION]" << std::endl;
    std::cout << "Original Data: " << p.data << std::endl;
    std::cout << "Recovered Data: " << finalResult << std::endl;

    if (p.data == finalResult) {
        std::cout << ">> RESULT: SUCCESS - Bit-Perfect Recovery <<" << std::endl;
    } else {
        std::cout << ">> RESULT: FAILURE - Data Mismatch <<" << std::endl;
    }
}