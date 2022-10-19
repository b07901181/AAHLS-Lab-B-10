#include "matrix_mul.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[]){
	int32_t A[N][N], B[N][N], C[N][N]={0};
	stream_t Ain, Bin, Cout;
	value_t valData;

	cout<<">>Start test!"<<endl;

	valData.data = 0;
	valData.keep = 0xF;
	valData.strb = 0;
	valData.user = 0;
	valData.last = 0;
	valData.id = 0;
	valData.dest = 0;

	//create and input data
	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			if( i*j >= N*N-1 ) valData.last = 1;
			A[i][j] = 1 - i;
			valData.data = 1 - i;
			Ain.write(valData);
			B[i][j] = 2 + j;
			valData.data = 2 + j;
			Bin.write(valData);
		}
	}

	//compute C=A*B in TestBench
	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			for(int k=0; k<N; k++){
				C[i][j] += A[i][k] * B[k][j];
			}
		}
	}

	//run kernel
	matrix_mul(&Ain, &Bin, &Cout);

	//compare result
	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			int32_t out = Cout.read().data;
			if( out != C[i][j] ){
				cout<<"test fail!!"<<endl;
				return 1;
			}
		}
	}

	cout<<"test pass!!"<<endl;
	return 0;
}
