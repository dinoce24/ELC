//zh_cn.hpp
/*
未完成的elc解释器_share文件
由steve02081504与Alex0125设计、编写
转载时请在不对此文件做任何修改的同时注明出处
项目地址：https://github.com/steve02081504/ELC
*/
/*
locale说明
elc使用的字符串.
调整这些,实现快速本地化.
*/
namespace elc::defs::locale::func{

}
namespace elc::defs::locale::str{
	inline namespace gc{
		inline constexpr auto gc_fail=es"gc失败"_constexpr_str;
		inline constexpr auto empty_gc_method=es"gc方法为空时gc被调用"_constexpr_str;
	}
	inline namespace code_convert{
		inline constexpr auto setlocale_error=es"setlocale出错"_constexpr_str;
		inline constexpr auto code_convert_error=es"编码转换出错"_constexpr_str;
	}
	inline namespace lib_load{
		inline constexpr auto null_lib=es"访问null处的lib对象"_constexpr_str;
	}
	inline namespace exception{
		inline constexpr auto unknow_error=es"未知错误"_constexpr_str;
		inline constexpr auto core_runtime_internal_helper_leak=es"未知错误"_constexpr_str;
	}
	inline namespace base_read{
		inline constexpr auto ending_of_expr_beyond_expectations=es"表达式的结尾超出预期"_constexpr_str;
		inline constexpr auto expr_incomplete=es"表达式未完成"_constexpr_str;
		inline constexpr auto symbol_is_undefined=es"此符号未定义"_constexpr_str;
		inline constexpr auto expr_too_outrageous=es"表达式过于离谱"_constexpr_str;
	}
	inline namespace package_symbol_loader{
		inline constexpr auto load_failed=es"无法加载的package_symbol_loader"_constexpr_str;
		inline constexpr auto load_interface_failed=es"package_symbol_loader缺失load_interface"_constexpr_str;
	}
}

//file_end

