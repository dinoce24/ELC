//literal.hpp
//at namespace elc::defs
/*
未完成的elc解释器string文件
由steve02081504与Alex0125设计、编写
转载时请在不对此文件做任何修改的同时注明出处
项目地址：https://github.com/steve02081504/ELC
*/
inline string operator ""_elc_string(const char_t*a,size_t N)noexcept{
	return{a,note::size(N)};
}

[[deprecated("run time string code convert and class string<char> instantiation")]]
inline string operator ""_elc_string(const char*a,size_t N)noexcept{
	return ::elc::APIs::str_code_convert::to_char_t_str({a,note::size(N)});
}

//file_end

