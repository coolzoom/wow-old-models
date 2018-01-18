#pragma once
#include<cstdint>
#include<array>
#include<chrono>
#include<stdexcept>
#include"file_parser.h"
#include<bitset>

namespace m2
{
	namespace md20
	{
		namespace common_types
		{
			struct vector2
			{
				float x;
				float y;
			};
			struct vector3
			{
//				float x;
//				float y;
//				float z;
				std::uint32_t x,y,z;
			};
			
			template<typename ostrm>
			decltype(auto) operator<<(ostrm &out,const vector3 &v3)
			{
/*				union
				{
					vector3 v;
					std::bitset<8*sizeof(vector3)> b;
				}u{v3};*/
				struct b
				{
					float x,y,z;
				};
				union
				{
					vector3 v1;
					b v;
				}u{v3};
				return out<<u.v.x<<","<<u.v.y<<","<<u.v.z<<" {"<<v3.x<<","<<v3.y<<","<<v3.z<<"}";
			}
			
			struct vector4
			{
				float x;
				float y;
				float z;
				float w;
			};
			
			struct aa_box
			{
				vector3 min;
				vector3 max;
			};
		}
		
		template<typename T>
		struct iterator
		{
			std::uint32_t number;
			std::uint32_t offset_elements;
			using value_type = T;
		};
		
		struct loop
		{
			std::uint32_t timestamp;
		};
		
		template<typename ostrm>
		decltype(auto) operator<<(ostrm &os,const loop &p)
		{
			return os<<p.timestamp;
		}
		
		struct range
		{
			uint32_t minimum;
			uint32_t maximum;
		};
		
		struct bounds
		{
			common_types::aa_box extent;
			float radius;
		};
		
		struct sequence
		{
			std::uint16_t id;                   // Animation id in AnimationData.dbc
			std::uint16_t variation_index;       // Sub-animation id: Which number in a row of animations this one is.
			std::uint32_t duration;             // The length of this animation sequence in milliseconds.
			float movespeed;               // This is the speed the character moves with in this animation.
			std::uint32_t flags;                // See below.
			std::int16_t frequency;             // This is used to determine how often the animation is played. For all animations of the same type, this adds up to 0x7FFF (32767).
			std::uint16_t padding;
			range replay;
			std::uint16_t blend_time_in;          // The client blends (lerp) animation states between animations where the end and start values differ. This specifies how long that blending takes. Values: 0, 50, 100, 150, 200, 250, 300, 350, 500.
			std::uint16_t blend_time_out;         // The client blends between this sequence and the next sequence for blendTimeOut milliseconds.
									// For both blendTimeIn and blendTimeOut, the client plays both sequences simultaneously while interpolating between their animation transforms.
			bounds bounds;
			std::int16_t variation_next;         // id of the following animation of this AnimationID, points to an Index or is -1 if none.
			std::uint16_t alias_next;            // id in the list of animations. Used to find actual animation if this sequence is an alias (flags & 0x40)
		};
		
		template<typename ostrm>
		decltype(auto) operator<<(ostrm &os,const sequence &p)
		{
			return os<<p.id;
		}
		
		struct track_base
		{
			std::uint16_t interpolation_type;
			std::uint16_t global_sequence;
			iterator<iterator<std::uint32_t>> timestamps;
		};
		
		template<typename T>
		struct track : track_base
		{
			using value_type = T;
			iterator<iterator<value_type>> values;
		};
		
		template<typename T>
		struct spline_key
		{
			using value_type = T;
			value_type value;
			value_type in;
			value_type out;
		};
		
		struct color
		{
			track<common_types::vector3> color;
			track<std::uint16_t> alpha;
		};
		
		struct texture_weight
		{
			track<std::uint16_t> weight;
		};
		
		struct texture_transform
		{
			track<common_types::vector3> translation;
			track<common_types::vector4> rotation;
			track<common_types::vector3> scaling;
		};
		enum class keybone:std::int32_t
		{
			larm,rarm,lshoulder,rshoulder,spinelow,waist,head,jaw,rfingerindex,rfingermiddle,rfingerpinky,rfingerring,rfingerthumb,lfingerindex,lfingermiddle,lfingerpinky,lfingerring,lfingerthumb,bth,csr,csl,breath,name,namemount,chd,cch,root,
			not_exist = -1,
		};
		
		template<typename ostrm>
		decltype(auto) operator<<(ostrm& os,const keybone &c)
		{
			os<<std::int32_t(c);
			switch(c)
			{
				case keybone::larm:
					return os<<"(left arm)";
				case keybone::rarm:
					return os<<"(right arm)";
				case keybone::lshoulder:
					return os<<"(left shoulder)";
				case keybone::rshoulder:
					return os<<"(right shoulder)";
				case keybone::spinelow:
					return os<<"(spine low)";
				case keybone::waist:
					return os<<"(waist)";
				case keybone::head:
					return os<<"(head)";
				case keybone::jaw:
					return os<<"(jaw)";
				case keybone::rfingerindex:
					return os<<"(right finger index)";
				case keybone::rfingermiddle:
					return os<<"(right finger middle)";
				case keybone::rfingerpinky:
					return os<<"(right finger pinky)";
				case keybone::rfingerring:
					return os<<"(right finger ring)";
				case keybone::rfingerthumb:
					return os<<"(right finger thumb)";
				case keybone::lfingerindex:
					return os<<"(left finger index)";
				case keybone::lfingermiddle:
					return os<<"(left finger middle)";
				case keybone::lfingerpinky:
					return os<<"(left finger pinky)";
				case keybone::lfingerring:
					return os<<"(left finger ring)";
				case keybone::lfingerthumb:
					return os<<"(left finger thumb)";
				case keybone::bth:
					return os<<"(bth)";
				case keybone::csr:
					return os<<"(csr)";
				case keybone::csl:
					return os<<"(csl)";
				case keybone::breath:
					return os<<"(breath)";
				case keybone::name:
					return os<<"(name)";
				case keybone::namemount:
					return os<<"(name mount)";
				case keybone::chd:
					return os<<"(chd)";
				case keybone::cch:
					return os<<"(cch)";
				case keybone::root:
					return os<<"(root)";
				case keybone::not_exist:
					return os<<"(not exist)";
				default:
					return os<<"(unknown)";
			}
		}
		struct compbone
		{
			keybone key_bone_id;
			enum
			{
				spherical_billboard = 0x8,
				cylindrical_billboard_lock_x = 0x10,
				cylindrical_billboard_lock_y = 0x20,
				cylindrical_billboard_lock_z = 0x40,
				transformed = 0x200,
				kinematic_bone = 0x400,       // MoP+: allow physics to influence this bone
				helmet_anim_scaled = 0x1000,  // set blend_modificator to helmetAnimScalingRec.m_amount for this bone
			};
			std::uint32_t flags;
			std::int16_t parent_bone;
			std::uint16_t submesh_id;
			union
			{
				struct
				{
					std::uint16_t u_dist_to_furth_desc;
					std::uint16_t u_z_ratio_of_chain;
				} compress_data;
				std::uint32_t bone_name_crc;         // these are for debugging only. their bone names match those in key bone lookup.
			};
			track<common_types::vector3> translation;
			track<std::array<std::uint16_t,4>> rotation;
			track<common_types::vector3> scale;
			common_types::vector3 pivot;
		};
		

		
		template<typename ostrm>
		decltype(auto) operator<<(ostrm& os,const compbone &c)
		{
			if(c.key_bone_id==keybone::not_exist)
			{
				if(c.parent_bone==-1)
					os<<"independent bone";
				else
					os<<"->"<<c.parent_bone;
			}
			else
				os<<c.key_bone_id;
			
			return os<<"\tpivot("<<c.pivot<<")";
//			return os<<c.key_bone_id<<' '<<c.parent_bone<<' '<<c.pivot;
		}
		
		struct vertex
		{
			common_types::vector3 pos;
			std::array<std::uint8_t,4> weight,indice;
			common_types::vector3 normal;
			std::array<common_types::vector2,2> tex_coords;
		};

		struct texture
		{
			std::uint32_t type;
			std::uint32_t flags;
			iterator<char> filename;
		};

		template<typename ostrm>
		decltype(auto) operator<<(ostrm& os,const texture &c)
		{
			return os<<"type:"<<c.type<<"\tflag:"<<c.flags;
		}

		struct material
		{
			std::uint16_t flags;
			std::uint16_t blending_mode;
		};

		struct attachment
		{
			std::uint32_t id;
			std::uint16_t bone;
			std::uint16_t unknown;
			common_types::vector3 position;
			track<std::uint8_t> animate_attached;
		};

		template<typename ostrm>
		decltype(auto) operator<<(ostrm& os,const attachment &c)
		{
			return os<<"id "<<c.id<<"\tbone "<<c.bone<<"\tpivot "<<c.position;
		}

		struct event
		{
			union
			{
				std::uint32_t u;
				std::array<char,4> s;
			}identifier;
			std::uint32_t data;
			std::uint32_t bone;
			common_types::vector3 position;
			track_base enabled;
		};

		struct camera
		{
			std::uint32_t type;
			float far_clip;
			float near_clip;
			track<spline_key<common_types::vector3>> target_position;
			common_types::vector3 target_position_base;
			track<spline_key<float>> roll;
			track<spline_key<float>> fov;
		};

		struct light
		{
			std::uint16_t type;
			std::int16_t bone;
			common_types::vector3 position;
			track<common_types::vector3> ambient_color;
			track<float> ambient_intensity;
			track<common_types::vector3> diffuse_color;
			track<float> diffuse_intensity;
			track<float> attenuation_start;
			track<float> attenuation_end;
			track<std::uint8_t> visibility;
		};

		struct ribbon
		{
			std::uint32_t id;
			std::uint32_t bone_index;
			common_types::vector3 position;
			iterator<std::uint16_t> texture_indices;
			iterator<std::uint16_t> material_indices;
			track<common_types::vector3> color_track;
			track<std::uint16_t> alpha_track;
			track<float> height_above_track;
			track<float> height_below_track;
			std::chrono::duration<float> edges_per_second;
			std::chrono::duration<float> edges_lifetime;
			float gravity;
			std::uint16_t texture_rows;
			std::uint16_t texture_cols;
			track<std::uint16_t> tex_slot_track;
			track<std::uint8_t> visibility_track;
			std::int16_t priority_plane;
			std::uint16_t padding;
		};

		class version
		{
			std::uint32_t v;
		public:
			decltype(auto) get() const
			{
				return v;
			}
			decltype(auto) get()
			{
				return v;
			}
		};
		template<typename ostrm>
		decltype(auto) operator<<(ostrm& os,const version& v)
		{
			auto val(v.get());
			switch(val)
			{
				case 264:
					return os<<"Wrath of the Lich King";
				case 272:
					return os<<"Mists of Pandaria";
				case 273:
					return os<<"Warlords of Draenor";
				case 274:
					return os<<"Legion";
				default:
					if(val<256)
						return os<<"Classic ("<<val<<')';
					else if(260<val&&val<264)
						return os<<"The Burning Crusade ("<<val<<')';
					else if(264<val&&val<272)
						return os<<"Cataclysm ("<<val<<')';
					else
						return os<<"Unknown Expansion ("<<val<<')';
			}
		}
		struct header
		{
			std::uint32_t magic;
			version vers;
			iterator<char> name;
			struct
			{
				std::uint32_t flag_tilt_x: 1;
				std::uint32_t flag_tilt_y: 1;
				std::uint32_t : 1;
				std::uint32_t flag_use_texture_combiner_combos: 1;
				std::uint32_t : 1;
				std::uint32_t flag_load_phys_data : 1;
				std::uint32_t : 1;
				std::uint32_t flag_demon_hunter_tatto_glowing: 1;  
				std::uint32_t flag_camera_related: 1;
				std::uint32_t flag_new_particle_record: 1;
				std::uint32_t flag_unk_0x400 : 1;
				std::uint32_t flag_texture_transforms_use_bone_sequences: 1;
				std::uint32_t flag_unk_0x1000: 1;
				std::uint32_t flag_unk_0x2000: 1;
				std::uint32_t flag_unk_0x4000: 1;
				std::uint32_t flag_unk_0x8000: 1;
				std::uint32_t flag_unk_0x10000: 1;
				std::uint32_t flag_unk_0x20000: 1;
				std::uint32_t flag_unk_0x40000: 1;
				std::uint32_t flag_unk_0x80000: 1;
				std::uint32_t flag_unk_0x100000: 1;
				std::uint32_t flag_unk_0x200000: 1;// apparently: use 24500 upgraded model format: chunked .anim files, change in the exporter reordering sequence+bone blocks before name
			}flags;

			iterator<loop> loops;
			iterator<sequence> sequences;
			iterator<std::uint16_t> sequences_lookups;
			iterator<compbone> bones;
			iterator<std::int16_t> key_bone_lookups;
			iterator<vertex> vertices;
			std::uint32_t num_skin_profiles;
			iterator<color> colors;
			iterator<texture> textures;
			iterator<texture_weight> texture_weights;
			iterator<texture_transform> texture_transforms;
			iterator<std::uint16_t> replacable_texture_lookup;
			iterator<material> materials;

			iterator<std::uint16_t> bone_lookup_table;
			iterator<std::uint16_t> texture_lookup_table;
			iterator<std::uint16_t> tex_unit_lookup_table;
			iterator<std::uint16_t> transparency_lookup_table;
			iterator<std::uint16_t> texture_transforms_lookup_table;

			common_types::aa_box bounding_box;
			float bounding_sphere_radius;
			common_types::aa_box collision_box;
			float collision_sphere_radius;
			iterator<std::uint16_t> collision_triangles;
			iterator<common_types::vector3> collision_vertices;
			iterator<common_types::vector3> collision_normals;
			iterator<attachment> attachments;

			iterator<std::uint16_t> attachment_lookup_table;
			iterator<event> events;
			iterator<light> lights;
			iterator<camera> cameras;
			iterator<std::uint16_t> camera_lookup_table;
			iterator<ribbon> ribbon_emitters;
			iterator<void> particle_emitters;
		};
	}

	struct md20_magic_tag_t{}md20_magic_tag;
	
	class md21
	{
		span<std::uint8_t> m;
		md20::header *hd;
		bool md20_tg=false;
	public:
		md21(const span<std::uint8_t> &s):m(s)
		{
			using namespace std::string_literals;
			parser p(m.begin(),m.end());
			hd = p.at<md20::header>();
			if(hd->magic!=0x3032444D)
			{
				union
				{
					std::uint32_t u;
					std::array<char,4> a;
				}mg{hd->magic};
				throw std::runtime_error("not a md20 block : "s+std::to_string(mg.u)+'\t'+std::string(mg.a.begin(),mg.a.end()));
			}
		}
		md21(md20_magic_tag_t,const span<std::uint8_t> &s):m(s.begin()-4,s.end()),md20_tg(true)
		{
			using namespace std::string_literals;
			parser p(m.begin(),m.end());
			hd = p.at<md20::header>();
			if(hd->magic!=0x3032444D)
			{
				union
				{
					std::uint32_t u;
					std::array<char,4> a;
				}mg{hd->magic};
				throw std::runtime_error("not a md20 block : "s+std::to_string(mg.u)+'\t'+std::string(mg.a.begin(),mg.a.end()));
			}
		}
		
		decltype(auto) head() const
		{
			return *hd;
		}
		
		auto size() const
		{
			return m.size();
		}
		
		template<typename T>
		auto operator[](const md20::iterator<T> &i)
		{
			return span<T>(m.begin()+i.offset_elements,i.number);
		}
		
		template<typename T>
		auto operator[](const md20::iterator<T> &i) const
		{
			return span<const T>(m.cbegin()+i.offset_elements,i.number);
		}
		
		template<typename T>
		auto at(const md20::iterator<T> &i)
		{
			if(i.offset_elements+i.number*sizeof(T)<size())
				return operator[](i);
			throw std::out_of_range("md20 iterator out of range");
		}
		
		template<typename T>
		auto at(const md20::iterator<T> &i) const
		{
			if(i.offset_elements+i.number*sizeof(T)<size())
				return operator[](i);
			throw std::out_of_range("md20 iterator out of range");
		}
		
		bool is_md20() const
		{
			return md20_tg;
		}
		
		void set_attachment_position(std::size_t pos,const md20::common_types::vector3& v)
		{
			decltype(auto) bones(at(hd->bones));
			decltype(auto) attachments(at(hd->attachments));
			std::size_t i(0);
			for(;i!=attachments.size();++i)
				if(attachments[i].id==pos)
					break;
			if(i==attachments.size())
				throw std::runtime_error("no this attachment in the model file");
			bones.at(attachments.at(i).bone).pivot=attachments.at(i).position=v;
		}
	};
	
	template<typename ostrm>
	decltype(auto) operator<<(ostrm& os,const md21& v)
	{
		if(v.is_md20())
			os<<"MD20\t";
		else
			os<<"MD21\t";
		os<<v.size()<<" bytes\t"<<v.head().vers<<'\t';
		auto s(v.at(v.head().name));
		if(s.back())
			os.rdbuf()->sputn(s.data(),s.size());
		else
			os<<s.data();
		if(v.head().flags.flag_unk_0x200000)
			os<<"\t(24500 upgraded model format)";
		return (os);
	}
	
}