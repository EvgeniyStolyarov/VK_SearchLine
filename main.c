//
//  main.c
//  VK_HashTable
//
//  Created by Stolyarov on 19.02.17.
//  Copyright © 2017 temp. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "InputProcessing.h"
#include "HashTable.h"

int main(int argc, const char * argv[]) {
    if (argc < 2)
        return EXIT_FAILURE;
    FILE* dictionary = fopen(argv[1], "rb");
    if (!dictionary)
        return EXIT_FAILURE;
    puts("Process dictionary...");
    clock_t begin = clock();
    HashTable* hashTable = CreateHashTable(0);
    if (BuildHashTable(hashTable, dictionary) == BUILD_FAILURE) {
        HashTableFree(hashTable);
        return EXIT_FAILURE;
    }
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%lf\n", time_spent);
    fclose(dictionary);
    
    puts("Enter strings");
    CheckInput(hashTable, stdin, "exit");
    
    HashTableFree(hashTable);
    return EXIT_SUCCESS;
}

