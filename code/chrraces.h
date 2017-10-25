#ifndef CHRRACES_H
#define CHRRACES_H
#include"wdb6.h"
#include<array>

namespace db2
{
	struct chrraces
	{
		uint32_t m_flags;
		std::array<uint8_t,112> com;
	};
	
	template<typename ostrm>
	decltype(auto) operator<<(ostrm& out,const chrraces& e)
	{
		return out<<e.m_flags;
	}
	using chrraces_file = wdb6_file<chrraces>;
}
#endif