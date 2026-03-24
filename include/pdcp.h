#ifndef PDCP_H
#define PDCP_H

#include <string>
#include <vector>
#include <cstdint>

enum Direction { UPLINK, DOWNLINK };

// Core PDCP Functions
std::string compressHeader(std::string &header);
std::vector<uint8_t> pdcp_encrypt(const std::vector<uint8_t>& payload, uint32_t count, uint8_t bearer, uint8_t direction, const std::vector<uint8_t>& key);
std::vector<uint8_t> pdcp_decrypt(const std::vector<uint8_t>& encryptedPayload, uint32_t count, uint8_t bearer, uint8_t direction, const std::vector<uint8_t>& key);
int generateMACI(const std::string &data);
bool verifyMACI(std::string data, int receivedMACI);

#endif