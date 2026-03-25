# Section 3d: Protocol Stack Profiling Analysis

## Performance Observations:
* PDCP Analysis: Processing time increased by approximately 3x when scaling from 30B to 500B. This is attributed to the computational overhead of the byte-by-byte XOR encryption used for security.
* RLC Analysis: This sublayer exhibited the highest scaling delay, rising from 13.9us to 50.1us. The increase is due to the higher frequency of segmentation operations and the management of multiple RLC PDU headers required for larger SDUs[cite: 39, 49].
* MAC Analysis: Processing efficiency remained high even at 500B. This confirms that the multiplexing and padding logic is effectively optimized for high-throughput 5G NR scenarios[cite: 41, 53].

## Conclusion:
The results validate that the Layer 2 stack handles varying transport block lengths with predictable, linear scaling, meeting the performance requirements for the 5G User Plane (U-Plane)[cite: 11, 18].
