#ifndef CHARSECTIONS_H
#define CHARSECTIONS_H
#include"wdb6.h"
#include<array>
#include"race.h"

namespace db2
{
	namespace charsections_details
	{
		struct flag
		{
			std::uint16_t value;
			flag() = default;
			flag(const std::uint16_t &v):value(v){}
			bool operator=(const flag& b) const
			{
				return value==b.value;
			}
		};
		
		template<typename ostrm>
		decltype(auto) operator<<(ostrm& out,const flag& e)
		{
			out<<static_cast<std::uint32_t>(e.value);
			if(e.value&1)
				out<<"[P]";
			if(e.value&2)
				out<<"[B]";
			if(e.value&4)
				out<<"[DK]";
			if(e.value&8)
				out<<"[NPC]";
			if(e.value&64)
				out<<"[DH]";
			return (out);
		}
		enum class sex : std::uint8_t
		{male,female};
		template<typename ostrm>
		decltype(auto) operator<<(ostrm& out,const sex& e)
		{
			switch(e)
			{
			case sex::male:
				out.put('M');
			break;
			case sex::female:
				out.put('F');
			break;
			default:
				throw std::runtime_error("unknown sex");
			}
			return (out);
		}

		enum class field : std::uint8_t
		{skin,face,facial,hair,underwear,hd_skin,hd_face,hd_facial,hd_hair,hd_underwear,demon_hunter_tatto=11};
		template<typename ostrm>
		decltype(auto) operator<<(ostrm& out,const field& e)
		{
			switch(e)
			{
			case field::skin:
				out<<"Skin";
			break;
			case field::face:
				out<<"Face";
			break;
			case field::facial:
				out<<"Facial";
			break;
			case field::hair:
				out<<"Hair";
			break;
			case field::underwear:
				out<<"Underwear";
			break;
			case field::hd_skin:
				out<<"HD Skin";
			break;
			case field::hd_face:
				out<<"HD Face";
			break;
			case field::hd_facial:
				out<<"HD Facial";
			break;
			case field::hd_hair:
				out<<"HD Hair";
			break;
			case field::hd_underwear:
				out<<"HD Underwear";
			break;
			case field::demon_hunter_tatto:
				out<<"DH Tatto";
			break;
			default:
				out<<"Unknown("<<static_cast<std::uint32_t>(e)<<")";
			}
			return (out);
		}
	}

	struct charsections
	{
		std::array<std::uint32_t,3> textures;
		charsections_details::flag flag;
		db2::race race;
		charsections_details::sex sex;
		charsections_details::field field;
		std::array<std::uint8_t,3> c;
		charsections() = default;
		charsections(const std::uint32_t& t1,const std::uint32_t& t2,const std::uint32_t& t3,
					const charsections_details::flag &f,
					const db2::race &r,const charsections_details::sex &s,
					const charsections_details::field &fd,
					const std::uint8_t &c1,const std::uint8_t &c2,const std::uint8_t &c3)
						:textures{t1,t2,t3},flag(f),race(r),sex(s),field(fd),c{c1,c2,c3}{}
	};	
	
	template<typename ostrm>
	decltype(auto) operator<<(ostrm& out,const charsections& e)
	{
		for(const auto &ele : e.textures)
			(out<<ele).put('\t');
		(out<<e.flag).put('\t');
		(out<<e.race).put('\t');
		(out<<e.sex).put('\t');
		out<<e.field;
		for(const auto &ele : e.c)
		{
			out.put('\t');
			out<<ele;
		}
		return (out);
	}
	using charsections_file = wdb6<charsections>;
}
#endif