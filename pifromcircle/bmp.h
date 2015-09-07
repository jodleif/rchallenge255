#pragma once
#include <string>
#include <vector>
#include <cinttypes>
namespace bmp {
	class bmp_header;
	// ushort - 2bytt
	// uint - 4 bytt
	//void load_and_print_bmp_info(std::string filename);
	std::array<char, 2> short_to_arr(unsigned short sh);
	std::array<char, 4>  int_to_arr(unsigned int in);
	//int vector_sum(const std::vector<int>& vec);
	
	
#pragma pack(push,1)
	typedef struct BITMAPFILEHEADER
	{
		unsigned short Signature;
		unsigned int FileSize;
		unsigned short Res1;
		unsigned short Res2;
		unsigned int fOffset;
	}*pHeader;
#pragma pack(pop)
#pragma pack(push, 1)
	typedef struct BMPINFOHEADER
	{
		unsigned int Size;
		int Width;
		int Height;
		unsigned short Planes;
		unsigned short Bitcount;
		unsigned int Compression;
		unsigned int SizeImage;
		int XPelsPerMeter;
		int YPelsPerMeter;
		unsigned int ColorUsed;
		unsigned int ColorImportant;
	}*pInfoheader;
#pragma pack(pop)
	class bmp_header {
	private:
		/*typedef struct BMPHeader
		{
			unsigned short Signature;
			unsigned int FileSize;
			unsigned short Res1;
			unsigned short Res2;
			unsigned int fOffset;
		} *pHeader;

		typedef struct BMPInfoHeader
		{
			unsigned int Size;
			int Width;
			int Height;
			unsigned short Planes;
			unsigned short Bitcount;
			unsigned int Compression;
			unsigned int SizeImage;
			int XPelsPerMeter;
			int YPelsPerMeter;
			unsigned int ColorUsed;
			unsigned int ColorImportant;

		} *pHeaderInfo; */

		std::vector<unsigned char> raw_data;

		void load_bitmap(const std::string filename);
		void load_headers();
	public:
		bmp_header(const std::string filename);
		void print_headerinfo() const;
		int nof_blackpixles() const;
		uint64_t nof_blackpixles_accumulate() const;
		// public vars
		pHeader header;
		pInfoheader info_header;
	};
}
