#include <mpi.h>

class CDComm
{
  public:
   static  MPI_Comm* __mpi_comm;
   static  MPI_Group* __mpi_group;
};

