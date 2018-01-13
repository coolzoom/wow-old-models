#include"m2.h"
#include<exception>
#include<stdexcept>
#include<iostream>

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
		if(argc<3)
		{
			std::cerr<<"Usage : "<<*argv<<" <m2 input file path> <m2 output file path>\n";
			return 1;
		}
//		std::cout<<sizeof(m2::md20::common_types::vector3)<<' '<<sizeof(m2::md20::common_types::aa_box)<<'\n';
		m2::m2 p(argv[1]);
		std::cout<<p<<'\n';
		decltype(auto) md21(p.get<m2::md21>());
/*		std::cout<<"sequences\n";
		output(md21.at(md21.head().sequences));
		
		std::cout<<"sequences lookups\n";
		output(md21.at(md21.head().sequences_lookups));*/

		decltype(auto) bones(md21.at(md21.head().bones));
		std::cout<<"bones before modifying\n";
		output(bones);
//		bones.at(19).set_pivot(3177218249,1025387631,1070336046);
//		bones.at(22).set_pivot(3177218238,3172872417,1070336049);
//		bones.at(28).set_pivot(3182249210,1041519159,1070374070);
//		bones.at(29).set_pivot(3182249210,3189002807,1070374070);
		std::cout<<"bones after modifying\n";
		
	}
	catch(const std::exception& ex)
	{
		std::cerr<<ex.what()<<'\n';
		return 1;
	}
}