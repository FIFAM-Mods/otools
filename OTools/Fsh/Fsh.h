#pragma once
#include "Buffer.h"
#include "File.h"
#include "Exception.h"
#include "..\D3DDevice\D3DDevice.h"
#include <string>
#include <vector>
#include <algorithm>
#include <filesystem>
#include <functional>
#include "..\binbuf.h"

namespace ea {

	enum Platform {
		PLATFORM_PC,
		PLATFORM_PSP
	};

	class FshData abstract {
		friend class FshImage;
		friend class Fsh;
	public:
		enum DataType { UNKNOWN, PIXELDATA, NAME, METALBIN, COMMENT, HOTSPOT };
		template<typename T>
		T *As() { return reinterpret_cast<T *>(this); }
	protected:
		virtual ~FshData();
		virtual DataType GetDataType() const = 0;
		virtual size_t GetDataSize() const = 0;
	};

	class FshPixelData : public FshData {
		friend class FshImage;
		unsigned char mFormat = 0, mNumMipLevels = 0, mFlags = 0;
		unsigned short mWidth = 0, mHeight = 0, mCenterX = 0, mCenterY = 0, mLeft = 0, mTop = 0;
		Buffer mPixels;
		DataType GetDataType() const override;
		size_t GetDataSize() const override;
	public:
		enum PixelFormat {
			PIXEL_8888 = 0x7D,
			PIXEL_888 = 0x7F,
			PIXEL_4444 = 0x6D,
			PIXEL_5551 = 0x7E,
			PIXEL_565 = 0x78,
			PIXEL_PAL4 = 0x79,
			PIXEL_PAL8 = 0x7B,
			PIXEL_6666 = 0x66,
			PIXEL_484 = 0x68,
			PIXEL_1010102 = 0x6A,
			PIXEL_DXT1 = 0x60,
			PIXEL_DXT3 = 0x61,
			PIXEL_DXT5 = 0x62,
			PIXEL_P24 = 0x24,
			PIXEL_P32 = 0x2A,
			PIXEL_P15 = 0x2D,
			PIXEL_P16 = 0x29,
			PIXEL_P18 = 0x22,
			PIXEL_PAL4_PSP = 0x5C,
			PIXEL_PAL8_PSP = 0x5D,
			PIXEL_P32_PSP = 0x3B,
			PIXEL_4444_PSP = 0x59
		};
		FshPixelData(unsigned char format, Buffer const &pixels, unsigned short width, unsigned short height, unsigned char numMipLevels = 0, unsigned short centerX = 0, unsigned short centerY = 0, unsigned short left = 0, unsigned short top = 0, unsigned char flags = 0);
		FshPixelData(unsigned char format, Buffer &&pixels, unsigned short width, unsigned short height, unsigned char numMipLevels = 0, unsigned short centerX = 0, unsigned short centerY = 0, unsigned short left = 0, unsigned short top = 0, unsigned char flags = 0);
		Buffer &Pixels();
		unsigned char GetFormat() const;
		void SetFormat(unsigned char format);
		unsigned short GetWidth() const;
		void SetWidth(unsigned short width);
		unsigned short GetHeight() const;
		void SetHeight(unsigned short height);
		unsigned short GetCenterX() const;
		void SetCenterX(unsigned short centerX);
		unsigned short GetCenterY() const;
		void SetCenterY(unsigned short centerY);
		unsigned short GetLeft() const;
		void SetLeft(unsigned short left);
		unsigned short GetTop() const;
		void SetTop(unsigned short top);
		unsigned char GetNumMipLevels() const;
		void SetNumMipLevels(unsigned char numLevels);
		unsigned char GetFlags() const;
		void SetFlags(unsigned char flags);
	};

	class FshName : public FshData {
		std::string mName;
		DataType GetDataType() const override;
		size_t GetDataSize() const override;
	public:
		FshName(std::string const &name);
		std::string const &GetName() const;
		void SetName(std::string const &name);
	};

	class FshMetalBin : public FshData {
		Buffer mBuffer;
		unsigned short mFlags = 0;
		unsigned int mUnknown1 = 0;
		unsigned int mUnknown2 = 0;
		DataType GetDataType() const override;
		size_t GetDataSize() const override;
	public:
		FshMetalBin(Buffer const &buffer, unsigned short flags, unsigned int unknown1 = 0, unsigned int unknown2 = 0);
		FshMetalBin(Buffer &&buffer, unsigned short flags, unsigned int unknown1 = 0, unsigned int unknown2 = 0);
		unsigned short GetFlags() const;
		void SetFlags(unsigned short flags);
		unsigned int GetUnknown1() const;
		void SetUnknown1(unsigned int unknown1);
		unsigned int GetUnknown2() const;
		void SetUnknown2(unsigned int unknown2);
		Buffer &Buffer();
	};

	class FshComment : public FshData {
		std::string mComment;
		DataType GetDataType() const override;
		size_t GetDataSize() const override;
	public:
		FshComment(std::string const &comment);
		std::string const &GetComment() const;
		void SetComment(std::string const &comment);
	};

	class FshHotSpot : public FshData {
	public:
		struct Region {
			unsigned int mId = 0, mUnknown = 0, mLeft = 0, mTop = 0, mWidth = 0, mHeight = 0;
			Region();
			Region(unsigned int id, unsigned int left, unsigned int top, unsigned int width, unsigned int height, unsigned int unknown = 0);
		};
	private:
		std::vector<Region> mRegions;
		DataType GetDataType() const override;
		size_t GetDataSize() const override;
	public:
		std::vector<Region> &Regions();
	};

	class FshUnknown : public FshData {
		unsigned char mId = 0;
		Buffer mBuffer;
		DataType GetDataType() const override;
		size_t GetDataSize() const override;
	public:
		FshUnknown(unsigned char id, Buffer const &buffer);
		FshUnknown(unsigned char id, Buffer &&buffer);
		unsigned char GetId() const;
		void SetId(unsigned char id);
		Buffer &Buffer();
	};

	class FshImage {
		friend class Fsh;
		char mTag[4] = {};
		std::vector<FshData *> mDatas;
	public:
		std::string GetTag() const;
		void SetTag(std::string const &tag);
		void Clear();
		~FshImage();
        FshImage();
        FshImage(FshImage &&rhs);
		std::vector<FshData *> FindAllDatas(FshData::DataType dataType);
		FshData *FindFirstData(FshData::DataType dataType);
		void RemoveAllDatas(FshData::DataType dataType);
		void SetData(FshData *data);
		FshData *AddData(FshData *data);

		enum FileFormat {
			BMP = 0, JPG = 1, TGA = 2, PNG = 3, DDS = 4, PPM = 5, DIB = 6, HDR = 7, PFM = 8
		};

		struct LoadingInfo {
			std::filesystem::path filepath;
			bool fileExists = false;
			void *fileData = nullptr;
			unsigned int fileDataSize = 0;
			FileFormat fileFormat;
			void *data = nullptr;
			unsigned int dataWidth = 0;
			unsigned int dataHeight = 0;
			unsigned int dataFormat = 0;
		} loadingInfo;

    private:
		static unsigned int GetPixelD3DFormat(unsigned char format);
		static unsigned char GetPixelFormat(unsigned int format);
		static unsigned int GetPixelDataSize(unsigned char format);
		static unsigned int GetPixelDataSize(unsigned short width, unsigned short height, unsigned char format);
    public:
        void WriteToFile(std::filesystem::path const &filepath, FileFormat fileFormat);
        void ReadFromFile(std::filesystem::path const &filepath, Platform platform = PLATFORM_PC, unsigned int d3dformat = ((unsigned int)-3), unsigned int levels = ((unsigned int)-3), bool rescale = false);
		void Load(LoadingInfo const &loadingInfo, Platform platform = PLATFORM_PC, unsigned int d3dformat = ((unsigned int)-3), unsigned int levels = ((unsigned int)-3), bool rescale = false, bool forceAlphaCheck = false, int paletteBits = -1);
	};

	class Fsh {
		struct WritingOptions {
			bool mAddBuyERTS = false;
			size_t mAlignment = 16;
		} mWritingOptions;

		char mTag[4] = { 'G','3','5','9' };
		std::vector<FshImage> mImages;
		Platform mPlatform = PLATFORM_PC;
	public:
		static D3DDevice *GlobalDevice;
		static bool UseCompressonator;
		static bool PreferDxt3;
		static void SetDevice(D3DDevice *device);
		static void ClearDevice();
		std::string GetTag() const;
		void SetTag(std::string const &tag);
		bool GetAddBuyERTS() const;
		void SetAddBuyERTS(bool set);
		size_t GetAlignment() const;
		void SetAlignment(size_t alignment);
		void Clear();
		FshImage &AddImage();;
		size_t GetImagesCount();
		void ForAllImages(std::function<void(FshImage &)> callback);
		void Read(std::filesystem::path const &filepath);
		void Write(std::filesystem::path const &filepath);
		void WriteImageToBuffer(BinaryBuffer &buf, size_t i);
		Platform GetPlatform();
		void SetPlatform(Platform platform);
	};
}
