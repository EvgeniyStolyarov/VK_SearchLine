//
//  HashTable.c
//  VK_HashTable
//
//  Created by Stolyarov on 19.02.17.
//  Copyright © 2017 temp. All rights reserved.
//

#include "HashTable.h"

#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define HashFunc HashEmaxx

#define PrimesNumberCount 11
int SavedPrimes[PrimesNumberCount] = {11, 101, 10111, 101111, 199999, 524287, 1011001, 5308417, 10010101, 100100111, 193877777};

static inline uint32_t HashEmaxx(const void* data,const size_t bytesCnt)
{
    uint32_t hash = 0;
    uint32_t pow = 131;
    for (size_t i = 0; i < bytesCnt; ++i) {
        hash += pow * ((uint8_t*)data)[i];
        pow *= pow;
    }
    return hash;
}

extern inline int HashTableBucketsCount(const HashTable* hashTable)
{
    return hashTable->primesIdx < PrimesNumberCount
            ? SavedPrimes[hashTable->primesIdx] : 1;
}

HashTable* CreateHashTable()
{
    HashTable* hashTable = malloc(sizeof(HashTable));
    if (!hashTable)
        return NULL;
    hashTable->primesIdx = 0;
    hashTable->buckets = calloc(sizeof(BucketNode*), HashTableBucketsCount(hashTable));
    hashTable->size = 0;
    hashTable->factor = 2.0;
    return hashTable;
}

BucketNode* CreateBacketNode(const void* data, const size_t len)
{
    BucketNode* bucketNode = malloc(sizeof(BucketNode));
    if (!bucketNode)
        return NULL;
    bucketNode->next = NULL;
    bucketNode->length = len;
    bucketNode->data = malloc(len);
    if (!bucketNode->data)
        return bucketNode;
    memcpy(bucketNode->data, data, len);
    return bucketNode;
}

int HashTableAddBucketNode(HashTable* hashTable, BucketNode* bucketNode)
{
    size_t idx = HashFunc(bucketNode->data, bucketNode->length) % SavedPrimes[hashTable->primesIdx];
    bucketNode->next = hashTable->buckets[idx];
    hashTable->buckets[idx] = bucketNode;
    return 0;
}

static int HashTableRehash(HashTable* hashTable)
{
    if (hashTable->primesIdx + 1 >= PrimesNumberCount)
        return 0;
    
    BucketNode** dumpBuckets = hashTable->buckets;
    hashTable->buckets = calloc(sizeof(BucketNode*), SavedPrimes[hashTable->primesIdx+1]);
    if (!hashTable->buckets) {
        hashTable->buckets = dumpBuckets;
        return 0;
    }
    ++hashTable->primesIdx;
    for (int i = 0; i < SavedPrimes[hashTable->primesIdx - 1]; ++i) {
        BucketNode* bucketNode = dumpBuckets[i];
        while (bucketNode) {
            BucketNode* bucketNodeNext = bucketNode->next;
            HashTableAddBucketNode(hashTable, bucketNode);
            bucketNode = bucketNodeNext;
        }
    }
    free(dumpBuckets);
    return 1;
}



int HashTableAddData(HashTable* hashTable, const void* data, const size_t len)
{
    if ((double)hashTable->size / HashTableBucketsCount(hashTable) > hashTable->factor) {
        if(HashTableRehash(hashTable))
            HashTableAddData(hashTable, data, len);
    }
    size_t idx = HashFunc(data, len) % HashTableBucketsCount(hashTable);
    BucketNode** bucketNode = &hashTable->buckets[idx];
    while (*bucketNode) {
        if ((*bucketNode)->length == len && memcmp((*bucketNode)->data, data, len) == 0)
            return 1;
        bucketNode = &(*bucketNode)->next;
    }
    BucketNode* newBucketNode = CreateBacketNode(data, len);
    if (!newBucketNode)
        return 0;
    ++hashTable->size;
    *bucketNode = newBucketNode;
    return 1;
}

int HashTableFind(const HashTable* hashTable, const void* data, const size_t len)
{
    size_t idx = HashFunc(data, len) % HashTableBucketsCount(hashTable);
    BucketNode* bucketNode = hashTable->buckets[idx];
    while (bucketNode) {
        if (bucketNode->length == len && memcmp(bucketNode->data, data, len) == 0)
            return 1;
        bucketNode = bucketNode->next;
    }
    return 0;
}

void BucketNodeFree(BucketNode* bucketNode)
{
    if (!bucketNode)
        return;
    free(bucketNode->data);
    BucketNodeFree(bucketNode->next);
    free(bucketNode);
}

void HashTableFree(HashTable* hashTable)
{
    if (!hashTable)
        return;
    for (int i = 0; i < HashTableBucketsCount(hashTable); ++i) {
        if (hashTable->buckets[i]) {
            BucketNodeFree(hashTable->buckets[i]);
        }
    }
    free(hashTable->buckets);
    free(hashTable);
}

