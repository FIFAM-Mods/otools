#include "File.h"
#include "Exception.h"

void ea::File::ValidateFileBounds(size_t range, bool fromCurentPos) {
	if (mFile) {
		auto startPos = fromCurentPos ? ftell(mFile) : 0;
		if ((startPos + range) > static_cast<size_t>(mFileSize))
			throw Exception("reached end of file in " + mFilePath);
	}
}

long ea::File::FileSize() {
	if (mFile)
		return mFileSize;
	return 0;
}

ea::File::File(std::filesystem::path const & filepath, Mode mode) {
	mFile = _wfopen(filepath.c_str(), mode == READ ? L"rb" : L"wb");
	if (!mFile)
		throw Exception("failed to open: " + filepath.string());
	mFilePath = filepath.string();
	if (mode == READ) {
		fseek(mFile, 0, SEEK_END);
		mFileSize = ftell(mFile);
		fseek(mFile, 0, SEEK_SET);
	}
}

ea::File::~File() {
	if (mFile)
		fclose(mFile);
}

FILE *ea::File::Interface() { return mFile; }

void ea::File::WriteNull(unsigned int count) {
	if (mFile) {
		unsigned char n = 0;
		for (unsigned int i = 0; i < count; i++)
			fwrite(&n, 1, 1, mFile);
	}
}

void ea::File::Write(void const * data, size_t size) {
	if (mFile) {
		fwrite(data, size, 1, mFile);
	}
}

unsigned int ea::File::Alignment(unsigned int size, unsigned int a) {
	if (a == 0)
		return 0;
	unsigned int m = size % a;
	return m > 0 ? (a - m) : 0;
}

unsigned int ea::File::GetAlignedSize(unsigned int size, unsigned int a) {
	return size + Alignment(size, a);
}

void ea::File::Read(void *dst, size_t size) {
	if (mFile) {
		ValidateFileBounds(size);
		fread(dst, size, 1, mFile);
	}
}

std::string ea::File::ReadNullTerminated() {
	std::string result;
	char c = Read<char>();
	while (c != '\0') {
		result.push_back(c);
		c = Read<char>();
	}
	return result;
}

void ea::File::Skip(size_t bytes) {
	if (mFile) {
		ValidateFileBounds(bytes);
		fseek(mFile, bytes, SEEK_CUR);
	}
}

void ea::File::JumpTo(size_t position) {
	if (mFile) {
		ValidateFileBounds(position, false);
		fseek(mFile, position, SEEK_SET);
	}
}

long ea::File::Position() {
	if (mFile)
		return ftell(mFile);
	return 0;
}
