#pragma once
#include<cstdint>
#include<array>
#include<chrono>
#include"md20.h"
#include<any>
#include<vector>
#include"file_parser.h"
#include<stdexcept>
#include"chunk.h"
#include<string>
#include<ostream>

namespace m2
{
	class chunk
	{
		struct base
		{
			virtual std::ostream& output(std::ostream& os) const = 0;
			virtual const std::type_info& type() const noexcept = 0;
			virtual base* clone() const = 0;
			virtual ~base() = default;
		}*u;
		template<typename T>
		struct derv : public base
		{
			T t;
			template<typename ...Args>
			derv(Args&& ...args):t(std::forward<Args>(args)...){}
			std::ostream& output(std::ostream& os) const
			{
				return os<<t;
			}
			const std::type_info& type() const noexcept
			{
				return typeid(t);
			}
			
			base* clone() const
			{
				return new derv(*this);
			}
		};
	public:
		template<typename T,typename ...Args>
		chunk(std::in_place_type_t<T>,Args&& ...args):u(new derv<T>(std::forward<Args>(args)...)){}
		
		const std::type_info& type() const noexcept
		{
			return u->type();
		}
		
		template<typename T>
		T& get()
		{
			if(type()==typeid(T))
				return static_cast<derv<T>*>(u)->t;
			throw std::bad_cast();
		}
		
		template<typename T>
		const T& get() const
		{
			if(type()==typeid(T))
				return static_cast<const derv<T>*>(u)->t;
			throw std::bad_cast();
		}

		~chunk()
		{
			delete u;
		}

		chunk(const chunk& c):u(c.u->clone()){}

		chunk& operator=(const chunk& c)
		{
			auto newp(c.u->clone());
			delete u;
			u=newp;
			return *this;
		}
				
		chunk(chunk&& c) noexcept:u(c.u)
		{
			c.u = nullptr;
		}
		
		chunk& operator=(chunk &&c) noexcept
		{
			if(&c!=this)
			{
				delete u;
				u=c.u;
				c.u=nullptr;
			}
			return *this;
		}
	
		void swap(chunk& c) noexcept
		{
			using std::swap;
			swap(u,c.u);
		}
		
		friend std::ostream& operator<<(std::ostream& os,const chunk &c)
		{
			return c.u->output(os);
		}
	};
	
	inline void swap(chunk& a,chunk &b)
	{
		a.swap(b);
	}
	
	class m2
	{
		file_parser f;
		std::vector<chunk> chunks;
		auto next_chunk()
		{
			return f.at_n<std::uint8_t>(*f.next<std::uint32_t>());
		}
		
		md21 md;
		
		auto init_md21()
		{
			using namespace std::string_literals;
			auto m(f.at<std::uint32_t>());
			switch(*m)
			{
				case 0x3132444D:
					return md21(next_chunk());
				case 0x3032444D:
					return md21(md20_magic_tag,f.remain());
				default:
					throw std::runtime_error("Not a m2 file. The first block is not MD21. Which is "s+std::string(reinterpret_cast<std::uint8_t*>(m),reinterpret_cast<std::uint8_t*>(m+1))+" ("s+std::to_string(*m)+')');
			}
		}
		
	public:
		m2(const char* filename):f(filename),md(init_md21())
		{
			for(;f;)
			{
				auto m(*f.at<std::uint32_t>());
				switch(m)
				{
					case 1145652801:
						chunks.emplace_back(std::in_place_type<afid>,next_chunk());
					break;
					case 1145652819:
						chunks.emplace_back(std::in_place_type<sfid>,md,next_chunk());
					break;
					case 1128355924:
						chunks.emplace_back(std::in_place_type<txac>,md,next_chunk());
					break;
					case 1145652802:
						chunks.emplace_back(std::in_place_type<bfid>,next_chunk());
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
					return ele.get<T>();
			throw std::logic_error("md file does not have this type");
		}
		

		
		template<typename T>
		decltype(auto) get() const
		{
			for(auto &ele : chunks)
				if(ele.type()==typeid(T))
					return ele.get<T>();
			throw std::logic_error("md file does not have this type");
		}
		

		template<typename T>
		auto gets()
		{
			std::vector<std::reference_wrapper<T>> vec;
			for(auto &ele : chunks)
				if(ele.type()==typeid(T))
					vec.emplace_back(ele.get<T>());
			return vec;
		}
		template<typename T>
		auto gets() const
		{
			std::vector<std::reference_wrapper<const T>> vec;
			for(auto &ele : chunks)
				if(ele.type()==typeid(T))
					vec.emplace_back(ele.get<const T>());
			return vec;
		}
		
		decltype(auto) vector()
		{
			return (chunks);
		}
		
		decltype(auto) vector() const
		{
			return (chunks);
		}
	};
	
	template<>
	decltype(auto) m2::get<md21>() const
	{
		return (md);
	}

	template<>
	decltype(auto) m2::get<md21>()
	{
		return (md);
	}
	
	std::ostream& operator<<(std::ostream& os,const m2& m)
	{
		os<<m.get<md21>();
		for(const auto &ele : m.vector())
			os<<'\n'<<ele;
		return os;
	}
}