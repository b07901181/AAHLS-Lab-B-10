# AAHLS-Lab-B-10
Matrix Multiplication (Implement on Vitis HLS and PYNQ)
## Introduction
This project implements matrix multiplication (_A*B=C_) for _A,B,C_ being square integer matrices.  
We performs matrix multiplication in two ways: 1. **Brute Force** and 2. **Block Matrix Multiplication**.  
Both of them use data parallism to accelerate computation.  
The brute force implementation uses full paralism on inner products (between rows of _A_ and columns of _B_) but is not flexible and will face resource limitation in even small-size matrices.  
![image](https://user-images.githubusercontent.com/65820999/196753221-d26b805c-2132-49e3-91a0-2e9f4c9b60f3.png)
The block matrix multiplication limits the unroll factor (number of data parallism branches) and resource by block size, which can be used in large-size matrix multiplication.  
There are two implementations for block multiplication: the first one is traditional block multiplication and the second one use vectors for fast transmission.  
The first block multiplication implementation divides the task into several blocks.  
![image](https://user-images.githubusercontent.com/65820999/196753630-81fd23a7-e0dc-4ab2-9172-0f429c1816ae.png)
The second block multiplication implementation uses vector data type, which can accelerate transmission of data.  
![image](https://user-images.githubusercontent.com/65820999/196753902-fcd94ee9-9093-4dc6-a179-70d73f826af3.png)
### Files
In folder **/Brute_Force** and **/Block_MM_1**, there are files for Vitis HLS and PYNQ running.  
In folder **/Block_MM_2**, there are files for Vitis HLS running.  
Follow the README in each folder, and refer to the references in Building section, you may perform Vitis HLS analysis and run the program on PYNQ.
### Building
Please follow [Lab 1](https://github.com/bol-edu/course-lab_1) or [Lab 2](https://github.com/bol-edu/course-lab_2) stream part.
## References
1. [Lab 2 in Bridge of Life Education GitHub](https://github.com/bol-edu/course-lab_2).<br>
2. [AAHLS-LabB-Matrix-Multiplication in andy39866821 GitHub](https://github.com/andy39866821/AAHLS-LabB-Matrix-Multiplication).
