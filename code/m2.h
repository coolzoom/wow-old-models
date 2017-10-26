#pragma once
#include<cstdint>
#include<array>
#include<chrono>
#include"md20.h"
#include<any>
#include<vector>
#include"file_parser.h"
#include<stdexcept>
#include"md20.h"
#include<string>

namespace m2
{
	class unknown
	{
		union
		{
			std::uint32_t u;
			std::array<char,4> a;
		}t;
		span<std::uint8_t> m;
	public:
		unknown(std::uint32_t tag,const span<std::uint8_t> &s):t{tag},m(s){}		
		std::uint32_t tag()
		{
			return t.u;
		}
		std::string name() const
		{
			return std::string(t.a.cbegin(),t.a.cend());
		}
		decltype(auto) data() const
		{
			return m;
		}
	};
	
	class m2
	{
		file_parser f;
		std::vector<std::any> chunks;
		auto next_chunk()
		{
			return f.at_n<std::uint8_t>(*f.next<std::uint32_t>());
		}
	public:
		m2(const char* filename):f(filename)
		{
			for(;f;)
			{
				auto m(*f.at<std::uint32_t>());
				switch(m)
				{
					case 0x3132444D:
						chunks.emplace_back(std::in_place_type<md21>,next_chunk());
					break;
					default:
						chunks.emplace_back(std::in_place_type<unknown>,m,next_chunk());
				}
			}
		}
		
		template<typename T>
		decltype(auto) get()
		{
			for(auto &ele : chunks)
				if(ele.type()==typeid(T))
					return std::any_cast<T>(ele);
			throw std::logic_error("md file does not have this type");
		}
		
		decltype(auto) vector()
		{
			return chunks;
		}
	};
}