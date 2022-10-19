#include "matrix_mul.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[]){
	int32_t A[N][N], B[N][N], C[N][N]={0};
	stream_t Ain, Bin, Cout;
	int32_vt Av, Bv;
	value_t valData;
	//tlast check
	//ap_uint<1> tlastChk[N*VTN];

	cout<<">>Start test!"<<endl;

	cout<<"vector size: "<<sizeof(int32_vt)<<endl;

	valData.keep = 0xF;
	valData.strb = 0;
	valData.user = 0;
	valData.last = 0;
	valData.id = 0;
	valData.dest = 0;

	//create and input data
	for(int i=0; i<N; i++){
		for(int j=0; j<VTN; j++){
			for(int v=0; v<VT; v++){
				A[i][VT*j+v] = 1 - i;
				Av[v] = 1 - i;
				B[i][VT*j+v] = 1 + j + v;
				Bv[v] = 1 + j + v;
			}
			if(i*j>=N*VTN-1) valData.last = 1;
			valData.data = Av;
			Ain.write(valData);
			valData.data = Bv;
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
		for(int j=0; j<VTN; j++){
			valData = Cout.read();
			//tlast check
			//tlastChk[i*VTN + j] = valData.last;
			int32_vt dataTemp = valData.data;
			for(int v=0; v<VT; v++){
				if(dataTemp[v]!=C[i][VT*j+v]){
					cout<<"test fail!!"<<endl;
					return 1;
				}
			}
		}
	}

	/*//tlast checking
	cout<<"tlast check list:"<<endl;
	for(int s=0; s<N*VTN-1; s++){
		cout<<tlastChk[s]<<", ";
	}
	cout<<tlastChk[N*VTN-1]<<endl;
	*/

	if(!valData.last){
		cout<<"test fail with no TLAST output!!"<<endl;
		return 1;
	}

	cout<<"test pass!!"<<endl;
	return 0;
}
