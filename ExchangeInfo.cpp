#include "ExchangeInfo.h"

std::string ExchangeInfo::getIdentifier()
{
	int end = 10000;
	int start = 1;
	int  num = (CCRANDOM_0_1()*(end - start + 1) + start);
	log("num==================================%d" + num);
	String* ns = String::createWithFormat("%d", num);
	//return ns->getCString();
	return "1116";
	//user: 1351258
	//return "66666666-6666-6666-6666-666666666666";
}

void ExchangeInfo::CreateQRFImage(const char* str, const char* headIcon, float mSize)
{
	
}

std::map<int, std::string> ExchangeInfo::getProvinces()
{
	return std::map<int, std::string>();
}


void ExchangeInfo::OpenScan()
{
}

int ExchangeInfo::getLocationProvince()
{
	return 1001;
}


void ExchangeInfo::SaomaAddFriend(const char* str)
{

}

void ExchangeInfo::AddPhoto(int idex)
{

}

void ExchangeInfo::UpLoadPhoto(const char* str, int index)
{

}

cocos2d::CCTexture2D * ExchangeInfo::GetTextureForData(const char* data)
{
	return nullptr;
}

void ExchangeInfo::UpLoadIcon(int index)
{

}

bool ExchangeInfo::regexStr(const char* str, const char* dec)
{
	return true;
}

void ExchangeInfo::SaveImag(const char* imgdata, const char* destpath)
{
}
