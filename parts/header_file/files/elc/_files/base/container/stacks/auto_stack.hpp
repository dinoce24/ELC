//defs.hpp
//at namespace elc::defs::container::stack_n
/*
未完成的elc解释器base文件
由steve02081504与Alex0125设计、编写
转载时请在不对此文件做任何修改的同时注明出处
项目地址：https://github.com/steve02081504/ELC
*/
template<typename T>
struct auto_stack_t:base_stack_t<T>{//提头优化容器，可用于hashtable
private:
	typedef base_stack_t<T>base_t;
	typedef auto_stack_t<T>this_t;

	using base_t::data_t;
	using base_t::_m;
public:
	using base_t::base_t;
	auto_stack_t(const base_t&a)noexcept_as(base_t(a)):base_t(a){}
	auto_stack_t(base_t&&a)noexcept_as(base_t(a)):base_t(a){}

	this_t&operator=(this_t&&a)&noexcept{base_t::operator=(move(a));return*this;}
	template<typename U>
	[[nodiscard]]maybe_fail_reference<T>find(U&&a)noexcept_as(declvalue(T&)==a){
		data_t*tmp=_m,**tmp_=&_m;
		while(tmp!=null_ptr){
			if(tmp->_data==a){
				*tmp_=tmp->_next;
				tmp->_next=_m;//提头
				_m=tmp;
				return tmp->_data;
			}
			tmp_=&tmp->_next;
			tmp=*tmp_;
		}
		return note::fail;
	}
	[[nodiscard]]bool in_stack(const T&a)const noexcept_as(declvalue(this_t).find(a).not_fail()){
		return remove_const(this)->find(a).not_fail();
	}
	[[nodiscard]]bool not_in_stack(const T&a)const noexcept_as(declvalue(this_t).in_stack(a)){
		return not in_stack(a);
	}
};

//file_end

