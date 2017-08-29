#include "LogoLayer.h"
#include "LoginningLayer.h"

bool LogoLayer::init()
{
	if (!Layer::init())
		return false;

	auto rootNode = CSLoader::createNode("LogoLayer.csb");

	addChild(rootNode);

	rootNode->setOpacity(0);
	ActionInterval* fadeIn = FadeIn::create(3);
    ActionInterval* fadeOut = fadeIn->reverse();
	
	CallFunc* callFuntion = CallFunc::create(CC_CALLBACK_0(LogoLayer::goToLoginLayer,this));
	DelayTime* time = DelayTime::create(1);
	Spawn* spawn = Spawn::create(fadeOut,Sequence::create(time, callFuntion, NULL), NULL);
	Action* action = Sequence::create(fadeIn, spawn, NULL);
	rootNode->runAction(action);

	return true;
}

void LogoLayer::goToLoginLayer()
{
	//auto scene = Scene::create();
	auto loginningLayer = LoginingLayer::create();
	//scene->addChild(loginningLayer);
	//CCLOG("=======================");
	//Director::getInstance()->replaceScene(scene);
    
    this->getParent()->addChild(loginningLayer);
    this->removeFromParent();
    
}
