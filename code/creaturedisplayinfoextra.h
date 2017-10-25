#ifndef CREATUREDISPLAYINFOEXTRA_H
#define CREATUREDISPLAYINFOEXTRA_H
#include"wdb6.h"
#include<array>

namespace db2
{
	struct creaturedisplayinfoextra
	{
		std::uint32_t sd;
		std::uint32_t hd;
		std::array<std::uint8_t,11> a;
		std::uint8_t flags;
	};

	template<typename ostrm>
	decltype(auto) operator<<(ostrm& out,const creaturedisplayinfoextra& e)
	{
		out<<"sd\t"<<e.sd<<'\n';
		out<<"hd\t"<<e.hd<<'\n';
		out<<"flags\t"<<static_cast<unsigned>(e.flags)<<'\n';
		return out;
	}
	using creaturedisplayinfoextra_file = wdb6_file<creaturedisplayinfoextra>;
}
#endif