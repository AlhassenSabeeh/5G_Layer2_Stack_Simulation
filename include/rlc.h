#ifndef RLC_H
#define RLC_H

#include <vector>
#include <cstdint>
#include "pdcp.h"

struct RlcPdu {
    uint16_t sequenceNumber;
    std::vector<uint8_t> data;
    void print() const;
};

// Function prototypes
std::vector<RlcPdu> rlc_segment(const std::vector<uint8_t>& sdu, uint16_t maxPduSize);
std::vector<uint8_t> rlc_reassemble(const std::vector<RlcPdu>& pdus);
bool RLC_Process(std::vector<uint8_t>& data, Direction dir, uint16_t maxPduSize = 10);

#endif