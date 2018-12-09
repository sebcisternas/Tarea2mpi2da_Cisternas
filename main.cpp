#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mpi.h"
#include <time.h>
using namespace std;

void num_random(int n, int a[]){
   srand(time(NULL));
    for(int i=0;i<n;i++){
        a[i]=rand();
    }
}

float promedio(int n, int a[]){
    
    float sum=0;

    for(int i=0;i<n;i++){
        sum=sum+a[i];
    }
    sum=sum/n;

    return sum;
}

float varianza(int n, int a[]){
   
    float sum=0,prom,var;
    prom=promedio(n,a);

    for(int i=0;i<n;i++){
        sum=sum+pow(prom-a[i], 2);

    }

    var=sum/(n-1);

    return var;
}

float desviacion(int n, int a[]){
    float var,des;
    var=varianza(n, a);
    des=sqrt(var);
    return des;
}

int main(int argc, char *argv[])
{

    int n=10000,a[n],size,rank;
    float prom,var,des;
	

	MPI_Status state;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	num_random(n, a);

	

	if(rank==1){
	prom=promedio(n, a);
	MPI_Recv(&var, 1, MPI_FLOAT, 2, 1, MPI_COMM_WORLD, &state);
	MPI_Recv(&des, 1, MPI_FLOAT, 3, 1, MPI_COMM_WORLD, &state);
        cout<<"El promedio es = "<<prom<<endl;
        cout<<"La varianza es = "<<var<<endl;
        cout<<"La desviacion estandar es = "<<des<<endl;
    }
	if(rank==2){
            var=varianza(n, a);
			MPI_Send(&var, 2, MPI_FLOAT, 1, 1, MPI_COMM_WORLD);
				
    if(rank==3){
			des=desviacion(n, a);

			MPI_Send(&des, 1, MPI_FLOAT, 1, 1, MPI_COMM_WORLD);
    }
		
	}

	MPI_Finalize();

    return 0;
}

