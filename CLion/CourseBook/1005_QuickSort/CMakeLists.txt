# 包含公共库
#include_directories(${CMAKE_SOURCE_DIR}/Status)

# 生成可执行文件
add_executable(QuickSort  C10-1.H		C9.H	algo10-5.c	bo10-2.c	c1.h)
# 链接公共库
#target_link_libraries(GarbageCollection Scanf_lib)

## 记录要拷贝到*.exe目录下的资源文件
#file(GLOB TestData TestData*.txt)
## 将资源文件拷贝到*.exe目录下，不然无法加载
#file(COPY ${TestData} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
