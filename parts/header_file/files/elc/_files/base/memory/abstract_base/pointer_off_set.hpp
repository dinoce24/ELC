//pointer_off_set.hpp
//at namespace elc::defs::memory::abstract_base_n
/*
未完成的elc解释器base文件
由steve02081504与Alex0125设计、编写
转载时请在不对此文件做任何修改的同时注明出处
项目地址：https://github.com/steve02081504/ELC
*/
inline thread_local pointer base_ptr;
inline thread_local ptrdiff_t off_set;
distinctive inline void is_base_ptr(void*a)noexcept{base_ptr=a;}
distinctive inline void is_instance_ptr(void*a)noexcept{off_set=get_off_set(note::from(a),note::to(base_ptr));}
distinctive inline void*get_ptr_after_off_set(void*a)noexcept{return apply_off_set(a,off_set);}

//file_end

