#include "kvs.h"

int put(kvs_t* kvs, const char* key, const char* value) {
    // 현재 노드를 순회하여 키가 존재하는지 확인
    node_t* current = kvs->db;
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            // 키가 이미 존재하면 값을 업데이트하고 반환
            free(current->value);  // 기존 값을 해제
            current->value = strdup(value);  // 새 값으로 설정
            printf("Updated key: %s, with value: %s\n", key, value);  // 디버그 출력
            return 0;
        }
        current = current->next;
    }

    // 새로운 노드 할당 및 설정
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    if (!new_node) {
        printf("Memory allocation failed\n");
        return -1;
    }
    strncpy(new_node->key, key, sizeof(new_node->key) - 1);
    new_node->key[sizeof(new_node->key) - 1] = '\0';  // 널 종료 보장
    new_node->value = strdup(value);
    new_node->next = kvs->db;  // 새 노드를 리스트의 앞에 삽입
    kvs->db = new_node;

    printf("Inserted key: %s, with value: %s\n", key, value);  // 디버그 출력

    kvs->items++;
    return 0;
}



