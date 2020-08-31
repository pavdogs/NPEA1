/***************************************************************************
 *
 *   File        : tasks.h
 *   Student Id  : <INSERT STUDENT ID HERE>
 *   Name        : <INSERT STUDENT NAME HERE>
 *
 ***************************************************************************/

#ifndef TASKS_H
#define TASKS_H

// //define struct
// typedef struct {
//   double x, y, u, v, rho, flux;
// } row_t;

typedef struct node_t {
    void* data; 
    struct node_t* next;
} node_t;

 // linked list type 
typedef struct {
    int num_elements;
    node_t* head;
    node_t* tail;
    void (*del)(void*);
} list_t;

list_t* list_new(void (*delfunc)(void*));
// list_t* list_new();

void list_push_front(list_t* list, void* d);
void* list_pop_front(list_t* list);
void list_free(list_t* list);


void max_min_flux(const char* flow_file);

void coarsegrid(const char* flow_file, int grid_resolution);

void searching(const char* flow_file);


void calculate_vorticity(const char* flow_file, int vorticity_numthreshold);

// //helper functions
// void print_task1_row(row_t *T, FILE* fp);



#endif
