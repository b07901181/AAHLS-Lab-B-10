#include "matrix_mul.h"


void matrix_mul(stream_t* As, stream_t* Bs, stream_t* Cs){
#pragma HLS INTERFACE mode=s_axilite port=return
#pragma HLS INTERFACE mode=axis register both port=As
#pragma HLS INTERFACE mode=axis register both port=Bs
#pragma HLS INTERFACE mode=axis register both port=Cs

	int32_t A[N][N];
	int32_t B[N][N];
#pragma HLS ARRAY_PARTITION variable=A type=cyclic factor=32 dim=2 //change block (factor) size here
#pragma HLS ARRAY_PARTITION variable=B type=cyclic factor=32 dim=1 //change block (factor) size here

#pragma HLS DATAFLOW

	read_data_A(As, A);
	read_data_B(Bs, B);
	block_MM(A, B, Cs);

	return;

}

void read_data_A(stream_t* As, int32_t A[N][N]){
	ap_uint<1> tlast = 0;
read_A:
	for(int s=0; s<N*N; s++){
		#pragma HLS PIPELINE II=1
		int i = s/N;
		int j = s%N;
		if( !tlast ){
			value_t valTemp = As -> read();
			A[i][j] = valTemp.data;
			tlast = valTemp.last;
		}
		else{
			A[i][j] = 0;
		}
	}
}

void read_data_B(stream_t* Bs, int32_t B[N][N]){
	ap_uint<1> tlast = 0;
read_B:
	for(int s=0; s<N*N; s++){
		#pragma HLS PIPELINE II=1
		int i = s/N;
		int j = s%N;
		if( !tlast ){
			value_t valTemp = Bs -> read();
			B[i][j] = valTemp.data;
			tlast = valTemp.last;
		}
		else{
			B[i][j] = 0;
		}
	}
}

void block_MM(int32_t A[N][N], int32_t B[N][N], stream_t* Cs){
	int32_t C[N][N] = {0};
	value_t valTemp;
	valTemp.data = 0;
	valTemp.keep = 0xF;
	valTemp.strb = 0;
	valTemp.user = 0;
	valTemp.last = 0;
	valTemp.id = 0;
	valTemp.dest = 0;
	for(int kb=0; kb<BN; kb++){
		for(int s=0; s<N*N; s++){
			for(int k=0; k<BL; k++){
				#pragma HLS LOOP_FLATTEN
				#pragma HLS UNROLL factor=32 //change unroll factor here
				int i = s/N;
				int j = s%N;
				C[i][j] += A[i][BL*kb+k] * B[BL*kb+k][j];
				if(kb >= BN-1 && k>= BL-1){
					if(s >= N*N-1) valTemp.last = 1;
					valTemp.data = C[i][j];
					Cs -> write(valTemp);
				}
			}
		}
	}

	return;
}
