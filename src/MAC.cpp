#include "../include/mac.h"
#include <iostream>

using namespace std;

// MAC Uplink: Uses your partner's || separator and # padding logic
string mac_uplink(const vector<RlcPdu>& segments, int max_tb_size) {
    // Header includes the number of segments
    string tb = "_MAC_" + to_string(segments.size()) + "segs";

    for (const auto& seg : segments) {
        // Convert RLC vector data to string to maintain your partner's format
        string dataStr(seg.data.begin(), seg.data.end());
        tb += "||" + dataStr;   
    }

    // Apply # padding if under max size
    if ((int)tb.size() < max_tb_size) {
        tb += string(max_tb_size - tb.size(), '#');
    }

    return tb;
}

// MAC Downlink: Exactly as your partner's original implementation
vector<string> mac_downlink(string tb) {
    vector<string> segments;

    // remove padding
    while (!tb.empty() && tb.back() == '#') {
        tb.pop_back();
    }

    // find header end
    size_t pos = tb.find("||");
    if (pos == string::npos) {
        cout << "[MAC] Invalid format or no segments found!" << endl;
        return segments;
    }

    // Logic to split by ||
    string data = tb.substr(pos + 2);
    size_t start = 0;
    size_t end;
    while ((end = data.find("||", start)) != string::npos) {
        segments.push_back(data.substr(start, end - start));
        start = end + 2;
    }

    if (start < data.size()) {
        segments.push_back(data.substr(start));
    }

    return segments;
}
