#ifndef FILE_PARSER_H__
#define FILE_PARSER_H__

#include<boost/interprocess/file_mapping.hpp>
#include<boost/interprocess/mapped_region.hpp>
#include"span.h"

class file_parser
{
	boost::interprocess::file_mapping mfile;
	boost::interprocess::mapped_region region;
	std::uint8_t *iptr,*end;
public:
	file_parser(const char* filename):mfile(filename,boost::interprocess::read_write),region(mfile,boost::interprocess::read_write),iptr(reinterpret_cast<uint8_t*>(region.get_address())),end(iptr+region.get_size())
	{
	}
	template<typename T>
	auto next()
	{
		const auto ptr(reinterpret_cast<T*>(iptr));
		iptr += sizeof(T);
		return ptr;
	}
	template<typename T>
	auto at()
	{
		if(end<iptr+sizeof(T))
			throw std::out_of_range("at<T>() out of range");
		return next<T>();
	}
	template<typename T>
	auto next_n(std::size_t n)
	{
		const auto ptr(iptr);
		iptr+=n*sizeof(T);
		return span<T>(ptr,ptr+n*sizeof(T));
	}
	template<typename T>
	auto at_n(std::size_t n)
	{
		if(end<iptr+n*sizeof(T))
			throw std::out_of_range("at_n<T>() out of range");
		return next_n<T>(n);
	}
};

#endif