//defs.hpp
//at namespace elc::defs
/*
未完成的elc解释器string文件
由steve02081504与Alex0125设计、编写
转载时请在不对此文件做任何修改的同时注明出处
项目地址：https://github.com/steve02081504/ELC
*/
namespace string_n{
	#include "string_data_t/_body.hpp"
	template<typename char_T>
	struct string_t{
		typedef base_string_data_t<char_T>			base_t_w;
		typedef base_t_w::ptr_t						ptr_t;
		typedef base_t_w::string_view_t				string_view_t;
		typedef array_end_by_zero_t<const char_T>	string_view_end_by_zero_t;
		typedef string_t<char_T>					this_t;
		static constexpr size_t						npos=size_t(-1);

	private:
		mutable ptr_t _m;

		string_t(ptr_t str):_m(str){}
		[[nodiscard]]ptr_t ptr_copy()const{ return _m; }
	public:
		void swap_with(this_t& a)noexcept{
			swap(_m,a._m);
		}

		string_t()noexcept=default;
		constexpr string_t(special_init_t,string_view_t str)noexcept:_m(get<constexpr_string_data_t<char_T>>(str,hash(str))){}
		string_t(string_view_t str)noexcept:_m(get<comn_string_data_t<char_T>>(str)){}
		string_t(string_view_end_by_zero_t str)noexcept:string_t((string_view_t)(str)){}
		string_t(const char_T* str)noexcept:string_t(string_view_end_by_zero_t(str)){}
		string_t(char_T ch)noexcept:string_t(string_view_t{&ch,1}){}
		string_t(const string_t& str)noexcept=default;
		string_t(string_t&& str)noexcept=default;

		string_t& operator=(const string_t& str)noexcept=default;
		string_t& operator=(string_t&& str)noexcept=default;
		string_t& operator=(null_ptr_t p)noexcept{clear();return*this;}
		string_t& operator=(nullptr_t p)noexcept{return*this=null_ptr;}


		[[nodiscard]]string_t operator+(const string_t& str)const&noexcept{
			return ptr_copy()->apply_str_to_end(str._m);
		}
		[[nodiscard]]string_t operator+(string_view_t str)const&noexcept{
			return ptr_copy()->apply_str_to_end(str);
		}
		[[nodiscard]]string_t operator+(const char_T* str)const&noexcept{
			return *this+string_view_end_by_zero_t(str);
		}
		friend [[nodiscard]]string_t operator+(string_view_t str1,const string_t& str2)noexcept{
			return str2.ptr_copy()->apply_str_to_begin(str1);
		}
		friend [[nodiscard]]string_t operator+(const char_T* str1,const string_t& str2)noexcept{
			return string_view_end_by_zero_t(str1)+str2;
		}
		friend [[nodiscard]]string_t operator+(char_T ch,const string_t& str)noexcept{
			return string_view_t{&ch,1}+str;
		}

		string_t& operator+=(string_t str)&noexcept{
			_m=_m->apply_str_to_end(str._m);
			return *this;
		}
		string_t& operator+=(string_view_t str)&noexcept{
			_m=_m->apply_str_to_end(str);
			return *this;
		}
		string_t& operator+=(const char_T* str)&noexcept{
			return *this+=string_view_end_by_zero_t(str);
		}
		string_t& operator+=(char_T ch)&noexcept{
			return *this += string_view_t{&ch,1};
		}
		template<typename U>
		[[nodiscard]]string_t&& operator+(U&& b)&&noexcept_as(*this+=b) requires was_not_an_ill_form(*this+=b){		  //对右值的operator+优化为operator+=
			*this+=b;
			return move(*this);
		}

		float_size_t memory_cost()const noexcept{return _m->get_memory_cost();}
	private:
		void equivalent_optimization(const string_t& a)const noexcept{
			if(this->memory_cost() >= a.memory_cost())
				_m.do_replace(a._m);
			else
				a._m.do_replace(_m);
		}
	public:
		[[nodiscard]]constexpr auto operator<=>(const string_t& a)const noexcept(compare.nothrow<char_T>){
			auto ssize = size();
			auto scom = compare(ssize,a.size());//先比较大小，若需要再调用data
			if(!scom){//大小相等
				auto aret = compare(data(),a.data(),ssize);
				if(!aret)//相等
					equivalent_optimization(a);
				return aret;
			}
			return scom;
		}
		[[nodiscard]]constexpr auto operator==(const string_t& a)const noexcept(equal.nothrow<char_T>){
			auto ssize = size();
			const auto seq = equal(ssize,a.size());//先比较大小，若需要再调用data
			if(seq){
				const auto aret = equal(data(),a.data(),ssize);
				if(aret)
					equivalent_optimization(a);
				return aret;
			}
			return seq;
		}
		[[nodiscard]]constexpr auto operator<=>(string_view_t a)const noexcept(compare.nothrow<char_T>){
			return compare(data(),size(),a.begin(),a.size());
		}
		[[nodiscard]]constexpr auto operator==(string_view_t a)const noexcept(equal.nothrow<char_T>){
			return equal(data(),size(),a.begin(),a.size());
		}
		[[nodiscard]]constexpr auto operator<=>(const char_T* a)const noexcept(compare.nothrow<char_T>){
			return compare(data(),size(),a,end_by_zero);
		}
		[[nodiscard]]constexpr auto operator==(const char_T* a)const noexcept(equal.nothrow<char_T>){
			return equal(data(),size(),a,end_by_zero);
		}

	private:
		char_T* unique_c_str(){ return _m->get_unique_c_str(_m); }
		char_T	arec(size_t index)noexcept{ return _m->arec(index); }
		void	arec_set(size_t index,char_T a)noexcept{ return _m->arec_set(index,a,_m); }

	public:
		class arec_t: non_copyable,non_moveable{
			string_t* _to;
			size_t	  _index;

			friend class string_t;
		public:
			arec_t(string_t* to,size_t index)noexcept:_to(to),_index(index){}
			arec_t(special_init_t,const arec_t&ref)noexcept:_to(ref._to),_index(ref._index){}
			[[nodiscard]]operator char_T()const noexcept{ return _to->arec(_index); }
			arec_t&		 operator=(char_T a)noexcept{
				_to->arec_set(_index,a);
				return *this;
			}
			[[nodiscard]]char_T*		operator&()noexcept{ return _to->unique_c_str()+_index; }
			[[nodiscard]]const char_T*	operator&()const noexcept{ return (add_const(_to))->c_str()+_index; }
			[[nodiscard]]explicit operator char_T&()noexcept{ return *operator&(); }
			[[nodiscard]]explicit operator const char_T&()const noexcept{ return *operator&(); }
		};

		[[nodiscard]]arec_t		  operator[](size_t index){ return{this,index}; }
		[[nodiscard]]const arec_t operator[](size_t index)const{ return{remove_const(this),index}; }

		[[nodiscard]]string_t substr(size_t begin,size_t size=npos)const{
			size=min(size,this->size()-begin);
			if(size)
				return _m->get_substr_data(begin,size);
			else
				return {};
		}
		[[nodiscard]]const char_T*	data()const noexcept{ return _m->get_data(_m); }
		[[nodiscard]]char_T*		c_str()noexcept{ return this->unique_c_str(); }
		[[nodiscard]]const char_T*	const_c_str()const noexcept{ return _m->get_const_c_str(_m); }
		[[nodiscard]]const char_T*	c_str()const noexcept{ return const_c_str(); }
		[[nodiscard]]size_t			size()const noexcept{ return _m->get_size(); }
		void resize(size_t nsize,char_T ch ={}){
			auto size=this->size();
			if(size > nsize)
				*this=substr(0,nsize);
			elseif(size == nsize)
				return;
			else
				_m=get<end_apply_string_data_t<char_T>>(_m,nsize-size,ch);
		}
		void clear()noexcept{ _m=null_ptr; }
	private:
		struct iterator_base_t{
			string_t* _to;
			ptrdiff_t _index;		//rend: -1，使用size_t也不是不可以（标准允许无符号整数溢出），但是operator<=>会出问题

			[[nodiscard]]constexpr iterator_base_t	get_before()const noexcept{ return{_to,_index-1}; }
			[[nodiscard]]constexpr iterator_base_t	get_next()const noexcept{ return{_to,_index+1}; }
			[[nodiscard]]arec_t						get_value()noexcept{ return (*_to)[_index]; }
			[[nodiscard]]const arec_t				get_value()const noexcept{ return (*add_const(_to))[_index]; }
			[[nodiscard]]char_T*					get_handle()noexcept{ return &get_value(); }
			[[nodiscard]]const char_T*				get_handle()const noexcept{ return &get_value(); }
			constexpr bool operator==(const iterator_base_t& a)const noexcept{ return _to==a._to && _index==a._index; }
			constexpr auto operator<=>(const iterator_base_t& a)const noexcept{ return _to==a._to ? _index<=>a._index : NAN<=>NAN; }
		};
		[[nodiscard]]iterator_base_t get_iterator_data_at(ptrdiff_t index)const{ return iterator_base_t{(string_t*)this,index}; }
	public:
		typedef iterator_t<char_T,iterator_base_t>				iterator;
		typedef const_iterator_t<char_T,const iterator_base_t>	const_iterator;

		[[nodiscard]]iterator		get_iterator_at(ptrdiff_t index){ return get_iterator_data_at(index); }
		[[nodiscard]]const_iterator get_iterator_at(ptrdiff_t index)const{ return get_iterator_data_at(index); }
		[[nodiscard]]iterator		begin(){ return get_iterator_at(0); }
		[[nodiscard]]const_iterator begin()const{ return get_iterator_at(0); }
		[[nodiscard]]const_iterator cbegin()const{ return begin(); }
		[[nodiscard]]iterator		end(){ return get_iterator_at(size()); }
		[[nodiscard]]const_iterator end()const{ return get_iterator_at(size()); }
		[[nodiscard]]const_iterator cend()const{ return end(); }

		typedef reverse_iterator_t<char_T,iterator_base_t>				reverse_iterator;
		typedef reverse_const_iterator_t<char_T,const iterator_base_t>	reverse_const_iterator;

		[[nodiscard]]reverse_iterator		get_reverse_iterator_at(ptrdiff_t index){ return get_iterator_data_at(index); }
		[[nodiscard]]reverse_const_iterator get_reverse_iterator_at(ptrdiff_t index)const{ return get_iterator_data_at(index); }
		[[nodiscard]]reverse_iterator		rbegin(){ return get_reverse_iterator_at(size()-1); }
		[[nodiscard]]reverse_const_iterator rbegin()const{ return get_reverse_iterator_at(size()-1); }
		[[nodiscard]]reverse_const_iterator rcbegin()const{ return rbegin(); }
		[[nodiscard]]reverse_iterator		rend(){ return get_reverse_iterator_at(-1); }
		[[nodiscard]]reverse_const_iterator rend()const{ return get_reverse_iterator_at(-1); }
		[[nodiscard]]reverse_const_iterator rcend()const{ return rend(); }

		//

		void push_back(const string_t& str){ _m=_m->apply_str_to_end(str._m); }
		void push_back(string_view_t str){ _m=_m->apply_str_to_end(str); }
		void push_back(char_T ch){ push_back(string_view_t{&ch,1}); }
		void push_back(const char_T* str){ push_back(string_view_end_by_zero_t(str)); }

		void push_front(const string_t& str){ _m=_m->apply_str_to_begin(str._m); }
		void push_front(string_view_t str){ _m=_m->apply_str_to_begin(str); }
		void push_front(char_T ch){ push_front(string_view_t{&ch,1}); }
		void push_front(const char_T* str){ push_front(string_view_end_by_zero_t(str)); }

		string_t pop_back(size_t size){ return _m->do_pop_back(size,_m); }
		string_t pop_front(size_t size){ return _m->do_pop_front(size,_m); }
		char_T pop_back(){ return pop_back(1)[0]; }
		char_T pop_front(){ return pop_front(1)[0]; }

		//

		operator string_view_t()const&noexcept{ return string_view_t{data(),size()}; }
		auto to_string_view_t()const&noexcept{ return operator string_view_t(); }
		[[nodiscard]]explicit operator hash_t()const noexcept{return hash(to_string_view_t());}
		/*
		TODO:

		find_first_of
		find_first_not_of
		find_last_of
		find_last_not_of
		*/

		[[nodiscard]]size_t find(const char_T ch)const{
			auto result = in_range(ch, to_string_view_t());
			if(result)
				return result - data();
			else
				return npos;
		}
		[[nodiscard]]size_t reverse_find(const char_T ch)const{
			auto result = in_range_but_reverse(ch, to_string_view_t());
			if(result)
				return result - data();
			else
				return npos;
		}
		[[nodiscard]]size_t find(string_view_t str) const {
			auto result = in_range(str, to_string_view_t());
			if(result)
				return result - data();
			else
				return npos;
		}
		[[nodiscard]]size_t reverse_find(string_view_t str) const {
			auto result = in_range_but_reverse(str, to_string_view_t());
			if(result)
				return result - data();
			else
				return npos;
		}
		/*
		[[nodiscard]]string_t operator[](size_t index,char_T delimiter)const{
			auto pos=find(delimiter);
			auto end=find(delimiter,pos);
			while(index--){
				pos=end;
				end=find(delimiter,pos);
			}
			return substr(pos,end-pos);
		}
		[[nodiscard]]string_t operator[](size_t index,string_view_t delimiter_str)const{
			auto pos=find(delimiter_str);
			auto end=find(delimiter_str,pos);
			while(index--){
				pos=end;
				end=find(delimiter_str,pos);
			}
			return substr(pos,end-pos);
		}
		*/

		void erase(size_t pos,size_t size=1)&{
			_m=_m->do_erase(pos,size);
		}
		void insert(size_t pos,string_t str)&{
			_m=_m->do_insert(pos,str);
		}
		void insert(size_t pos,string_view_t str)&{
			_m=_m->do_insert(pos,str);
		}
		void insert(size_t pos,const char_T* str)&{
			insert(pos,string_view_end_by_zero_t(str));
		}
		void insert(size_t pos,char_T ch)&{
			insert(pos,string_view_t{&ch,1});
		}
		/*
		compare
		starts_with
		ends_with
		contains
		replace
		*/
	};
	template<typename T>
	inline void swap(string_t<T>& a,string_t<T>& b)noexcept{ a.swap_with(b); }

	//std ostream
	template<typename some_fucking_std_ostream, typename T>
	decltype(auto) operator<<(some_fucking_std_ostream& stream, const string_t<T>& str) {
		typedef some_fucking_std_ostream stream_t;
		typedef stream_t::traits_type	 traits_t;
		typename stream_t::iostate		 state = stream_t::goodbit;

		#if defined(_MSC_VER)
			#pragma warning(push)
			#pragma warning(disable:26494)//未初始化警告diss
		#endif
		size_t pad;
		#if defined(_MSC_VER)
			#pragma warning(pop)
		#endif
		size_t size = str.size();
		if(stream.width() <= 0 || static_cast<size_t>(stream.width()) <= size)
			pad = 0;
		else
			pad = static_cast<size_t>(stream.width()) - size;

		const typename stream_t::sentry isok(stream);

		if(!isok)
			state |= stream_t::badbit;
		else {
			try {
				if((stream.flags() & stream_t::adjustfield) != stream_t::left) {
					for(; 0 < pad; --pad) {		  // pad on left
						if(traits_t::eq_int_type(traits_t::eof(), stream.rdbuf()->sputc(stream.fill()))) {
							state |= stream_t::badbit;		 // insertion failed, quit
							break;
						}
					}
				}

				if(state == stream_t::goodbit && stream.rdbuf()->sputn(str.c_str(), static_cast<::std::streamsize>(size)) != static_cast<::std::streamsize>(size))
					state |= stream_t::badbit;
				else {
					for(; 0 < pad; --pad) {		  // pad on right
						if(traits_t::eq_int_type(traits_t::eof(), stream.rdbuf()->sputc(stream.fill()))) {
							state |= stream_t::badbit;		 // insertion failed, quit
							break;
						}
					}
				}

				stream.width(0);
			}
			catch(...) {
				stream.setstate(stream_t::badbit, true);
				return stream;
			}
		}
		stream.setstate(state);
		return stream;
	}

	template<class T>
	[[nodiscard]]inline auto size_of_array_like(const string_t<T>& a)noexcept{ return a.size(); }
	template<class T>
	[[nodiscard]]inline auto begin_of_array_like(string_t<T>& a)noexcept{ return(T*)a.c_str(); }
	template<class T>
	[[nodiscard]]inline auto begin_of_array_like(const string_t<remove_cv<T>>& a)noexcept{ return(const T*)a.c_str(); }

	typedef string_t<char_t>string;

	template<typename T>
	using string_view_t=string_t<T>::string_view_t;

	typedef string_view_t<char_t>string_view;
}
using string_n::string_t;
using string_n::string;
using string_n::string_view_t;
using string_n::string_view;

//file_end

