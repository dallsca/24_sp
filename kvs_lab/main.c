#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kvs.h"

int main() {
    kvs_t* kvs = open();
    if (!kvs) {
        printf("Failed to open kvs\n");
        return -1;
    }

    FILE* query_file = fopen("query.dat", "r");
    FILE* answer_file = fopen("answer.dat", "w");

    if (!query_file) {
        printf("Failed to open query.dat\n");
        close(kvs);
        return -1;
    } else {
        printf("query.dat opened successfully\n");
    }
    if (!answer_file) {
        printf("Failed to open answer.dat\n");
        close(kvs);
        fclose(query_file);
        return -1;
    }

    char line[256];
    char *operation, *key, *value;

    // 파일에서 한 줄씩 읽기
    while (fgets(line, sizeof(line), query_file) != NULL) {
        // 줄 끝의 개행 문자 제거
        line[strcspn(line, "\n")] = 0;

        // 쉼표로 구분하여 operation, key, value 추출
        operation = strtok(line, ",");
        key = strtok(NULL, ",");
        value = strtok(NULL, ",");

        // `set` 연산인 경우
        if (strcmp(operation, "set") == 0 && key != NULL && value != NULL) {
            printf("Setting key: %s, value: %s\n", key, value);  // 디버그 출력
            put(kvs, key, value);
        }
        // `get` 연산인 경우
        else if (strcmp(operation, "get") == 0 && key != NULL) {
            printf("Getting key: %s\n", key);  // 디버그 출력
            char* result = get(kvs, key);
            if (result) {
                fprintf(answer_file, "get,%s,%s\n", key, result);
                free(result);
            } else {
                fprintf(answer_file, "get,%s,NOT_FOUND\n", key);
            }
        }
    }

    fclose(query_file);
    fclose(answer_file);
    close(kvs);
    return 0;
}

