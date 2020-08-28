/***************************************************************************
 *
 *   File        : tasks.c
 *   Student Id  : <INSERT STUDENT ID HERE>
 *   Name        : <INSERT STUDENT NAME HERE>
 *
 ***************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <string.h>
#include "tasks.h"

#define OUTPUT_FILE "task1.csv"
#define TASK1COL 6
#define X 0
#define Y 1
#define U 2
#define V 3
#define RHO 4

typedef struct {
  double x, y, u, v, rho, flux;
} row_t;

void *safe_malloc(size_t bytes);

void max_min_flux(const char* flow_file)
{

    int counter = 0;

    double x, y , u , v, rho;
    row_t row_where_u_rho_is_max, row_where_u_rho_is_min, row_where_v_rho_is_max, row_where_v_rho_is_min;
    //
    // row_t* row_where_u_rho_is_max = (row_t*)safe_malloc(sizeof(row_t));
    // row_t* row_where_u_rho_is_min = (row_t*)safe_malloc(sizeof(row_t));
    // row_t* row_where_v_rho_is_max = (row_t*)safe_malloc(sizeof(row_t));
    // row_t* row_where_v_rho_is_min = (row_t*)safe_malloc(sizeof(row_t));

    FILE *fp_in = fopen(flow_file, "r"); //open file and read only
    FILE *fp_out = fopen(OUTPUT_FILE, "w"); // open file and write only

    //exit if file doesn't exist
    if(fp_in == NULL) {
      perror("Error opening file");
      exit(EXIT_FAILURE);
    }
    // discard first line
    fscanf(fp_in, "%*[^\n]");

    /* while x, y , u, v, rho exists, and if x is larger than 20, then print to
    new file */
    while(fscanf(fp_in,"%lf,%lf,%lf,%lf,%lf\n", &x, &y, &u, &v, &rho) == 5){
        if (x <= 20.0) {
          continue;
        }
        //set first row read as min/max
        if (counter == 0) {

          row_where_u_rho_is_min = row_where_u_rho_is_max =
            (row_t){x, y, u, v, rho, u*rho};
          row_where_v_rho_is_min = row_where_v_rho_is_max =
            (row_t){x, y, u, v, rho, v*rho};
        }

        // now find max and min
        if (row_where_u_rho_is_max.flux < u*rho) {
          row_where_u_rho_is_max.flux = u*rho;
          row_where_u_rho_is_max.x = x;
          row_where_u_rho_is_max.y = y;
          row_where_u_rho_is_max.u = u;
          row_where_u_rho_is_max.v = v;
          row_where_u_rho_is_max.rho = rho;
        }

        if (row_where_u_rho_is_min.flux > u*rho) {
          row_where_u_rho_is_min.flux = u*rho;
          row_where_u_rho_is_min.x = x;
          row_where_u_rho_is_min.y = y;
          row_where_u_rho_is_min.u = u;
          row_where_u_rho_is_min.v = v;
          row_where_u_rho_is_min.rho = rho;
        }

        if (row_where_v_rho_is_max.flux < v*rho) {
          row_where_v_rho_is_max.flux = v*rho;
          row_where_v_rho_is_max.x = x;
          row_where_v_rho_is_max.y = y;
          row_where_v_rho_is_max.u = u;
          row_where_v_rho_is_max.v = v;
          row_where_v_rho_is_max.rho = rho;
        }

        if (row_where_v_rho_is_min.flux > v*rho) {
          row_where_v_rho_is_min.flux = v*rho;
          row_where_v_rho_is_min.x = x;
          row_where_v_rho_is_min.y = y;
          row_where_v_rho_is_min.u = u;
          row_where_v_rho_is_min.v = v;
          row_where_v_rho_is_min.rho = rho;
        }

        counter++;
      }
        fprintf(fp_out, "%.6lf,%.6lf,%.6lf,%.6lf,%.6lf,%.6lf\n", row_where_u_rho_is_max.x, row_where_u_rho_is_max.y,
          row_where_u_rho_is_max.u , row_where_u_rho_is_max.v, row_where_u_rho_is_max.rho, row_where_u_rho_is_max.flux);

        fprintf(fp_out, "%.6lf,%.6lf,%.6lf,%.6lf,%.6lf,%.6lf\n", row_where_u_rho_is_min.x, row_where_u_rho_is_min.y,
          row_where_u_rho_is_min.u , row_where_u_rho_is_min.v, row_where_u_rho_is_min.rho, row_where_u_rho_is_min.flux);

        fprintf(fp_out, "%.6lf,%.6lf,%.6lf,%.6lf,%.6lf,%.6lf\n", row_where_v_rho_is_max.x, row_where_v_rho_is_max.y,
          row_where_v_rho_is_max.u , row_where_v_rho_is_max.v, row_where_v_rho_is_max.rho, row_where_v_rho_is_max.flux);

        fprintf(fp_out, "%.6lf,%.6lf,%.6lf,%.6lf,%.6lf,%.6lf\n", row_where_v_rho_is_min.x, row_where_v_rho_is_min.y,
          row_where_v_rho_is_min.u , row_where_v_rho_is_min.v, row_where_v_rho_is_min.rho, row_where_v_rho_is_min.flux);



      //close files
      fclose(fp_in);
      fclose(fp_out);
      //printf("total number of lines is %d\n", num_total);

    printf("max_min_flux() - IMPLEMENT ME!\n");
}

void coarsegrid(const char* flow_file, int grid_resolution)
{
    printf("coarsegrid() - IMPLEMENT ME!\n");
}

void searching(const char* flow_file)
{
    printf("searching() - IMPLEMENT ME!\n");
}

void calculate_vorticity(const char* flow_file, int vorticity_numthreshold)
{
    printf("calculate_vorticity() - IMPLEMENT ME!\n");
}

//function definitions
void *safe_malloc(size_t bytes) {
  void *ptr = malloc(bytes);
  if (ptr == NULL) {
    printf("Failed to allocate %lu bytes\n", bytes);
    exit(EXIT_FAILURE);
  }
  return ptr;
}
