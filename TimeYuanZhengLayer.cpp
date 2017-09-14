#include "TimeYuanZhengLayer.h"
#include "SimpleTools.h"
#include "RotateMenu.h"
#include "Global.h"
#include "MainScene.h"


bool TimeYuanZhengLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	rootNode = CSLoader::createNode("TimeYuanZhengLayer.csb");

	addChild(rootNode);
	cocos2d::ui::Layout* rongqi = (cocos2d::ui::Layout*)seekNodeByName(rootNode, "Panel_xuanzhuan");
	Size visibleSize = rongqi->getContentSize();

	zuduiBox = (cocos2d::ui::Layout*)seekNodeByName(rootNode, "zuduiBox");
	auto btn_close = (cocos2d::ui::Button*)seekNodeByName(zuduiBox, "btn_close");
	btn_close->addTouchEventListener([=](Ref*, cocos2d::ui::Widget::TouchEventType type)
	{
		if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
		{
			log("yincang zuduiBox========================================");
			zuduiBox->setVisible(false);
		}
	});

	auto btn_quxiaozudui = (cocos2d::ui::Button*)seekNodeByName(zuduiBox, "btn_quxiaozudui");
	if (Global::getInstance()->GetIsZuDui())
	{
		btn_close->setVisible(false);
		btn_quxiaozudui->setVisible(true);
	}
	else
	{
		btn_close->setVisible(true);
		btn_quxiaozudui->setVisible(false);
	}
	btn_quxiaozudui->addTouchEventListener([=](Ref*, cocos2d::ui::Widget::TouchEventType type)
	{
		if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
		{
			log("quxiao zudui========================================");
			zuduiBox->setVisible(false);
		}
	});

	auto btn_zudui = (cocos2d::ui::Button*)seekNodeByName(zuduiBox, "btn_zudui");
	btn_zudui->addTouchEventListener([=](Ref*, cocos2d::ui::Widget::TouchEventType type)
	{
		if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
		{

			log("zudui========================================");
			MainScene* main = dynamic_cast<MainScene*>(getParent()->getParent());
			Global::getInstance()->SetIsZuDui(true);
			main->reqZuDui();
			this->unschedule(schedule_selector(TimeYuanZhengLayer::timeUpdate));
			this->removeFromParent();
			
		}
	});


	auto Image_award = (cocos2d::ui::ImageView*)seekNodeByName(rootNode, "Image_award");
	auto scrollView = (cocos2d::ui::ScrollView*)seekNodeByName(rootNode, "ScrollView");
	Image_award_width = Image_award->getSize().width;
	Image_award_poiX = Image_award->getPositionX();
	//Image_award_poiY = scrollView->getSize().height + Image_award->getSize().height * 2;
	Image_award_poiY = Image_award->getPositionY();


	auto btn1 = (cocos2d::ui::Button*)seekNodeByName(rootNode, "btn_huangjin1");
	auto btn2 = (cocos2d::ui::Button*)seekNodeByName(rootNode, "btn_huangjin2");
	auto btn3 = (cocos2d::ui::Button*)seekNodeByName(rootNode, "btn_huangjin3");
	auto btn4 = (cocos2d::ui::Button*)seekNodeByName(rootNode, "btn_huangjin4");
	auto btn5 = (cocos2d::ui::Button*)seekNodeByName(rootNode, "btn_huangjin5");
	auto btn6 = (cocos2d::ui::Button*)seekNodeByName(rootNode, "btn_huangjin6");
	copy1 = (cocos2d::ui::Button*)btn1->clone();
	copy2 = (cocos2d::ui::Button*)btn2->clone();
	copy3 = (cocos2d::ui::Button*)btn3->clone();
	copy4 = (cocos2d::ui::Button*)btn4->clone();
	copy5 = (cocos2d::ui::Button*)btn5->clone();
	copy6 = (cocos2d::ui::Button*)btn6->clone();
	
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


	//for (int i = 0; i < 6; i++){
	//	char str[20];
	//	sprintf(str, "TimeYuanZhengLayer/mian/huangjin%d.png", i + 1);
	//	sprite[i] = Sprite::create(str);
	//	sprite[i]->setAnchorPoint(Vec2(0.5f, 0.5f));
	//	sprite[i]->setPosition(visibleSize / 2);
	//	this->addChild(sprite[i]);
	//}
	//hideAllSprite();


	showDaoJiShi();

	
	text1 = (cocos2d::ui::Text*)seekNodeByName(copy1, "timeNum");
	text2 = (cocos2d::ui::Text*)seekNodeByName(copy2, "timeNum");
	text3 = (cocos2d::ui::Text*)seekNodeByName(copy3, "timeNum");
	text4 = (cocos2d::ui::Text*)seekNodeByName(copy4, "timeNum");
	text5 = (cocos2d::ui::Text*)seekNodeByName(copy5, "timeNum");
	text6 = (cocos2d::ui::Text*)seekNodeByName(copy6, "timeNum");
	/*char str[4];
	sprintf(str, "%d", Global::getInstance()->GetZuDuiDaoJiShiInfo().xing1time);*/
	//text1->setText(str);

	t1 = Global::getInstance()->GetZuDuiDaoJiShiInfo().xing1time;
	t2 = Global::getInstance()->GetZuDuiDaoJiShiInfo().xing2time;
	t3 = Global::getInstance()->GetZuDuiDaoJiShiInfo().xing3time;
	t4 = Global::getInstance()->GetZuDuiDaoJiShiInfo().xing4time;
	t5 = Global::getInstance()->GetZuDuiDaoJiShiInfo().xing5time;
	t6 = Global::getInstance()->GetZuDuiDaoJiShiInfo().xing6time;

	//得到 各个黄金战场的倒计时 开始时间
	if (t1 <= 9)
	{
		t1 = 9 - t1;
	}
	else
	{
		t1 = (60 - t1) + 9;
	}
	if (t2 <= 19)
	{
		t2 = 19 - t2;
	}
	else
	{
		t2 = (60 - t2) + 19;
	}
	if (t3 <= 29)
	{
		t3 = 29 - t3;
	}
	else
	{
		t3 = (60 - t3) + 29;
	}
	if (t4 <= 39)
	{
		t4 = 39 - t4;
	}
	else
	{
		t4 = (60 - t4) + 39;
	}
	if (t5 <= 49)
	{
		t5 = 49 - t5;
	}
	else
	{
		t5 = (60 - t5) + 49;
	}
	if (t6 <= 59)
	{
		t6 = 59 - t6;
	}
	else
	{
		t6 = (60 - t6) + 59;
	}


	auto btnClose = (cocos2d::ui::Button*)seekNodeByName(rootNode, "btnClose");
	btnClose->addTouchEventListener([=](Ref*, cocos2d::ui::Widget::TouchEventType type)
	{
		if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
		{
			this->unschedule(schedule_selector(TimeYuanZhengLayer::timeUpdate));
			this->removeFromParent();

		}
	});

	auto btnHelp = (cocos2d::ui::Button*)seekNodeByName(rootNode, "btnHelp");
	btnHelp->addTouchEventListener([=](Ref*, cocos2d::ui::Widget::TouchEventType type)
	{
		if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
		{
			log("click    btnHelp");

		}
	});

	//char str1[2];
	sprintf(str1, "%d", t1);
	text1->setText(str1);

	//char str2[2];
	sprintf(str2, "%d", t2);
	text2->setText(str2);

	//char str3[2];
	sprintf(str3, "%d", t3);
	text3->setText(str3);

	//char str4[2];
	sprintf(str4, "%d", t4);
	text4->setText(str4);

	//char str5[2];
	sprintf(str5, "%d", t5);
	text5->setText(str5);

	//char str6[2];
	sprintf(str6, "%d", t6);
	text6->setText(str6);

	this->schedule(schedule_selector(TimeYuanZhengLayer::timeUpdate), 1);

	initZuDuiAwardInfo();
	return true;
}

void TimeYuanZhengLayer::menuItem1Callback(cocos2d::Ref* pSender)
{
	log("btn1");
	showZuDuiBox(1);
}

void TimeYuanZhengLayer::menuItem2Callback(cocos2d::Ref* pSender)
{
	log("btn2");
	showZuDuiBox(2);
}

void TimeYuanZhengLayer::menuItem3Callback(cocos2d::Ref* pSender)
{
	log("btn3");
	showZuDuiBox(3);
}

void TimeYuanZhengLayer::menuItem4Callback(cocos2d::Ref* pSender)
{
	log("btn4");
	showZuDuiBox(4);
}

void TimeYuanZhengLayer::menuItem5Callback(cocos2d::Ref* pSender)
{
	log("btn5");
	showZuDuiBox(5);
}

void TimeYuanZhengLayer::menuItem6Callback(cocos2d::Ref* pSender)
{
	log("btn6");
	showZuDuiBox(6);
}
void TimeYuanZhengLayer::hideAllSprite()
{
	for (auto p : sprite){
		if (p->isVisible())
			p->setVisible(false);
	}
}

void TimeYuanZhengLayer::showDaoJiShi()
{
	Json* root = ReadJson("zuduidaojishi.json");

	Json* jsonChild = root->child;
	//Json* result = Json_getItem(root, "resultCode");
	zuduidaojishi_info info;
	int i = -1;
	while (jsonChild)
	{
		i++;
		switch (jsonChild->type)
		{
		case Json_NULL:
			break;
		case Json_Number:
		{
		}
			break;
		case Json_Object:
		{
							uint32_t time = Json_getItem(jsonChild, "time")->valueInt;
							//uint32_t time = jsonChild->valueInt;
							switch (i)
							{
							case 0:
								info.xing1time = time;
								break;
							case 1:
								info.xing2time = time;
								break;
							case 2:
								info.xing3time = time;
								break;
							case 3:
								info.xing4time = time;
								break;
							case 4:
								info.xing5time = time;
								break;
							case 5:
								info.xing6time = time;
								break;
							default:
								break;
							}
		}
			break;
		case Json_String:
		{
		}
			break;
		case Json_True:
			break;
		case Json_Array:
			break;
		default:
			break;
		}

		jsonChild = jsonChild->next;
	}

	Global::getInstance()->SetZuDuiDaoJiShiInfo(info);

}

void TimeYuanZhengLayer::timeUpdate(float dt)
{
	//char str1[2];
	sprintf(str1, "%d", t1);
	text1->setText(str1);

	//char str2[2];
	sprintf(str2, "%d", t2);
	text2->setText(str2);

	//char str3[2];
	sprintf(str3, "%d", t3);
	text3->setText(str3);

	//char str4[2];
	sprintf(str4, "%d", t4);
	text4->setText(str4);

	//char str5[2];
	sprintf(str5, "%d", t5);
	text5->setText(str5);

	//char str6[2];
	sprintf(str6, "%d", t6);
	text6->setText(str6);

	
		//计算倒计时 起点
		if (t1 == 0)
		{
			t1 = 60;
		}
		if (t2 == 0)
		{
			t2 = 60;
		}
		if (t3 == 0)
		{
			t3 = 60;
		}
		if (t4 == 0)
		{
			t4 = 60;
		}
		if (t5 == 0)
		{
			t5 = 60;
		}
		if (t6 == 0)
		{
			t6 = 60;
		}
		t1--;
		t2--;
		t3--;
		t4--;
		t5--;
		t6--;
	
}

void TimeYuanZhengLayer::showZuDuiBox(int tag)
{
	std::string titleStr = awards[tag].title;
	Global::getInstance()->SetWaitTimeBoxTitleStr(titleStr.c_str());
	titleStr = "TimeYuanZhengLayer\\xiaohao\\title\\" + titleStr + ".png";
	
	auto title = (cocos2d::ui::ImageView*)seekNodeByName(rootNode, "title");
	title->loadTexture(titleStr.c_str());
	std::string xiaohaoStr = awards[tag].xiaohao;
	xiaohaoStr = "TimeYuanZhengLayer\\xiaohao\\killzuanshi\\" + xiaohaoStr + ".png";
	auto xiaohao = (cocos2d::ui::ImageView*)seekNodeByName(rootNode, "zuanshi");
	xiaohao->loadTexture(xiaohaoStr.c_str());
	std::string awardsStr = awards[tag].allawards;
	std::vector<std::string> awardsArrays = Global::getInstance()->split(awardsStr, "|");

	auto scrollView = (cocos2d::ui::ScrollView*)seekNodeByName(rootNode, "ScrollView");
	scrollView->removeAllChildren();
	for (int i = 0; i < awardsArrays.size(); i++)
	{
		cocos2d::ui::ImageView* cloneImage = cocos2d::ui::ImageView::create();
		scrollView->addChild(cloneImage);
		std::string clonePath = "TimeYuanZhengLayer\\xiaohao\\reward\\" + awardsArrays.at(i) + ".png";
		cloneImage->loadTexture(clonePath.c_str());
		cloneImage->setPosition(ccp(Image_award_poiX + Image_award_width * i, Image_award_poiY));

	}
	zuduiBox->setVisible(true);
}

void TimeYuanZhengLayer::initZuDuiAwardInfo()
{
	Json* root = ReadJson("jingjichang.json");

	Json* jsonChild = root->child;
	int i = -1;
	while (jsonChild)
	{
		i++;
		switch (jsonChild->type)
		{
		case Json_NULL:
			break;
		case Json_Number:
			break;
		case Json_Object:
		{


							Json* title = Json_getItem(jsonChild, "title");
							//CCLog("<<<<<<%s", title->valuestring);
							Json * xiaohao = Json_getItem(jsonChild, "xiaohao");
							Json* allawards = Json_getItem(jsonChild, "allawards");
							AwardInfo info;
							info.title = title->valueString;
							info.xiaohao = xiaohao->valueString;
							info.allawards = allawards->valueString;
							awards[i] = info;
		}
			break;
		case Json_String:
			log("<<<<<<%s", jsonChild->valueString);

			break;
		case Json_True:
			break;
		case Json_Array:
			break;
		default:
			break;
		}

		jsonChild = jsonChild->next;
	}

	for (int i = 0; i < sizeof(awards) / sizeof(awards[0]); i++)
	{
		std::string title = awards[i].title;
		log("<<<<<<%s", title.c_str());
	}
}

