#include"file_parser.h"
#include"chrraces.h"
#include<iostream>
#include<fstream>

int main()
{
	std::ios::sync_with_stdio(false);
	try
	{
		db2::chrraces_file cf("chrraces.db2");
		std::ofstream fout("chrraces.txt",std::ofstream::binary);
		auto rc(cf.records());
		rc.at(3).m_flags^=0x80;					//set flag for NE
		rc.at(10).m_flags^=0x80;					//set flag for draenei
//		rc.at(9).m_flags^=0x80;					//set flag for blood elf. disable it by default since model files are currently broken.


		for(std::size_t i(0);i!=rc.size();++i)
			fout<<i<<":\t"<<rc[i]<<'\n';
	}
	catch(const std::exception& ex)
	{
		std::cerr<<ex.what()<<'\n';
		return 1;
	}
}