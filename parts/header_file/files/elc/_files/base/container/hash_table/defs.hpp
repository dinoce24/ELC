//defs.hpp
//at namespace elc::defs::container
/*
未完成的elc解释器base文件
由steve02081504与Alex0125设计、编写
转载时请在不对此文件做任何修改的同时注明出处
项目地址：https://github.com/steve02081504/ELC
*/
namespace hash_table_n{
	template<typename T,template<typename>class stack_t=auto_stack_t,size_t bucket_max_size=256>
	class hash_table_t{
		typedef hash_table_t<T,stack_t,bucket_max_size>this_t;
		typedef stack_t<T>bucket_t;
	public:
		typedef array_t<bucket_t>base_t_w;
	private:
		base_t_w _m;
	public:
		void swap(base_t_w&a)noexcept{_m.swap_with(a);}
	private:
		[[nodiscard]]bucket_t&find_bucket(hash_t a)noexcept{
			return _m[a%_m.size()];
		}
		void bucket_count_grow()noexcept{
			this_t tmp(special_init,get_next_gold_size_to_resize_for_hash(_m.size()));
			for(bucket_t&a:_m){
				while(!a.empty())
					a.move_top_to(tmp.find_bucket(a.get_top_hash()));
			}
			swap(tmp);
		}
		hash_table_t(const base_t_w&a)noexcept:_m(a){}
		this_t copy()noexcept(copy_construct.nothrow<base_t_w>){
			return{_m};
		}
	public:
		hash_table_t()noexcept:_m(5){}
		hash_table_t(special_init_t,size_t bucket_size)noexcept:_m(bucket_size){}
		~hash_table_t()noexcept(destruct.nothrow<base_t_w>)=default;

		operator base_t_w&()noexcept{return _m;}
		operator const base_t_w&()const noexcept{return _m;}

		hash_table_t(const this_t&a)noexcept:_m(a._m){}
		hash_table_t(this_t&&a)noexcept:_m(a._m){}

		this_t&operator=(base_t_w&&a)&noexcept{
			swap(_m,a);
			return*this;
		}
		this_t&operator=(const base_t_w&a)&noexcept{
			_m=a;
			return*this;
		}

		template<typename U>
		static constexpr bool hash_nothrow=noexcept(hash(declvalue(U)));
		template<typename U>
		static constexpr bool find_nothrow=hash_nothrow<U>&&noexcept(declvalue(bucket_t).find(declvalue(U)));

		void add(const T&a)noexcept(hash_nothrow<const T&>&&bucket_t::add_nothrow){
			auto&bucket=find_bucket(hash(a));
			bucket.add(a);
			if(bucket.size() > bucket_max_size)
				bucket_count_grow();
		}
		bool remove(const T&a)noexcept(bucket_t::remove_nothrow){
			auto&bucket=find_bucket(hash(a));
			bool remove_success=bucket.remove(a);
			if constexpr(is_unstable_hash<T>)
				if(not remove_success){
					for(auto&i:_m){
						if(is_eq(i,bucket))
							continue;
						remove_success=i.remove(a);
						if(remove_success)
							break;
					}
				}
			return remove_success;
		}
		template<typename U>
		[[nodiscard]]maybe_fail_reference<T>find(U&&a)noexcept(find_nothrow<U>){
			auto&bucket=find_bucket(hash(a));
			#if defined(_MSC_VER)
				#pragma warning(push)
				#pragma warning(disable:26496)//?
			#endif
			auto reference=bucket.find(a);
			#if defined(_MSC_VER)
				#pragma warning(pop)
			#endif
			if constexpr(is_unstable_hash<T>)
				if(reference.fail()){
					for(auto&i:_m){
						if(is_eq(i,bucket))
							continue;
						re_construct[&reference](i.find(a));
						if(reference.not_fail())
							break;
					}
				}
			return reference;
		}
		[[nodiscard]]bool in_table(const T&a)noexcept_as(declvalue(this_t).find(a).not_fail()){
			return find(a).not_fail();
		}
		[[nodiscard]]bool not_in_table(const T&a)noexcept_as(declvalue(this_t).in_table(a)){
			return not in_table(a);
		}

		size_t size()noexcept{
			size_t aret=0;
			for(const bucket_t&a:_m){
				aret+=a.size();
			}
			return aret;
		}

		void clear()noexcept(re_construct.nothrow<this_t>){
			re_construct(this);
		}

		#define expr declvalue(func_t)(declvalue(T&))
		template<typename func_t> requires was_not_an_ill_form(expr)
		void for_each(func_t&&func)noexcept_as(expr){
			for(bucket_t&a:_m){
				a.for_each(func);
			}
		}
		#undef expr

		#define expr declvalue(func_t)(declvalue(const T&))
		template<typename func_t> requires was_not_an_ill_form(expr)
		void for_each(func_t&&func)const noexcept_as(expr){
			for(bucket_t&a:_m){
				a.for_each(func);
			}
		}
		#undef expr

		#define expr declvalue(func_t)(declvalue(bucket_t&))
		template<typename func_t> requires was_not_an_ill_form(expr)
		void for_each_bucket(func_t&&func)noexcept_as(expr){
			_m.for_each(func);
		}
		#undef expr

		#define expr declvalue(func_t)(declvalue(const bucket_t&))
		template<typename func_t> requires was_not_an_ill_form(expr)
		void for_each_bucket(func_t&&func)const noexcept_as(expr){
			_m.for_each(func);
		}
		#undef expr
	};
	template<typename T,template<typename>class stack_t,size_t _,size_t __>
	inline void swap(hash_table_t<T,stack_t,_>&a,hash_table_t<T,stack_t,__>&b)noexcept{a.swap(b);}
	template<typename T,template<typename>class stack_t,size_t _>
	inline void swap(hash_table_t<T,stack_t,_>&a,typename hash_table_t<T,stack_t,_>::base_t_w&b)noexcept{a.swap(b);}
	template<typename T,template<typename>class stack_t,size_t _>
	inline void swap(typename hash_table_t<T,stack_t,_>::base_t_w&b,hash_table_t<T,stack_t,_>&a)noexcept{a.swap(b);}
}

//file_end

