/**
 * Name: Juntae Park
 * GTID: 903734410
 */

/*  PART 2: A CS-2200 C implementation of the arraylist data structure.
    Implement an array list.
    The methods that are required are all described in the header file. Description for the methods can be found there.

    Hint 1: Review documentation/ man page for malloc, calloc, and realloc.
    Hint 2: Review how an arraylist works.
    Hint 3: You can use GDB if your implentation causes segmentation faults.
*/

#include "arraylist.h"

/* Student code goes below this point */
arraylist_t *create_arraylist(uint capacity) {
    arraylist_t *arraylist = (arraylist_t * ) malloc(sizeof(arraylist_t));
    if (!arraylist) {
        return 0;
    }
    
    arraylist -> backing_array = (char **) malloc(sizeof(char *) * capacity);
    if (!(arraylist -> backing_array)) {
        free(arraylist);
        return 0;
    }
    arraylist -> capacity = capacity;
    arraylist -> size = 0;
    
    return arraylist;
}

void add_at_index(arraylist_t *arraylist, char *data, int index) {
    if (index < 0 || index > arraylist -> size || !data) {
        return;
    }
    if (arraylist -> capacity == arraylist -> size) {
        resize(arraylist);
    }

    for (int i = arraylist -> size; i > index; i--) {
        arraylist -> backing_array[i] = arraylist -> backing_array[i - 1];
    }
    arraylist -> backing_array[index] = data;
    arraylist -> size++;

    return;
}

void append(arraylist_t *arraylist, char *data) {
    if (!data || !arraylist) {
        return;
    }
    add_at_index(arraylist, data, arraylist -> size);

    return;
}

char *remove_from_index(arraylist_t *arraylist, int index) {
    if (!arraylist || index < 0 || index >= arraylist->size) {
        return NULL;
    }

    char *data = arraylist->backing_array[index];

    for (int i = index; i < arraylist->size - 1; i++) {
        arraylist->backing_array[i] = arraylist->backing_array[i + 1];
    }

    arraylist->backing_array[arraylist->size - 1] = NULL;
    arraylist->size--;

    return data;
}

void resize(arraylist_t *arraylist) {
    if (!arraylist) {
        return;
    }
    
    char **resizedlist = (char **) realloc(arraylist -> backing_array, sizeof(char *) * 2 * arraylist -> capacity);
    if (!resizedlist) {
        return;
    }

    arraylist -> capacity = arraylist -> capacity * 2;
    arraylist -> backing_array = resizedlist;
}

void destroy(arraylist_t *arraylist) {
    if (!arraylist) {
        return;
    }
    free(arraylist -> backing_array);
}