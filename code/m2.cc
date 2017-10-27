#include"m2.h"
#include<exception>
#include<stdexcept>
#include<iostream>

int main(int argc,char **argv)
{
	try
	{
		if(argc<2)
		{
			std::cerr<<"Usage : "<<*argv<<" <m2 filename path>\n";
			return 1;
		}
		const m2::m2 p(argv[1]);
		std::cout<<p<<'\n';
		decltype(auto) md21(p.get<m2::md21>());
		decltype(auto) m(md21.at(md21.head().bones));
		std::cout<<m.size()<<'\n';
		std::size_t i(0);
		for(const auto &ele : m)
		{
			std::cout<<i<<' '<<ele<<'\n';
			++i;
		}
	}
	catch(const std::exception& ex)
	{
		std::cerr<<ex.what()<<'\n';
		return 1;
	}
}