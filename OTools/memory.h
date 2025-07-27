#pragma once

template<typename T>
T *At(void *object, unsigned int offset) {
    return (T *)((unsigned int)object + offset);
}

template<typename T>
T GetAt(void *object, unsigned int offset) {
    return *At<T>(object, offset);
}

template<typename T>
void SetAt(void *object, unsigned int offset, T const &value) {
    *At<T>(object, offset) = value;
}

unsigned int GetNumBytesToAlign(unsigned int offset, unsigned int alignment);
unsigned int GetAligned(unsigned int offset, unsigned int alignment);
void Memory_Fill(void *dst, int val, size_t size);
void Memory_Zero(void *dst, size_t size);
void Memory_Copy(void *dst, void const *src, size_t size);

template<typename T>
void Memory_Zero(T &obj) {
    Memory_Zero(&obj, sizeof(T));
}
