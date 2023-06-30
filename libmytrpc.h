// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� LIBMYTRPC_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// LIBMYTRPC_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef LIBMYTRPC_EXPORTS
#define LIBMYTRPC_API __declspec(dllexport)
#else
#define LIBMYTRPC_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C"{
#endif
/*
����˵��:Զ�������豸
����˵��:
	ip : ��ҪԶ�̿��Ƶ��豸��IP��ַ
	port :��ҪԶ�̿��Ƶ��豸�Ķ˿�
	timeout: Զ�����ӵĳ�ʱʱ�䵥λ����
����ֵ:����һ��������id���������еĲ���������Ҫ�����id ����0��ʾ�ɹ�ʧ�ܷ���0
*/
LIBMYTRPC_API long  WINAPI   openDevice(const char* ip,int port,long timeout);
/*
����˵��:�ر�Զ������
����˵��:
	handle : openDevice���ص�id
����ֵ:����0��ʾ�ɹ�ʧ�ܷ���0
*/
LIBMYTRPC_API int   WINAPI   closeDevice(long handle);
/*
����˵��:Զ�̽�ͼ����ȡ����RGBA��������
����˵��:
	handle : openDevice���ص�id
	w:		ָ�����ͷ���ͼƬ�Ŀ��
	h:		ָ�����ͷ���ͼƬ�ĸ߶�
    stride  ÿһ�е��ֽ���
����ֵ:ָ�����͵��������飨�ͷ���freeRpcPtr��
*/
LIBMYTRPC_API BYTE* WINAPI   takeCaptrue(long handle,int* w,int* h,int* stride);
/*
����˵��:Զ�̽�ͼ����ȡ����ѹ����png����jpg���͵��ļ���
����˵��:
	handle : openDevice���ص�id
	type:	 0��ʾ��ȡpng 1��ʾ��ȡjpg
	quality: ��ʾѹ������ȡֵ��0-100
	len:ָ�����ͱ�ʾ�����������Ĵ�С
����ֵ:ָ�����͵����������ͷ���freeRpcPtr��
*/
LIBMYTRPC_API BYTE* WINAPI	 takeCaptrueCompress(long handle,int type,int quality,int* len);
/*
����˵��:ģ�ⰴ��
����˵��:
	handle : openDevice���ص�id
	id:	 ��ʾҪ���µ���ָ��ţ�0-9��
	x: ˮƽ����
	y: ��ֱ����
*/
LIBMYTRPC_API int   WINAPI	 touchDown(long handle,int id,int x,int y);
/*
����˵��:ģ�ⵯ��
����˵��:
	handle : openDevice���ص�id
	id:	 ��ʾҪ�������ָ��ţ�0-9��
	x: ˮƽ����
	y: ��ֱ����
*/
LIBMYTRPC_API int   WINAPI	 touchUp(long handle,int id,int x,int y);
/*
����˵��:ģ�⻬��
����˵��:
	handle : openDevice���ص�id
	id:	 ��ʾҪ���µ���ָ��ţ�0-9��
	x: ˮƽ����
	y: ��ֱ����
*/
LIBMYTRPC_API int   WINAPI	 touchMove(long handle,int id,int x,int y);
/*
����˵��:ģ�ⵥ��
����˵��:
	handle : openDevice���ص�id
	id:	 ��ʾҪ��������ָ��ţ�0-9��
	x: ˮƽ����
	y: ��ֱ����
*/
LIBMYTRPC_API int   WINAPI	 touchClick(long handle,int id,int x,int y);
/*
����˵��:ģ�ⰴ��
����˵��:
	handle : openDevice���ص�id
	code:	 ��ʾ�����루���в鿴KeyEvent.java�İ����룩
*/
LIBMYTRPC_API int   WINAPI	 keyPress(long handle,int code);
/*
����˵��:ģ����������
����˵��:
	handle : openDevice���ص�id
	text:	Ҫ������ַ��� UTF8 ��ʽ
*/
LIBMYTRPC_API int   WINAPI	 sendText(long handle,const char* text);
/*
����˵��:��ָ��������app
����˵��:
	handle : openDevice���ص�id
	pkg:	����
*/
LIBMYTRPC_API int   WINAPI	 openApp(long handle,const char* pkg);
/*
����˵��:�ر�ָ��������app
����˵��:
	handle : openDevice���ص�id
	pkg:	����
*/
LIBMYTRPC_API int   WINAPI	 stopApp(long handle,const char* pkg);

/*
����˵��:���ص�ǰ��Ļ�Ľڵ�xml ����
����˵��:
����ֵ:
 xml �ļ�
 ʹ����ɺ������ freeRpcPtr �ͷ�
*/
//LIBMYTRPC_API char* WINAPI dumpNodeXml();

/*
����˵��:�ͷŽ�ͼ���ݣ���ͼ���ݱ�������������ͷŷ��������ڴ�й¶��
����˵��:
	handle : openDevice���ص�id
	ptr:	ָ������
*/
LIBMYTRPC_API void  WINAPI   freeRpcPtr(void* ptr);

#ifdef __cplusplus
}
#endif