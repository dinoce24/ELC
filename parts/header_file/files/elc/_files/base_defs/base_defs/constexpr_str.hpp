//constexpr_str.hpp
//at namespace elc::defs::base
/*
未完成的elc解释器base_defs文件
由steve02081504与Alex0125设计、编写
转载时请在不对此文件做任何修改的同时注明出处
项目地址：https://github.com/steve02081504/ELC
*/
namespace constexpr_str_n{
	template<typename char_T>
	struct constexpr_str_view_t:array_like_view_t<const char_T>{
		typedef array_like_view_t<const char_T> base_t;
		using base_t::base_t;
		[[nodiscard]]constexpr const char_T*str()const noexcept{return base_t::cbegin();}
		[[nodiscard]]constexpr operator const char_T*()const noexcept{return str();}
	};
	template<typename char_T>
	struct constexpr_str_t:constexpr_str_view_t<char_T>{
		typedef constexpr_str_view_t<char_T> base_t;
		hash_t hash_result;
		range_n::match_pattern<const char_T> match_pattern;
		range_n::reverse_match_pattern<const char_T> reverse_match_pattern;
		constexpr constexpr_str_t(const char_T* str, size_t size):
			base_t(str, size),
			hash_result(defs::hash(str, size)),
			match_pattern(array_like_view_t<const char_T>{str, size}),
			reverse_match_pattern(array_like_view_t<const char_T>{str, size}) {}
		[[nodiscard]]constexpr hash_t hash()const noexcept{return hash_result;}
	};
	template<class char_T,size_t N>
	struct constexpr_str_t_literal_helper{
		const char_T* _array_begin;
		constexpr constexpr_str_t_literal_helper(const char_T(&str)[N])noexcept{
			_array_begin=str;
		}
		[[nodiscard]]constexpr auto get_constexpr_str_t()const noexcept{
			return constexpr_str_t{_array_begin,N};
		}
	};
	template<constexpr_str_t_literal_helper v>
	struct literal_result_provider {
		distinctive static constexpr auto value = v.get_constexpr_str_t();
	};
	//别问，问就是傻逼c++
	template<constexpr_str_t_literal_helper str_helper>
	[[nodiscard]]inline consteval auto& operator ""_constexpr_str()noexcept{
		return literal_result_provider<str_helper>::value;
	}
	template<class char_T>
	distinctive inline constexpr auto empty_constexpr_str_of = constexpr_str_t(&const_default_value_of<char_T>,0);
};
using constexpr_str_n::constexpr_str_view_t;
using constexpr_str_n::constexpr_str_t;
using constexpr_str_n::empty_constexpr_str_of;
using constexpr_str_n::operator ""_constexpr_str;

//file_end

