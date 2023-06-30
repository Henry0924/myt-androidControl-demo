// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 LIBMYTRPC_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// LIBMYTRPC_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifdef LIBMYTRPC_EXPORTS
#define LIBMYTRPC_API __declspec(dllexport)
#else
#define LIBMYTRPC_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C"{
#endif
/*
函数说明:远程连接设备
参数说明:
	ip : 需要远程控制的设备的IP地址
	port :需要远程控制的设备的端口
	timeout: 远程连接的超时时间单位是秒
返回值:返回一个长整形id，后面所有的操作函数都要用这个id 大于0表示成功失败返回0
*/
LIBMYTRPC_API long  WINAPI   openDevice(const char* ip,int port,long timeout);
/*
函数说明:关闭远程连接
参数说明:
	handle : openDevice返回的id
返回值:大于0表示成功失败返回0
*/
LIBMYTRPC_API int   WINAPI   closeDevice(long handle);
/*
函数说明:远程截图，获取的是RGBA像素数组
参数说明:
	handle : openDevice返回的id
	w:		指针类型返回图片的宽度
	h:		指针类型返回图片的高度
    stride  每一行的字节数
返回值:指针类型的像素数组（释放用freeRpcPtr）
*/
LIBMYTRPC_API BYTE* WINAPI   takeCaptrue(long handle,int* w,int* h,int* stride);
/*
函数说明:远程截图，获取的是压缩的png或者jpg类型的文件流
参数说明:
	handle : openDevice返回的id
	type:	 0表示获取png 1表示获取jpg
	quality: 表示压缩质量取值是0-100
	len:指针类型表示接受数据流的大小
返回值:指针类型的数据流（释放用freeRpcPtr）
*/
LIBMYTRPC_API BYTE* WINAPI	 takeCaptrueCompress(long handle,int type,int quality,int* len);
/*
函数说明:模拟按下
参数说明:
	handle : openDevice返回的id
	id:	 表示要按下的手指编号（0-9）
	x: 水平坐标
	y: 垂直坐标
*/
LIBMYTRPC_API int   WINAPI	 touchDown(long handle,int id,int x,int y);
/*
函数说明:模拟弹起
参数说明:
	handle : openDevice返回的id
	id:	 表示要弹起的手指编号（0-9）
	x: 水平坐标
	y: 垂直坐标
*/
LIBMYTRPC_API int   WINAPI	 touchUp(long handle,int id,int x,int y);
/*
函数说明:模拟滑动
参数说明:
	handle : openDevice返回的id
	id:	 表示要按下的手指编号（0-9）
	x: 水平坐标
	y: 垂直坐标
*/
LIBMYTRPC_API int   WINAPI	 touchMove(long handle,int id,int x,int y);
/*
函数说明:模拟单击
参数说明:
	handle : openDevice返回的id
	id:	 表示要单击的手指编号（0-9）
	x: 水平坐标
	y: 垂直坐标
*/
LIBMYTRPC_API int   WINAPI	 touchClick(long handle,int id,int x,int y);
/*
函数说明:模拟按键
参数说明:
	handle : openDevice返回的id
	code:	 表示按键码（自行查看KeyEvent.java的按键码）
*/
LIBMYTRPC_API int   WINAPI	 keyPress(long handle,int code);
/*
函数说明:模拟文字输入
参数说明:
	handle : openDevice返回的id
	text:	要输入的字符串 UTF8 格式
*/
LIBMYTRPC_API int   WINAPI	 sendText(long handle,const char* text);
/*
函数说明:打开指定包名的app
参数说明:
	handle : openDevice返回的id
	pkg:	包名
*/
LIBMYTRPC_API int   WINAPI	 openApp(long handle,const char* pkg);
/*
函数说明:关闭指定包名的app
参数说明:
	handle : openDevice返回的id
	pkg:	包名
*/
LIBMYTRPC_API int   WINAPI	 stopApp(long handle,const char* pkg);

/*
函数说明:返回当前屏幕的节点xml 数据
参数说明:
返回值:
 xml 文件
 使用完成后必须用 freeRpcPtr 释放
*/
//LIBMYTRPC_API char* WINAPI dumpNodeXml();

/*
函数说明:释放截图数据（截图数据必须用这个函数释放否则会造成内存泄露）
参数说明:
	handle : openDevice返回的id
	ptr:	指针类型
*/
LIBMYTRPC_API void  WINAPI   freeRpcPtr(void* ptr);

#ifdef __cplusplus
}
#endif