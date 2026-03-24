#include "../include/pdcp.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <iomanip>

using namespace std;

// PDCP header compression function [cite: 250, 271]
string compressHeader(string &header) {
    string compressed = "";

    size_t verPosition = header.find("Version");
    size_t srcPosition = header.find("Src");
    size_t dstPosition = header.find("Dst");

    if (verPosition != string::npos && srcPosition != string::npos 
        && dstPosition != string::npos) { 
       
        size_t verEnd = header.find("|", verPosition);
        compressed += header.substr(verPosition, verEnd - verPosition) + "|";

        size_t srcEnd = header.find("|", srcPosition);
        compressed += header.substr(srcPosition, srcEnd - srcPosition) + "|";

        size_t dstEnd = header.find("|", dstPosition);
        compressed += header.substr(dstPosition, dstEnd - dstPosition);
    }

    return compressed;
}

// Decompress header (downlink) [cite: 250]
string decompressHeader(const string &compressedHeader) {
    return compressedHeader; 
}

// Advanced 5G-style encryption [cite: 35, 41]
vector<uint8_t> pdcp_encrypt(
    const vector<uint8_t>& payload,
    uint32_t count,
    uint8_t bearer,
    uint8_t direction,
    const vector<uint8_t>& key
) {
    vector<uint8_t> encrypted(payload.size());

    for (size_t i = 0; i < payload.size(); ++i) {
        // Generates a keystream based on 3GPP parameters [cite: 238, 239]
        uint8_t keystream_byte = key[i % key.size()]
                          ^ static_cast<uint8_t>(count >> ((i % 4) * 8))
                          ^ (bearer & 0x1F)
                          ^ (direction & 0x01);
        encrypted[i] = payload[i] ^ keystream_byte;
    }

    return encrypted;
}   

// XOR decryption is symmetric [cite: 55, 60]
vector<uint8_t> pdcp_decrypt(
    const vector<uint8_t>& encryptedPayload,
    uint32_t count,
    uint8_t bearer,
    uint8_t direction,
    const vector<uint8_t>& key)
{
    return pdcp_encrypt(encryptedPayload, count, bearer, direction, key);
}

// Integrity protection: MAC-I Generation [cite: 250, 271]
int generateMACI(const string &data) {
    int maci = 0;
    for (char c : data) {
        maci += c;
    }
    return maci;
}

// Verify integrity for Downlink [cite: 52, 53]
bool verifyMACI(string data, int receivedMACI) {
    int calculatedMACI = generateMACI(data);
    return (calculatedMACI == receivedMACI);
}