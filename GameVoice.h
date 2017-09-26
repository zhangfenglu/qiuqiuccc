#pragma once
#include "cocos2d.h"
#include"SimpleAudioEngine.h"
USING_NS_CC;

class GameVoice
{
public:
	virtual ~GameVoice();

	//************************************
	// Method:    getInstance		单例
	// FullName:  GameVoice::getInstance
	// Access:    public static 
	// Returns:   GameVoice*
	// Qualifier:
	//************************************
	static GameVoice* getInstance();

	//************************************
	// Method:    playClickBtnVoive		播放游戏按钮音效
	// FullName:  GameVoice::playClickBtnVoive
	// Access:    public 
	// Returns:   void
	// Qualifier:
	//************************************
	void playClickBtnVoive();

private:
	GameVoice();

	// 音效配置文件
	ValueMap _voiveMap;
};

