#pragma once
#include <memory>

namespace ea {
	class Buffer {
		void *mData = nullptr;
		size_t mSize = 0;
		bool mOwner = false;

	public:
		Buffer();
		Buffer(Buffer const &rhs);
		Buffer(Buffer &&rhs);
		Buffer &operator=(Buffer const &rhs);
		Buffer &operator=(Buffer &&rhs);
		~Buffer();
		bool HasData() const;
		void Clear();
		Buffer(void *data, unsigned int size, bool owner = false);
		void SetData(void *data, unsigned int size, bool owner = false);
		void *GetData() const;
		size_t GetSize() const;
		bool GetIsOwner() const;
		void SetIsOwner(bool set);
		void Allocate(size_t size, void *data = nullptr);
		void CopyFrom(Buffer const &buffer);
	};
}
