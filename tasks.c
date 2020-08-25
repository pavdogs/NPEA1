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

typedef struct {
  double x, y, u, v, rho;
} data_t;


void max_min_flux(const char* flow_file)
{
    double x= 0.0, y = 0.0, u = 0.0, v = 0.0 , rho = 0.0;
    int num_total = 0;
    int num_lines = 0;

    FILE *fp_in = fopen("flow_file.csv", "r"); //open file and read only
    FILE *fp_out = fopen("task1_sample.csv", "w"); // open file and write only

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
        num_total++;
        if (x > 20.0) {
        fprintf(fp_out, "%.6lf,%.6lf,%.6lf,%.6lf,%.6lf\n", x, y, u , v, rho);
        }
      }

      //close files
      fclose(fp_in);
      fclose(fp_out);
      printf("total number of lines is %d", num_total);

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