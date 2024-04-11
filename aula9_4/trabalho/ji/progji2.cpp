#include <iostream>
#include <vector>
#include <mpi.h>
#include <chrono>


//Faça um programa que crie uma matriz A de tamanho M x N, alocando A[i][j]. Inicialize a
//matriz fazendo A[i][j]=i+j. Verifique o tempo de execução em função do tamanho da matriz. Faça isso
//com o loop mais interno sendo j e o mais interno sendo i e depois inverta. Repita o procedimento
//alocando A[MxN] e inicialize seus elementos fazendo A[j+i*N]=i+j. Compare, utilizando gráficos, os
//tempos de execução nos dois casos, em função do tamanho da matriz.
using namespace std;

int main(int argc,char *argv[])
{
	int M,N;

	for(M=10000;M<30000;M+=1000)
	{
		auto start = std::chrono::steady_clock::now();
		double **a = new double*[M];
		for (int i=0; i < M; i++)
			a[i]=new double[M];

		for(int j=0;j<M;j++)
			for(int i=0;i<M;i++)
				a[i][j]=i+j;

		auto end = std::chrono::steady_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

    // Convertendo a duração para um tipo double
   		 double duration_seconds = duration.count() / 1e9;
		cout << M << " " << duration_seconds << endl;
			
		delete a;
	}
}

//Faça um programa que crie uma matriz A de tamanho M x N, alocando A[i][j]. Inicialize a
//matriz fazendo A[i][j]=i+j. Verifique o tempo de execução em função do tamanho da matriz. Faça isso
//com o loop mais interno sendo j e o mais interno sendo i e depois inverta. Repita o procedimento
//alocando A[MxN] e inicialize seus elementos fazendo A[j+i*N]=i+j. Compare, utilizando gráficos, os
//tempos de execução nos dois casos, em função do tamanho da matriz.

