# Brute Force Implementation for Matrix Multiplication
====
## Files
----
This is the first implementation in the report.<br>
We provide Vitis HLS code (including TestBench) in **/src**.<br>
Also, the Python host code in **/host_py** and .bit and .hwh files in **/bit** can run on FPGA.<br>
Please follow [Lab 1](https://github.com/bol-edu/course-lab_1) or [Lab 2](https://github.com/bol-edu/course-lab_2) stream part.
## Brief Description for Codes
----
We implement Brute Force Matrix Multiplication for two 32*32 integer matrices multiplication with **AXI Stream interface**.<br>
The code use **Array Partition** to accelerate computation. The rows of left matrix and the columns of right matrix are completely partition.<br>
You may try to modify **Matrix Size (N)**(=32) in **/src/matrix_mul.h** to see that the latency grows in O(N^2).
## References
----
1. [Lab 2 in Bridge of Life Education GitHub](https://github.com/bol-edu/course-lab_2).<br>
2. [AAHLS-LabB-Matrix-Multiplication in andy39866821 GitHub](https://github.com/andy39866821/AAHLS-LabB-Matrix-Multiplication).
