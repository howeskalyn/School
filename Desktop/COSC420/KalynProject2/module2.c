
/*

  Chloe VanCory,  Kalyn Howes & Bevan Smith
  COSC 420
  11/ 20 /2021
  Project 2



*/

#include <ctype.h>
#include <fcntl.h>
#include <mpi.h>
#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#include "matrixFunctions.c"

#define ROOT 0
// const unsigned long  CITATIONBYTES = 119367527;




void printbuffer(double *buf, int size) {
  for (int i = 0; i < size; i++) {
    printf("arr=%f\n", buf[i]);
  }
}

int *findCounts(int count, int worldsize) {
  int *temp = malloc(worldSize * sizeof(int));

  int minSend = count / worldSize;
  // printf("minsend=%d \n", minSend);
  for (int i = 0; i < worldSize; i++) {
    temp[i] = minSend;
  }

  for (int i = 0; i < count % worldSize; i++) {
    temp[i]++;
  }
  return temp;
}

void everyonePrint(int rank, char *str, int *arr) {
  printf("Rank =%d %s=%d\n", rank, str, arr[rank]);
}

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
  NotUsed = 0;
  for (int i = 0; i < argc; i++) {
    // printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
  }
  // printf("\n");

  // if(argv[0] !=  NULL) 
  //   return argv[0];


  return 0;
}


typedef struct rows {
  int globalID;
  int length;
  int *data;  // Holds the global index from db that this paper cites
} rows;



//  QUESTION - DOES THIS NEED TO HAVE THE GLBAL PAPER ID ALSO?
// is it a int * ?? because it is just holding either a 0 or 1


int main(int argc, char **argv) {
  MPI_Init(&argc, &argv);
  world = MPI_COMM_WORLD;

  // passing the container for the result in second param
  MPI_Comm_size(world, &worldSize);
  MPI_Comm_rank(world, &rank);
  MPI_Get_processor_name(name, &nameLen);
  

  // for powermethod 
  // int THRESHOLD = atoi(argv[3]);
  int THRESHOLD = 5;
  double e = 10E-16;

  /***** Open Database ******/
  sqlite3 *db;
  char *err_msg = 0;
  sqlite3_stmt *res;

  int rc = sqlite3_open("meta.db", &db);

  if (rc != SQLITE_OK) {
    fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);

    return 1;
  }



  // opens the citation file
  FILE *fp;
  fp = fopen("testCitations.txt", "r");
  int TOTALPAPERS = 50;

  // int TOTALPAPERS = 1354753;
  // fp = fopen("arxiv-citations.txt", "r");

  if (fp == NULL) printf("ERROR opening file ");

  // // tracks the amount of papers each proc will read in
  int *localPapercount = findCounts(TOTALPAPERS, worldSize);

  // //based on localpapercount , calc the bytes ( ie cant divide bytes /
  // worldsize since the file wouldnt be parsed correctly in every case)
  int *sendcnt = malloc(worldSize * sizeof(int));


  // vector being used for the powermethod ( will be scatter and gathered )
  // easier than scattering the struct 
  Matrix Matrixlengths; 
  Matrixlengths.rows = TOTALPAPERS;
  Matrixlengths.cols = 1;
  // // printf("rank=%d rows =%d \n", rank,  Matrixlengths.rows);


  // initialize & allocate MatrixA for power method
  /* assume there are at least 10 citations and allocate, if more than
  reallocate later */
  rows * matrixA = malloc(TOTALPAPERS * 2 * sizeof(int) * sizeof(int* )); // SEG FAULTING this line only 
  int MALLOCEDSIZE = 10;
  if (rank == ROOT) {
    Matrixlengths.data = malloc(Matrixlengths.rows * Matrixlengths.cols * sizeof(int));
    if(Matrixlengths.data == NULL){ printf("error malloc matrixlengths"); return 1; }

    for (int i = 0; i < TOTALPAPERS; i++) {
      matrixA[i].data = malloc(MALLOCEDSIZE * sizeof(int));
      matrixA[i].length = 0;
      matrixA[i].globalID = -1;  
      Matrixlengths.data[i] = 0; 

    }
  } else{
    Matrixlengths.data = NULL; 
  }


  // /* does calcs for number of bytes every proc needs to read in based on even
  //  * division of papers */
  if (rank == ROOT) {
    char *line = NULL;
    int numread;
    int curPaperCount = 0;  // index of the current paper we are looking at in the list

    int i = 0;
    for (i = 0; i < worldSize; i++) sendcnt[i] = 0;  // initalize the sendcounts = 0

    int citedCount = 0;  // counts the len of "rows" array
    size_t len = 0;      // used by getline function (gets returned a power of 2
                         // corresponding to bytes read)

    int matrixA_it = 0;      // traverse through A arrary
    int checkCitations = 0;  // ensures the name being read in is a cited paper
                             // and an actual paperID

    

    while ((numread = getline(&line, &len, fp)) != -1) {
      
      int length = strlen(line);
      sendcnt[i] += numread;  // tracks the total amount of bytes
                              // printf("line: %s count: %zu\n", line, len);


      // TODO: store the paper id of the paper being read in currently 
      // citations are being counted, and their global ID is stored in matrixA
      if (checkCitations == 1 && line[0] != '+') {

        matrixA[matrixA_it].length++;
        Matrixlengths.data[matrixA_it]++;

        // printf("matrixA_it =%d %s\n", matrixA_it , line);
        line[length-1] = 0; // removes the newline


        char *query = "select ind from Meta where id=";
        char * test = malloc(200);
        sprintf(test, "%s \'%s\';",  query, line);
          // printf("%s\n", test);


        rc = sqlite3_prepare_v2(db, test, -1, &res, 0);
        int step = sqlite3_step(res);
        if (step == SQLITE_ROW) {
          // printf("%s\n", sqlite3_column_text(res, 0));
        } 
    
        int returnedIndex = (int) sqlite3_column_int(res, 0);


        int dataIT = matrixA[matrixA_it].length-1;
        matrixA[matrixA_it].data[dataIT] = returnedIndex ;
        // printf(" data =%d retrun index =%d\n",  matrixA[matrixA_it].data[dataIT], dataIT);
        //  printf(" data=%d          dataIT =%d ----\n",  dataIT);


        // more than 10 citations , need to realloc the data array
        // if(matrixA[matrixA_it].length > MALLOCEDSIZE ){
        //   int newSize = matrixA[matrixA_it].length * 2; // curent length * 2,
        //   first resize occurs after 10 citations matrixA[matrixA_it].data =
        //   (int*) realloc( matrixA[matrixA_it].data  , newSize * sizeof(int));

        // }

      } else if (checkCitations == 1 && line[0] == '+') {
        checkCitations = 0;
        // TODO: should i free it if it has no citations at all
      }

      // printf("length=%d \n", length);
      // printf("line[len-1]=%c  line[len] =%c ",line[length-2] , line[length-1]
      // );

      // indicates that the next line will be the list of cited papers if there are any 
      if (line[length - 2] == '-' && line[length - 1] == '\n') {
        // citedCount++;
        // matrixA[curPaperCount].length++;
        // // printf("ENTER \n");
        checkCitations = 1;  // the next name you read in is a citation
      }

      // indicates a new paper is being read in 
      if (line[0] == '+') {
        curPaperCount++;
        matrixA_it++;


        if (curPaperCount == localPapercount[i]) {
          // printf("citedCount=%d \n", citedCount);
          citedCount = 0;  // resets the cited count

          i++;
          curPaperCount = 0;
        }
      }

      free(line);
      line = NULL;
      len = 0;
    }
  }

 
  // //  printing results
  if (rank == ROOT) {
    for (int i = 0; i < TOTALPAPERS; i++) {
      printf("i=%d matrixA.length= %d\n", i, matrixA[i].length );
    }
  }

  MPI_Barrier(world);
  /* preparing for the powermethod */
  Matrix X; 
  X.rows = TOTALPAPERS;
  X.cols = 1;
  X.data= malloc(X.rows * X.cols * sizeof(double));
  // printf("RANK =%d localX rows= %d cols=%d\n", rank,X.rows,X.cols);


  /* set X to the 1's vector */
  for(int i =0 ;i < X.rows* X.cols; i++) X.data[i] = 1;



  SGData matrix_counts = getSGCounts(Matrixlengths.rows, Matrixlengths.cols , worldSize);
  // everyonePrint(rank, "count", matrix_counts.cnts);
  // everyonePrint(rank, "displs", matrix_counts.displs);
  // printf("Matrixlengths rank =%d rows=%d cols =%d \n",rank, Matrixlengths.rows, Matrixlengths.cols);


  Matrix local_A;
  local_A.rows = matrix_counts.cnts[rank] ;
  local_A.cols = 1;
  local_A.data = malloc(local_A.rows* local_A.cols* sizeof(double));
  // printf("localA rank =%d rows=%d cols =%d \n",rank, local_A.rows, local_A.cols);

  MPI_Scatterv(
            Matrixlengths.data,         // sendbuf
            matrix_counts.cnts,        // sendcnts
            matrix_counts.displs,      // displacements
            MPI_DOUBLE,               // datatype
            local_A.data,              // recvbuf
            matrix_counts.cnts[rank],  // recvcnt
            MPI_DOUBLE, ROOT, world);

    
  // char *arrbuf = bufArr(local_A.data, matrix_counts.cnts[rank]);
  // printf("Rank %d received %s\n", rank, arrbuf);  

  double eigenvalue = powerMethod(local_A, X,  Matrixlengths.rows , Matrixlengths.cols, THRESHOLD, e);

  if(rank ==0 )printf("EIGENVALUE= %f\n",eigenvalue );

  /*
  where i left off:
  - do we need to log the paperid of the one we are loading in (could be the
  global index query from db )
  - should i free the data arr of there is no data present there
  - powermethod needs to end once there is no change in iterations  

  todo :
  - power method 
  - update the new matrixA vector or insert it into the database based off of the global ID 


  */






  // puts("finish");
  sqlite3_close(db);
  MPI_Finalize();
 
  return 0;
}
