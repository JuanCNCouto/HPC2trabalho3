#include <iostream>
#include <vector>
#include <mpi.h>


//Faça um programa que crie uma matriz A de tamanho M x N, alocando A[i][j]. Inicialize a
//matriz fazendo A[i][j]=i+j. Verifique o tempo de execução em função do tamanho da matriz. Faça isso
//com o loop mais interno sendo j e o mais interno sendo i e depois inverta. Repita o procedimento
//alocando A[MxN] e inicialize seus elementos fazendo A[j+i*N]=i+j. Compare, utilizando gráficos, os
//tempos de execução nos dois casos, em função do tamanho da matriz.
using namespace std;

int main()
{
	int M=atoi(argv[1]),N=atoi(argv[2]);
	double **a = new double*[M];
		for (int i=0; i < M; i++)
			a[i]=new double[N];

	for(int j=0;j<N;j++)
		for(int i=0;i<M;i++)
			a[i][j]=i+j;
}

//Faça um programa que crie uma matriz A de tamanho M x N, alocando A[i][j]. Inicialize a
//matriz fazendo A[i][j]=i+j. Verifique o tempo de execução em função do tamanho da matriz. Faça isso
//com o loop mais interno sendo j e o mais interno sendo i e depois inverta. Repita o procedimento
//alocando A[MxN] e inicialize seus elementos fazendo A[j+i*N]=i+j. Compare, utilizando gráficos, os
//tempos de execução nos dois casos, em função do tamanho da matriz.

