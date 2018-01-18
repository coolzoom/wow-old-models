#pragma once
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
	return out<<"sd:"<<e.sd<<"\thd:"<<e.hd;
}
}