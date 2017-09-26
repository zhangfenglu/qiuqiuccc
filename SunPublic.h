#pragma once
#include "cocos2d.h"

class SunPublic
{
public:
	~SunPublic();

	//************************************
	// Method:    getInstance			单例
	// FullName:  SunNetPublic::getInstance
	// Access:    public static 
	// Returns:   SunNetPublic*
	// Qualifier:
	//************************************
	static SunPublic* getInstance();

	//************************************
	// Method:    returnMainScene		返回主界面
	// FullName:  SunPublic::returnMainScene
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: cocos2d::Node * node
	//************************************
	void returnMainScene(cocos2d::Node* node);
private:
	SunPublic();


};