#include "kvs.h"

int close(kvs_t* kvs) {
    node_t* current = kvs->db;
    while (current != NULL) {
        node_t* next = current->next;
        free(current->value);
        free(current);
        current = next;
    }
    free(kvs);
    return 0;
}


