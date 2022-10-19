#ifndef __MATRIX_MUL_H__
#define __MATRIX_MUL_H__

#include <ap_axi_sdata.h>
#include <hls_stream.h>
#include <hls_vector.h>

#define N 128
#define BL 8 //Block size, should be smaller than N
#define BN (N/BL)
#define VT 4 //Vector transfer size should be smaller (or equal to) than BL
#define VTN (N/VT)


typedef ap_uint<32> reg32_t;
typedef signed int int32_t;
typedef unsigned int uint32_t;
typedef hls::vector<int32_t, VT> int32_vt;
typedef hls::axis<int32_vt,1,1,1> value_t;
typedef hls::stream<value_t> stream_t; //maximum supported port width is 4096 bits


void matrix_mul(stream_t* As, stream_t* Bs, stream_t* Cs);
void read_data_A(stream_t* As, int32_t A[N][N]);
void read_data_B(stream_t* Bs, int32_t B[N][N]);
void block_MM(int32_t A[N][N], int32_t B[N][N], stream_t* Cs);

#endif
