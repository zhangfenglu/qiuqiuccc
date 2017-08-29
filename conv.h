#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
//UNICODE码转为GB2312码
int utf82gb2312(char *inbuf,int inlen,char *outbuf,int outlen);
//GB2312码转为UNICODE码
int gb23122utf8(char *inbuf,int inlen,char *outbuf,int outlen);
//UTF8码转为UCS2码
int utf82ucs2(char *inbuf,int inlen,char *outbuf,int outlen);
//UCS2码转为UTF8码
int ucs22utf8(char *inbuf,int inlen,char *outbuf,int outlen);

int gbk2utf8(char *inbuf, int inlen, char* outbuf, int outlen);
int utf82gbk(char *inbuf, int inlen, char* outbuf, int outlen);

std::string u2a(const char *inbuf);
std::string a2u(const char *inbuf);

int icuuc_init();
int icuuc_uninit();