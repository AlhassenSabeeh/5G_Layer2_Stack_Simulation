# 5G Layer 2 Simulator - User Manual

## System Requirements
* Operating System: Windows 10/11 (PowerShell)
* Compiler: GCC/G++ (MinGW-w64)
* Version Control: Git

## Execution Instructions
1. Open PowerShell in the project root directory.
2. Run the "Golden Command" to compile and execute:
   g++ -I./include src/*.cpp -o 5G_Sim; if ($?) { .\5G_Sim }

## Configuration
* To change packet sizes for testing, modify `src/main.cpp`.
* RLC segmentation limits can be adjusted in `src/stack_integration.cpp`.
