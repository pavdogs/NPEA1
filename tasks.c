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
#include <assert.h>
#include "tasks.h"

#define OUTPUT_FILE1 "task1.csv"
#define OUTPUT_FILE2 "task2.csv"
#define TASK1COL 6
#define OUTPUTROWS 4
#define LOWERBOUND_X -10
#define UPPERBOUND_X 80
#define LOWERBOUND_Y -18
#define UPPERBOUND_Y 18
#define OUTPUT_FILE3 "task3.csv"

//data type
typedef struct {
   double x, y, u, v, rho, flux;
} row_t;

// /* node type */
// typedef struct point point_t;

// struct  {
//     void* point; 
//     point_t* next;
// };

//  linked list type 
// typedef struct {
//     int num_elements;
//     point_t* head;
//     point_t* tail;
//     void (*del)(void*);
// } list_t;


void *safe_malloc(size_t bytes);

void max_min_flux(const char* flow_file)
{

    int counter = 0;

    double x, y , u , v, rho;
    row_t row_u_rho_is_max, row_u_rho_is_min, row_v_rho_is_max, row_v_rho_is_min;

    FILE *fp_in = fopen(flow_file, "r"); //open file and read only
    FILE *fp_out = fopen(OUTPUT_FILE1, "w"); // open file and write only

    //exit if file doesn't exist
    if (fp_in == NULL) {
      perror("Error opening file");
      exit(EXIT_FAILURE);
    }
    // discard first line
    fscanf(fp_in, "%*[^\n]");

    /* while x, y , u, v, rho exists, and if x is larger than 20, then print to
    new file */

  
    while(fscanf(fp_in,"%lf,%lf,%lf,%lf,%lf\n", &x, &y, &u, &v, &rho) == 5) {
        // skip row if x less than 20
        if (x <= 20.0) {
          continue;
        }
        //set first row read as min/max
        if (counter == 0) {
          row_u_rho_is_max = row_u_rho_is_min = (row_t){x,y,u,v,rho,u*rho};
          row_v_rho_is_max = row_v_rho_is_min = (row_t){x,y,u,v,rho,v*rho};
        }

        // now find max and min
        if (row_u_rho_is_max.flux < u*rho) {
          // free(row_u_rho_is_max);
          // row_u_rho_is_max = (row_t){x,y,u,v,u*rho};
          row_u_rho_is_max.flux = u*rho;
          row_u_rho_is_max.x = x;
          row_u_rho_is_max.y = y;
          row_u_rho_is_max.u = u;
          row_u_rho_is_max.v = v;
          row_u_rho_is_max.rho = rho;
        }

        if (row_u_rho_is_min.flux > u*rho) {
          row_u_rho_is_min.flux = u*rho;
          row_u_rho_is_min.x = x;
          row_u_rho_is_min.y = y;
          row_u_rho_is_min.u = u;
          row_u_rho_is_min.v = v;
          row_u_rho_is_min.rho = rho;
        }

        if (row_v_rho_is_max.flux < v*rho) {
          row_v_rho_is_max.flux = v*rho;
          row_v_rho_is_max.x = x;
          row_v_rho_is_max.y = y;
          row_v_rho_is_max.u = u;
          row_v_rho_is_max.v = v;
          row_v_rho_is_max.rho = rho;
        }

        if (row_v_rho_is_min.flux > v*rho) {
          row_v_rho_is_min.flux = v*rho;
          row_v_rho_is_min.x = x;
          row_v_rho_is_min.y = y;
          row_v_rho_is_min.u = u;
          row_v_rho_is_min.v = v;
          row_v_rho_is_min.rho = rho;
        }

      counter++;
    }
    //now print outputs
    fprintf(fp_out, "x,y,u,v,rho\n");
    fprintf(fp_out, "Number of lines read is %d\n", counter);
    // // print_task1_output( &row_u_rho_is_max);
    // // print_task1_output( &row_u_rho_is_min);
    // // print_task1_output( &row_v_rho_is_max);
    // // print_task1_output( &row_v_rho_is_min);
    //
    row_t outputs[OUTPUTROWS] = {row_u_rho_is_max, row_u_rho_is_min, row_v_rho_is_max, row_v_rho_is_min};
    for (int i = 0; i<OUTPUTROWS; i++){
      //  print_task1_row(&outputs[i], fp_out);
      row_t store = outputs[i];
      fprintf(fp_out, "%.6lf,%.6lf,%.6lf,%.6lf,%.6lf,%.6lf\n", store.x, store.y,
     store.u , store.v, store.rho, store.flux);
    }

    //close files
    fclose(fp_in);
    fclose(fp_out);

    printf("max_min_flux() - IMPLEMENT ME!\n");
}

void coarsegrid(const char* flow_file, int grid_resolution)
{
    double gridsize[grid_resolution][grid_resolution];
    float width_x, width_y;
    int cell_val_x, cell_val_y;
    double x, y , u , v, rho;
    int i;

    FILE *fp_in = fopen(flow_file, "r"); //open file and read only
    FILE *fp_out = fopen(OUTPUT_FILE2, "w"); // open file and write only

    //check that file exists
    if (fp_in == NULL) {
      perror("Error opening file");
      exit(EXIT_FAILURE);
    }



    // make 2d array 
    list_t **grid = (list_t**)safe_malloc(grid_resolution * sizeof(list_t*));
    for (i = 0; i < grid_resolution; i++) { 
      grid[i] = (list_t*)safe_malloc(grid_resolution * sizeof(list_t));
    }



    //set cell width 
    width_x = 1.0 * (- LOWERBOUND_X + UPPERBOUND_X) / grid_resolution;
    width_y = 1.0 * (- LOWERBOUND_Y + UPPERBOUND_Y) / grid_resolution;
    printf("Width size of x is %f, width size of y is %f\n", width_x, width_y);

    int offset_x = floor((- LOWERBOUND_X) / width_x);
    int offset_y = floor((- LOWERBOUND_Y) / width_y);

    // discard first line
    fscanf(fp_in, "%*[^\n]");

    //store x value in appropriate x cell 
    while(fscanf(fp_in,"%lf,%lf,%lf,%lf,%lf\n", &x, &y, &u, &v, &rho) == 5) {

      //finding what cell the x value belongs to 
      // so far, this if statement works. 
      if ( (x > LOWERBOUND_X) && (x < UPPERBOUND_X) && (y > LOWERBOUND_Y) && (y < UPPERBOUND_Y)) {
        cell_val_x = floor(x / width_x) + offset_x;
        cell_val_y = floor(y / width_y) + offset_y; 
        fprintf(fp_out, "The cell x goes into is %d, the cell y goes into is %d,",cell_val_x, cell_val_y);
        fprintf(fp_out, "x y is %lf,%lf\n", x,y);
      }
      else {
        continue;
      }


      }


     





    printf("coarsegrid() - IMPLEMENT ME!\n");
}

void searching(const char* flow_file)
{
  double x, y , u , v, rho, rho_v;

  // row_t *array_task3 = NULL;
  // int i=0;
  // FILE *fp_in = fopen(flow_file, "r"); //open file and read only
  // FILE *fp_out = fopen(OUTPUT_FILE3, "w"); // open file and write only

  // //exit if file doesn't exist
  // if (fp_in == NULL) {
  //   perror("Error opening file");
  //   exit(EXIT_FAILURE);
  // }
  // // discard first line
  // fscanf(fp_in, "%*[^\n]");

  // /* while x, y , u, v, rho exists, and while y = 0.0, then print to new file */

  // while(fscanf(fp_in,"%lf,%lf,%lf,%lf,%lf\n", &x, &y, &u, &v, &rho) == 5) {
  //   if ( y == 0.0) { 
  //      fscanf(fp_in,"%d %s %s %d %d %d\n",&array_task3[i].x,&array_task3[i].y,&array_task3[i].u,&array_task3[i].v,
  //       &array_task3[i].rho,&array_task3[i].flux);
  //      fprintf(fp_out, "Values read are %lf,%lf,%lf,%lf,%lf,%lf\n",
  //        array_task3[i].x,array_task3[i].y,array_task3[i].u,array_task3[i].v,
  //       array_task3[i].rho,array_task3[i].flux);
  //      i++;

  //     // x = array_task3[counter].x;
  //     // y = array_task3[counter].y;
  //     // u = array_task3[counter].u;
  //     // v = array_task3[counter].v;
  //     // rho = array_task3[counter].rho;
  //     // rho_v = rho*v;
  //     // rho_v = array_task3[counter].flux; // stores rho*v value which will need to sort ascending later
  //     // fprintf(fp_out, "Values read are %lf,%lf,%lf,%lf,%lf,%lf\n",
  //     //   &array_task3[counter].x,&array_task3[counter].y,&array_task3[counter].u,&array_task3[counter].v,
  //     //   &array_task3[counter].rho,&array_task3[counter].flux);
  //     // counter++;
  //   }
  // }

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

// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// LINKED LIST
// 
// 
// 
// 
// 


// /create new linked list 
list_t* list_new(void (*delfunc)(void*))
{
    list_t* list;
    list = (list_t*)malloc(sizeof(list_t));
    assert(list != NULL);
    list->head = NULL;
    list->tail = NULL;
    list->num_elements = 0;
    list->del = delfunc;
    return list;
}

//add node at front of list 
void list_push_front(list_t* list, void* d) 
{
    assert(list != NULL);
    node_t* new = (node_t*)malloc(sizeof(node_t));
    assert(new);
    new->data = d;
    new->next = list->head;
    list->head = new;
    if (list->tail == NULL)
        list->tail = new;
    list->num_elements++;
}


void* list_pop_front(list_t* list)
{
    assert(list != NULL);
    assert(list->num_elements > 0);
    node_t* old;
    assert(list->head != NULL);
    old = list->head;
    list->head = list->head->next;
    void* d = old->data;
    free(old);
    list->num_elements--;
    if (list->num_elements == 0) {
        list->head = NULL;
        list->tail = NULL;
    }
    return d;
}

/* free all memory associated with a list */
void list_free(list_t* list)
{
    assert(list != NULL);
    while (list->num_elements) {
        void* elem = list_pop_front(list);
        list->del(elem);
    }
    free(list);
}


