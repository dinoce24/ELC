//_test.hpp
//at namespace elc::defs::memory::ptr_n
/*
未完成的elc解释器base文件
由steve02081504与Alex0125设计、编写
转载时请在不对此文件做任何修改的同时注明出处
项目地址：https://github.com/steve02081504/ELC
*/
namespace ptr_n{
	struct tester:type_info_t<tester>::template_name
		with_common_attribute<ref_able,weak_ref_able,never_in_array>,build_by_get_only{};
	void waiting_for_destroy(tester*)noexcept{}
	inline void test(){
		ELC_TEST_EVENTNAME("ptr部分测试");
		{
			comn_ptr_t a=get<tester>();
			weak_ptr_t b=a;
		}
		check_memory_lack();
	}
	inline void test_log_out(){
	}
	inline void test_end(){
	}
}

//file_end

