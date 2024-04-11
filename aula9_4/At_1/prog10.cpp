#include <iostream>
#include <vector>

#include <mpi.h>

void Manager(int manager,int M,int N);
void Worker(int manager);

using namespace std;

int main(int argc,char *argv[])
{
   if (MPI_Init(NULL,NULL) != MPI_SUCCESS)
       MPI_Abort(MPI_COMM_WORLD,911);

   int idproc;
   MPI_Comm_rank(MPI_COMM_WORLD,&idproc);

   int manager=0;

   if (argc != 3) {
       if (idproc == manager) {
           cout << endl << endl << endl
                << "Digite: Nome-do-programa M N"
                << endl << endl << endl;
       }

       MPI_Finalize();
       exit(-1);
   }

   if (idproc == manager) {
       double tstart=MPI_Wtime();
       int M=atoi(argv[1]),N=atoi(argv[2]);

       Manager(manager,M,N);

       double tend=MPI_Wtime();

       cout << "delta T = " << tend-tstart << " segundos" << endl;
   }
   else
       Worker(manager);

   MPI_Finalize();

   return 0;
}

void Manager(int manager,int M,int N)
{
   int nprocs;
   MPI_Comm_size(MPI_COMM_WORLD,&nprocs);

   if (nprocs == 1) {
       cout << endl << endl << endl
            << "Erro: # processos MPI deve ser ao menos 2."
            << endl << endl << endl;

       MPI_Finalize();
       exit(-1);
   }

   vector <double > A(M*N),b(N);

   for (int j=0; j < N; j++)
       b[j]=1;

   for (int i=0; i < M; i++) {
       for (int j=0; j < N; j++)
           A[j+i*N]=i-j;
   }

   MPI_Bcast(&N,1,MPI_INT,manager,MPI_COMM_WORLD);
   MPI_Bcast(&b[0],N,MPI_DOUBLE,manager,MPI_COMM_WORLD);

   int nsent=0;

   for (int i=0; i < min(nprocs-1,M); nsent++,i++)
       MPI_Send(&A[i*N],N,MPI_DOUBLE,i+1,i+1,MPI_COMM_WORLD);

   vector <double > c(M);

   for (int i=0; i < M; i++) {
       double scratch ;
       MPI_Status status;

       MPI_Recv(&scratch,1,MPI_DOUBLE,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&status);

       int worker=status.MPI_SOURCE,row=status.MPI_TAG-1;

       c[row]=scratch;

       if (nsent < M) {
           MPI_Send(&A[nsent*N],N,MPI_DOUBLE,worker,nsent+1,MPI_COMM_WORLD);
           nsent++;
       }
       else
           MPI_Send(MPI_BOTTOM,0,MPI_DOUBLE,worker,0,MPI_COMM_WORLD);
   }

   for (int i=M+1; i < nprocs; i++)
       MPI_Send(MPI_BOTTOM,0,MPI_DOUBLE,i,0,MPI_COMM_WORLD);
}

void Worker(int manager)
{
   vector <int > buff(2);

   int N;
   MPI_Bcast(&N,1,MPI_INT,manager,MPI_COMM_WORLD);

   vector <double > A(N),b(N);

   MPI_Bcast(&b[0],N,MPI_DOUBLE,manager,MPI_COMM_WORLD);

   MPI_Status status;

   while (1) {
       MPI_Recv(&A[0],N,MPI_DOUBLE,manager,MPI_ANY_TAG,MPI_COMM_WORLD,&status);

       if (status.MPI_TAG == 0)
           break ;

       double sum=0.0;
       int row=status.MPI_TAG-1;

       for (int j=0; j < N; j++)
           sum+=A[j]*b[j];

       MPI_Send(&sum,1,MPI_DOUBLE,manager,row+1,MPI_COMM_WORLD);
   }
}
