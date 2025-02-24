//common_node.hpp
//at namespace elc::defs::core
/*
未完成的elc解释器core文件
由steve02081504与Alex0125设计、编写
转载时请在不对此文件做任何修改的同时注明出处
项目地址：https://github.com/steve02081504/ELC
*/
inline value car_of(ptr p){
	return (*p)[t];
}
inline value cdr_of(ptr p){
	return (*p)[nil];
}
inline value car_of(auto&&node){
	return car_of(as_ptr(node));
}
inline value cdr_of(auto&&node){
	return cdr_of(as_ptr(node));
}

struct cons:node_like,instance_struct<cons>{
	typedef cons this_t;

	value _car;
	value _cdr;

	cons(ptr car,ptr cdr){
		_car = car;
		_cdr = cdr;
	}

	[[nodiscard]]virtual base_type_info_t get_type_info()const noexcept override{return type_info<cons>;}
protected:
	[[nodiscard]]virtual logical_bool equal_with(const_ptr a)const noexcept override{
		if(a->get_type_info() != this->get_type_info())
			return false;
		const this_t*p=down_cast<const this_t*>(a.get());
		return _car==p->_car&&_cdr==p->_cdr;
	}
public:
	[[nodiscard]]virtual value arec(const value index)override{
		const_ptr v=index;
		if(v==&nil)
			return _cdr;
		elseif(v==&t)
			return _car;
		else{
			ptr to=get<common_node>();
			_car >> car_of(to);
			_cdr >> cdr_of(to);
			be_replace_as(to);
			return (*to)[v];
		}
	}

	virtual void clear()noexcept override{as_value(&the_void)>>_car>>_cdr;}
};

[[nodiscard]]inline ptr make_list()noexcept{return &nil;}
template<typename T,typename...Args>
[[nodiscard]]inline ptr make_list(T&&first,Args&&...rest){
	ELC_TEST_EVENTNAME("make_list调用");
	return get<cons>(as_ptr(first),make_list(forward<Args>(rest)...));
}

//file_end

