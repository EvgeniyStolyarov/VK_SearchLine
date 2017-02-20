//
//  InputProcessing.c
//  VK_test
//
//  Created by Stolyarov on 18.02.17.
//  Copyright © 2017 VK. All rights reserved.
//

#include "InputProcessing.h"

#include <stdlib.h>
#include <string.h>

const int FILE_MAX_SIZE = 128 * 0x100000;

int BuildHashTable(HashTable* hashTable, FILE* input)
{
    if (!hashTable || !input)
        return BUILD_FAILURE;
    const int readSize = FILE_MAX_SIZE;
    char* buff = malloc(readSize+1);
    while (fgets(buff, readSize+1, input)) {
        size_t buffLength = strlen(buff);
        if (buff[buffLength-1] == '\n') {
            buff[buffLength-1] = '\0';
            --buffLength;
        }
        HashTableAddData(hashTable, buff, buffLength);
    }
    free(buff);
    return BUILD_SUCCESS;
}

void CheckInput(const HashTable* hashTable, FILE* input, const char* endString)
{
    const int readSize = FILE_MAX_SIZE;
    char* buff = malloc(readSize+1);
    const size_t endStringLength = strlen(endString);
    while (fgets(buff, readSize+1, input)) {
        size_t buffLength = strlen(buff);
        if (buff[buffLength-1] == '\n') {
            buff[buffLength-1] = '\0';
            --buffLength;
        }
        if (buffLength == endStringLength && strcmp(buff, endString) == 0)
            break;
        HashTableFind(hashTable, buff, buffLength) ? puts("YES") : puts("NO");
    }
    free(buff);
}