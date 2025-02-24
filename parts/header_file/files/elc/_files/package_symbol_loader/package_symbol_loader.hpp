//package_symbol_loader.hpp
/*
未完成的elc解释器template文件
由steve02081504与Alex0125设计、编写
转载时请在不对此文件做任何修改的同时注明出处
项目地址：https://github.com/steve02081504/ELC
*/
namespace package_symbol_loader_n{
	struct package_symbol_loader_t{
		library_handle_t package_symbol_loader_handle;
		function_t<ptr(string lib_name, size_t lib_ver, string symbol_name)noexcept> load_interface;
		function_t<ptr()noexcept>													 load_error_interface;
		
		package_symbol_loader_t()noexcept{
			if(package_symbol_loader_handle = load_lib(paths::package_symbol_loader_path)) {
				load_interface		 = package_symbol_loader_handle->get_symbol_as_function<ptr(string lib_name,size_t lib_ver,string symbol_name)noexcept>(es"load_interface");
				load_error_interface = package_symbol_loader_handle->get_symbol_as_function<ptr()noexcept>(es"load_error_interface");
			}
			else
				die_with(locale::str::package_symbol_loader::load_failed);
			if(!load_interface)
				die_with(locale::str::package_symbol_loader::load_interface_failed);
		}
		~package_symbol_loader_t()noexcept = default;
		
		ptr load_symbol(string lib_name,size_t lib_ver,string symbol_name)noexcept{
			return load_interface(lib_name,lib_ver,symbol_name);
		}
		ptr get_load_error()noexcept{
			return load_error_interface();
		}
	};
}

//file_end
