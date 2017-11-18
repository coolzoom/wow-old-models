#include"charsections.h"
#include<exception>
#include<vector>
#include<random>
#include<numeric>
#include<algorithm>

int main()
{
	try
	{
		std::random_device rd;
		db2::charsections_file c("charsections.db2");
		fast_io::obuf obuf("charsections.txt");
		std::vector<db2::charsections> vec;
		std::vector<std::uint32_t> label(10);
		std::iota(label.begin(),label.end(),0);
		std::shuffle(label.begin(),label.end(),rd);
		auto label2(label);
		using namespace db2::charsections_details;
		for(std::size_t i(0);i!=6;++i)
		{
			auto v(label[i]);
			vec.emplace_back(3244+v,0,0,17,db2::race::bloodelf,sex::female,field::skin,0,i+19,0);
		}
		for(std::size_t i(0);i!=6;++i)
		{
			auto k(label[i]);


			std::shuffle(label2.begin(),label2.end(),rd);
			for(std::size_t j(0);j!=1;++j)
			{
				auto v(0);
//				auto v(label2[j]);
				vec.emplace_back(3024+10*k+j,3124+10*k+j,0,33,db2::race::bloodelf,sex::female,field::face,i,19+j,0);
			}
		}


		for(const auto &ele : vec)
		{
			fprint(obuf,"%\n",ele);
		}
		c.insert(vec.cbegin(),vec.cend());
		c.save("charsections1.db2");
	}
	catch(const std::exception &ex)
	{
		fprint(fast_io::err,"%\n",ex.what());
		return 1;
	}
}