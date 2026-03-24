#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <iomanip>
#include "../include/pdcp.h"


using namespace std;

enum Direction {
    UPLINK,
    DOWNLINK
};

// PDCP header compression function
string compressHeader(string &header) {
    string compressed = "";

    size_t verPosition = header.find("Version");
    size_t srcPosition = header.find("Src");
    size_t dstPosition = header.find("Dst");

    if (verPosition != string::npos && srcPosition != string::npos 
        && dstPosition != string::npos) { // we make sure the version, source and destination of IP exist before extracting them
       
        size_t verEnd = header.find("|", verPosition);  // Extract Version field
        compressed += header.substr(verPosition, verEnd - verPosition) + "|";

        
        size_t srcEnd = header.find("|", srcPosition); // Extract Src field
        compressed += header.substr(srcPosition, srcEnd - srcPosition) + "|";

    
        size_t dstEnd = header.find("|", dstPosition); // Extract Dst field
        compressed += header.substr(dstPosition, dstEnd - dstPosition);
    }

    return compressed;
}
// Decompress header (downlink) - for simulation, just returns the string
string decompressHeader(const string &compressedHeader) {
    // In a real implementation, you would reconstruct the full header
    return compressedHeader; 
}

vector<uint8_t> pdcp_encrypt(
    const vector<uint8_t>& payload,
    uint32_t count,
    uint8_t bearer,
    uint8_t direction,
    const vector<uint8_t>& key
) {
    vector<uint8_t> encrypted(payload.size());

    // Generate a simple XOR keystream from COUNT, BEARER, DIRECTION, and key
    for (size_t i = 0; i < payload.size(); ++i) {
        // Simple keystream byte:
        uint8_t keystream_byte = key[i % key.size()]          // repeat key bytes
                          ^ static_cast<uint8_t>(count >> ((i % 4) * 8)) // use COUNT bytes
                          ^ (bearer & 0x1F)                       // use BEARER (5 bits)
                          ^ (direction & 0x01);                   // use DIRECTION (1 bit)
        encrypted[i] = payload[i] ^ keystream_byte;
    }

    return encrypted;
}   

vector<uint8_t> pdcp_decrypt(
    const vector<uint8_t>& encryptedPayload,
    uint32_t count,
    uint8_t bearer,
    uint8_t direction,
    const vector<uint8_t>& key)
     {
    // XOR decryption is symmetric
    return pdcp_encrypt(encryptedPayload, count, bearer, direction, key);
}

vector<uint8_t> extractPayload(const string &packet, size_t headerLength) {
    return vector<uint8_t>(packet.begin() + headerLength, packet.end());
}
// Simple integrity function (generate MAC)
int generateMACI(const string &data) {
    int maci = 0;

    for (char c : data) {
        maci += c;  // add ASCII values
    }

    return maci;
}

// Verify integrity
bool verifyMACI(string data, int receivedMACI) {
    int calculatedMACI = generateMACI(data);
    return (calculatedMACI == receivedMACI);
}



// ---------- PDCP Module (Bidirectional) ----------
bool PDCP_Process(string &packet, int &MACI, Direction dir) {

    if (dir == UPLINK) {
        // Generate MAC-I for uplink
        MACI = generateMACI(packet);
        cout << "[PDCP Uplink] Packet: " << packet << endl;
        cout << "[PDCP Uplink] MAC-I Generated: " << MACI << endl;
        return true;
    } 
    else if (dir == DOWNLINK) {
        // Verify MAC-I for downlink
        bool valid = verifyMACI(packet, MACI);
        cout << "[PDCP Downlink] Packet: " << packet << endl;
        if (valid)
            cout << "[PDCP Downlink] Integrity: SUCCESS" << endl;
        else
            cout << "[PDCP Downlink] Integrity: FAILED" << endl;
        return valid;
    }

    return false;
}

