#ifndef WDB6_H
#define WDB6_H
#include<cstdint>
#include<string>
#include"file_parser.h"

namespace db2
{
	struct field_structure
	{
		std::uint16_t size,position;
	};
	template<typename ostrm>
	decltype(auto) operator<<(ostrm& o,const field_structure& fs)
	{
		return o<<"size\t"<<fs.size<<"\nposition\t"<<fs.position;
	}
	
	template<typename record_type>
	class wdb6_file
	{
		file_parser f;
	public:
		struct header
		{
			uint32_t magic;
			uint32_t record_count;
			uint32_t field_count;
			uint32_t record_size;
			uint32_t string_table_size;
			uint32_t table_hash;
			uint32_t layout_hash;
			uint32_t min_id;
			uint32_t max_id;
			uint32_t locale;
			uint32_t copy_table_size;
			uint16_t flags;
			uint16_t id_index;
			uint32_t total_field_count;
			uint32_t common_data_table_size;
		};
	private:
		header *pheader;
		span<field_structure> filedst;
		span<record_type> rcd;
		span<char> strn;
	public:
		wdb6_file(const char *filename):f(filename),pheader(f.at<header>())
		{
			using namespace std::string_literals;
			if(pheader->magic!=910312535)
				throw std::runtime_error(filename+" is not a wdb6 file, which is "s+std::string((const char*)(&pheader->magic),(const char*)(&pheader->magic+1)));
			if(pheader->record_size!=sizeof(record_type))
				throw std::runtime_error("record_type incorrect size :"s+std::to_string(sizeof(record_type))+" ; which should be "s+std::to_string(pheader->record_size));
			filedst = f.at_n<field_structure>(pheader->field_count);
			rcd = f.at_n<record_type>(pheader->record_count);
			strn = f.at_n<char>(pheader->string_table_size);
		}
		
		decltype(auto) get_header() const
		{
			return *pheader;
		}
		decltype(auto) field_structures() const
		{
			return filedst;
		}
		decltype(auto) cstring() const
		{
			return strn;
		}
		decltype(auto) records() const
		{
			return rcd;
		}
	};
}
#endif