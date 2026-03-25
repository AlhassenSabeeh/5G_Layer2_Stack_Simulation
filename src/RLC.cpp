#include "../include/rlc.h"
#include <iostream>
#include <algorithm>
#include <iomanip>

void RlcPdu::print() const {
    std::cout << "  SN: " << std::setw(4) << std::setfill('0') << sequenceNumber
              << ", Data Size: " << data.size() << ", Data: ";
    for (uint8_t byte : data) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte) << " ";
    }
    std::cout << std::dec << std::endl;
}

std::vector<RlcPdu> rlc_segment(const std::vector<uint8_t>& sdu, uint16_t maxPduSize) {
    std::vector<RlcPdu> pdus;
    uint16_t sequenceNumber = 0;
    size_t offset = 0;

    while (offset < sdu.size()) {
        RlcPdu pdu;
        pdu.sequenceNumber = sequenceNumber++;
        size_t segmentSize = std::min(static_cast<size_t>(maxPduSize), sdu.size() - offset);
        pdu.data.assign(sdu.begin() + offset, sdu.begin() + offset + segmentSize);
        pdus.push_back(pdu);
        offset += segmentSize;
    }
    return pdus;
}

std::vector<uint8_t> rlc_reassemble(const std::vector<RlcPdu>& pdus) {
    std::vector<uint8_t> sdu;
    std::vector<RlcPdu> sortedPdus = pdus;
    std::sort(sortedPdus.begin(), sortedPdus.end(), [](const RlcPdu& a, const RlcPdu& b) {
        return a.sequenceNumber < b.sequenceNumber;
    });

    for (const auto& pdu : sortedPdus) {
        sdu.insert(sdu.end(), pdu.data.begin(), pdu.data.end());
    }
    return sdu;
}

bool RLC_Process(std::vector<uint8_t>& data, Direction dir, uint16_t maxPduSize) {
    if (dir == UPLINK) {
        std::cout << "[RLC Uplink] Segmenting encrypted data..." << std::endl;
        std::vector<RlcPdu> segmentedPdus = rlc_segment(data, maxPduSize);
        for (const auto& pdu : segmentedPdus) pdu.print();
        
        // Internal reassembly for verification
        data = rlc_reassemble(segmentedPdus);
        return true;
    } 
    return false;
}
