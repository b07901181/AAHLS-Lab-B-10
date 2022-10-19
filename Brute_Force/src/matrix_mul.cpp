#include "matrix_mul.h"


void matrix_mul(stream_t* As, stream_t* Bs, stream_t* Cs){
#pragma HLS INTERFACE mode=s_axilite port=return
#pragma HLS INTERFACE mode=axis register both port=As
#pragma HLS INTERFACE mode=axis register both port=Bs
#pragma HLS INTERFACE mode=axis register both port=Cs

	int32_t A[N][N];
	int32_t B[N][N];
#pragma HLS ARRAY_PARTITION variable=A type=complete dim=2
#pragma HLS ARRAY_PARTITION variable=B type=complete dim=1

#pragma HLS DATAFLOW

	read_data_A(As, A);
	read_data_B(Bs, B);
	brute_force(A, B, Cs);

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

void brute_force(int32_t A[N][N], int32_t B[N][N], stream_t* Cs){
	value_t valTemp;
	valTemp.keep = 0xF;
	valTemp.strb = 0;
	valTemp.user = 0;
	valTemp.last = 0;
	valTemp.id = 0;
	valTemp.dest = 0;
brute_force:
	for(int s=0; s<N*N; s++){
		#pragma HLS PIPELINE II=1
		int i = s/N;
		int j = s%N;
		int32_t Cij = 0;
		for(int k=0; k<N; k++){
			Cij += A[i][k] * B[k][j];
		}
		valTemp.data = Cij;
		if( s>=N*N-1 ) valTemp.last = 1;
		Cs -> write(valTemp);
	}

	return;
}
