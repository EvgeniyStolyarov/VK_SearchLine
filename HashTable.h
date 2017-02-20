//
//  HashTable.h
//  VK_HashTable
//
//  Created by Stolyarov on 19.02.17.
//  Copyright © 2017 temp. All rights reserved.
//

#ifndef HashTable_h
#define HashTable_h

#include <stdio.h>

typedef struct BucketNode BucketNode;
struct BucketNode
{
    BucketNode* next;
    void* data;
    size_t length;
};

typedef struct HashTable
{
    BucketNode** buckets;
    size_t size;
    double factor;
    short primesIdx;
} HashTable;

HashTable* CreateHashTable(const int size);
int HashTableAddData(HashTable* hashTable, const void* data, const size_t len);
int HashTableFind(const HashTable* hashTable, const void* data, const size_t len);
void HashTableFree(HashTable* hashTable);


#endif /* HashTable_h */
