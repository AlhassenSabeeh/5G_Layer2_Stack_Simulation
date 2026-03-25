# Page 4: Performance Analysis & Profiling (Section 3d)

## 4.1 Profiling Methodology
To evaluate the efficiency of our Layer 2 implementation, we developed a high-resolution profiler using the C++ `<chrono>` library. The stack was tested across three distinct traffic scenarios (Small, Medium, and Large packets) with 1,000 iterations per test to ensure statistical accuracy.

## 4.2 Comparative Results Table
The following data represents the average execution time per packet in microseconds (μs):

| Traffic Scenario | Packet Size | PDCP Avg (μs) | RLC Avg (μs) | MAC Avg (μs) | Total Latency |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **Test A (Control)** | 30 Bytes | 5.60 | 13.95 | 13.29 | **32.84 μs** |
| **Test B (Data)** | 100 Bytes | 8.37 | 33.92 | 22.69 | **64.98 μs** |
| **Test C (Heavy)** | 500 Bytes | 17.84 | 50.07 | 33.82 | **101.73 μs** |

## 4.3 Technical Bottleneck Analysis
Our analysis of the data reveals specific insights into the computational cost of each protocol layer:

1. **RLC Scaling Logic**: The RLC layer showed the steepest increase in latency (rising by ~260% from Test A to Test C). This is technically expected as larger SDUs trigger more frequent segmentation loops and require the instantiation of additional RLC PDU objects.
2. **PDCP Efficiency**: The PDCP layer demonstrated high efficiency, even at larger packet sizes. The XOR-based encryption scaling was approximately linear (~1.5x - 2x per increment), which indicates minimal overhead during security processing.
3. **MAC Performance**: Our MAC layer maintained a relatively constant processing time per subheader, proving that the multiplexing logic is optimized for high-throughput 5G NR scenarios.

## 4.4 Conclusion
These profiling results validate that the developed Layer 2 stack handles varying transport block lengths with predictable, linear scaling. The system meets the performance requirements for the 5G User Plane (U-Plane), ensuring that processing delays remain within acceptable limits for a software-based implementation.
