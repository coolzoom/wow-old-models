#include"chrraces.h"
#include<iostream>
#include<fstream>
#include<string>

int main(int argc,char **argv)
{
	std::ios::sync_with_stdio(false);
	try
	{
		db2::chrraces_file cf("chrraces.db2");
		std::ofstream fout("chrraces.txt");
		auto rc(cf.records());
		std::vector<std::string> args(argv+1,argv+argc);
		for(auto &ele : args)
		{
			for(auto &e : ele)
			{
				if('A'<=e&&e<='Z')
					e+='a'-'A';
			}
		}
		auto set_flag([&rc](std::size_t pos,const std::string& str)
		{
			decltype(auto) flag((rc.at(pos).m_flags));
			flag^=0x80;
			decltype(auto) cout_rdbuf(*std::cout.rdbuf());
			cout_rdbuf.sputn(str.data(),str.size());
			if(flag&0x80)
				std::cout<<" old models is now disabled\n";
			else
				std::cout<<" old models is now enabled\n";
		});
		using namespace std::string_literals;
		for(const auto &ele : args)
		{
			if(ele=="ne"s||ele=="nightelf"s)
				set_flag(3,"Night elf"s);
			else if(ele=="tauren"s)
				set_flag(6,"Tauren"s);
			else if(ele=="draenei"s)
				set_flag(10,"Draenei"s);
			else if(ele=="be"s||ele=="bloodelf"s)
				set_flag(9,"Blood elf"s);
		}
		for(std::size_t i(0);i!=rc.size();++i)
		{
			fout<<i;
			switch(i)
			{
				case 3:
					fout<<"(Night elf)";
				break;
				case 6:
					fout<<"(Tauren)";
				break;
				case 9:
					fout<<"(Blood elf)";
				break;
				case 10:
					fout<<"(Draenei)";
				break;
			}
			fout<<":\t";
			fout<<rc[i]<<'\n';
		}
		std::cout<<"Log has been saved to chrraces.txt\n";
	}
	catch(const std::exception& ex)
	{
		std::cerr<<ex.what()<<'\n';
		return 1;
	}
}