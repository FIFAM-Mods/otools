#include "Buffer.h"

ea::Buffer::~Buffer() {
	Clear();
}

bool ea::Buffer::HasData() const {
	return mData != nullptr;
}

ea::Buffer::Buffer() {}

ea::Buffer::Buffer(Buffer const & rhs) {
	CopyFrom(rhs);
}

ea::Buffer::Buffer(Buffer && rhs) {
	operator=(std::move(rhs));
}

ea::Buffer &ea::Buffer::operator=(Buffer const &rhs) {
	CopyFrom(rhs);
	return *this;
}

ea::Buffer &ea::Buffer::operator=(Buffer &&rhs) {
	if (rhs.HasData()) {
		if (rhs.mOwner) {
			SetData(rhs.GetData(), rhs.GetSize(), true);
			rhs.mData = nullptr;
			rhs.mSize = 0;
		}
		else
			Allocate(rhs.GetSize(), rhs.GetData());
	}
	else
		Clear();
	return *this;
}

void ea::Buffer::Clear() {
	if (HasData()) {
		if (mOwner)
			operator delete(mData);
		mData = nullptr;
		mSize = 0;
	}
}

ea::Buffer::Buffer(void * data, unsigned int size, bool owner) {
	SetData(data, size, owner);
}

void ea::Buffer::SetData(void * data, unsigned int size, bool owner) {
	Clear();
	mData = data;
	mSize = size;
	mOwner = owner;
}

void * ea::Buffer::GetData() const {
	return mData;
}

size_t ea::Buffer::GetSize() const {
	return mSize;
}

bool ea::Buffer::GetIsOwner() const {
	return mOwner;
}

void ea::Buffer::SetIsOwner(bool set) {
	if (set) {
		if (!mOwner) {
			void *oldData = mData;
			mData = operator new(mSize);
			memcpy(mData, oldData, mSize);
			mOwner = true;
		}
	}
	else {
		if (mOwner)
			mOwner = false;
	}
}

void ea::Buffer::Allocate(size_t size, void *data) {
	Clear();
	mData = operator new(size);
	if (data)
		memcpy(mData, data, size);
	else
		memset(mData, 0, size);
	mSize = size;
	mOwner = true;
}

void ea::Buffer::CopyFrom(Buffer const & buffer) {
	if (buffer.HasData())
		Allocate(buffer.GetSize(), buffer.GetData());
	else
		Clear();
}
