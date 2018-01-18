#include"m2.h"
#include<exception>
#include<stdexcept>
#include<iostream>
#include<vector>

template<typename T>
void output(const T& c)
{
	for(std::size_t i(0);i!=c.size();++i)
		std::cout<<i<<':'<<c[i]<<'\n';
}

int main(int argc,char **argv)
{
	try
	{
		
//		std::cout<<sizeof(m2::md20::common_types::vector3)<<' '<<sizeof(m2::md20::common_types::aa_box)<<'\n';
		if(argc<2)
		{
			std::cerr<<"Usage : "<<*argv<<" <m2 filename path>\n";
			return 1;
		}
		const m2::m2 p(argv[1]);
		std::cout<<p<<'\n';
/*		decltype(auto) md21(p.get<m2::md21>());
		std::cout<<"sequences\n";
		output(md21.at(md21.head().sequences));
		
		std::cout<<"sequences lookups\n";
		output(md21.at(md21.head().sequences_lookups));
		std::cout<<"key bone lookups\n";
		output(md21.at(md21.head().key_bone_lookups));

		std::cout<<"bones\n";
		output(md21.at(md21.head().bones));
		

		
		decltype(auto) attc(md21.at(md21.head().attachments));		
		std::cout<<"attachments\n";
		output(attc);*/
		
/*		decltype(auto) attclup(md21.at(md21.head().attachment_lookup_table));		
		std::cout<<"attachments lookups\n";
		output(attclup);*/
		
		
//		for(std::size_t i(0);i!=attc.size();++i)
//			std::cout<<i<<' '<<attc[i]<<'\n';
	}
	catch(const std::exception& ex)
	{
		std::cerr<<ex.what()<<'\n';
		return 1;
	}
}