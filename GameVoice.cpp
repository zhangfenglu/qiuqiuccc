#include "GameVoice.h"

using namespace CocosDenshion;

GameVoice::GameVoice()
{
	_voiveMap = cocos2d::FileUtils::getInstance()->getValueMapFromFile("music/voice.plist");
}


GameVoice::~GameVoice()
{
}

static GameVoice* p = nullptr;
GameVoice* GameVoice::getInstance()
{
	if (p == nullptr)
	{
		p = new GameVoice();
	}
	return p;
}

void GameVoice::playClickBtnVoive()
{
	SimpleAudioEngine::getInstance()->playEffect(_voiveMap["clickBtnVoice"].asString().c_str());
}
