# Block Matrix Multiplication Implementation 2 for Matrix Multiplication
====
## Files
----
This is the third implementation described in the report.<br>
We provide Vitis HLS code (including TestBench) in **/src**.<br>
This implementation still has bug when running on FPGA, and thus we only provide codes for Vitis HLS.<br>
Please follow [Lab 1](https://github.com/bol-edu/course-lab_1) or [Lab 2](https://github.com/bol-edu/course-lab_2) stream part.
## Brief Description for Codes
----
We implement Block Matrix Multiplication for two 128*128 integer matrices multiplication with **AXI Stream interface**.<br>
The code use **Array Partition** to accelerate computation. The rows of left matrix and the columns of right matrix are unrolled with cyclic array partition and unroll factor 8.<br>
In this implementation we also use vector type variables to transmit data. The vector size is set to 4.<br>
You may try to modify **Matrix Size (N)**(=128) in **/src/matrix_mul.h**, **Block Size for Array Partition (BL)**(=8) and **Vector Size (VT)**(=4) in both **/src/matrix_mul.cpp** and **/src/matrix_mul.h**. We have commented where to modify in the code.<br>
(You need to change code in **.cpp** file since **#pragma** do not accept variable factor.)
## References
----
1. [Lab 2 in Bridge of Life Education GitHub](https://github.com/bol-edu/course-lab_2).<br>
2. [AAHLS-LabB-Matrix-Multiplication in andy39866821 GitHub](https://github.com/andy39866821/AAHLS-LabB-Matrix-Multiplication).
