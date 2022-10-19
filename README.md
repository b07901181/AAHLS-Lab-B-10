# AAHLS-Lab-B-10
Matrix Multiplication (Implement on Vitis HLS and PYNQ)
## Introduction
This project implements matrix multiplication (_A*B=C_) for _A,B,C_ being square integer matrices.  
We performs matrix multiplication in two ways: 1. **Brute Force** and 2. **Block Matrix Multiplication**.  
Both of them use data parallism to accelerate computation.  
The brute force implementation uses full paralism on inner products (between rows of _A_ and columns of _B_) but is not flexible and will face resource limitation in even small-size matrices.  
The block matrix multiplication limits the unroll factor (number of data parallism branches) and resource by block size, which can be used in large-size matrix multiplication.  
There are two implementations for block multiplication: the first one is traditional block multiplication and the second one use vectors for fast transmission.
### Files

### Building
