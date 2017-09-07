#include "HelloWorldScene.h"  
#include "RotateMenu.h"  


USING_NS_CC;
typedef struct SceneList{
	const char *name;
	std::function<cocos2d::Scene*()> callback;
}SceneList;
SceneList sceneList[] = {
	{ "Demo1", [](){return HelloWorld::createScene(); } }
};
const unsigned int sceneCount = sizeof(sceneList) / sizeof(SceneList);
#define LINE_SPACE 30  

Scene* HelloWorld::createScene()
{
	// 'scene' is an autorelease object  
	auto scene = Scene::create();

	// 'layer' is an autorelease object  
	auto layer = HelloWorld::create();

	// add layer as a child to scene  
	scene->addChild(layer);

	// return the scene  
	return scene;
}

// on "init" you need to initialize your instance  
bool HelloWorld::init()
{
	//////////////////////////////  
	// 1. super init first  
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////  
	// 2. add a menu item with "X" image, which is clicked to quit the program  
	//    you may modify it.  

	// add a "close" icon to exit the progress. it's an autorelease object  
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	//  create menu, it's an autorelease object  
	/*  auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);*/
	auto item1 = MenuItemImage::create("Demo1/item1_1.png", "Demo1/item1_1.png", CC_CALLBACK_1(HelloWorld::menuItem1Callback, this));
	auto item2 = MenuItemImage::create("Demo1/item2_1.png", "Demo1/item2_1.png", CC_CALLBACK_1(HelloWorld::menuItem2Callback, this));
	auto item3 = MenuItemImage::create("Demo1/item3_1.png", "Demo1/item3_1.png", CC_CALLBACK_1(HelloWorld::menuItem3Callback, this));
	auto item4 = MenuItemImage::create("Demo1/item4_1.png", "Demo1/item4_1.png", CC_CALLBACK_1(HelloWorld::menuItem4Callback, this));
	auto item5 = MenuItemImage::create("Demo1/item5_1.png", "Demo1/item5_1.png", CC_CALLBACK_1(HelloWorld::menuItem5Callback, this));
	auto item6 = MenuItemImage::create("Demo1/item6_1.png", "Demo1/item6_1.png", CC_CALLBACK_1(HelloWorld::menuItem5Callback, this));

	RotateMenu *menu = RotateMenu::create();

	menu->addMenuItem(item1);
	menu->addMenuItem(item2);
	menu->addMenuItem(item3);
	item3->setName("shao");
	menu->addMenuItem(item4);
	
	menu->addMenuItem(item5);
	item5->setName("duo");
	menu->addMenuItem(item6);

	menu->setPosition(visibleSize / 2);
	this->addChild(menu, 2);


	for (int i = 0; i < 6; i++){
		char str[20];
		sprintf(str, "Demo1/item%d_1.png", i + 1);
		sprite[i] = Sprite::create(str);
		sprite[i]->setAnchorPoint(Vec2(0.5f, 0.5f));
		sprite[i]->setPosition(visibleSize / 2);
		this->addChild(sprite[i]);
	}
	hideAllSprite();

	/////////////////////////////  
	// 3. add your codes below...  


	// add a label shows "Hello World"  
	// create and initialize a label  

	auto label = LabelTTF::create("Hello World", "Arial", 24);

	// position the label on the center of the screen  
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));

	// add the label as a child to this layer  
	this->addChild(label, 1);




	return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)  
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif  

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)  
	exit(0);
#endif  
}

void HelloWorld::menuItem1Callback(cocos2d::Ref* pSender){
	hideAllSprite();
	sprite[0]->setVisible(true);
}
void HelloWorld::menuItem2Callback(cocos2d::Ref* pSender){
	hideAllSprite();
	sprite[1]->setVisible(true);
}
void HelloWorld::menuItem3Callback(cocos2d::Ref* pSender){
	hideAllSprite();
	sprite[2]->setVisible(true);
}
void HelloWorld::menuItem4Callback(cocos2d::Ref* pSender){
	hideAllSprite();
	sprite[3]->setVisible(true);
}
void HelloWorld::menuItem5Callback(cocos2d::Ref* pSender){
	hideAllSprite();
	sprite[4]->setVisible(true);
}

void HelloWorld::hideAllSprite(){
	for (auto p : sprite){
		if (p->isVisible())
			p->setVisible(false);
	}
}

void HelloWorld::menuItem6Callback(cocos2d::Ref* pSender)
{
	hideAllSprite();
	sprite[5]->setVisible(true);
}
