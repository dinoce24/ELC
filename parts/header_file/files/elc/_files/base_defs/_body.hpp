//_body.hpp
//at namespace ::
/*
未完成的elc解释器base_defs文件
由steve02081504与Alex0125设计、编写
转载时请在不对此文件做任何修改的同时注明出处
项目地址：https://github.com/steve02081504/ELC
*/
//include default_data_type：基础数据类型定义
#include "../../../../../_share/default_data_type.hpp"
namespace elc::defs{ //在elc::defs中定义内容
	#include "../_share/_defs.hpp"

	namespace base{}
	using namespace base;//导出内容：defs内的名称空间只起到大体名称分组的作用，不进行名称阻拦

	//内存泄露检测
	#if defined(ELC_TEST_ON)||defined(ELC_TEST_CHECK_MEMORY_LACK)
	namespace memory{
		inline void check_memory_lack()noexcept;
		inline struct distinctive memory_lack_checker_t{
			~memory_lack_checker_t(){
				check_memory_lack();
			}
		}memory_lack_checker{};
	}
	#endif

	namespace base{
		#include "base_defs/_body.hpp"
	}

	#include "../_share/_undefs.hpp"
}

//file_end

