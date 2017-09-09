#include "TimeYuanZhengLayer.h"
#include "SimpleTools.h"
#include "RotateMenu.h"

bool TimeYuanZhengLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto rootNode = CSLoader::createNode("res/TimeYuanZhengLayer.csb");

	addChild(rootNode);
	cocos2d::ui::Layout* rongqi = (cocos2d::ui::Layout*)seekNodeByName(rootNode, "Panel_xuanzhuan");

	Size visibleSize = rongqi->getContentSize();


	auto btn1 = (cocos2d::ui::Button*)seekNodeByName(rootNode, "btn_huangjin1");
	auto btn2 = (cocos2d::ui::Button*)seekNodeByName(rootNode, "btn_huangjin2");
	auto btn3 = (cocos2d::ui::Button*)seekNodeByName(rootNode, "btn_huangjin3");
	auto btn4 = (cocos2d::ui::Button*)seekNodeByName(rootNode, "btn_huangjin4");
	auto btn5 = (cocos2d::ui::Button*)seekNodeByName(rootNode, "btn_huangjin5");
	auto btn6 = (cocos2d::ui::Button*)seekNodeByName(rootNode, "btn_huangjin6");
	auto copy1 = btn1->clone();
	auto copy2 = btn2->clone();
	auto copy3 = btn3->clone();
	auto copy4 = btn4->clone();
	auto copy5 = btn5->clone();
	auto copy6 = btn6->clone();
	
	copy1->setVisible(true);
	copy2->setVisible(true);
	copy3->setVisible(true);
	copy4->setVisible(true);
	copy5->setVisible(true);
	copy6->setVisible(true);




	auto item1 = MenuItemImage::create("TimeYuanZhengLayer/mian/huangjin1.png", "TimeYuanZhengLayer/mian/huangjin1.png", CC_CALLBACK_1(TimeYuanZhengLayer::menuItem1Callback, this));
	auto item2 = MenuItemImage::create("TimeYuanZhengLayer/mian/huangjin2.png", "TimeYuanZhengLayer/mian/huangjin2.png", CC_CALLBACK_1(TimeYuanZhengLayer::menuItem2Callback, this));
	auto item3 = MenuItemImage::create("TimeYuanZhengLayer/mian/huangjin3.png", "TimeYuanZhengLayer/mian/huangjin3.png", CC_CALLBACK_1(TimeYuanZhengLayer::menuItem3Callback, this));
	auto item4 = MenuItemImage::create("TimeYuanZhengLayer/mian/huangjin4.png", "TimeYuanZhengLayer/mian/huangjin4.png", CC_CALLBACK_1(TimeYuanZhengLayer::menuItem4Callback, this));
	auto item5 = MenuItemImage::create("TimeYuanZhengLayer/mian/huangjin5.png", "TimeYuanZhengLayer/mian/huangjin5.png", CC_CALLBACK_1(TimeYuanZhengLayer::menuItem5Callback, this));
	auto item6 = MenuItemImage::create("TimeYuanZhengLayer/mian/huangjin6.png", "TimeYuanZhengLayer/mian/huangjin6.png", CC_CALLBACK_1(TimeYuanZhengLayer::menuItem5Callback, this));
	
	copy1->setAnchorPoint(Vec2::ZERO);
	copy2->setAnchorPoint(Vec2::ZERO);
	copy3->setAnchorPoint(Vec2::ZERO);
	copy4->setAnchorPoint(Vec2::ZERO);
	copy5->setAnchorPoint(Vec2::ZERO);
	copy6->setAnchorPoint(Vec2::ZERO);
	copy1->setPosition(item1->getPosition());
	copy2->setPosition(item2->getPosition());
	copy3->setPosition(item3->getPosition());
	copy4->setPosition(item4->getPosition());
	copy5->setPosition(item5->getPosition());
	copy6->setPosition(item6->getPosition());

	item1->addChild(copy1);
	item2->addChild(copy2);
	item3->addChild(copy3);
	item4->addChild(copy4);
	item5->addChild(copy5);
	item6->addChild(copy6);
	


	/*item1->setScaleY(1.2);
	item2->setScaleY(1.2);
	item3->setScaleY(1.2);
	item4->setScaleY(1.2);
	item5->setScaleY(1.2);
	item6->setScaleY(1.2);
	item1->setScaleX(1.1);
	item2->setScaleX(1.1);
	item3->setScaleX(1.1);
	item4->setScaleX(1.1);
	item5->setScaleX(1.1);
	item6->setScaleX(1.1);*/

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
	rongqi->addChild(menu, 2);


	for (int i = 0; i < 6; i++){
		char str[20];
		sprintf(str, "Demo1/item%d_1.png", i + 1);
		sprite[i] = Sprite::create(str);
		sprite[i]->setAnchorPoint(Vec2(0.5f, 0.5f));
		sprite[i]->setPosition(visibleSize / 2);
		this->addChild(sprite[i]);
	}
	hideAllSprite();





	return true;
}

void TimeYuanZhengLayer::menuItem1Callback(cocos2d::Ref* pSender)
{
	log("btn1");

}

void TimeYuanZhengLayer::menuItem2Callback(cocos2d::Ref* pSender)
{
	log("btn2");
	
}

void TimeYuanZhengLayer::menuItem3Callback(cocos2d::Ref* pSender)
{
	log("btn3");
}

void TimeYuanZhengLayer::menuItem4Callback(cocos2d::Ref* pSender)
{
	log("btn4");
}

void TimeYuanZhengLayer::menuItem5Callback(cocos2d::Ref* pSender)
{
	log("btn5");
}

void TimeYuanZhengLayer::menuItem6Callback(cocos2d::Ref* pSender)
{
	log("btn6");
}
void TimeYuanZhengLayer::hideAllSprite()
{
	for (auto p : sprite){
		if (p->isVisible())
			p->setVisible(false);
	}
}
