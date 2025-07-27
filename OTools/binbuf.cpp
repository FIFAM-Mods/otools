#include "binbuf.h"
#include "memory.h"
#include "outils.h"

void BinaryBuffer::PutData(void const *data, unsigned int size) {
    if (size > 0) {
        unsigned int requiredSize = Position() + size;
        if (requiredSize > mCapacity) {
            unsigned int newCapacity = mCapacity * 2;
            if (requiredSize > newCapacity)
                newCapacity = requiredSize;
            unsigned char *newData = new unsigned char[newCapacity];
            if (!newData)
                throw std::runtime_error("Unable to allocate memory for BinaryBuffer");
            Memory_Copy(newData, mData, mCapacity);
            delete[] mData;
            mData = newData;
            mCapacity = newCapacity;
            mCurrent = mData + mSize;
        }
        Memory_Copy(mCurrent, data, size);
        mCurrent += size;
        if (mCurrent > (mData + mSize))
            mSize = mCurrent - mData;
    }
}

BinaryBuffer::BinaryBuffer() {
    mData = new unsigned char[DEFAULT_START_CAPACITY];
    mSize = 0;
    mCapacity = DEFAULT_START_CAPACITY;
    mCurrent = mData;
}

BinaryBuffer::BinaryBuffer(unsigned int startingCapacity) {
    mData = new unsigned char[startingCapacity];
    mSize = 0;
    mCapacity = startingCapacity;
    mCurrent = mData;
}

BinaryBuffer::~BinaryBuffer() {
    delete[] mData;
}

unsigned int BinaryBuffer::Position() const {
    return mCurrent - mData;
}

unsigned int BinaryBuffer::Size() const {
    return mSize;
}

unsigned int BinaryBuffer::Capacity() const {
    return mCapacity;
}

unsigned char *BinaryBuffer::Data() const {
    return mData;
}

void BinaryBuffer::MoveTo(unsigned int position) {
    if (position <= mSize)
        mCurrent = mData + position;
    else
        mCurrent = mData + mSize;
}

void BinaryBuffer::Put(char const *str) {
    PutData(str, strlen(str));
    Put<char>('\0');
}

void BinaryBuffer::Put(wchar_t const *str) {
    PutData(str, wcslen(str) * 2);
    Put<wchar_t>('\0');
}

void BinaryBuffer::Put(std::string const &str) {
    PutData((void *)str.c_str(), str.size());
    Put<char>('\0');
}

void BinaryBuffer::Put(std::wstring const &str) {
    PutData((void *)str.c_str(), str.size() * 2);
    Put<wchar_t>(L'\0');
}

void BinaryBuffer::Put(void const *data, unsigned int size) {
    PutData(data, size);
}

void BinaryBuffer::Put(BinaryBuffer const &buf) {
    PutData(buf.Data(), buf.Size());
}

bool BinaryBuffer::WriteToFile(std::filesystem::path const &filepath) {
    FILE *f = _wfopen(filepath.c_str(), L"wb");
    bool result = false;
    if (f) {
        if (fwrite(mData, mSize, 1, f) == 1)
            result = true;
        fclose(f);
    }
    return result;
}

bool BinaryBuffer::WriteToFile(std::filesystem::path const &filepath, unsigned int from, unsigned int size) {
    if ((from + size) > Size())
        return false;
    FILE *f = _wfopen(filepath.c_str(), L"wb");
    bool result = false;
    if (f) {
        if (fwrite(mData + from, size, 1, f) == 1)
            result = true;
        fclose(f);
    }
    return result;
}

bool BinaryBuffer::Compare(BinaryBuffer const &otherBuf) {
    if (mSize == otherBuf.mSize)
        return mSize == 0 || !memcmp(mData, otherBuf.mData, mSize);
    return false;
}

void BinaryBuffer::Align(unsigned int alignment) {
    auto numBytes = GetNumBytesToAlign(Position(), alignment);
    for (unsigned int i = 0; i < numBytes; i++)
        Put<unsigned char>(0);
}
