#include "HttpGetImg.h"
#include "SimpleTools.h"

HttpGetImg::HttpGetImg()
{
}


HttpGetImg::~HttpGetImg()
{
}

HttpGetImg * HttpGetImg::getInstance()
{
	static HttpGetImg getImg;

	return &getImg;
}

void HttpGetImg::GetHttpImg(string imgurl, function<void(Texture2D * texture)>func)
{
	string url = imgurl;

	CCLOG("GetHttpImg:%s", url.c_str());

	requestFroGet(url, [=](HttpClient *sender, HttpResponse *response)
	{
		if (response == nullptr || !response->isSucceed())
		{
			CCLOG("responese is null");
			CCLOG("responese not succeed");

			return;
		}

		vector<char> *buffer = response->getResponseData();

		//create image
		Image* img = new Image;
		bool b = img->initWithImageData((unsigned char*)buffer->data(), buffer->size());

		Texture2D * texture = nullptr;
		if (b)
		{
			texture = Director::getInstance()->getTextureCache()->addImage(img, imgurl);
		}
		else
		{
			texture = Director::getInstance()->getTextureCache()->addImage("ActiveLayer/neirong.png");
		}

		img->release();

		if (func && texture) func(texture);

	}, "GetHttpImg");
}

