#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char **argv){
  int numproc; //num de procesos
  int miproc; // id de proceso
  MPI_Status status;
  int msg[] = {0}; //valor que estamos sumando
  int m = 2;  //cantidad de ciclos
  

  MPI_Init (&argc, &argv); /* Inicializar MPI */
  MPI_Comm_rank(MPI_COMM_WORLD,&miproc); /* Determinar el rango del proceso invocado*/
  MPI_Comm_size(MPI_COMM_WORLD,&numproc); /* Determinar el numero de procesos */  
  
  if (miproc == 0){ 
    MPI_Send(&msg, sizeof(msg), MPI_CHAR, 1, 0, MPI_COMM_WORLD);
  }

  for (int cycle = 0; cycle < m; cycle++){
    int prev = miproc-1; // proceso anterior
    if(miproc == 0){
      prev = numproc-1;
    } 
    MPI_Recv(&msg, sizeof(msg), MPI_CHAR, prev, 0, MPI_COMM_WORLD, &status);

    int i = prev + 1 + numproc * cycle;
    msg[0]+=i; // sumar acumulativa de todos los i

    int next = miproc+1; // proceso siguiente
    if(miproc == numproc-1){
      next = 0;
    }
    MPI_Send(&msg, sizeof(msg), MPI_CHAR, next, 0, MPI_COMM_WORLD);
  }

  if (miproc == 0){
    printf("Resultado: %d",msg[0]);
  }

  
  //MPI_Barrier (MPI_COMM_WORLD); 

  MPI_Finalize ();

  return 0;

}


