//ref_able.hpp
//at namespace elc::defs::memory::ptr_n
/*
未完成的elc解释器base文件
由steve02081504与Alex0125设计、编写
转载时请在不对此文件做任何修改的同时注明出处
项目地址：https://github.com/steve02081504/ELC
*/
template<typename T>
struct ref_able:ref_t,can_t_use_default_null_ptr,is_common_attribute(ref_able){
private:
	typedef ref_t base_t;
public:
	using base_t::base_t;
	inline void cut_ref()const noexcept{
		T*this_T=remove_const(get_handle(this));
		if(base_t::cut_ref())
			if constexpr(was_weak_ref_able<T>)
				if(get_weak_ref_num(this_T)!=0)
					waiting_for_destroy(this_T);
				else
					destroy_and_free(this_T);
			else
				destroy_and_free(this_T);
	}
};

//file_end

