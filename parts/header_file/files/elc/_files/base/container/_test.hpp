//_test.hpp
//at namespace elc::defs::container
/*
未完成的elc解释器base文件
由steve02081504与Alex0125设计、编写
转载时请在不对此文件做任何修改的同时注明出处
项目地址：https://github.com/steve02081504/ELC
*/
inline void test(){
	ELC_TEST_EVENTNAME("container部分测试");
	array_n::test();
	function_n::test();
	stack_n::test();
}
inline void test_log_out(){
	array_n::test_log_out();
	function_n::test_log_out();
	stack_n::test_log_out();
}
inline void test_end(){
	array_n::test_end();
	function_n::test_end();
	stack_n::test_end();
}

//file_end

