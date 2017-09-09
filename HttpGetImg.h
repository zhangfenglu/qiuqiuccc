#ifndef __HttpGetImg__
#define __HttpGetImg__

#include "cocos2d.h"
#include "network/HttpClient.h"

using namespace std;
using namespace cocos2d;
using namespace network;


class HttpGetImg
{
public:
	HttpGetImg();
	virtual ~HttpGetImg();

	static HttpGetImg * getInstance();

	//获取网络图片，需要地址
	static void GetHttpImg(string imgurl, function<void(Texture2D * texture)>func = nullptr);

private:

};

#endif /* HttpGetImg */