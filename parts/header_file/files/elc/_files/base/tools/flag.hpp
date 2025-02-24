//flag.hpp
//at namespace elc::defs::base
/*
未完成的elc解释器base文件
由steve02081504与Alex0125设计、编写
转载时请在不对此文件做任何修改的同时注明出处
项目地址：https://github.com/steve02081504/ELC
*/
/*
表示flag是否被设置的enum字面量.
*/
enum flag_set_type:bool{seted=true,not_set=false};
/*
bool的简易包装以表示『是否被设置』,无法使用operator=,因为不应如此.
*/
class flag{
	bool _m;
public:
	constexpr explicit flag(flag_set_type a=not_set)noexcept:_m(bool(a)){}
	[[nodiscard]]explicit operator bool()const noexcept{return _m;}
	flag(flag&a)noexcept:_m((bool)a){}
	flag(flag&&a)noexcept:_m((bool)a){}
	inline void operator=(flag&)&noexcept=delete;
	inline void operator=(flag&&)&noexcept=delete;
	inline void set()noexcept{_m=true;}
	inline void unset()noexcept{_m=false;}
};

//file_end

