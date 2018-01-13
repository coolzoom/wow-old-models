#pragma once
#include"md20.h"

namespace m2
{
	class unknown
	{
		union
		{
			std::uint32_t u;
			std::array<char,4> a;
		}t;
		span<std::uint8_t> m;
	public:
		unknown(std::uint32_t tag,const span<std::uint8_t> &s):t{tag},m(s){}		
		std::uint32_t tag() const
		{
			return t.u;
		}
		std::string name() const
		{
			return std::string(t.a.cbegin(),t.a.cend());
		}
		decltype(auto) data() const
		{
			return m;
		}
		template<typename ostr>
		friend decltype(auto) operator<<(ostr& o,const unknown &c)
		{
			o.rdbuf()->sputn(c.t.a.data(),c.t.a.size());
			return o<<'\t'<<c.t.u<<'\t'<<c.data().size()<<" bytes\tunknown";
		}
	};
	
	struct afid_block
	{
		std::uint16_t anim_id;
		std::uint16_t sub_anim_id;
		std::uint32_t file_id;
	};
	
	class afid
	{
		span<afid_block> b;
	public:
		afid(span<std::uint8_t> s):b(s.begin(),s.end()){}
		
		decltype(auto) blocks() const
		{
			return (b);
		}
		decltype(auto) blocks()
		{
			return (b);			
		}
	};
	
	template<typename ostrm>
	decltype(auto) operator<<(ostrm& os,const afid& v)
	{
		return os<<"AFID\tstd::array<std::uint64_t,"<<v.blocks().size()<<'>';
	}
	
	class bfid
	{
		span<std::uint32_t> b;
	public:
		using value_type = std::uint32_t;
		bfid(span<std::uint8_t> s):b(s.begin(),s.end()){}
		
		decltype(auto) blocks() const
		{
			return (b);
		}
		decltype(auto) blocks()
		{
			return (b);			
		}
	};
	
	template<typename ostrm>
	decltype(auto) operator<<(ostrm& os,const bfid& v)
	{
		return os<<"BFID\tstd::array<std::uint32_t,"<<v.blocks().size()<<'>';
	}
	
	class txac
	{
		span<std::uint8_t> tot;
		span<std::array<char,2>> s;
	public:
		using value_type = std::array<char,2>;
		txac(const md21& m,span<std::uint8_t> sp):tot(sp),s(tot.begin(),m.head().materials.number){}
		
		decltype(auto) blocks()
		{
			return (s);
		}
		
		decltype(auto) blocks() const
		{
			return (s);
		}
		
		decltype(auto) entire()
		{
			return (tot);
		}
		decltype(auto) entire() const
		{
			return (tot);
		}
	};
	
	template<typename ostrm>
	decltype(auto) operator<<(ostrm& os,const txac& v)
	{
		return os<<"TXAC\tstd::array<std::array<char,2>,"<<v.blocks().size()<<">\t"<<v.entire().size()<<" bytes";
	}
		
	class sfid
	{
		span<std::uint8_t> tot;
		span<std::uint32_t> s;
	public:
		sfid(const md21& m,span<std::uint8_t> sp):tot(sp),s(tot.begin(),m.head().num_skin_profiles){}
		
		decltype(auto) blocks()
		{
			return (s);
		}
		
		decltype(auto) blocks() const
		{
			return (s);
		}
		
		decltype(auto) entire()
		{
			return (tot);
		}
		decltype(auto) entire() const
		{
			return (tot);
		}
	};
	
	template<typename ostrm>
	decltype(auto) operator<<(ostrm& os,const sfid& v)
	{
		return os<<"SFID\tstd::array<std::uint32_t,"<<v.blocks().size()<<">\t"<<v.entire().size()<<" bytes";
	}
}