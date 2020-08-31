// hash table

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	void *data // array
	int nbins, min, max;
} hashtable_t;

// create a new hashtable: create an array with the appropriate number of bins
hashtable_t* 
new_table(int min, int max, double bin_width) {
	return
}


// put data in the appropriate bin
int*
put(void* data) {
}

void*
get(int n) {
}