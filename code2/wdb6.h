#ifndef WDB6_H
#define WDB6_H
#include<cstdint>
#include<string>
#include"include/fast_io.h"
#include<vector>

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
	struct wdb6_header
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
	
	template<typename record_type>
	class wdb6
	{
	private:
		wdb6_header hd;
		std::vector<field_structure> filedst;
		std::vector<record_type> rcd;
		std::string rm;

	public:
		wdb6(const char *filename)
		{
			using namespace std::string_literals;
			fast_io::ibuf ibuf(filename);
			ibuf.read(&hd,&hd+1);
			if(hd.magic!=910312535)
				throw std::runtime_error(filename+" is not a wdb6 file, which is "s+std::string((const char*)(&hd.magic),(const char*)(&hd.magic+1)));
			if(hd.record_size!=sizeof(record_type))
				throw std::runtime_error("record_type incorrect size :"s+std::to_string(sizeof(record_type))+" ; which should be "s+std::to_string(hd.record_size));
			filedst=std::vector<field_structure>(hd.field_count);
			ibuf.read(filedst.data(),filedst.data()+filedst.size());
			rcd=std::vector<record_type>(hd.record_count);
			ibuf.read(rcd.data(),rcd.data()+rcd.size());
			for(char ch;ibuf.get(ch);rm.push_back(ch));
		}
		
		const auto& header() const
		{
			return hd;
		}
		const auto& field_structures() const
		{
			return filedst;
		}

		const auto& records() const
		{
			return rcd;
		}

		auto& records()
		{
			return rcd;
		}
		void update()
		{
			hd.record_count = static_cast<std::uint32_t>(rcd.size());
		}
		
		template<typename Iter>
		void insert(Iter b,Iter e)
		{
			rcd.insert(rcd.end(),b,e);
			update();
		}

		const auto& remain() const
		{
			return rm;
		}

		template<typename ...Args>
		void save(Args &&...args) const
		{
			fast_io::obuf obuf(std::forward<Args>(args)...);
			obuf.write(&hd,&hd+1);
			obuf.write(filedst.data(),filedst.data()+filedst.size());
			obuf.write(rcd.data(),rcd.data()+rcd.size());
			obuf.write(rm.data(),rm.data()+rm.size());
		}
	};
}
#endif