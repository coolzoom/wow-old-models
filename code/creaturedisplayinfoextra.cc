#include"file_parser.h"
#include"creaturedisplayinfoextra.h"
#include<iostream>
#include<fstream>

int main()
{
	std::ios::sync_with_stdio(false);
	try
	{
		db2::creaturedisplayinfoextra_file cf("creaturedisplayinfoextra.db2");
		std::ofstream fout("creaturedisplayinfoextra.txt",std::ofstream::binary);
		auto rc(cf.records());
		std::size_t counter(0);
		using std::swap;
		for(std::size_t i(0);i!=rc.size();++i)
		{
			decltype(auto) ele(rc[i]);
			if(!ele.sd&&ele.hd)
			{
				++counter;
				swap(ele.sd,ele.hd);
				fout<<i<<":\n"<<rc[i]<<'\n';
			}
		}
		fout<<counter<<'\n';
	}
	catch(const std::exception& ex)
	{
		std::cerr<<ex.what()<<'\n';
		return 1;
	}
}