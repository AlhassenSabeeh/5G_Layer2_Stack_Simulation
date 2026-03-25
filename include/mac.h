#ifndef MAC_H
#define MAC_H

#include <vector>
#include <string>
#include <cstdint>
#include "rlc.h"

// Core MAC Functions using your partner's logic
std::string mac_uplink(const std::vector<RlcPdu>& segments, int max_tb_size);
std::vector<std::string> mac_downlink(std::string tb);

#endif