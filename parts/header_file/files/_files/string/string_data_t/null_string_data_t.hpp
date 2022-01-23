//null_string_data_t.hpp
//at namespace elc::defs::string_n::string_data_n
/*
未完成的elc解释器string文件
由steve02081504与Alex0125设计、编写
转载时请在不对此文件做任何修改的同时注明出处
项目地址：https://github.com/steve02081504/ELC
*/
template<typename char_T>
struct null_string_data_t final:base_string_data_t<char_T>,instance_struct<null_string_data_t<char_T>>{
	typedef null_string_data_t<char_T> this_t;
	typedef base_string_data_t<char_T> base_t;
	using base_t::ptr_t;
	using base_t::string_view_t;

	null_string_data_t()noexcept:base_t(never_ref_num_zero){}

	virtual void be_replace_as(ptr_t a)override final{nothing;}
	[[nodiscard]]virtual char_T* get_c_str()override final{
		static char_T data[1]{};
		return data;
	}
	[[nodiscard]]virtual size_t get_size()override final{ return 0; }
	[[nodiscard]]virtual ptr_t get_substr_data([[maybe_unused]]size_t begin,[[maybe_unused]]size_t size)override final{ return this; }
	[[nodiscard]]virtual ptr_t apply_str_to_begin(string_view_t str)override final{ return get<comn_string_data_t<char_T>>(str); }
	[[nodiscard]]virtual ptr_t apply_str_to_begin(ptr_t str)override final{ return str; }
	[[nodiscard]]virtual ptr_t apply_str_to_end(string_view_t str)override final{ return get<comn_string_data_t<char_T>>(str); }
	[[nodiscard]]virtual ptr_t apply_str_to_end(ptr_t str)override final{ return str; }

	[[nodiscard]]virtual ptr_t do_insert([[maybe_unused]]size_t pos,[[maybe_unused]]string_view_t str)override final{ return get<comn_string_data_t<char_T>>(str); }
	[[nodiscard]]virtual ptr_t do_insert([[maybe_unused]]size_t pos,[[maybe_unused]]ptr_t str)override final{ return str; }
	[[nodiscard]]virtual ptr_t do_erase([[maybe_unused]]size_t pos,[[maybe_unused]]size_t size)override final{ return this; }

	virtual void copy_part_data_to([[maybe_unused]]char_T* to,[[maybe_unused]]size_t pos,[[maybe_unused]]size_t size)override final{ return; }
	[[nodiscard]]virtual char_T arec([[maybe_unused]]size_t index)override final{ return*(char_T*)null_ptr; }
	virtual void arec_set([[maybe_unused]]size_t index,[[maybe_unused]]char_T a,[[maybe_unused]]ptr_t& p)override final{ nothing; }
	[[nodiscard]]virtual ptr_t do_pop_back([[maybe_unused]]size_t size,[[maybe_unused]]ptr_t& self)override final{ return this; }
	[[nodiscard]]virtual ptr_t do_pop_front([[maybe_unused]]size_t size,[[maybe_unused]]ptr_t& self)override final{ return this; }
};
template<typename char_T>
inline null_string_data_t<char_T> null_string_data{};
template<typename char_T>
base_string_data_t<char_T>* get_null_ptr(const base_string_data_t<char_T>*){ return&null_string_data<char_T>; }


//file_end

