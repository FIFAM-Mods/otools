#pragma once
#include <cstring>
#include <string>
#include <filesystem>

class BinaryBuffer {
    static const unsigned int DEFAULT_START_CAPACITY = 4096;
    unsigned char *mData;
    unsigned int mSize;
    unsigned int mCapacity;
    unsigned char *mCurrent;

    void PutData(void const *data, unsigned int size);
public:
    BinaryBuffer();
    BinaryBuffer(unsigned int startingCapacity);
    ~BinaryBuffer();
    unsigned int Position() const;
    unsigned int Size() const;
    unsigned int Capacity() const;
    unsigned char *Data() const;
    void MoveTo(unsigned int position);
    void Put(std::string const &str);
    void Put(std::wstring const &str);
    void Put(const char *str);
    void Put(const wchar_t *str);
    void Put(void const *data, unsigned int size);
    void Put(BinaryBuffer const &buf);
    bool WriteToFile(std::filesystem::path const &filepath);
    bool WriteToFile(std::filesystem::path const &filepath, unsigned int from, unsigned int size);
    bool Compare(BinaryBuffer const &otherBuf);
    void Align(unsigned int alignment);

    template<typename T>
    void Put(T const &value) {
        PutData((void *)&value, sizeof(T));
    }
};
