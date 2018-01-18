#include"file_parser.h"
#include"creaturedisplayinfoextra.h"
#include"wdb6.h"
#include<iostream>
#include<fstream>

int main()
{
	std::ios::sync_with_stdio(false);
	try
	{
		db2::wdb6_file<db2::creaturedisplayinfoextra> cf("creaturedisplayinfoextra.db2");
		std::ofstream fout("creaturedisplayinfoextra.txt");
		auto rc(cf.records());
		std::size_t counter(0);
		using std::swap;
		for(std::size_t i(0);i!=rc.size();++i)
		{
			decltype(auto) ele(rc[i]);
			if(!ele.sd&&ele.hd)
			{
				++counter;
				fout<<i<<"\t"<<rc[i]<<'\n';
			}
		}
		fout<<counter<<'\n';
//		std::cout<<"Log has been saved to creaturedisplayinfoextra.txt\n";
	}
	catch(const std::exception& ex)
	{
		std::cerr<<ex.what()<<'\n';
		return 1;
	}
}