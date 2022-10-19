
# coding: utf-8

# In[ ]:


from __future__ import print_function

import sys, os
import numpy as np
from time import time 

sys.path.append('.')
os.environ['XILINX_XRT'] = '/usr'
from pynq import Overlay
from pynq import allocate

if __name__ == "__main__":
    print("Entry:", sys.argv[0])
    print("System argument(s):", len(sys.argv))

    print("Start of \"" + sys.argv[0] + "\"")

    ol = Overlay("Matrix_mul.bit")
    ipMM = ol.matrix_mul_0
    ipDMAInA = ol.axi_dma_in_A
    ipDMAInB = ol.axi_dma_in_B
    ipDMAOutC = ol.axi_dma_out_C

    N = 32
    Ntest = 10

    AinBuffer = allocate(shape=(N*N,), dtype=np.int32)
    BinBuffer = allocate(shape=(N*N,), dtype=np.int32)
    CoutBuffer = allocate(shape=(N*N,), dtype=np.int32)

    PyTime = []
    KernelTime = []
    TFList = []

    for s in range(Ntest):
        A = np.random.randint(-3, 3, size=(N,N))
        B = np.random.randint(-3, 3, size=(N,N))
        timePyStart = time()
        C = np.dot(A, B)
        timePyEnd = time()
        for i in range(N):
            for j in range(N):
                AinBuffer[N*i+j] = A[i][j]
                BinBuffer[N*i+j] = B[i][j]
        timeKernelStart = time()

        ipMM.write(0x00, 0x01)
        ipDMAInA.sendchannel.transfer(AinBuffer)
        ipDMAInB.sendchannel.transfer(BinBuffer)
        ipDMAOutC.recvchannel.transfer(CoutBuffer)
        ipDMAInA.sendchannel.wait()
        ipDMAInB.sendchannel.wait()
        ipDMAOutC.recvchannel.wait()
        timeKernelEnd = time()
        TF = True
        for i in range(N):
            for j in range(N):
                if C[i][j] != CoutBuffer[N*i+j]:
                    TF = False
        TFList.append(TF)
        PyTime.append(float(timePyEnd - timePyStart))
        KernelTime.append(float(timeKernelEnd - timeKernelStart))


    print("Kernel Time:")
    print(KernelTime)
    print("============================")
    print("Python Time:")
    print(PyTime)
    print("============================")
    print("Correctness:")
    print(TFList)
    print("============================")


    print("============================")
    print("Exit process")

