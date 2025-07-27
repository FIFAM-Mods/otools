#include "VertexCache.h"

VertexCache::VertexCache(int size) {
    numEntries = size;
    entries = new int[numEntries];
    for (int i = 0; i < numEntries; i++)
        entries[i] = -1;
}

VertexCache::VertexCache() { this->VertexCache::VertexCache(16); }

VertexCache::~VertexCache() { delete[] entries; entries = 0; }

bool VertexCache::InCache(int entry) {
    for (int i = 0; i < numEntries; i++) {
        if (entries[i] == entry)
            return true;
    }
    return false;
}

int VertexCache::AddEntry(int entry) {
    int removed = entries[numEntries - 1];
    //push everything right one
    for (int i = numEntries - 2; i >= 0; i--)
        entries[i + 1] = entries[i];
    entries[0] = entry;
    return removed;
}

void VertexCache::Clear() {
    memset(entries, -1, sizeof(int) * numEntries);
}

void VertexCache::Copy(VertexCache *inVcache) {
    for (int i = 0; i < numEntries; i++)
        inVcache->Set(i, entries[i]);
}

int VertexCache::At(int index) { return entries[index]; }

void VertexCache::Set(int index, int value) { entries[index] = value; }
