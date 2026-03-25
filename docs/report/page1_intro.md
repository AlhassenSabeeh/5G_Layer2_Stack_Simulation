# 5G NR Layer 2 User-Plane Protocol Stack Simulation
**Course:** Telecommunications Software Design
**Project:** 5G NR Software Implementation (U-Plane)
**Date:** March 2026

---

## 1. Group Members and Roles (Section 3a)
In accordance with the project guidelines for effective collaboration and distribution of responsibilities, the following roles were assigned:

| Member Name | Primary Responsibility | Contribution Detail |
| :--- | :--- | :--- |
| **[ريم عثمان (184040)]** | Stage 1: IP Generator | Developed the dummy packet tool for traffic simulation. |
| **[ريان نور الدين (184039)]** | Stage 2: PDCP Layer | Implemented XOR-based security and header convergence. |
| **[محمد فيصل (204114)]** | Stage 3: RLC Layer | Managed segmentation and SDU reassembly logic. |
| **[ملاذ عبد الرحمن (184101)]** | Stage 4: MAC Layer | Developed TB multiplexing and downlink extraction. |
| **[الحسن محمد (184025)]** | Stage 5: System Integration | Developed the Orchestrator and full-stack loopback. |
| **[احمد علي (184017)]** | Stage 6: Performance | Developed high-resolution profiling for sublayers. |
| **[ليلى الامين حسن  (184065)]** | Stage 7: Documentation | Authored User Manual and Technical Project Report. |

---

## 2. Project Executive Summary
This report documents the design, implementation, and performance analysis of a 5G New Radio (NR) Layer 2 protocol stack. The system successfully demonstrates a complete data cycle: from IP packet generation through PDCP/RLC/MAC processing, followed by a bit-perfect recovery on the downlink path.
