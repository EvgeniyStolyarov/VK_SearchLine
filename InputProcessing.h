//
//  InputProcessing.h
//  VK_test
//
//  Created by Stolyarov on 18.02.17.
//  Copyright © 2017 VK. All rights reserved.
//

#ifndef InputProcessing_h
#define InputProcessing_h

#include <stdio.h>
#include "HashTable.h"

#define BUILD_SUCCESS 1
#define BUILD_FAILURE 0

int BuildHashTable(HashTable* hashTable, FILE* input);
void CheckInput(const HashTable* trie, FILE* input, const char* endString);

#endif /* InputProcessing_h */
