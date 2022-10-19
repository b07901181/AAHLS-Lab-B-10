#ifndef __MATRIX_MUL_H__
#define __MATRIX_MUL_H__

#include <ap_axi_sdata.h>
#include <hls_stream.h>

#define N 32
#define BL 4
#define BN (N/BL)

typedef ap_axiu<32,1,1,1> value_t;
typedef hls::stream<value_t> stream_t;
typedef ap_uint<32> reg32_t;
typedef signed int int32_t;
typedef unsigned int uint32_t;

void matrix_mul(stream_t* As, stream_t* Bs, stream_t* Cs);
void read_data_A(stream_t* As, int32_t A[N][N]);
void read_data_B(stream_t* Bs, int32_t B[N][N]);
void brute_force(int32_t A[N][N], int32_t B[N][N], stream_t* Cs);

#endif
