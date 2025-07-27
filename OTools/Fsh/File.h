#pragma once
#include <filesystem>

namespace ea {
	class File {
		FILE *mFile = nullptr;
		std::string mFilePath;
		long mFileSize = 0;

		void ValidateFileBounds(size_t range, bool fromCurentPos = true);

	public:
		enum Mode { READ, WRITE };

		long FileSize();
		File(std::filesystem::path const &filepath, Mode mode);
		~File();
		FILE *Interface();
		void WriteNull(unsigned int count = 1);
		void Write(void const *data, size_t size);
		static unsigned int Alignment(unsigned int size, unsigned int a);
		static unsigned int GetAlignedSize(unsigned int size, unsigned int a);
		void Read(void *dst, size_t size);
		std::string ReadNullTerminated();
		void Skip(size_t bytes);
		void JumpTo(size_t position);
		long Position();

		template<typename T>
		void Write(T const &value) {
			if (mFile)
				fwrite(&value, sizeof(T), 1, mFile);
		}

		template<typename T>
		T Read() {
			T result = {};
			if (mFile) {
				ValidateFileBounds(sizeof(T));
				fread(&result, sizeof(T), 1, mFile);
			}
			return result;
		}

		template<typename T>
		void Read(T &out) {
			if (mFile) {
				ValidateFileBounds(sizeof(T));
				fread(&out, sizeof(T), 1, mFile);
			}
		}
	};

}
