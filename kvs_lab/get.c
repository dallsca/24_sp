#include "kvs.h"

char* get(kvs_t* kvs, const char* key) {
    node_t* current = kvs->db;
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            printf("Found key: %s, returning value: %s\n", key, current->value);  // 디버그 출력
            return strdup(current->value);
        }
        current = current->next;
    }
    // 키가 없는 경우 NULL 반환
    printf("Key not found: %s\n", key);  // 디버그 출력
    return NULL;
}

