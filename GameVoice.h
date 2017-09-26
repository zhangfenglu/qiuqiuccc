#pragma once
#include "cocos2d.h"
#include"SimpleAudioEngine.h"
USING_NS_CC;

class GameVoice
{
public:
	virtual ~GameVoice();

	//************************************
	// Method:    getInstance		����
	// FullName:  GameVoice::getInstance
	// Access:    public static 
	// Returns:   GameVoice*
	// Qualifier:
	//************************************
	static GameVoice* getInstance();

	//************************************
	// Method:    playClickBtnVoive		������Ϸ��ť��Ч
	// FullName:  GameVoice::playClickBtnVoive
	// Access:    public 
	// Returns:   void
	// Qualifier:
	//************************************
	void playClickBtnVoive();

private:
	GameVoice();

	// ��Ч�����ļ�
	ValueMap _voiveMap;
};

