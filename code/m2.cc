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
		m2::m2 p(argv[1]);
	}
	catch(const std::exception& ex)
	{
		std::cerr<<ex.what()<<'\n';
		return 1;
	}
}