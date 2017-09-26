#pragma once

#include "cocos2d.h"
#include "network/HttpClient.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;

class HelpLayer:public Layer
{
public:

	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(HelpLayer);

private:

	Node* _mainNode;	// Ö÷½Úµã
};

