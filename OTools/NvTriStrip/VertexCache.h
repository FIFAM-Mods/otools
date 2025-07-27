#pragma once
#include <string.h>

class VertexCache {
    int *entries;
    int numEntries;
public:
    VertexCache(int size);
    VertexCache();
    ~VertexCache();
    bool InCache(int entry);
    int AddEntry(int entry);
    void Clear();
    void Copy(VertexCache *inVcache);
    int At(int index);
    void Set(int index, int value);
};
