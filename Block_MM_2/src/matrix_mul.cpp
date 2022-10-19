#include "matrix_mul.h"


void matrix_mul(stream_t* As, stream_t* Bs, stream_t* Cs){
#pragma HLS INTERFACE mode=s_axilite port=return
#pragma HLS INTERFACE mode=axis register both port=As
#pragma HLS INTERFACE mode=axis register both port=Bs
#pragma HLS INTERFACE mode=axis register both port=Cs

	int32_t A[N][N];
	int32_t B[N][N];
#pragma HLS ARRAY_PARTITION variable=A type=cyclic factor=8 dim=2 //change block size (factor) here
#pragma HLS ARRAY_PARTITION variable=B type=cyclic factor=8 dim=1 //change block size (factor) here
#pragma HLS ARRAY_PARTITION variable=B type=cyclic factor=4 dim=2 //change VT (factor) here

#pragma HLS DATAFLOW

	read_data_A(As, A);
	read_data_B(Bs, B);
	block_MM(A, B, Cs);

	return;

}

void read_data_A(stream_t* As, int32_t A[N][N]){
	ap_uint<1> tlast = 0;
read_A:
	for(int s=0; s<N*VTN; s++){
		#pragma HLS PIPELINE II=1
		int i = s/VTN;
		int j = s%VTN;
		if( !tlast ){
			value_t valTemp = As -> read();
			int32_vt dataTemp = valTemp.data;
			for(int v=0; v<VT; v++){
				A[i][VT*j+v] = dataTemp[v];
			}
			tlast = valTemp.last;
		}
		else{
			for(int v=0; v<VT; v++){
				A[i][VT*j+v] = 0;
			}
		}
	}
}

void read_data_B(stream_t* Bs, int32_t B[N][N]){
	ap_uint<1> tlast = 0;
read_B:
	for(int s=0; s<N*VTN; s++){
		#pragma HLS PIPELINE II=1
		int i = s/VTN;
		int j = s%VTN;
		if( !tlast ){
			value_t valTemp = Bs -> read();
			int32_vt dataTemp = valTemp.data;
			for(int v=0; v<VT; v++){
				B[i][VT*j+v] = dataTemp[v];
			}
			tlast = valTemp.last;
		}
		else{
			for(int v=0; v<VT; v++){
				B[i][VT*j+v] = 0;
			}
		}
	}
}

void block_MM(int32_t A[N][N], int32_t B[N][N], stream_t* Cs){
	int32_t C[N][N] = {0};
	#pragma HLS ARRAY_PARTITION variable=C type=cyclic factor=4 dim=2 //change VT (factor) here
	value_t valTemp;
	valTemp.keep = 0xF;
	valTemp.strb = 0;
	valTemp.user = 0;
	valTemp.last = 0;
	valTemp.id = 0;
	valTemp.dest = 0;
block_mul:
	for(int kb=0; kb<BN; kb++){
		for(int s=0; s<N*VTN; s++){
			#pragma HLS PIPELINE II=1
			int32_vt dataTemp;
			int i = s/VTN;
			int j = s%VTN;
			for(int v=0; v<VT; v++){
				for(int k=0; k<BL; k++){
					C[i][VT*j+v] += A[i][BL*kb+k]*B[BL*kb+k][VT*j+v];
				}
				dataTemp[v] = C[i][VT*j+v];
			}
			if(kb>=BN-1){
				if(s>=N*VTN-1) valTemp.last = 1;
				valTemp.data = dataTemp;
				Cs -> write(valTemp);
			}
		}
	}

	return;
}
