// linked_list.h

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

void list_push_front(list_t* list, void* d);
void* list_pop_front(list_t* list);
void list_free(list_t* list);
