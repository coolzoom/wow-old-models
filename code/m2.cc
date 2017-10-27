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
		auto sp(md21.at(md21.head().bones));
		std::cout<<sp.size()<<'\n';
		for(const auto &ele : sp)
		{
			std::cout<<ele<<'\n';
		}
	}
	catch(const std::exception& ex)
	{
		std::cerr<<ex.what()<<'\n';
		return 1;
	}
}