#include "bmp.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <cassert>
#include <numeric>


namespace bmp
{

	std::array<char, 2> short_to_arr(unsigned short sh)
	{
		return std::array<char, 2u> { static_cast<char>(sh), static_cast<char>(sh >> 8) };
	}

	std::array<char, 4> int_to_arr(unsigned in)
	{
		return std::array<char, 4u> {static_cast<char>(in), static_cast<char>(in >> 8), static_cast<char>(in >> 16), static_cast<char>(in >> 24)};
	}

	void bmp_header::load_bitmap(const std::string filename)
	{
		std::fstream bmp_file(filename.c_str());
		if (bmp_file) {
			bmp_file.seekg(0, std::ios::end);

			auto length = bmp_file.tellg(); // streamsize - signed
			auto ulength = static_cast<std::size_t>(length);
			std::vector<unsigned char> buffer(ulength);
			bmp_file.seekg(0, std::ios::beg);


			bmp_file.read(reinterpret_cast<char*>(&buffer[0]), length);
			raw_data = std::move(buffer);

		}
	}

	void bmp_header::load_headers()
	{
		header = reinterpret_cast<pHeader>(&raw_data[0]);
		info_header = reinterpret_cast<pInfoheader>(&raw_data[0] + sizeof(BITMAPFILEHEADER));
	}


	bmp_header::bmp_header(const std::string filename)
	{
		load_bitmap(filename);
		if (raw_data.size() > 0) {
			load_headers();
		}
	}

	void bmp_header::print_headerinfo() const
	{
		std::cout << "------------ header information below ------------\n";
		std::cout << "Sig: " << header->Signature << " Filesize: " << header->FileSize << std::endl;
		std::cout << "Foffset: " << header->fOffset << std::endl;
		std::cout << "Res1: " << short_to_arr(header->Res1)[0] << short_to_arr(header->Res1)[1]
			<< " Res2: " << short_to_arr(header->Res2)[0] << short_to_arr(header->Res2)[1];
		std::cout << "\nheader: " << short_to_arr(header->Signature)[0] << short_to_arr(header->Signature)[1] << std::endl;
		std::cout << "Size: " << info_header->Size << " SizeImage: " << info_header->SizeImage << " Bitcount: " << info_header->Bitcount << std::endl;
		std::cout << "Size x: " << info_header->Width << " height: " << info_header->Height << std::endl;
	}

	int bmp_header::nof_blackpixles() const
	{
		int black{ 0 };
		int white{ 0 };

		auto vec_iter = raw_data.cbegin();
		vec_iter += header->fOffset;

		for (;vec_iter != raw_data.cend();vec_iter+=3) {
			if(*vec_iter==0) {
				++black;
			}  else {
				++white;
			}
		}
		//std::cout << "Black: " << black << " white: " << white << " sum: " << black + white << std::endl;
		assert((white + black) == (info_header->Width*info_header->Height));

		return black;
	}

	uint64_t bmp_header::nof_blackpixles_accumulate() const
	{
		auto iter = raw_data.cbegin();
		iter += header->fOffset;

		uint64_t accu {0};
		accu = std::accumulate(iter, raw_data.cend(), accu);
		accu /= (255 * 3); // counts R,G,B - white == 255.
		uint64_t total_pixles{ static_cast<uint64_t>(info_header->Width*info_header->Height) };
		return (total_pixles-accu);
	}

	long double bmp_header::get_radius() const
	{
		return (info_header->Width / 2.0L);
	}
}


