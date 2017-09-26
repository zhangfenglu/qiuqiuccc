#include "Config.h"
#include "Resources.h"

Config* Config::s_pConfig = nullptr;

Config* Config::getInstance()
{
	if (nullptr == s_pConfig)
	{
		s_pConfig = new (std::nothrow)Config();
		s_pConfig->init();
		s_pConfig->retain();
	}
	return s_pConfig;
}

Config::Config()
{

}

Config::~Config()
{

}

bool Config::init()
{
	initDiamondInfo();
	initGoodsInfo();
	initOtherInfo();

	return true;
}

//vip界面配置
bool Config::initGoodsInfo()
{
	s_vGoodsInfo = FileUtils::getInstance()->getValueMapFromFile("config/GoodsInfo.plist");
	return true;
}

bool Config::initDiamondInfo(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	s_vDiamondInfo = FileUtils::getInstance()->getValueMapFromFile("config/DiamondInfoAndroid.plist");
#elif(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	s_vGoodsInfo = FileUtils::getInstance()->getValueMapFromFile("config/DiamondInfo.plist");
#endif
	return true;
}

//道具配置 包含皮肤， 光环 孢子 ，拖尾
//配置注意 皮肤类型为1， 光环为2 孢子为3 拖尾为4
//nId 和服务器id相同
bool Config::initOtherInfo()
{
	s_vItemInfo = FileUtils::getInstance()->getValueMapFromFile("config/ItemInfo.plist");

	return true;
}