# 5G NR Layer 2 User-Plane Protocol Stack Simulation
**Course:** Telecommunications Software Design
**Project:** 5G NR Software Implementation (U-Plane)
**Date:** March 2026

---

## 1. Group Members and Roles (Section 3a)
In accordance with the project guidelines for effective collaboration and distribution of responsibilities, the following roles were assigned:

| Member Name | Primary Responsibility | Contribution Detail |
| :--- | :--- | :--- |
| **[Name 1]** | Stage 1: IP Generator | Developed the dummy packet tool for traffic simulation. |
| **[Name 2]** | Stage 2: PDCP Layer | Implemented XOR-based security and header convergence. |
| **[Name 3]** | Stage 3: RLC Layer | Managed segmentation and SDU reassembly logic. |
| **[Name 4]** | Stage 4: MAC Layer | Developed TB multiplexing and downlink extraction. |
| **[Name 5]** | Stage 5: System Integration | Developed the Orchestrator and full-stack loopback. |
| **[Name 6]** | Stage 6: Performance | Developed high-resolution profiling for sublayers. |
| **[Name 7]** | Stage 7: Documentation | Authored User Manual and Technical Project Report. |

---

## 2. Project Executive Summary
This report documents the design, implementation, and performance analysis of a 5G New Radio (NR) Layer 2 protocol stack. The system successfully demonstrates a complete data cycle: from IP packet generation through PDCP/RLC/MAC processing, followed by a bit-perfect recovery on the downlink path.
