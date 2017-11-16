#include"charsections.h"
#include<exception>
#include<vector>
#include<string>
#include<random>
#include<algorithm>

namespace race_range
{
template<std::size_t T,std::size_t N>
constexpr std::pair<std::size_t,std::size_t> range(std::size_t i)
{
	return {T+i*N,T+i*(N+1)};
}

constexpr auto blood_elf_female(std::size_t i)
{
	return range<3244,10>(i);
}


}

int main()
{
	try
	{
		db2::charsections_file c("charsections.db2");
		fast_io::obuf obuf("charsections.txt");
		std::vector<db2::charsections> sv;
		
		
		for(const auto &ele : c.records())
			if(ele.race==db2::race::bloodelf&&ele.field<db2::charsections_details::field::hd_skin&&ele.sex==db2::charsections_details::sex::female)
				sv.emplace_back(ele);
		std::vector<db2::charsections> vec;
		
		for(const auto &ele : c.records())
		{
			if(ele.flag.value!=256&&ele.sex==db2::charsections_details::sex::female&&ele.race==db2::race::bloodelf&&db2::charsections_details::field::hd_skin<=ele.field&&ele.field<=db2::charsections_details::field::hd_underwear)
			{
				const db2::charsections_details::field f(db2::charsections_details::field(static_cast<std::uint8_t>(ele.field)-static_cast<std::uint8_t>(db2::charsections_details::field::hd_skin)));
				for(const auto &e1:sv)
				{
					if(f==e1.field&&e1.flag.value==ele.flag.value&&e1.sex==ele.sex&&e1.field==f&&ele.c==e1.c)
					{
						goto next_loop;
					}
				}
				vec.emplace_back(ele);
				next_loop:;
			}
		}
		for(const auto &ele : sv)
			(obuf<<ele).put('\n');
		obuf.put('\n');

		std::vector<db2::charsections> v2(vec.cbegin()+40,vec.cbegin()+46);
//		std::random_device rdv;
//		std::uniform_int_distribution<std::uint32_t> ud(3244,3253);
		for(auto &ele : v2)
		{
//			ele.textures.front() = ud(rdv);
			ele.field=static_cast<db2::charsections_details::field>(static_cast<std::uint8_t>(ele.field)-5);
		}
		fprint(obuf,"v2\n");
		for(std::size_t i(0);i!=v2.size();++i)
			fprint(obuf,"%\t%\n",i,v2[i]);

		std::vector<db2::charsections> v3(vec.cbegin()+46,vec.cbegin()+81);
		for(auto &ele : v3)
		{
//			ele.textures.front() = ud(rdv);
			ele.field=static_cast<db2::charsections_details::field>(static_cast<std::uint8_t>(ele.field)-5);
		}
		fprint(obuf,"v3\n");
		
		for(std::size_t i(0);i!=v3.size();++i)
			fprint(obuf,"%\t%\n",i,v3[i]);

		c.insert(v3.begin(),v3.end());
		c.save("charsections1.db2");

	}
	catch(const std::exception &ex)
	{
		fprint(fast_io::err,"%\n",ex.what());
		return 1;
	}
}