#include <cstdlib>
#include <cstdio>
#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include <dlfcn.h>
//#include "libcnv.h"
/* use dl API include file */


/* typedef a function pointer to pointer ucnv_convert method */
/*
see the source code define
int32_t ucnv_convert(const char *toConverterName, const char *fromConverterName,
     char *target, int32_t targetSize,
     const char *source, int32_t sourceSize,
     int32_t * err)
*/
typedef int32_t (*TUCNVCONVERT)(const char *lpcOutEcd, const char *lpcInEcd,
  char* lpOutBuf, int32_t nOutBufLen,
  const char* lpcInStr, int32_t nInStrLen,
  int32_t *pnErrCode);

/* pointer libicuuc.so dl lib */
static void* g_lpdlIcuuc = 0;
/* ucnv_convert method pointer */
static TUCNVCONVERT g_lpfnUcnvConvert = 0;

//在libicuuc.so中找到函数ucnv_convert
int icuuc_init()
{
	g_lpfnUcnvConvert = 0;
	g_lpdlIcuuc = dlopen("/system/lib/libicuuc.so", RTLD_LAZY);
	if (g_lpdlIcuuc != 0)
	{
		int i, j;
		char szDLFnName[32]={0};
		i = 3;
		j = 8;
		//android1.5, ucnv_convert_3_8
		//android1.6, ucnv_convert_3_8
		//android2.1, ucnv_convert_3_8
		//android2.2, ucnv_convert_4_2
		//android2.3, ucnv_convert_44
		//android3.0, ucnv_convert_44
		//android3.1, ucnv_convert_44
		//android3.2, ucnv_convert_44
		//android4.0, ucnv_convert_46
		g_lpfnUcnvConvert = (TUCNVCONVERT)dlsym(g_lpdlIcuuc, "ucnv_convert_3_8");
	
		while (0 == g_lpfnUcnvConvert)
		{
			memset(szDLFnName, 0, 32*sizeof(char));
			sprintf(szDLFnName, "ucnv_convert_%d%d", i, j);
			g_lpfnUcnvConvert = (TUCNVCONVERT)dlsym(g_lpdlIcuuc, szDLFnName);
			if (g_lpfnUcnvConvert != 0){
				return 1;
			}

			sprintf(szDLFnName, "ucnv_convert_%d_%d", i, j);
			g_lpfnUcnvConvert = (TUCNVCONVERT)dlsym(g_lpdlIcuuc, szDLFnName);
			if (g_lpfnUcnvConvert != 0){
				return 1;
			}

			j++;
			if (j > 9){
				j = 1;
				i++;
				if (i > 5){
					break;
				}
			}
		}
	}
	return 0;
}

int icuuc_uninit()
{
	if (g_lpdlIcuuc != 0)
	{
		dlclose(g_lpdlIcuuc);
		g_lpdlIcuuc = 0;
	}
	return 1;
} 

//utf-8,gb2312,ucs4
//utf-8:  一个英文字母或者是数字占用一个字节，汉字占3个字节
//gb2312: 一个英文字母或者是数字占用一个字节，汉字占2个字节
int32_t gb23122utf8(char *instring, int32_t inlen, char *outbuf, int32_t buflen)
{
	int32_t iret;
	iret = 0;
	if (outbuf != 0 && instring != 0)
	{
		if (g_lpfnUcnvConvert != 0)
		{
			int32_t err_code = 0;
			iret = g_lpfnUcnvConvert("utf-8", "gb2312"
			  ,outbuf, buflen
			  ,instring, inlen
			  ,&err_code);
		}
	}
	return iret;
}

int32_t utf82gb2312(char *instring, int32_t inlen, char *outbuf, int32_t buflen)
{
	int32_t iret;
	iret = 0;
	if (outbuf != 0 && instring != 0)
	{
		if (g_lpfnUcnvConvert != 0)
		{
			int32_t err_code = 0;
			iret = g_lpfnUcnvConvert("gb2312", "utf-8"
			  ,outbuf, buflen
			  ,instring, inlen
			  ,&err_code);
		}
	}
	return iret;
}

int ucs22utf8(char *instring,int inlen,char *outbuf,int buflen)
{
	int32_t iret;
	iret = 0;
	if (outbuf != 0 && instring != 0)
	{
		if (g_lpfnUcnvConvert != 0)
		{
			int32_t err_code = 0;
			iret = g_lpfnUcnvConvert("utf-8", "ucs-2"
			  ,outbuf, buflen
			  ,(const char *)instring, inlen*sizeof(unsigned short)/sizeof(char)
			  ,&err_code);
		}
	}
	return iret;
}

int utf82ucs2(char *instring,int inlen,char *outbuf,int buflen)
{
	unsigned int iret;
	iret = 0;
	if (outbuf != 0 && instring != 0)
	{
		if (g_lpfnUcnvConvert != 0)
		{
			int32_t err_code = 0;
			iret = g_lpfnUcnvConvert("ucs-2", "utf-8"
			  ,(char *)outbuf, buflen*sizeof(unsigned short)/sizeof(char)
			  ,instring, inlen
			  ,&err_code);
		}
	}
	return iret;
}


unsigned int gbk2utf8(char *inbuf, unsigned int  inlen, char* outbuf, unsigned int  outlen)
{
	int32_t iret;
	iret = 0;
	if (outbuf != 0 && inbuf != 0)
	{
		if (g_lpfnUcnvConvert != 0)
		{
			int32_t err_code = 0;
			iret = g_lpfnUcnvConvert("gbk", "utf-8"
				,outbuf, inlen
				,(const char *)inbuf, inlen*sizeof(unsigned short)/sizeof(char)
				,&err_code);
		}
	}
	return iret;
}

unsigned int utf82gbk(char *inbuf, unsigned int  inlen, char* outbuf, unsigned int  outlen)
{
	int32_t iret;
	iret = 0;
	if (outbuf != 0 && inbuf != 0)
	{
		if (g_lpfnUcnvConvert != 0)
		{
			int32_t err_code = 0;
			iret = g_lpfnUcnvConvert("utf-8", "gbk"
				,outbuf, inlen
				,(const char *)inbuf, inlen*sizeof(unsigned short)/sizeof(char)
				,&err_code);
		}
	}
	return iret;
}


#else
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include "iconv.h"
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include <iconv.h>
#endif
#include <cstring>
#include "conv.h"
//代码转换//

int code_convert(const char *from_charset,const char *to_charset,const char *inbuf,size_t inlen,char *outbuf,size_t outlen)
{
	iconv_t cd;
	//int rc;
	const char *temp = inbuf;
    const char** pin = &temp;
	char **pout = &outbuf;
    memset(outbuf,0,outlen);
	cd = iconv_open(to_charset,from_charset);
	if (cd==0) return -1;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	if (iconv(cd,(const char**)pin,(size_t*)&inlen,pout,(size_t*)&outlen)==-1) return -1;
#else
    if (iconv(cd,(char**)pin,&inlen,pout,&outlen)==-1) return -1;
#endif
	iconv_close(cd);
	return 0;
}
/*UTF8转为GB2312*/
std::string u2a(const char *inbuf)
{     
	size_t inlen = strlen(inbuf);     
	char * outbuf = new char[inlen * 2 + 2];     
	std::string strRet;     
	if(code_convert("utf-8", "gb2312", inbuf, inlen, outbuf, inlen * 2 + 2) == 0)     
	{         
		strRet = outbuf;     
	}     
	delete [] outbuf;     
	return strRet; 
}       
/*GB2312转为UTF8*/
std::string a2u(const char *inbuf) 
{     
	size_t inlen = strlen(inbuf);     
	char * outbuf = new char[inlen * 2 + 2];     
	std::string strRet;     
	if(code_convert("gb2312", "utf-8", inbuf, inlen, outbuf, inlen * 2 + 2) == 0)     
	{         
		strRet = outbuf;     
	}     
	delete [] outbuf;     
	return strRet; 
}
//UNICODE码转为GB2312码
int utf82gb2312(const char *inbuf,int inlen,char *outbuf,int outlen)
{
	return code_convert("utf-8","gb2312",inbuf,(size_t)inlen,outbuf,(size_t)outlen);
}

//GB2312码转为UNICODE码
int gb23122utf8(char *inbuf,int inlen,char *outbuf,int outlen)
{
	return code_convert("gb2312","utf-8",inbuf,(size_t)inlen,outbuf,(size_t)outlen);
}

//UTF8码转为UCS2码
int utf82ucs2(char *inbuf,int inlen,char *outbuf,int outlen)
{
	return code_convert("utf-8","ucs-2",inbuf,(size_t)inlen,outbuf,(size_t)outlen);
}

//UCS2码转为UTF8码
int ucs22utf8(char *inbuf,int inlen,char *outbuf,int outlen)
{
	return code_convert("ucs-2","utf-8",inbuf,(size_t)inlen,outbuf,(size_t)outlen);
}

int gbk2utf8(char *inbuf, int inlen, char* outbuf, int outlen)
{
	return code_convert("gbk","utf-8",inbuf,(size_t)inlen,outbuf,(size_t)outlen);
}

int utf82gbk(char *inbuf, int inlen, char* outbuf, int outlen)
{
	return code_convert("utf-8","gbk",inbuf,(size_t)inlen,outbuf,(size_t)outlen);
}

#endif